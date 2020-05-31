"""
牛顿-柯特思公式

"""
import sympy as sp


def r(num):
    """
    将num转化成sp.Rational(num)
    """
    return sp.Rational(num)


# 柯特思系数表
cotes_coef_tb = [
    [r(1 / 2), r(1 / 2)],
    [r(1 / 6), r(2 / 3), r(1 / 6)],
    [r(1 / 8), r(3 / 8), r(3 / 8), r(1 / 8)],
    [r(7 / 90), r(16 / 45), r(2 / 15), r(16 / 45), r(7 / 90)],
    [r(19 / 288), r(25 / 96), r(25 / 144), r(25 / 144), r(25 / 96), r(19 / 288)],
    [r(41 / 840), r(9 / 35), r(9 / 280), r(34 / 105), r(9 / 280), r(9 / 35), r(41 / 840)]
]


def newton_cotes(f, x, interval, n):
    """
    Newton-Cotes公式
    :param f: 原函数
    :param x: 变量
    :param interval: 积分区间
    :param n: 将区间分成n段
    :return:  近似的积分值
    """
    bottom, top = interval  # 积分区间的上下限
    step = sp.Rational((top - bottom) / n)  # 步长
    X = [bottom + step * k for k in range(n + 1)]  # 等距节点
    res = 0
    for k in range(n + 1):
        res += cotes_coef_tb[n - 1][k] * f.limit(x, X[k])
    res *= top - bottom
    return res


if __name__ == '__main__':
    from sympy.abc import x
    f = sp.sqrt(x)
    res = newton_cotes(f, x, (sp.Rational(1 / 2), 1), 4)
    print(float(res))
