"""
非线性方程的迭代

"""
import sympy as sp
from sympy.abc import x


def nonlinear_equa_iter(f, x0, precision=0.0, max_k=100):
    """
    对一个非线性的迭代方程f赋予x初值x0进行k次迭代
    :param f: 迭代方程 new_x = f(old_x)
    :param x0: x初值
    :param precision: 精度
    :param max_k: 最大迭代次数
    :return: 打印每次迭代的值
    """
    old_x = x0
    print("第{}次迭代, x{} = {}".format(0, 0, x0))
    for i in range(1, max_k + 1):  # i 为当前迭代的次数
        new_x = f.limit(x, old_x)
        print("第{}次迭代, x{} = {}".format(i, i, new_x))
        if new_x - old_x <= precision:
            break
        else:
            old_x = new_x


def newton_iter(f, x0, precision=0.0, max_k=100):
    """
    牛顿迭代法对一个非线性方程f(x) = 0进行k次迭代
    :param f: 方程
    :param x0: 初始值
    :param precision: 精度
    :param max_k: 最大迭代次数
    :return: 打印每次迭代的值
    """
    df = f.diff(x)  # f的一阶导数
    g = x - f / df  # 牛顿迭代公式
    nonlinear_equa_iter(g, x0, precision, max_k)


if __name__ == '__main__':
    f = x * sp.exp(x) - 1
    newton_iter(f, 0.5, 0.0001, 10)
