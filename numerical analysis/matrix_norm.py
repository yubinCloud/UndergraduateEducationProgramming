"""
求矩阵的范数

"""
import numpy as np


def matrix_norm(X, ord):
    """
    求矩阵的范数
    :param X: 待求的矩阵
    :param ord: 范数类型，无穷大用np.inf表示
    :return: 范数
    """
    res = np.linalg.norm(X, ord)
    print("其{}范数值为：".format(ord))
    print(res)
    return res


if __name__ == '__main__':
    B = np.array([
        [0, 3/8, -2/8],
        [-4/11, 0, 1/11],
        [-6/12, -3/12, 0]
    ])
    matrix_norm(B, np.inf)