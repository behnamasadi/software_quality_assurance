cmake_minimum_required(VERSION 3.1)

project(gtest_gmock_demo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


option(BUILD_TESTING "this will automatically enable testing" ON)
option(PACKAGE_TESTS "Build the tests" ON)
option(BUILD_TESTING "enabling tests" ON)


if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    include(CTest)
    add_subdirectory(tests)
    MESSAGE( STATUS "BUILD_TESTING: " ${BUILD_TESTING} )
    MESSAGE( STATUS "CMAKE_CTEST_COMMAND: " ${CMAKE_CTEST_COMMAND} )
endif()

add_executable(flip_coin apps/main.cpp)
target_link_libraries(flip_coin ${PROJECT_SOURCE_DIR}/src/coin_flipper.cpp)


