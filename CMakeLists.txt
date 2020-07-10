cmake_minimum_required(VERSION 3.1)

project(gtest_gmock_demo)

set(CMAKE_CXX_STANDARD 17)
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


add_executable(assert_expect_tests src/assert_expect_tests.cpp)
target_link_libraries(assert_expect_tests -pthread ${GTEST_BOTH_LIBRARIES} ${GMOCK_BOTH_LIBRARIES})

add_executable(gmock_test src/gmock_test.cpp)
target_link_libraries(gmock_test -pthread ${GTEST_BOTH_LIBRARIES} ${GMOCK_BOTH_LIBRARIES})

add_executable(test_fixtures src/test_fixtures.cpp)
target_link_libraries(test_fixtures -pthread ${GTEST_BOTH_LIBRARIES} ${GMOCK_BOTH_LIBRARIES})


############################################Test Driven Development############################################

ADD_EXECUTABLE(test_driven_development src/test_driven_development.cpp)
TARGET_LINK_LIBRARIES(test_driven_development  ${GTEST_BOTH_LIBRARIES} )

