"""
求矩阵的条件数

"""
import numpy as np


def cond(X, ord):
    """
    求矩阵的条件数
    :param X: 矩阵
    :param ord: 矩阵的范数， 无穷大用np.inf表示
    :return: 矩阵条件数
    """
    return np.linalg.cond(X, ord)


if __name__ == '__main__':
    A = np.array([
        [1, -1],
        [1, 1]
    ])
    print(cond(A, np.inf))