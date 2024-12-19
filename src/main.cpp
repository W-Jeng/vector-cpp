#include "custom_vector.h"
#include "custom_allocator.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <limits>

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


    return EXIT_SUCCESS;
}