# Shared third-party dependencies for every programming assignment.
get_filename_component(GAMES101_ROOT_DIR
    "${CMAKE_CURRENT_LIST_DIR}/.."
    ABSOLUTE
)

# Keep one dependency cache shared by all independently built PA projects.
set(FETCHCONTENT_BASE_DIR
    "${GAMES101_ROOT_DIR}/.deps"
    CACHE PATH "Shared FetchContent cache for GAMES101 assignments"
)

include(FetchContent)

set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(EIGEN_BUILD_DOC OFF CACHE BOOL "" FORCE)
set(EIGEN_BUILD_TESTING OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    eigen
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG 5.0.0
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
    UPDATE_DISCONNECTED TRUE
)

FetchContent_MakeAvailable(eigen)

if(GAMES101_ENABLE_OPENCV)
    # PA1 only uses OpenCV for displaying and saving the rendered image. Keep
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

    FetchContent_Declare(
        opencv
        GIT_REPOSITORY https://github.com/opencv/opencv.git
        GIT_TAG 4.10.0
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
        UPDATE_DISCONNECTED TRUE
    )

    FetchContent_MakeAvailable(opencv)
endif()
