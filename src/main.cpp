#include "custom_vector.h"
#include "custom_allocator.h"
#include <cstdlib>
#include <iostream>

int main()
{
    std::cout << "hello world!" << std::endl;
    ctm::vector a{};
    ctm::allocator<int> alloc;

    int* b = alloc.allocate(5);

    return EXIT_SUCCESS;
}