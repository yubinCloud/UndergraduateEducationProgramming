//
// Created by yubin on 2020/10/30.
//

#include "PartitionItem.h"

/**
 * 初始化一个 PartitionItem，默认该分区为空闲状态
 * @param serialNum 分区号
 * @param partitionSize 分区大小
 * @param beginAddr 分区初始地址
 */
PartitionItem::PartitionItem(int serialNum, int partitionSize, char *beginAddr, bool isFree) noexcept :
        serialNum(serialNum),
        partitionSize(partitionSize),
        beginAddr(beginAddr),
        isFree(isFree)
{}
