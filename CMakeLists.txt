# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(StudentLecturerAppointmentSystem)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the default build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
endif()

# Include Conan generated files
include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

# Find and link the SQLite3 package
find_package(SQLite3 REQUIRED)

if (NOT SQLite3_FOUND)
    message(FATAL_ERROR "SQLite3 not found")
endif()

# # Include the include directory
# include_directories(include)

# Add the executable target source files
file(GLOB SOURCES "src/*.cpp")

add_executable(AppointmentSystem ${SOURCES})

# Link with the SQLite3 library
target_link_libraries(AppointmentSystem PRIVATE SQLite::SQLite3)

# Include directories
target_include_directories(AppointmentSystem PRIVATE include)

# Set the output directory for binaries
set_target_properties(AppointmentSystem PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
