//
// Created by yubin on 2020/10/30.
//

#ifndef EXP3_MEMORYMANAGE_PARTITIONITEM_H
#define EXP3_MEMORYMANAGE_PARTITIONITEM_H


class PartitionItem
{
public:
    int serialNum;  // 序号
    int partitionSize;  // 分区大小
    char* beginAddr;  // 起始地址
    bool isFree;  // 状态，表示是否被分配出去，如果被分配出去则为false，反之为true

    explicit PartitionItem(int serialNum, int partitionSize, char* beginAddr, bool isFree) noexcept;
};


#endif //EXP3_MEMORYMANAGE_PARTITIONITEM_H


