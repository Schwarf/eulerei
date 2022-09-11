project(Google_tests)

# 'lib' is the folder with Google Test sources
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

#add_subdirectory(google_test_lib)
#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

enable_testing()
add_executable(test_big_integer
        big_integer/addition.cpp
        big_integer/string_conversion.cpp
        big_integer/subtraction.cpp
        big_integer/multiplication.cpp
        big_integer/exponentiation.cpp
        big_integer/equal_operator.cpp)



target_link_libraries(test_big_integer ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)


