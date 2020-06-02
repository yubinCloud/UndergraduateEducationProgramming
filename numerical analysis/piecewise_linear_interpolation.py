"""
分段线性插值

"""
import sympy as sp
from sympy import Rational as r


def piecewise_linear_inter(X, Y):
    """
    分段线性插值
    :param X: 一系列x的一维向量
    :param Y: 一系列y的一维向量
    :return: 分段线性插值多项式
    """
    x = sp.Symbol('x')
    for i in range(len(X) - 1):  # i代表当前第几段
        print('在[{}, {}]上的线性插值为：'.format(X[i], X[i + 1]))
        S = (x - X[i + 1]) / (X[i] - X[i + 1]) * Y[i] + (x - X[i]) / (X[i + 1] - X[i]) * Y[i + 1]
        print(S)


if __name__ == '__main__':
    # 注意根号用sp.sqrt()来表示，如sp.sqrt(2)表示 根号2
    # 分数用r(..)表示，如r(1 / 2)表示分式 1 / 2
    X = [r(30), r(45), r(60), r(90)]
    Y = [r(0.5), sp.sqrt(2) / 2, sp.sqrt(3) / 2, r(1)]
    piecewise_linear_inter(X, Y)
