# PA1：环境配置与运行

PA1 是一个独立的 CMake 项目。配置项目时，CMake 会自动下载 Eigen 5.0.0 和
OpenCV 4.10.0，并只构建本作业需要的 OpenCV 模块，因此不需要在系统中手动
安装这两个库。

## 环境要求

- Git（用于下载依赖）
- CMake 3.16 或更高版本
- 支持 C++17 的 C++ 编译器，例如 Visual Studio 2022、MinGW-w64 或 GCC

可以先在终端检查工具是否可用：

## 编译

在仓库根目录执行：

```powershell
cmake -S pa1 -B pa1/build -DCMAKE_BUILD_TYPE=Release
cmake --build pa1/build --config Release
```

首次配置需要联网下载依赖，且 OpenCV 的首次编译会花费较长时间。依赖统一保存
在仓库根目录的 `.deps/` 中，后续重新编译或其他 PA 使用时可以复用。

# 运行

程序运行时需要能找到随 OpenCV 生成的动态库。当前 CMake 配置会在常用的
单配置构建中把程序和动态库放到 `pa1/build/bin`，因此应直接从该目录运行生成的
程序。
