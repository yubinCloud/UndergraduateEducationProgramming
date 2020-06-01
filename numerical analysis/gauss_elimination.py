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


def gauss_elimination(A, b, need_primecol=False):
    """
    高斯消去法
    :param A: 系数矩阵
    :param b: 值矩阵
    :param need_primecol: 是否采用列主元策略
    :return: 消元后的矩阵
    """
    B = augment_matrix(A, b)  # 生成增广矩阵
    num_row, num_col = B.shape  # 增广矩阵的行数、列数
    print("初始：")
    print(B)
    for cur_row in range(0, num_row - 1):
        print("第{}轮：".format(cur_row + 1))
        # 若需要交换列主元则进行相关处理
        if (need_primecol):
            primecol_strategy(B, cur_row, cur_row)

        for row in range(cur_row + 1, num_row):
            coef = - B[row, cur_row] / B[cur_row, cur_row]
            B[row, :] = B[row] + coef * B[cur_row]
            print("row{} + ({}) * row{}".format(row + 1, coef, cur_row + 1))
        print("本轮结果：")
        print(B)
    return B


def primecol_strategy(B, cur_row, cur_col):
    """
    列主元策略
    :param B: 待处理的矩阵
    :return:列主元交换后的矩阵
    """
    primecol_row = find_primecol(B, cur_row, cur_col)  # 列主元所在行
    print("交换row{}与row{}".format(cur_row + 1, primecol_row + 1))
    B[[primecol_row, cur_row], :] = B[[cur_row, primecol_row]]  # 交换当前行与列主元所在行


def find_primecol(M, cur_row, cur_col):
    """
    寻找自row行及下面行中第col列的最大元所在行
    :param M: 所要处理的矩阵
    :param cur_row: 行
    :param cur_col: 列
    :return: 列主元所在行
    """
    num_row = M.shape[0]
    max_value = M[cur_row, cur_col]
    max_row = cur_row
    for row in range(cur_row + 1, num_row):
        if M[row, cur_col] > max_value:
            max_value = M[row, cur_col]
            max_row = row
    return max_row


if __name__ == '__main__':
    A = np.array([
        [r(2), r(2), r(3)],
        [r(4), r(7), r(7)],
        [r(-2), r(4), r(5)]
    ])
    b = np.array([r(3), r(1), r(-7)])
    gauss_elimination(A, b, need_primecol=True)
