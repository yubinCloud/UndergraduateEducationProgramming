"""
拉格朗日插值

"""
import numpy as np
from scipy.interpolate import lagrange


def lag_inter(X, Y):
    """
    根据给定的一系列x, y值来进行拉格朗日插值
    :param X: 所有x组成的一维向量
    :param Y: 所有y组成的一维向量
    :return: 插值多项式
    """
    res_poly = lagrange(X, Y)
    print(res_poly)
    return res_poly


if __name__ == '__main__':
    X = np.array([0, 1, 2])
    Y = np.array([1, 2, 3])
    lag_inter(X, Y)