#pragma once

#include "custom_allocator.h"
#include <memory>

namespace ctm 
{

template <typename T, typename Alloc = ctm::allocator<T>>
class vector 
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using allocator_type = Alloc;
    using difference_type = std::ptrdiff_t;
    using reference = T&;
    using const_reference = T&;
    using iterator = T*;
    using const_iterator = const T*;

    vector():
        data_(nullptr),
        size_(0),
        capacity_(0) {}

    ~vector()
    {
        for (size_t i = 0; i < size_; ++i)
        {
            allocator_.destroy(data_ + i);
        }
        if (data_)
        {
            allocator_.deallocate(data_, capacity_);
        }
        return;
    }
    
    // ELEMENT ACCESS
    reference at(std::size_t index)
    {
        if (index < 0 || index >= size_)
        {
            throw std::out_of_range("Indexing out of range");
        }
        return data_[index];
    }
    
    const_reference at(std::size_t index) const
    {
        if (index < 0 || index >= size_)
        {
            throw std::out_of_range("Indexing out of range");
        }
        return data_[index];
    }

    reference operator[](std::size_t index)
    {
        return data_[index];
    }

    // accessed when using const vector
    const_reference operator[](std::size_t index) const
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

    // Iterators
    iterator begin()
    {
        return data_;
    }

    const_iterator begin() const
    {
        return data_;
    }

    const_iterator cbegin() const
    {
        return data_;
    }

    iterator end()
    {
        return data_ + size_;
    }

    const_iterator end() const
    {
        return data_ + size_;
    }

    const_iterator cend() const
    {
        return data_ + size_;
    }

    // CAPACITY
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

        T* new_data = allocator_.allocate(new_capacity);

        for (std::size_t i = 0; i < size_; ++i)
        {
            allocator_.construct(new_data + i, std::move(data_[i]));
            allocator_.destroy(data_ + i);
        }

        if (data_)
        {
            allocator_.deallocate(data_, capacity_);
        }

        data_ = new_data;
        capacity_ = new_capacity;
        return;
    }

    size_type capacity() const
    {
        return capacity_;
    }

    // MODIFIERS

    void clear() 
    {
        for (std::size_t i = 0; i < size_; ++i) 
        {
            allocator_.destroy(data_ + i);
        }

        size_ = 0;
        // capacity is not released as per the standard's implementation
    }

    // iterator insert(const_iterator pos, const T& value)
    // {
    //     return;
    // }

    // iterator insert(const_iterator pos, size_type count, const T& value)
    // {

    // }

    void push_back(const T& value)
    {
        if (size_ == capacity_)
        {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }

        allocator_.construct(data_ + size_, value);
        ++size_;
        return;
    }


private:
    T* data_;
    std::size_t size_;  
    std::size_t capacity_;
    Alloc allocator_;

};


};