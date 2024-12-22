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

void print_vector(const ctm::vector<int> & vec)
{
    for (const auto& val: vec) 
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    return;
}

int main()
{
    std::cout << "hello world!" << std::endl;
    ctm::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    // std::cout << "temp 0: " << vec[0] << std::endl;
    test_const(vec);

    print_vector(vec);

    int a = 100;
    std::cout << "before vector capacity: " << vec.capacity() << std::endl;
    vec.insert(vec.begin()+1, std::move(a));
    std::cout << "after vector capacity: " << vec.capacity() << std::endl;
    print_vector(vec);

    std::vector<int> std_vec = {10, 11, 12, 13, 14};
    vec.insert(vec.begin()+1, std_vec.begin()+1, std_vec.end());
    print_vector(vec);
    std::cout << "new size: " << vec.size() << ", capacity: " << vec.capacity() << std::endl;

    vec.insert(vec.begin()+1, {100, 101, 102});
    print_vector(vec);
    std::cout << "new size: " << vec.size() << ", capacity: " << vec.capacity() << std::endl;

    vec.emplace(vec.end(), 10101);
    print_vector(vec);

    vec.pop_back();
    print_vector(vec);

    vec.resize(20);
    print_vector(vec);


    return EXIT_SUCCESS;
}