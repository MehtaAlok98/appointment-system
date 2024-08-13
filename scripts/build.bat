@echo off
REM Set up environment variables if needed
setlocal

REM Prompt user for their username (optional, commented out)
REM set /p USERNAME="Enter your username: "

REM Navigate to the parent directory
cd /d "%~dp1"

REM Define the build directory
set BUILD_DIR=build

REM Create the build directory if it doesn't exist
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"

REM Detect the current username
set "USERNAME=%USERNAME%"

REM Path to the Conan profile
set "PROFILE_PATH=C:\Users\%USERNAME%\.conan2\profiles\mingw"

REM Create a Conan profile if it doesn't already exist
if not exist "%PROFILE_PATH%" (
    echo [settings] > "%PROFILE_PATH%"
    echo os=Windows >> "%PROFILE_PATH%"
    echo compiler=gcc >> "%PROFILE_PATH%"
    echo compiler.version=12 >> "%PROFILE_PATH%"
    echo compiler.libcxx=libstdc++11 >> "%PROFILE_PATH%"
    echo compiler.threads=posix >> "%PROFILE_PATH%"
    echo compiler.exception=sjlj >> "%PROFILE_PATH%"
    echo arch=x86_64 >> "%PROFILE_PATH%"
    echo build_type=Release >> "%PROFILE_PATH%"
    echo [buildenv] >> "%PROFILE_PATH%"
    echo PATH+=C:/msys64/mingw64/bin >> "%PROFILE_PATH%"
    echo PATH+=C:/Program Files/ninja-win >> "%PROFILE_PATH%"
    echo [conf] >> "%PROFILE_PATH%"
    echo tools.cmake.cmaketoolchain:generator=Ninja >> "%PROFILE_PATH%"
)

REM Run Conan to install and build project dependencies
conan install . --build=missing --output-folder=%BUILD_DIR% -pr=mingw

REM Run CMake to configure the project
cmake -G "Ninja" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -S . -B %BUILD_DIR%

REM Build the project using Ninja
cmake --build %BUILD_DIR% --config Release

REM Ask the user if they want to run the program
set /p RUN_APP="Do you want to run the program? (y/n): "

if /i "%RUN_APP%"=="y" (
    "%BUILD_DIR%\bin\AppointmentSystem.exe"
)

REM Optionally, run tests here
REM ctest --output-on-failure

REM End of script
endlocal
pause
