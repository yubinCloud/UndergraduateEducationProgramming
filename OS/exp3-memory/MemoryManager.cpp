//
// Created by yubin on 2020/10/30.
//

#include "MemoryManager.h"

MemoryManager::MemoryManager(int memorySize, std::function<std::unique_ptr<PartitionItem> (int, std::list<PartitionItem>&)> strategy) noexcept :
        memorySize(memorySize),
        memory(new char[memorySize]),
        allocateStrategy(strategy),
        freePartitionList()
{
    freePartitionList.freeList.emplace_back(1, memorySize, memory, true);
}

std::unique_ptr<PartitionItem> MemoryManager::allocatePartition(const int size)
{
    return freePartitionList.allocatePartition(size, allocateStrategy);
}
