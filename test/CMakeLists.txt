
add_executable(runtest test.cpp)

enable_testing()

target_link_libraries(runtest gtest gtest_main)
target_include_directories(runtest PRIVATE ${CMAKE_SOURCE_DIR}/include)