


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

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(GMOCK_ROOT "$ENV{HOME}/usr" )

find_package(GMock REQUIRED)

MESSAGE("GMOCK_FOUND: " ${GMOCK_FOUND})
MESSAGE("GMOCK_BOTH_LIBRARIES: " ${GMOCK_BOTH_LIBRARIES})
MESSAGE("GMOCK_LIBRARIES: " ${GMOCK_LIBRARIES})
MESSAGE("GMOCK_MAIN_LIBRARIES: " ${GMOCK_MAIN_LIBRARIES})
MESSAGE("GMOCK_INCLUDE_DIRS: " ${GMOCK_INCLUDE_DIRS})

add_executable(assert_expect_tests src/assert_expect_tests.cpp)
target_link_libraries(assert_expect_tests -pthread ${GTEST_BOTH_LIBRARIES} ${GMOCK_BOTH_LIBRARIES})
gtest_discover_tests(assert_expect_tests)

add_executable(gmock_test src/gmock_test.cpp  ../../src/coin_flipper.cpp)
target_link_libraries(gmock_test -pthread ${GTEST_BOTH_LIBRARIES} ${GMOCK_BOTH_LIBRARIES})
gtest_discover_tests(gmock_test)


add_executable(test_fixtures src/test_fixtures.cpp)
target_link_libraries(test_fixtures -pthread ${GTEST_BOTH_LIBRARIES} ${GMOCK_BOTH_LIBRARIES})
gtest_discover_tests(test_fixtures)

############################################Test Driven Development############################################

ADD_EXECUTABLE(test_driven_development src/test_driven_development.cpp)
TARGET_LINK_LIBRARIES(test_driven_development  ${GTEST_BOTH_LIBRARIES} )
##gtest_discover_tests(test_driven_development)
