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
