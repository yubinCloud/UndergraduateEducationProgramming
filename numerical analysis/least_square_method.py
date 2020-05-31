"""
最小二乘法

"""

import sympy as sp


def least_square(X, Y, index):
    """
    最小二乘法
    :param X: 一系列的x值组成的一维向量
    :param Y: 一系列的y值组成的一维向量
    :param index: 用来模拟的多项式的最高次数
    :return: 所求的多项式
    """
    n = len(X)  # 点的个数
    A = sp.symarray('a', index + 1).reshape(index + 1, 1)  # 待定系数组成的列向量
    D = sp.zeros(index + 1, 1)  # 值矩阵
    H = sp.zeros(index + 1, index + 1)  # 系数矩阵
    # 计算值矩阵
    for i in range(index + 1):
        res = 0
        for k in range(n):
            res += Y[k] * X[k] ** i
        D[i, 0] = res
    # 计算系数矩阵
    for i in range(index + 1):
        for j in range(index + 1):
            res = 0
            for k in range(n):
                res += X[k] ** (i + j)
            H[i, j] = res
    # 计算正规方程组的待定系数
    A = sp.solve(H * A - D)
    print("H:")
    sp.pprint(H)
    print("D:")
    sp.pprint(D)
    print("A:")
    sp.pprint(A)


if __name__ == '__main__':
    X = [0, 1, 2, 3, 4, 5]
    Y = [5, 2, 1, 1, 2, 3]
    least_square(X, Y, 2)