"""
复合求积公式

"""

import sympy as sp


def compound_trapezoid(f, x, interval, n):
    """
    复合梯形公式
    :param f: 原函数
    :param x: 变量
    :param interval: 积分区间
    :param n: 对积分区间进行n等分
    :return: 近似的积分值
    """
    bottom, top = interval  # 积分上下限
    step = sp.Rational((top - bottom) / n)  # 步长
    X = [bottom + step * k for k in range(n + 1)]  # 等距节点
    # 计算结果
    res = 0
    for k in range(1, n):
        res += f.limit(x, X[k])
    res *= 2
    res += f.limit(x, bottom) + f.limit(x, top)
    res *= step / 2
    return res


def compound_simpso(f, x, interval, n):
    """
    复合辛普生公式
    :param f: 原函数
    :param x: 变量
    :param interval: 积分区间
    :param n: 对积分区间进行n等分
    :return: 近似的积分值
    """
    pass


if __name__ == '__main__':
    from sympy.abc import x
    f = sp.sin(x) / x
    res = compound_trapezoid(f, x, (0, 1), 8)
    print(float(res))


