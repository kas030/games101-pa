// clang-format off
//
// Created by goksu on 4/6/19.
//

#include <algorithm>
#include <vector>
#include "rasterizer.hpp"
#include <opencv2/opencv.hpp>
#include <math.h>


rst::pos_buf_id rst::rasterizer::load_positions(const std::vector<Eigen::Vector3f> &positions)
{
    auto id = get_next_id();
    pos_buf.emplace(id, positions);

    return {id};
}

rst::ind_buf_id rst::rasterizer::load_indices(const std::vector<Eigen::Vector3i> &indices)
{
    auto id = get_next_id();
    ind_buf.emplace(id, indices);

    return {id};
}

rst::col_buf_id rst::rasterizer::load_colors(const std::vector<Eigen::Vector3f> &cols)
{
    auto id = get_next_id();
    col_buf.emplace(id, cols);

    return {id};
}

auto to_vec4(const Eigen::Vector3f& v3, float w = 1.0f)
{
    return Vector4f(v3.x(), v3.y(), v3.z(), w);
}


// clang-format on

static bool insideTriangle(float x, float y, const Vector3f* _v) {
    // Check if the point (x, y) is inside the triangle represented by _v[0], _v[1], _v[2]
    auto edge1 = _v[1] - _v[0];
    auto edge2 = _v[2] - _v[1];
    auto edge3 = _v[0] - _v[2];

    Vector3f P = {x, y, 1.f};

    auto v1 = P - _v[0];
    auto v2 = P - _v[1];
    auto v3 = P - _v[2];

    auto p1 = edge1.cross(v1);
    auto p2 = edge2.cross(v2);
    auto p3 = edge3.cross(v3);

    float w1 = p1(2), w2 = p2(2), w3 = p3(2);

    return (w1 >= 0 && w2 >= 0 && w3 >= 0) || (w1 <= 0 && w2 <= 0 && w3 <= 0);
}

// clang-format off

static std::tuple<float, float, float> computeBarycentric2D(float x, float y, const Vector3f* v)
{
    float c1 = (x*(v[1].y() - v[2].y()) + (v[2].x() - v[1].x())*y + v[1].x()*v[2].y() - v[2].x()*v[1].y()) / (v[0].x()*(v[1].y() - v[2].y()) + (v[2].x() - v[1].x())*v[0].y() + v[1].x()*v[2].y() - v[2].x()*v[1].y());
    float c2 = (x*(v[2].y() - v[0].y()) + (v[0].x() - v[2].x())*y + v[2].x()*v[0].y() - v[0].x()*v[2].y()) / (v[1].x()*(v[2].y() - v[0].y()) + (v[0].x() - v[2].x())*v[1].y() + v[2].x()*v[0].y() - v[0].x()*v[2].y());
    float c3 = (x*(v[0].y() - v[1].y()) + (v[1].x() - v[0].x())*y + v[0].x()*v[1].y() - v[1].x()*v[0].y()) / (v[2].x()*(v[0].y() - v[1].y()) + (v[1].x() - v[0].x())*v[2].y() + v[0].x()*v[1].y() - v[1].x()*v[0].y());
    return {c1,c2,c3};
}

void rst::rasterizer::draw(pos_buf_id pos_buffer, ind_buf_id ind_buffer, col_buf_id col_buffer, Primitive type)
{
    auto& buf = pos_buf[pos_buffer.pos_id];
    auto& ind = ind_buf[ind_buffer.ind_id];
    auto& col = col_buf[col_buffer.col_id];

    float f1 = (50 - 0.1) / 2.0;
    float f2 = (50 + 0.1) / 2.0;

    Eigen::Matrix4f mvp = projection * view * model;
    for (auto& i : ind)
    {
        Triangle t;
        Eigen::Vector4f v[] = {
                mvp * to_vec4(buf[i[0]], 1.0f),
                mvp * to_vec4(buf[i[1]], 1.0f),
                mvp * to_vec4(buf[i[2]], 1.0f)
        };
        //Homogeneous division
        for (auto& vec : v) {
            vec /= vec.w();
        }
        //Viewport transformation
        for (auto & vert : v)
        {
            vert.x() = 0.5*width*(vert.x()+1.0);
            vert.y() = 0.5*height*(vert.y()+1.0);
            vert.z() = vert.z() * f1 + f2;
        }

        for (int i = 0; i < 3; ++i)
        {
            t.setVertex(i, v[i].head<3>());
            t.setVertex(i, v[i].head<3>());
            t.setVertex(i, v[i].head<3>());
        }

        auto col_x = col[i[0]];
        auto col_y = col[i[1]];
        auto col_z = col[i[2]];

        t.setColor(0, col_x[0], col_x[1], col_x[2]);
        t.setColor(1, col_y[0], col_y[1], col_y[2]);
        t.setColor(2, col_z[0], col_z[1], col_z[2]);

        rasterize_triangle_MSAA(t);
    }
    
    for(int i = 0; i < frame_buf.size(); i++) {
        Eigen::Vector3f mix = Eigen::Vector3f::Zero();
        for(int j = 0; j < 4; j++){
            mix += frame_buf_MSAA[i * 4 + j];
        }
        mix /= 4;
        frame_buf[i] = mix;
    }
}

// clang-format on
void rst::rasterizer::rasterize_triangle_MSAA(const Triangle& t) {
    auto v = t.toVector4();

    int x_min = std::min({v[0](0), v[1](0), v[2](0)});
    int x_max = std::max({v[0](0), v[1](0), v[2](0)});

    int y_min = std::min({v[0](1), v[1](1), v[2](1)});
    int y_max = std::max({v[0](1), v[1](1), v[2](1)});

    const std::vector<std::pair<float, float>> bias = {{.25f, .25f}, {.75f, .25f}, {.25f, .75f}, {.75f, .75f}};
    for (int x = x_min; x <= x_max; x++) {
        for (int y = y_min; y <= y_max; y++) {
            int ind = get_index(x, y) * 4;

            for (int j = 0; j < 4; j++) {
                float sample_x = x + bias[j].first;
                float sample_y = y + bias[j].second;

                if (insideTriangle(sample_x, sample_y, t.v)) {
                    auto [alpha, beta, gamma] = computeBarycentric2D(sample_x, sample_y, t.v);
                    float w_reciprocal = 1.0 / (alpha / v[0].w() + beta / v[1].w() + gamma / v[2].w());
                    float z_interpolated =
                        alpha * v[0].z() / v[0].w() + beta * v[1].z() / v[1].w() + gamma * v[2].z() / v[2].w();
                    z_interpolated *= w_reciprocal;

                    if (z_interpolated < depth_buf_MSAA[ind + j]) {
                        depth_buf_MSAA[ind + j] = z_interpolated;
                        frame_buf_MSAA[ind + j] = t.getColor();
                    }
                }
            }
        }
    }
}
// clang-format off

void rst::rasterizer::set_model(const Eigen::Matrix4f& m)
{
    model = m;
}

void rst::rasterizer::set_view(const Eigen::Matrix4f& v)
{
    view = v;
}

void rst::rasterizer::set_projection(const Eigen::Matrix4f& p)
{
    projection = p;
}

void rst::rasterizer::clear(rst::Buffers buff)
{
    if ((buff & rst::Buffers::Color) == rst::Buffers::Color)
    {
        std::fill(frame_buf_MSAA.begin(), frame_buf_MSAA.end(), Eigen::Vector3f{0, 0, 0});
    }
    if ((buff & rst::Buffers::Depth) == rst::Buffers::Depth)
    {
        std::fill(depth_buf_MSAA.begin(), depth_buf_MSAA.end(), std::numeric_limits<float>::infinity());
    }
}

rst::rasterizer::rasterizer(int w, int h) : width(w), height(h)
{
    frame_buf_MSAA.resize(w * h * 4);
    frame_buf.resize(w * h);
    depth_buf_MSAA.resize(w * h * 4);
}

int rst::rasterizer::get_index(int x, int y)
{
    return (height-1-y)*width + x;
}

// clang-format on