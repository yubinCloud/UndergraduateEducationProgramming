"""
利用切比雪夫多项式求最佳一致逼近多项式
"""

import math
import sympy as sp
from sympy.abc import t, x
from scipy.interpolate import lagrange

def Chebyshev_zeropoints(n):
    """
    求切比雪夫多项式 Tn 在[-1 , 1]上的n个零点
    :param n:
    :return: 有n个零点组成的列表
    """
    res = [math.cos((2 * k - 1) / (2 * n) * math.pi) for k in range(1, n + 1)]
    return res


def best_uniform_approximation(f, domain, index):
    """
    求最佳一致逼近多项式
    :param f: 关于x的原函数表达式，x为 sympy.abc.x
    :param domain: 定义域，利用tuple表示
    :param index: 要构造的拉格朗日插值多项式的最高次数
    :return: 插值节点(X, Y)
    """
    zero_points = Chebyshev_zeropoints(index + 1)  # 计算出切比雪夫多项式零点
    # 根据domain将零点转化为f的插值节点
    a, b = domain
    transform = (b + a) / 2 + (b - a) / 2 * t
    X = [transform.xreplace({t: num}) for num in zero_points]
    # 计算Y
    Y = [f.xreplace({x: x_num}) for x_num in X]
    print('X:', X)
    print('Y:', Y)
    return X, Y


if __name__ == '__main__':
    f = sp.exp(x)
    best_uniform_approximation(f, (0, 1), 4)
