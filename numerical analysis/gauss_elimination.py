"""
高斯消元法

"""

from sympy import Rational as r
import numpy as np


def augment_matrix(A, b):
    """
    将系数矩阵A和值矩阵D合成为一个增广矩阵
    :param A: 系数矩阵
    :param b: 值矩阵
    :return: 合成后的增广矩阵
    """
    b = b.reshape((-1, 1))
    return np.hstack((A, b))


def gauss_elimination(A, b):
    """
    高斯消去法
    :param A: 系数矩阵
    :param b: 值矩阵
    :return: 消元后的矩阵
    """
    B = augment_matrix(A, b)  # 生成增广矩阵
    num_row, num_col = B.shape  # 增广矩阵的行数、列数
    print("初始：")
    print(B)
    for cur_row in range(0, num_row - 1):
        print("第{}轮：".format(cur_row + 1))
        for row in range(cur_row + 1, num_row):
            coef = - B[row, cur_row] / B[cur_row, cur_row]
            B[row, :] = B[row] + coef * B[cur_row]
            print("row{} + ({}) * row{}".format(row + 1, coef, cur_row + 1))
        print("本轮结果：")
        print(B)
    return B


if __name__ == '__main__':
    A = np.array([
        [r(2), r(-1), r(3)],
        [r(4), r(2), r(5)],
        [r(1), r(2), r(0)]
    ])
    b = np.array([r(1), r(4), r(7)])
    gauss_elimination(A, b)
