//
// Created by yubin on 2020/10/30.
//

#ifndef EXP3_MEMORYMANAGE_MEMORYMANAGER_H
#define EXP3_MEMORYMANAGE_MEMORYMANAGER_H

#include "FreePartitionList.h"

class MemoryManager
{
private:
    int memorySize;  // 内存总大小
    char* memory;  // 指向实际的内存
    std::function<std::unique_ptr<PartitionItem> (int, std::list<PartitionItem>&)>& allocateStrategy;
public:
    explicit MemoryManager(int memorySize, std::function<std::unique_ptr<PartitionItem> (int, std::list<PartitionItem>&)>) noexcept;

    std::unique_ptr<PartitionItem> allocatePartition(const int size);

    FreePartitionList freePartitionList;  // 空闲分区链
};


#endif //EXP3_MEMORYMANAGE_MEMORYMANAGER_H
