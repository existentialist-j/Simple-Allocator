#pragma once

/*********************************************************************
*
*   @file           SimpleAllocator.h
*   @author         ONUR ERDALLI
*   @brief          A custom allocator which can be used with STL containers
*
*/

#include <memory>
#include <iostream>

class MemoryObject;

class MemoryObject
{
public:
    struct Bucket
    {
        Bucket* next = nullptr;
    };

    MemoryObject(size_t bucketSize, size_t numberOfBuckets);

    void* allocate();
    void deallocate(void* pointer);
    size_t getMaxSize();
    size_t getBucketSize();

private:
    char* m_buffer = nullptr;
    Bucket* m_first;
    size_t m_bufferSize;
    size_t m_bucketSize;
};

template <class T>
class SimpleAllocator
{
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using void_pointer = void*;
    using const_void_pointer = const void*;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;

    template <class U>
    struct rebind
    {
        using other = SimpleAllocator<U>;
    };

    SimpleAllocator(MemoryObject& mem) : m_memObject(mem)
    {

    }

    template <class U>
    SimpleAllocator(const SimpleAllocator<U>& other) noexcept : m_memObject(other.m_memObject)
    {
    }

    pointer allocate(size_type numberOfObjects)
    {
        if (numberOfObjects * sizeof(T) > m_memObject.getBucketSize())
        {
            throw std::bad_alloc();
        }
        T* address = reinterpret_cast<T*>(m_memObject.allocate());
        std::cout << "allocate is called size: " << numberOfObjects * sizeof(T) << " pointer: " << address << std::endl;
        return address;
    }

    void deallocate(pointer p, size_type numberOfObjects)
    {
        std::cout << "deallocate is called size: " << numberOfObjects * sizeof(T) << " pointer: " << p << std::endl;
        m_memObject.deallocate(p);
    }

    size_type max_size() const
    {
        return m_memObject.getMaxSize();
    }
    template <class U> friend class SimpleAllocator;
private:
    MemoryObject& m_memObject;
};
