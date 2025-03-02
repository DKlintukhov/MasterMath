# MasterMath
MasterMath is an intuitive platform designed for math educators to effortlessly create, customize, and assign timed exercises, quizzes, and problem sets.

## Building MasterMath on Windows

### Prerequisites

*   **CMake:**  Install CMake from [https://cmake.org/download/](https://cmake.org/download/). Make sure CMake is added to your system's PATH environment variable.
*   **Visual Studio build tools:** Install Visual Studio [build tools](https://visualstudio.microsoft.com/downloads/?q=build+tools) with the "Desktop development with C++" workload selected. Ensure the latest Windows SDK is installed.
*   **Git:** Install Git from [https://git-scm.com/downloads](https://git-scm.com/downloads).

## 1. vcpkg Installation

vcpkg is used for managing the project's dependencies.

1.  Clone the vcpkg repository:

    ```bash
    git clone https://github.com/microsoft/vcpkg
    cd vcpkg
    ```

2.  Bootstrap vcpkg:

    ```bash
    .\bootstrap-vcpkg.bat
    ```

3.  Integrate vcpkg with your user environment:

    ```bash
    .\vcpkg integrate install
    ```

## 2. Install Dependencies (Boost.JSON and Boost.Test)

Use vcpkg to install the required Boost libraries:

```bash
vcpkg install boost-json:x64-windows-static boost-test:x64-windows-static
```

3. CMake Configuration and Building
Create a build directory (if you haven’t already):

```bash
mkdir build
cd build
```

Configure the project with CMake, specifying the vcpkg toolchain file:

```bash
cmake -DCMAKE_TOOLCHAIN_FILE=<path_to_vcpkg>\scripts\buildsystems\vcpkg.cmake -DCMAKE_BUILD_TYPE=Release ..
```

bash
Replace <path_to_vcpkg> with the actual path to your vcpkg installation directory. For example: C:\dev\vcpkg
You can also use -DCMAKE_BUILD_TYPE=Debug for debug builds.
Build the project:

```bash
cmake --build . --config Release
```

## Building MasterMath on POSIX

> comming soon...

# Building the Frontend
The project includes a frontend component that requires specific build steps. These are defined as CMake targets.

## Install Frontend Dependencies:

```shell
cmake --build . --target install-frontend-deps
```

This target typically handles tasks such as installing Node.js dependencies for the frontend.

## Build the Frontend:

```shell
cmake --build . --target build-frontend
```

# Running the Application
After successful builds, you can find the executable files in the build directory, typically under `build/Release` or `build/Debug`. 
Refer to the project’s documentation for specific instructions on running the application. 
The built frontend assets will likely be in a separate frontend specific directory which is also defined in the project’s documentation.
