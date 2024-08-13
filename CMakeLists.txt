# Minimum CMake version required
cmake_minimum_required(VERSION 3.23)

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

# Find and link the SQLite3 and spdlog packages
find_package(SQLite3 REQUIRED)
find_package(spdlog REQUIRED)

# Ensure packages are found
if (NOT SQLite3_FOUND OR NOT spdlog_FOUND)
    message(FATAL_ERROR "Required packages not found")
endif()

# Add the executable target source files
file(GLOB SOURCES "src/main.cpp")
file(GLOB SOURCE_CORES "src/core/*.cpp")
file(GLOB SOURCE_CONFIGS "src/config/*.cpp")
file(GLOB SOURCE_MANAGERS "src/managers/*.cpp")

add_executable(AppointmentSystem ${SOURCES} ${SOURCE_CONFIGS} ${SOURCE_CORES} ${SOURCE_MANAGERS})


# Link with the SQLite3 and spdlog libraries
target_link_libraries(AppointmentSystem PRIVATE SQLite::SQLite3 spdlog::spdlog)

# Include directories
target_include_directories(AppointmentSystem PRIVATE include)

# Set the output directory for binaries
set_target_properties(AppointmentSystem PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Define source and destination for resources
set(RESOURCE_DIR "${CMAKE_SOURCE_DIR}/resources")
set(DESTINATION_DIR "${CMAKE_BINARY_DIR}/bin/resources")

# Copy entire resource directory to output
add_custom_command(TARGET AppointmentSystem POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${RESOURCE_DIR}
    ${DESTINATION_DIR}
)

# Include testing
enable_testing()
add_subdirectory(test)
