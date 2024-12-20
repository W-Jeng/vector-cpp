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
    ctm::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    std::cout << "temp 0: " << vec[0] << std::endl;


    test_const(vec);

    for (auto x: vec)
    {
        std::cout << "vec val: " << x << std::endl;
    }


    return EXIT_SUCCESS;
}