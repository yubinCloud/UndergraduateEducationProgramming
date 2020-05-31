"""
机械求积方法

"""

import sympy as sp


def trapezoid(f, x, interval):
    """
    梯形公式
    :param f: 原函数
    :param x: 未知量
    :param interval: 积分区间
    :return: 近似的积分值
    """
    a, b = interval
    return sp.Rational(1 / 2) * (b - a) * (f.xreplace({x: a}) + f.xreplace({x: b}))


def mid_rectangle(f, x, interval):
    """
    中矩形公式
    :param f: 原函数
    :param x: 未知量
    :param interval: 积分区间
    :return: 近似的积分值
    """
    a, b = interval
    return (b - a) * f.xreplace({x: sp.Rational((a + b) / 2)})


def simpson(f, x, interval):
    """
    辛普生公式
    :param f: 原函数
    :param x: 未知量
    :param interval: 积分区间
    :return: 近似的积分值
    """
    a, b = interval
    return sp.Rational(1 / 6) * (b - a) * \
           (f.xreplace({x: a}) + 4 * f.xreplace({x: sp.Rational((a + b) / 2)}) + f.xreplace({x: b}))


if __name__ == '__main__':
    from sympy.abc import x
    f = sp.exp(x)
    print(float(trapezoid(f, x, (0, 2))))
    print(float(mid_rectangle(f, x, (0, 2))))
    print(float(simpson(f, x, (0, 2))))
