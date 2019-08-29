cmake_minimum_required(VERSION 2.8)

project(gtest_demo)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


####################################### GTEST #######################################
#https://cmake.org/cmake/help/latest/module/FindGTest.html
#or cmake -DGTEST_ROOT=ENV{HOME}/usr
set(GTEST_ROOT "$ENV{HOME}/usr" )
find_package(GTest REQUIRED)

include_directories(BEFORE ${GTEST_INCLUDE_DIRS})

MESSAGE("GTEST_FOUND: " ${GTEST_FOUND})
MESSAGE("GTEST_INCLUDE_DIRS: " ${GTEST_INCLUDE_DIRS})
MESSAGE("GTEST_LIBRARIES: " ${GTEST_LIBRARIES})
MESSAGE("GTEST_MAIN_LIBRARIES: " ${GTEST_MAIN_LIBRARIES})
MESSAGE("GTEST_BOTH_LIBRARIES: " ${GTEST_BOTH_LIBRARIES})


####################################### GMOCK #######################################

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/src/cmake/Modules/")
set(GMOCK_ROOT "$ENV{HOME}/usr" )

find_package(GMock REQUIRED)

MESSAGE("GMOCK_FOUND: " ${GMOCK_FOUND})
MESSAGE("GMOCK_BOTH_LIBRARIES: " ${GMOCK_BOTH_LIBRARIES})
MESSAGE("GMOCK_LIBRARIES: " ${GMOCK_LIBRARIES})
MESSAGE("GMOCK_MAIN_LIBRARIES: " ${GMOCK_MAIN_LIBRARIES})
MESSAGE("GMOCK_INCLUDE_DIRS: " ${GMOCK_INCLUDE_DIRS})

add_executable(runTests src/tests.cpp)
target_link_libraries(runTests pthread  ${GTEST_BOTH_LIBRARIES} ${GMOCK_BOTH_LIBRARIES})

############################################Test Driven Development############################################

ADD_EXECUTABLE(test_driven_development TestDrivenDevelopment/test_driven_development.cpp)
TARGET_LINK_LIBRARIES(test_driven_development  ${GTEST_BOTH_LIBRARIES} )

