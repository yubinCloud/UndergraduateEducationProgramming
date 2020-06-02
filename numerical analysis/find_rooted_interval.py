"""
搜索法寻找有根区间

"""
import sympy as sp
from sympy.abc import x


def find_rooted_interval(f, big_interval, step):
    """
    搜索法寻找有根区间，打印出给定区间每个步长处的函数值
    :param f: 方程f(x) = 0 中的f
    :param big_interval: 总区间
    :param step: 步长
    """
    start, end = big_interval
    while start <= end:
        print("x = {}时, f(x) = {}".format(start, f.limit(x, start)))
        start += step


if __name__ == '__main__':
    f = x**3 - 4.2 * x**2 + 4.88 * x - 1.344
    find_rooted_interval(f, (0, 3), 0.5)