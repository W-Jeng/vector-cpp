#include <cstddef>
#include <memory>
#include <iostream>
#include <limits>

namespace ctm
{

template <typename T>
class allocator
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    constexpr allocator() noexcept = default;

    allocator( const allocator& other ) noexcept;

    template <typename U>
    constexpr allocator( const allocator<U>& other) noexcept;

    T* allocate(std::size_t n)
    {
        if (n == 0)
        {
            return nullptr;
        }

        if (n > max_size()) 
        {
            throw std::bad_alloc();
        }

        T* ptr = static_cast<T*>(::operator new(n * sizeof(T)));
        std::cout << "Allocated: " << n * sizeof(T) << " bytes\n";
        return ptr;
    }


    std::size_t max_size() noexcept
    {
        return std::numeric_limits<value_type>::max() / sizeof(T);
    }
};


};