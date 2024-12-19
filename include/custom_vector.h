#pragma once

#include "custom_allocator.h"
#include <memory>

namespace ctm 
{

template <typename T, typename Alloc = ctm::allocator<T>>
class vector 
{
private:
    T* data_;
    std::size_t size_;  
    std::size_t capacity_;
    Alloc allocator;

public:
    using value_type = T;
    using size_type = std::size_t;
    using allocator_type = Alloc;
    using difference_type = std::ptrdiff_t;
    using reference = T&;
    using const_reference = T&;


    vector(): data_(nullptr),
        size_(0),
        capacity_(0) {}

    ~vector()
    {
        for (size_t i = 0; i < size_; ++i)
        {
            allocator.destroy(data_ + i);
        }
        if (data_)
        {
            allocator.deallocate(data_, capacity_);
        }
        return;
    }
    
    void push_back(const T& value)
    {
        if (size_ == capacity_)
        {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        allocator.construct(data_ + size_, value);
        ++size_;
        return;
    }

    bool empty() const
    {
        return (size_ == 0);
    }

    size_type size() const
    {
        return size_;
    }

    size_type max_size() const
    {
        return std::numeric_limits<size_type>::max()/sizeof(T);
    }

    void reserve(std::size_t new_capacity)
    {
        if (new_capacity <= capacity_)
        {
            return;
        }

        T* new_data = allocator.allocate(new_capacity);

        for (std::size_t i = 0; i < size_; ++i)
        {
            allocator.construct(new_data + i, std::move(data_[i]));
            allocator.destroy(data_ + i);
        }

        if (data_)
        {
            allocator.deallocate(data_, capacity_);
        }

        data_ = new_data;
        capacity_ = new_capacity;
        return;
    }

    size_type capacity() const
    {
        return capacity_;
    }

    void clear() 
    {
        for (std::size_t i = 0; i < size_; ++i) 
        {
            allocator.destroy(data_ + i);
        }

        size_ = 0;
        // capacity is not released as per the standard's implementation
    }

    // operators
    const reference at(std::size_t index) const
    {
        if (index < 0 || index >= size_)
        {
            throw std::out_of_range("Indexing out of range");
        }
        return data_[index];
    }

    // accessed when using const vector
    const_reference operator[](std::size_t index) const
    {
        return data_[index];
    }

    reference operator[](std::size_t index)
    {
        return data_[index];
    }

    reference front() 
    {
        return data_[0];
    }

    const_reference front() const 
    {
        return data_[0];
    }

    reference back()
    {
        return data_[size_ - 1];
    }

    const_reference back() const
    {
        return data_[size_ - 1];
    }

    T* data() 
    {
        return data_;
    }

    const T* data() const
    {
        return data_;
    }

};


};