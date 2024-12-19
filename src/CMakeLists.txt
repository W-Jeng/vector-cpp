
add_executable(main main.cpp)

enable_testing()
add_executable(runtest test.cpp)

target_link_libraries(runtest gtest gtest_main)
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(runtest PRIVATE ${CMAKE_SOURCE_DIR}/include)



