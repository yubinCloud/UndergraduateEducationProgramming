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
    f = (x ** 2 + 1) * (x ** 9 - 9 * x + 7)
    find_rooted_interval(f, (0, 1), 0.2)