//
// Created by yubin on 2020/11/1.
//
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <random>

#include "MemoryManager.h"

using namespace std;


constexpr int EPOCHS = 3;
constexpr int COLLECT_TIMES = 4;

int main()
{
    cout << "Please enter the strategy of allocation." << endl;
    string strategyStr;
    getline(std::cin, strategyStr);
    auto strategy = PartitionAllocateStrategy::firstFitStrategy;
    if (strategyStr == "bf")
        strategy = PartitionAllocateStrategy::bestFitStrategy;
    else if (strategyStr == "wf")
        strategy = PartitionAllocateStrategy::worstFitStrategy;

    default_random_engine e;
    uniform_int_distribution<int> uRandom(10, 100);
    for (int i = 0; i < EPOCHS; ++i) {
        MemoryManager manager(1024, strategy);
        list<unique_ptr<PartitionItem>> itemPtrList;
        for (int j = 0; j < COLLECT_TIMES; ++j) {
            while (true) {
                int randomSize = uRandom(e);
                unique_ptr<PartitionItem> item = manager.allocatePartition(randomSize);
                if (item == nullptr) {
                    break;
                } else {
                    itemPtrList.push_back(std::move(item));
                }
            }
            int randInt = uniform_int_distribution<int>(0, itemPtrList.size())(e);
            auto iter = itemPtrList.begin();
            for (int i = 0; i != randInt; i++) {
                ++iter;
            }
            manager.freePartitionList.collectPartition(**iter);
        }
        cout << manager.freePartitionList.toString() << endl;
        cout << "Memory use ratio: " << endl;
        cout << manager.freePartitionList.memoryUseRatio() << endl;
        cout << "---------------------" << endl;
    }
}



