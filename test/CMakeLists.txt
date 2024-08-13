# Minimum CMake version required for test directory
cmake_minimum_required(VERSION 3.23)

# Include directories for the test
include_directories(${CMAKE_SOURCE_DIR}/include)

# Find GoogleTest
find_package(GTest REQUIRED)

# Add test sources
file(GLOB TEST_SOURCES "*/*.cpp")

# Add test executable
add_executable(AppointmentSystemTests ${TEST_SOURCES} ${SOURCE_CONFIGS} ${SOURCE_CORES} ${SOURCE_MANAGERS})

# Link libraries to test executable
target_link_libraries(AppointmentSystemTests PRIVATE GTest::GTest GTest::Main SQLite::SQLite3 spdlog::spdlog)

# Include directories for test executable
target_include_directories(AppointmentSystemTests PRIVATE ${GTEST_INCLUDE_DIRS})

# Add test cases
add_test(NAME AppointmentSystemTests COMMAND AppointmentSystemTests)
