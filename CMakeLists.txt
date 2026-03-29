cmake_minimum_required(VERSION 3.14)
project(sensor_fusion_kalman_lsfit VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_TESTS "Build unit tests" ON)

add_library(sensor_fusion_lib
    src/Kalman2State.cpp
    src/LeastSquaresFit.cpp
    src/SignalGenerator.cpp
)

target_include_directories(sensor_fusion_lib PUBLIC include)

add_executable(sensor_fusion_demo
    src/main.cpp
)

target_link_libraries(sensor_fusion_demo PRIVATE sensor_fusion_lib)

if(ENABLE_TESTS)
    include(FetchContent)

    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    )

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()

    add_executable(sensor_fusion_tests
        tests/test_main.cpp
    )

    target_link_libraries(sensor_fusion_tests
        PRIVATE
        sensor_fusion_lib
        GTest::gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(sensor_fusion_tests)
endif()