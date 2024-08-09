## Project Setup and Installation

### Prerequisites

Before you can build the project, ensure you have the following dependencies installed:

1. **Conan**: A package manager for C++.
   - Install using pip:
     ```bash
     pip install conan
     ```

2. **CMake**: A build system generator.
   - Download from [CMake Official Website](https://cmake.org/download/).

3. **Ninja**: A small build system with a focus on speed.
   - Download from [Ninja Official Website](https://ninja-build.org/).

4. **MinGW**: A port of GCC for Windows.
   - Download from [MinGW Official Website](https://sourceforge.net/projects/mingw-w64/).

### Dependency Management

This project uses Conan for dependency management. The required dependencies are specified in the `conanfile.txt`:

```txt
[requires]
sqlite3/3.41.2

[generators]
CMakeDeps
CMakeToolchain
```

### Build Instructions

1. **Create a Conan profile**:
   ```cmd
   conan profile detect --name mingw
   ```

   This will create a profile at `C:\Users\username\.conan2\profiles\mingw` with the following content:

   ```text
   [settings]
   os=Windows
   compiler=gcc
   compiler.version=12
   compiler.libcxx=libstdc++11
   compiler.threads=posix
   compiler.exception=sjlj
   arch=x86_64
   build_type=Release

   [buildenv]
   PATH+=(path)C:/msys64/mingw64/bin
   PATH+=(path)"C:/Program Files/ninja-win"

   [conf]
   tools.cmake.cmaketoolchain:generator=Ninja
   ```

2. **Install Conan dependencies**:
   ```cmd
   conan install . --build=missing --output-folder=build -pr=mingw
   ```

3. **Generate build files with CMake**:
   ```cmd
   cmake -G "Ninja" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Release -S . -B build
   ```

4. **Build the project**:
   ```cmd
   cmake --build build
   ```

5. **Run the application**:
   ```cmd
   ./build/bin/AppointmentSystem
   ```

---

## File Structure

- **conanfile.txt**: Conan configuration file for dependencies.
- **CMakeLists.txt**: CMake configuration file (not shown in the setup but necessary for CMake).
- **main.cpp**: The main source file of the application.
- **.conan2**: Directory containing Conan profiles and configurations.

## Notes

- Ensure that **Ninja** and **MSYS2** are properly installed and configured.
- The Conan profile and configuration should match your development environment.

## Troubleshooting

- **Path Issues**: Verify that paths in the Conan profile are correct.
- **Build Errors**: Check for missing dependencies or configuration issues in `CMakeLists.txt`.

For further assistance, consult the [Conan documentation](https://docs.conan.io/) and the [CMake documentation](https://cmake.org/documentation/).

---

This documentation provides a clear, step-by-step guide to setting up and building your project, ensuring that anyone following it will be able to replicate the setup successfully.