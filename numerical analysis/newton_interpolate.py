"""
牛顿插值

"""
import numpy as np


def cal_diff_quotient(X, Y):
    """
    计算差商
    :param X: 一系列x组成的一维向量
    :param Y: 一系列y组成的一维向量
    :return: 差商表
    """
    n = len(X)  # 点的个数
    tables = np.zeros(shape=(n, n + 1))  # 初始的差商表
    # 将X放入差商表
    tables[:, 0] = X.reshape(n)
    tables[:, 1] = Y.reshape(n)
    for j in range(1, n):  # j代表阶数，依次计算1阶到 n - 1 阶
        for i in range(j, n):  # i代表行数，逐行进行计算
            tables[i, j + 1] = (tables[i, j] - tables[i - 1, j]) / (tables[i, 0] - tables[i - j, 0])
    print(tables)
    return tables


if __name__ == '__main__':
    X = np.array([0, 2, 3, 5])
    Y = np.array([1, 3, 2, 5])
    # 计算差商表
    cal_diff_quotient(X, Y)

