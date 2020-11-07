//
// Created by yubin on 2020/10/30.
//

#include <sstream>

#include "FreePartitionList.h"

using namespace std;

FreePartitionList::FreePartitionList() noexcept :
        freeList()
{}

/**
 * 采用某个分区分配算法，从空闲链表中选择一个合适的分区分配出去
 * @param requestMemorySize 请求的内存大小
 * @param allocateStrategy 所采用的分配策略
 * @return 若分配成功，则返回描述该分区的PartitionItem；若分配失败则返回 nullptr
 */
unique_ptr<PartitionItem> FreePartitionList::allocatePartition(int requestMemorySize,
                                                               const function<unique_ptr<PartitionItem>(int, list<PartitionItem>&)>& allocateStrategy)
{
    return allocateStrategy(requestMemorySize, this->freeList);
}

/**
 * 回收一个之前分配出去的分区
 * @param partitionItem 存储分区的信息
 * @return 是否回收成功，若成功则返回 true，反之返回 false
 */
bool FreePartitionList::collectPartition(PartitionItem partitionItem) noexcept
{
    // 检查待回收的分区的初始地址是否位于整个内存的前面
    if (partitionItem.beginAddr < freeList.front().beginAddr) {
        return false;
    }
    bool hasFind = false;  // 标志是否找到可以插入的位置
    // 寻找到可以插入的位置
    for (auto iter = freeList.begin(); iter != freeList.end(); ++iter) {
        if (iter->beginAddr < partitionItem.beginAddr)
            continue;
        else if (iter->beginAddr > partitionItem.beginAddr) {
            return false;
        }
        else {
            if (iter->isFree)  // 如果该分区本身就未被使用
                return false;
            // 回收内存
            hasFind = true;
            iter->isFree = true;
            mergeFreePartitions(iter);
        }
    }
    return false;
}

/**
 * 以一个分区项为中心，将两边的未被使用的分区合并起来
 * @param centreItemIter 作为中心项的迭代器
 */
void FreePartitionList::mergeFreePartitions(const list<PartitionItem>::iterator centreItemIter) noexcept
{
    // 寻找需要进行合并的前面的首个分区
    auto preItemIter = centreItemIter;
    for (; preItemIter != freeList.begin(); --preItemIter) {
        if (preItemIter->isFree)
            continue;
        break;
    }
    if (preItemIter == freeList.begin() && preItemIter->isFree) {
        NULL;
    } else {
        ++preItemIter;
    }
    // 寻找需要进行合并的后面的尾巴分区
    auto tailItemIter = centreItemIter;
    for (; tailItemIter != freeList.end(); ++tailItemIter) {
        if (tailItemIter->isFree)
            continue;
        break;
    }
    // 使用preItemIter和tailItemIter进行合并
    mergePartitionsFromPreToTail(preItemIter, tailItemIter);
}

/**
 * 对前后两个迭代器所指向的分区进行全部合并
 * @param preIter 需要合并的所有分区的首分区，包含该分区
 * @param tailIter 需要合并的所有分区的尾分区，不包含该分区
 */
void FreePartitionList::mergePartitionsFromPreToTail(std::list<PartitionItem>::iterator preIter,
                                                     std::list<PartitionItem>::iterator tailIter) noexcept
{
    // 将 [preIter + 1, ..., tailIter) 的元素的大小累加到 preIter 上
    auto iter = preIter;
    ++iter;
    for ( ; iter != tailIter; ++iter) {
        preIter->partitionSize += iter->partitionSize;
    }

    freeList.erase(++preIter, tailIter);  // 删除[preIter + 1, ..., tailIter)的元素
}

/**
 * 将该空闲链表转化为字符串描述
 * @return 转化后的字符串
 */
string FreePartitionList::toString() const noexcept
{
    ostringstream strSteam;
    for (const auto& item: freeList) {
        strSteam << item.serialNum << "   " << item.partitionSize << "   " << item.beginAddr - freeList.front().beginAddr << "   " << item.isFree << std::endl;
    }
    return strSteam.str();
}

/**
 * 获取内存的利用率
 * @return
 */
double FreePartitionList::memoryUseRatio() const noexcept
{
    int totalSize = 0, usingSize = 0;
    for (auto& item: freeList) {
        totalSize += item.partitionSize;
        if (!item.isFree)
            usingSize += item.partitionSize;
    }
    return static_cast<double>(usingSize) / totalSize;
}

/**
 * 首次匹配策略
 * @param requestSize 请求的内存大小
 * @param freeList 空闲链表
 * @return 若分配成功，则返回描述该分区的PartitionItem；若分配失败则返回 nullptr
 */
unique_ptr<PartitionItem>
PartitionAllocateStrategy::firstFitStrategy(const int requestSize, list<PartitionItem>& freeList) noexcept
{
    for (auto pItem = freeList.begin(); pItem != freeList.end(); ++pItem) {  // 遍历空闲链表
        if (!pItem->isFree)
            continue;
        if (pItem->partitionSize < requestSize)
            continue;
        // 根据划分后剩余大小来决定是否全部分出去
        if (pItem->partitionSize - requestSize <= PartitionAllocateStrategy::DEBRIS_SIZE) {
            pItem->isFree = false;
            auto pItemCopy = new PartitionItem(0, pItem->partitionSize, pItem->beginAddr, false);
            return unique_ptr<PartitionItem>(pItemCopy);
        } else {
            auto pNextItem = pItem;
            ++pNextItem;
            freeList.emplace(pNextItem, pItem->serialNum + 1, pItem->partitionSize - requestSize,
                             pItem->beginAddr + requestSize, true);
            pItem->partitionSize = requestSize;
            pItem->isFree = false;
            // 将PNextItem之后的元素的序号加1
            int curSerialNum = pNextItem->serialNum;
            for (auto p = pNextItem; p != freeList.end(); ++p) {
                ++curSerialNum;
                p->serialNum = curSerialNum;
            }
            auto pItemCopy = new PartitionItem(0, pItem->partitionSize, pItem->beginAddr, false);
            return unique_ptr<PartitionItem>(pItemCopy);
        }
    }
    return nullptr;  // 没有可用的分区，返回空指针
}

/**
 * 最佳适应算法
 * @param requestSize 所需要的大小
 * @param freeList 空闲链表
 * @return 指向所分配的分区信息的 PartitionItem
 */
unique_ptr<PartitionItem>
PartitionAllocateStrategy::bestFitStrategy(const int requestSize, list<PartitionItem>& freeList) noexcept
{
    auto minFreePartition = freeList.begin();  // 指向最小空闲分区
    // 首先找到第一个非空的分区
    while (minFreePartition != freeList.end() && !minFreePartition->isFree)
        ++minFreePartition;
    if (minFreePartition == freeList.end())
        return nullptr;
    // 找出最小空闲分区
    for (auto iter = minFreePartition; iter != freeList.end(); ++iter) {
        if (!iter->isFree || iter->partitionSize >= minFreePartition->partitionSize) {
            continue;
        }
        if (iter->partitionSize < minFreePartition->partitionSize) {
            minFreePartition = iter;
        }
    }
    // 根据划分后剩余大小来决定是否全部分出去
    if (minFreePartition->partitionSize - requestSize <= PartitionAllocateStrategy::DEBRIS_SIZE) {
        minFreePartition->isFree = false;
        return unique_ptr<PartitionItem>(
                new PartitionItem(0, minFreePartition->partitionSize, minFreePartition->beginAddr, false)
        );
    } else {
        auto pNextItem = minFreePartition;
        ++pNextItem;
        freeList.emplace(pNextItem, minFreePartition->serialNum + 1, minFreePartition->partitionSize - requestSize,
                         minFreePartition->beginAddr + requestSize, true);
        minFreePartition->partitionSize = requestSize;
        minFreePartition->isFree = false;
        // 将PNextItem之后的元素的序号加1
        int curSerialNum = minFreePartition->serialNum;
        for (auto p = pNextItem; p != freeList.end(); ++p) {
            ++curSerialNum;
            p->serialNum = curSerialNum;
        }
        return unique_ptr<PartitionItem>(
                new PartitionItem(0, minFreePartition->partitionSize, minFreePartition->beginAddr, false)
        );
    }
}

/**
 * 最坏适应算法
 * @param requestSize
 * @param freeList
 * @return 指向所分配的分区信息的 PartitionItem
 */
unique_ptr<PartitionItem>
PartitionAllocateStrategy::worstFitStrategy(const int requestSize, list<PartitionItem>& freeList) noexcept
{
    auto maxFreePartition = freeList.begin();  // 指向最小空闲分区
    // 首先找到第一个非空的分区
    while (maxFreePartition != freeList.end() && !maxFreePartition->isFree)
        ++maxFreePartition;
    if (maxFreePartition == freeList.end())
        return nullptr;
    // 找出最小空闲分区
    for (auto iter = maxFreePartition; iter != freeList.end(); ++iter) {
        if (!iter->isFree || iter->partitionSize <= maxFreePartition->partitionSize) {
            continue;
        }
        if (iter->partitionSize > maxFreePartition->partitionSize) {
            maxFreePartition = iter;
        }
    }
    // 根据划分后剩余大小来决定是否全部分出去
    if (maxFreePartition->partitionSize - requestSize <= PartitionAllocateStrategy::DEBRIS_SIZE) {
        maxFreePartition->isFree = false;
        return unique_ptr<PartitionItem>(
                new PartitionItem(0, maxFreePartition->partitionSize, maxFreePartition->beginAddr, false)
        );
    } else {
        auto pNextItem = maxFreePartition;
        ++pNextItem;
        freeList.emplace(pNextItem, maxFreePartition->serialNum + 1, maxFreePartition->partitionSize - requestSize,
                         maxFreePartition->beginAddr + requestSize, true);
        maxFreePartition->partitionSize = requestSize;
        maxFreePartition->isFree = false;
        // 将PNextItem之后的元素的序号加1
        int curSerialNum = maxFreePartition->serialNum;
        for (auto p = pNextItem; p != freeList.end(); ++p) {
            ++curSerialNum;
            p->serialNum = curSerialNum;
        }
        return unique_ptr<PartitionItem>(
                new PartitionItem(0, maxFreePartition->partitionSize, maxFreePartition->beginAddr, false)
        );
    }
}
