cmake_minimum_required(VERSION 3.16)
project(Rasterizer LANGUAGES CXX)

set(GAMES101_ENABLE_OPENCV ON)
include("${CMAKE_CURRENT_LIST_DIR}/../cmake/Dependencies.cmake")

add_executable(
    Rasterizer
    main.cpp
    rasterizer.cpp
    Triangle.cpp
)
target_compile_features(Rasterizer PRIVATE cxx_std_17)
target_include_directories(
    Rasterizer
    PRIVATE
        "${opencv_SOURCE_DIR}/include"
        "${opencv_SOURCE_DIR}/modules/core/include"
        "${opencv_SOURCE_DIR}/modules/highgui/include"
        "${opencv_SOURCE_DIR}/modules/imgcodecs/include"
        "${opencv_SOURCE_DIR}/modules/imgproc/include"
        "${CMAKE_BINARY_DIR}"
)
target_link_libraries(
    Rasterizer
    PRIVATE
        Eigen3::Eigen
        opencv_core
        opencv_highgui
        opencv_imgcodecs
        opencv_imgproc
)
