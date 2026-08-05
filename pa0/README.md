# PA0：环境配置与运行

PA0 是一个独立的 CMake 项目。配置项目时，CMake 会自动下载 Eigen 5.0.0，
不需要手动安装 Eigen。

## 环境要求

- Git（用于下载依赖）
- CMake 3.16 或更高版本
- 支持 C++14 的 C++ 编译器，例如 Visual Studio 2022、MinGW-w64 或 GCC


## 编译

在仓库根目录执行：

```powershell
cmake -S pa0 -B pa0/build -DCMAKE_BUILD_TYPE=Release
cmake --build pa0/build --config Release
```

首次执行 `cmake` 时需要联网。下载的依赖会统一保存在仓库根目录的 `.deps/` 中，之后可以复用，不会重复下载。

## 运行

使用 MinGW、Ninja 等单配置生成器时：

```powershell
.\pa0\build\Transformation.exe
```

使用 Visual Studio 等多配置生成器时，可执行文件通常位于配置对应的子目录：

```powershell
.\pa0\build\Release\Transformation.exe
```
