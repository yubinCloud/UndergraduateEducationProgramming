//
// Created by yubin on 2020/10/30.
//

#ifndef EXP3_MEMORYMANAGE_FREEPARTITIONLIST_H
#define EXP3_MEMORYMANAGE_FREEPARTITIONLIST_H

#include <list>
#include <memory>
#include <functional>
#include <string>

#include "PartitionItem.h"


class FreePartitionList
{
public:
    std::list<PartitionItem> freeList;  // 空闲链

    FreePartitionList() noexcept;

    std::unique_ptr<PartitionItem> allocatePartition(int requestMemorySize,
                                                     const std::function<
                                                             std::unique_ptr<PartitionItem> (int, std::list<PartitionItem>&)
                                                     >& allocateStrategy);

    bool collectPartition(PartitionItem partitionItem) noexcept;

    std::string toString() const noexcept;

    double memoryUseRatio() const noexcept;

private:
    void mergeFreePartitions(std::list<PartitionItem>::iterator centreItemIter) noexcept;
    void mergePartitionsFromPreToTail(std::list<PartitionItem>::iterator preIter, std::list<PartitionItem>::iterator tailIter) noexcept;
};


namespace PartitionAllocateStrategy
{
    constexpr int DEBRIS_SIZE = 5;  // 碎片大小，当划分分区后剩余长度小于该大小时便将整个分区分配出去

    std::unique_ptr<PartitionItem> firstFitStrategy(int requestSize, std::list<PartitionItem>& freeList) noexcept;  // 最先适应算法
    std::unique_ptr<PartitionItem> bestFitStrategy(int requestSize, std::list<PartitionItem>& freeList) noexcept;  // 最佳适应算法
    std::unique_ptr<PartitionItem> worstFitStrategy(int requestSize, std::list<PartitionItem>& freeList) noexcept;  // 最坏适应算法
};

#endif //EXP3_MEMORYMANAGE_FREEPARTITIONLIST_H
