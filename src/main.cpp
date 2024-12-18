#include "custom_vector.h"
#include "custom_allocator.h"
#include <cstdlib>
#include <iostream>
#include <vector>


void test_const(const ctm::vector<int>& vec)
{
    std::cout << "testing const, vec 0: " << vec[0] << std::endl;
}

int main()
{
    std::cout << "hello world!" << std::endl;
    ctm::vector<int> temp;
    temp.push_back(1);
    temp[0] = 2;
    std::cout << "temp 0: " << temp[0] << std::endl;

    int x = temp[0];

    test_const(temp);

    temp[1] = 1;
    std::cout << "temp 1: " << temp[1] << std::endl;

    std::vector<int> std_vec;
    std_vec.push_back(1);
    std_vec[100] = 2;
    std::cout << "std vec: " << std_vec[100] << std::endl;

    return EXIT_SUCCESS;
}