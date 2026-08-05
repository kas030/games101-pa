# PA2：环境配置与运行

PA2 是一个独立的 CMake 项目。配置时，CMake 会自动获取固定版本的 Eigen 5.0.0 和
OpenCV 4.10.0，并且只构建本作业使用的 OpenCV 模块，无需手动安装这两个库。依赖缓存在
仓库根目录的 `.deps/`，可与其他 PA 共用。

## 环境要求

- Git（用于首次获取依赖）
- CMake 3.16 或更高版本
- 支持 C++17 的编译器，例如 Visual Studio 2022、MinGW-w64、Clang 或 GCC

## 配置与编译

在仓库根目录执行：

```powershell
cmake -S pa2 -B pa2/build -DCMAKE_BUILD_TYPE=Release
cmake --build pa2/build --config Release
```

首次配置需要联网获取依赖；如果 `.deps/` 中已有 PA1 下载的相同版本，CMake 会直接复用。
OpenCV 首次编译耗时较长。

## 运行

推荐使用命令行输出模式，它不会打开 GUI 窗口。程序只接受一个参数，即输出图片路径。
Visual Studio 等多配置生成器通常使用：

```powershell
.\pa2\build\bin\Release\Rasterizer.exe pa2\build\output.png
```

MinGW、Ninja、Linux 或 macOS 等单配置生成器通常使用：

```powershell
# Windows
.\pa2\build\bin\Rasterizer.exe pa2\build\output.png
```

```bash
# Linux 或 macOS
./pa2/build/bin/Rasterizer pa2/build/output.png
```

如果上述路径不存在，请在 `pa2/build/bin/` 下查找 `Rasterizer`。OpenCV 动态库由构建系统
放在对应的可执行文件目录中。

不传参数会进入交互显示模式，按 `Esc` 退出：

```powershell
.\pa2\build\bin\Release\Rasterizer.exe
```
