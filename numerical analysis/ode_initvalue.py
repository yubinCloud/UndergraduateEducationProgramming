"""
常微分方程（ODE）问题的数值解法

"""
import numpy as np
import sympy as sp
from sympy.abc import x, y


def euler(f, x0, y0, step, max_k):
    """
    Euler公式求解常微分方程的处置问题
    :param f: df = f(x, y)
    :param x0: x初值
    :param y0: y初值
    :param step: 步长
    :param max_k: 最大迭代次数
    :return:
    """
    g = y + step * f  # 由Euler公式得到的迭代方程
    old_x, old_y = x0, y0
    print('第0次迭代： x0 = {}; y0 = {}'.format(x0, y0))
    for i in range(1, max_k + 1):  # i表示当前迭代次数
        new_y = g.limit(x, old_x).limit(y, old_y)
        new_x = old_x + step
        print('第{}次迭代：x{} = {}; y{} = {}'.format(i, i, new_x, i, new_y))
        old_x, old_y = new_x, new_y


if __name__ == '__main__':
    f = y - 2 * x / y
    euler(f, 0, 1, 0.1, 10)
