#include  "SimpleAllocator.h"


MemoryObject::MemoryObject(size_t bucketSize, size_t numberOfBuckets) : m_bufferSize(bucketSize* numberOfBuckets), m_bucketSize(bucketSize)
{
    m_buffer = new char[m_bufferSize];
    memset(m_buffer, 0, m_bufferSize);
    m_first = new(m_buffer)Bucket();
    Bucket* temp = m_first;
    for (size_t i = 1; i < numberOfBuckets; ++i)
    {
        temp->next = new((char*)temp + m_bucketSize)Bucket();
        temp = temp->next;
    }
    temp->next = nullptr;
}

void* MemoryObject::allocate()
{
    if (nullptr == m_first)
    {
        throw std::bad_alloc();
    }
    Bucket* temp = m_first;
    m_first = (nullptr != m_first->next) ? m_first->next : nullptr;
    temp->~Bucket();
    return reinterpret_cast<void*>(temp);
}

void MemoryObject::deallocate(void* pointer)
{
    memset(pointer, 0, sizeof(Bucket));
    Bucket* temp = m_first;
    m_first = new(pointer)Bucket();
    m_first->next = temp;
}

size_t MemoryObject::getMaxSize()
{
    return m_bufferSize;
}

size_t MemoryObject::getBucketSize()
{
    return m_bucketSize;
}
