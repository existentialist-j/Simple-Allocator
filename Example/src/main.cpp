#include "SimpleAllocator.h"
#include <list>


int main()
{
    MemoryObject memory(32, 1024);
    std::list<int, SimpleAllocator<uint32_t>> myList(memory);
    for (size_t i = 0; i < 1022; i++)
    {
        myList.emplace_back(i);
    }

    return 0;
}
