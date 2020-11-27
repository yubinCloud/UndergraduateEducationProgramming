"""
银行家算法
@Time: 2020/11/7 21:27
@Author:
@File: main.py
"""

import numpy as np

import resource_req as rq


# 初始化可利用资源向量
available = np.array(
    [1, 5, 2, 0]
)
# 初始化最大需求矩阵
max_need = np.array(
    [[0, 0, 1, 2],
     [1, 7, 5, 0],
     [2, 3, 5, 6],
     [0, 6, 5, 2],
     [0, 6, 5, 6]]
)
# 初始化分配矩阵
allocation = np.array(
    [[0, 0, 1, 2],
     [1, 0, 0, 0],
     [1, 3, 5, 4],
     [0, 6, 3, 2],
     [0, 0, 1, 4]]
)
# 求出需求矩阵
need = max_need - allocation

PROCESS_NUM, RESOURCE_NUM = allocation.shape  # 进程数和资源数


def banker(request: rq.BaseResourceRequest, avail: np.ndarray,
           max: np.ndarray, alloc: np.ndarray, need: np.ndarray):
    """
    一次银行家算法
    :param request:
    :param avail:
    :param max:
    :param alloc:
    :param need:
    :return:
    """
    i = request.proc
    # 检测所需要的资源是否超出它所宣布的最大值
    if np.any(np.less(need[i], request.nums)):
        return  "所需要的资源超出它所宣布的最大值"

    if np.any(np.less(avail, request.nums)):
        return f"尚无足够资源，进程{request.proc}需要等待", []

    # 试探着把资源分配给该进程
    avail -= request.nums
    alloc[i] += request.nums
    need[i] -= request.nums
    # 安全性算法测试
    test_result = security_test(request, avail.copy(), alloc.copy(), need.copy())
    if test_result:  # 可以分配
        return "完成资源的分配", test_result
    else:  # 不可以分配
        avail += request.nums
        alloc[i] -= request.nums
        need[i] += request.nums
        return "该进程需要等待", []



def security_test(request: rq.BaseResourceRequest, avail: np.ndarray,
                  alloc: np.ndarray, need: np.ndarray):
    """
    安全性算法测试
    :param request:
    :param avail:
    :param alloc:
    :param need:
    :return:
    """
    work = avail.copy()  # 工作向量
    alloc_order = []  # 分配次序
    finish = np.array([False] * alloc.shape[0])

    under_test_proc = -1  # 待测试的进程号
    while True:
        # 检测finish是否全部为True，如果是则返回安全状态
        if np.all(finish):
            return alloc_order
        # 首先找一个finish[i]==false且need[i] <= work的进程，找不到则返回不安全状态
        for row in range(PROCESS_NUM):
            if (finish[row] == False) and (np.all(np.less_equal(need[row], work))):
                under_test_proc = row
                break
        if under_test_proc == -1:
            return False
        # 把资源分配给under_test_proc，执行完后释放它的所有资源
        alloc_order.append(under_test_proc)
        work += alloc[under_test_proc]
        finish[under_test_proc] = True


print("start running....")
while True:
    # 读取用户输入
    action = input("本次执行动作：")
    action = action.split(' ')
    action_type = action[0]
    proc = int(action[1])  # 所操作的进程号
    nums = action[2:]  # 输入的数值
    for i in range(len(nums)):
        nums[i] = int(nums[i])
    if action_type == 'req':
        req = rq.ApplyRequest(proc, nums)
        ret, order = banker(req, available, max_need, allocation, need)
        print(ret)
        print(order)
    elif action_type == 'rel':
        rel = rq.ReleaseRequest(proc, nums)
        # TODO：还未验证是否释放超额
        available += rel.nums
        allocation[i] -= rel.nums
        need[i] += rel.nums
        print("释放完毕")



