"""
最佳平方逼近

"""
import sympy as sp
from sympy.abc import x


def best_square_approximation(f, domain, num_base_funcs, weight_func=x ** 0):
    """
    最佳平方逼近
    默认基函数为{1, x, x_2, ...}
    :param f: 原函数
    :param domain: f的定义域
    :param num_base_funcs: 基函数个数
    :param weight_func: 权函数
    :return: 最佳平方逼近多项式
    """
    n = num_base_funcs  # 基函数个数
    H = sp.Matrix.zeros(n, n)
    for i in range(n):
        for j in range(n):
            H[i, j] = inner_product_func(x ** i, x ** j, domain, weight_func)
    D = sp.Matrix.zeros(n, 1)
    for i in range(n):
        D[i, 0] = inner_product_func(f, x ** i, domain, weight_func)
    X = sp.symarray('a', n).reshape(n, 1)
    print('H:')
    sp.pprint(H)
    print('D:')
    sp.pprint(D)
    return sp.solve(H * X - D)


def inner_product_func(func1, func2, domain, weight_func):
    """
    求两个函数的内积
    :param func1: 函数1
    :param func2: 函数2
    :param domain: 定义域
    :param weight_func: 权函数
    :return: 内积的结果
    """
    func = func1 * func2 * weight_func
    return sp.integrate(func, (x, *domain))


if __name__ == '__main__':
    f = sp.sqrt(x)
    a = best_square_approximation(f, (sp.Rational(1 / 4), 1), 2)
    sp.pprint(a)
