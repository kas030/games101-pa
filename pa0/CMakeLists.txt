cmake_minimum_required(VERSION 3.16)
project(Transformation LANGUAGES CXX)

include("${CMAKE_CURRENT_LIST_DIR}/../cmake/Dependencies.cmake")

add_executable(Transformation main.cpp)
target_compile_features(Transformation PRIVATE cxx_std_14)
target_link_libraries(Transformation PRIVATE Eigen3::Eigen)
