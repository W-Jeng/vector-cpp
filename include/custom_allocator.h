#pragma once

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

    allocator( const allocator& other ) noexcept = default;

    template <typename U>
    constexpr allocator( const allocator<U>& other) noexcept {};

    T* allocate(const std::size_t n)
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

    void deallocate(T* p, const std::size_t n) noexcept
    {
        if (p)
        {
            ::operator delete(p);
            std::cout << "Deallocated: " << n * sizeof(T) << " bytes\n";
        }
        return;
    }

    template <typename U, typename... Args>
    void construct(U* p, Args&&... args)
    {
        ::new ((void*)p) U(std::forward<Args>(args)...);
        std::cout << "Constructed object at " << p << "\n";
    }

    template <typename U>
    void destroy(U* p) noexcept
    {
        if (p) 
        {
            p->~U();
            std::cout << "Destroyed object at " << p << "\n";
        }
    }

    template <typename U>
    struct rebind
    {
        using other = allocator<U>;
    };

    std::size_t max_size() const noexcept
    {
        return std::numeric_limits<size_type>::max() / sizeof(T);
    }

    constexpr bool operator==(const allocator&) const noexcept
    {
        return true;
    }

    constexpr bool operator!=(const allocator&) const noexcept
    {
        return false;
    }

};


};