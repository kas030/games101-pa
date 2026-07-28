# 新 PA 的 CMake 模板

每个 PA 都是独立的 CMake 项目，可以单独配置、编译和运行。新建
`paN/CMakeLists.txt` 时使用：

```cmake
cmake_minimum_required(VERSION 3.16)
project(PAN LANGUAGES CXX)

include("${CMAKE_CURRENT_LIST_DIR}/../cmake/Dependencies.cmake")

add_executable(PAN main.cpp)
target_compile_features(PAN PRIVATE cxx_std_14)
target_link_libraries(PAN PRIVATE Eigen3::Eigen)
```

首次配置任意 PA 时会自动下载固定版本的 Eigen。下载结果保存在仓库根目录
`.deps/`，供所有 PA 共享，且不会提交到 Git。

独立构建示例：

```powershell
cmake -S paN -B paN/build
cmake --build paN/build --config Release
```
