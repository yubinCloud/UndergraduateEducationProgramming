"""
包含各常见函数对象
"""

import math

# x的n次方
x_0 = lambda x: 1
x_1 = lambda x: x
x_2 = lambda x: pow(x, 2)
x_3 = lambda x: pow(x, 3)
x_4 = lambda x: pow(x, 4)
x_5 = lambda x: pow(x, 5)
x_6 = lambda x: pow(x, 6)


def x_n(n):
    """
    返回一个计算x的n次方的函数对象
    :param n: 次方数
    :return: 计算x的n次方的函数对象
    """
    return lambda x: pow(x, n)


# 常见的三角函数对象
sin = math.sin
cos = math.cos
tan = math.tan


