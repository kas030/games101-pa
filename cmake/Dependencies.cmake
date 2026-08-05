# Shared third-party dependencies for every programming assignment.
get_filename_component(GAMES101_ROOT_DIR
    "${CMAKE_CURRENT_LIST_DIR}/.."
    ABSOLUTE
)

# Keep generator-specific dependency build trees inside each PA build directory.
# The downloaded source trees are declared separately below and remain shared.
set(FETCHCONTENT_BASE_DIR
    "${CMAKE_BINARY_DIR}/_deps"
    CACHE PATH "Per-build FetchContent working directory"
    FORCE
)

include(FetchContent)

set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(EIGEN_BUILD_DOC OFF CACHE BOOL "" FORCE)
set(EIGEN_BUILD_TESTING OFF CACHE BOOL "" FORCE)

set(EIGEN_SHARED_SOURCE_DIR "${GAMES101_ROOT_DIR}/.deps/eigen-src")
if(EXISTS "${EIGEN_SHARED_SOURCE_DIR}/CMakeLists.txt")
    # A source override skips FetchContent's per-build download/update step.
    set(FETCHCONTENT_SOURCE_DIR_EIGEN
        "${EIGEN_SHARED_SOURCE_DIR}"
        CACHE PATH "Shared Eigen source tree"
        FORCE
    )
else()
    unset(FETCHCONTENT_SOURCE_DIR_EIGEN CACHE)
endif()

FetchContent_Declare(
    eigen
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG 5.0.0
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
    UPDATE_DISCONNECTED TRUE
    SOURCE_DIR "${EIGEN_SHARED_SOURCE_DIR}"
)

FetchContent_MakeAvailable(eigen)

if(GAMES101_ENABLE_OPENCV)
    # The rasterizer assignments use OpenCV for displaying and saving the rendered image. Keep
    # the source build small and avoid pulling optional multimedia backends.
    set(BUILD_LIST core,imgproc,imgcodecs,highgui CACHE STRING "" FORCE)
    set(BUILD_opencv_apps OFF CACHE BOOL "" FORCE)
    set(BUILD_opencv_java OFF CACHE BOOL "" FORCE)
    set(BUILD_opencv_js OFF CACHE BOOL "" FORCE)
    set(BUILD_opencv_python2 OFF CACHE BOOL "" FORCE)
    set(BUILD_opencv_python3 OFF CACHE BOOL "" FORCE)
    set(BUILD_opencv_world OFF CACHE BOOL "" FORCE)
    set(BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_PERF_TESTS OFF CACHE BOOL "" FORCE)
    set(BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(WITH_FFMPEG OFF CACHE BOOL "" FORCE)
    set(WITH_GSTREAMER OFF CACHE BOOL "" FORCE)
    set(WITH_ADE OFF CACHE BOOL "" FORCE)
    set(WITH_IPP OFF CACHE BOOL "" FORCE)
    set(WITH_MSMF OFF CACHE BOOL "" FORCE)
    set(WITH_OPENCL OFF CACHE BOOL "" FORCE)

    set(OPENCV_SHARED_SOURCE_DIR "${GAMES101_ROOT_DIR}/.deps/opencv-src")
    if(EXISTS "${OPENCV_SHARED_SOURCE_DIR}/CMakeLists.txt")
        set(FETCHCONTENT_SOURCE_DIR_OPENCV
            "${OPENCV_SHARED_SOURCE_DIR}"
            CACHE PATH "Shared OpenCV source tree"
            FORCE
        )
    else()
        unset(FETCHCONTENT_SOURCE_DIR_OPENCV CACHE)
    endif()

    FetchContent_Declare(
        opencv
        GIT_REPOSITORY https://github.com/opencv/opencv.git
        GIT_TAG 4.10.0
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
        UPDATE_DISCONNECTED TRUE
        SOURCE_DIR "${OPENCV_SHARED_SOURCE_DIR}"
    )

    FetchContent_MakeAvailable(opencv)
endif()
