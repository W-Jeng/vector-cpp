#include "custom_vector.h"
#include "custom_allocator.h"
#include <cstdlib>
#include <iostream>

int main()
{
    std::cout << "hello world!" << std::endl;
    ctm::allocator<int> alloc;

    int* b = alloc.allocate(5);

    for (std::size_t i = 0; i < 5; ++i)
    {
        alloc.construct(&b[i], static_cast<int>(i * 10));
    }

    for (std::size_t i = 0; i < 5; ++i)
    {
        std::cout << "b[" << i << "] = " << b[i] << "\n";
    }

    for (std::size_t i = 0; i < 5; ++i)
    {
        alloc.destroy(&b[i]);
    }

    alloc.deallocate(b, 5);

    return EXIT_SUCCESS;
}