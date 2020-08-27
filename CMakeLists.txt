cmake_minimum_required(VERSION 3.1)

project(gtest_gmock_demo)
set(CMAKE_BUILD_TYPE DEBUG)
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

add_subdirectory(apps)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

message("############################## Cppcheck ##############################")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON )#this creats a compilation database that can be passed to cppcheck
#set(CMAKE_CXX_CPPCHECK "cppcheck")




set(CPPCHECK_SUPPRESSIONS ${PROJECT_ROOT_DIR}/CppCheckSuppressions.txt)
set(CPPCHECK_ERROR_EXITCODE_ARG "")
set(CPPCHECK_XML_OUTPUT "${PROJECT_BINARY_DIR}/analysis/cppcheck/cppcheck_analysis.xml")
set(CPPCHECK_EXCLUDES
    ${CMAKE_SOURCE_DIR}/3rd_party
    ${CMAKE_BINARY_DIR}/
)

find_package(Cppcheck)

add_executable(ALL_ANALYSIS_TARGETS src/cppcheck_demo.cpp)
add_custom_target(analysis)
#ADD_DEPENDENCIES(analysis ${ALL_ANALYSIS_TARGETS})
set_target_properties(analysis PROPERTIES EXCLUDE_FROM_ALL TRUE)
message("analysis analysis targets are ${ALL_ANALYSIS_TARGETS}")


message("############################## Valgrind ##############################")

add_executable(cppcheck_demo src/cppcheck_demo.cpp)
target_link_libraries(cppcheck_demo)

