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

    void reserve(std::size_t new_capacity)
    {
        if (new_capacity <= capacity_)
        {
            return;
        }

        T* new_data = allocator.allocate(new_capacity);

        for (std::size_t i = 0; i < size_; ++i)
        {
            allocator.construct(new_data+i, std::move(data_[i]));
            allocator.destroy(data_+i);
        }

        if (data_)
        {
            allocator.deallocate(data_, capacity_);
        }

        data_ = new_data;
        capacity_ = new_capacity;
        return;
    }

    // operators
    const T& at(std::size_t index) const
    {
        if (index < 0 || index >= size_)
        {
            throw std::out_of_range("Indexing out of range");
        }
        return data_[index];
    }

    // accessed when using const vector
    const T& operator[](std::size_t index) const
    {
        return data_[index];
    }

    T& operator[](std::size_t index)
    {
        return data_[index];
    }


};


};