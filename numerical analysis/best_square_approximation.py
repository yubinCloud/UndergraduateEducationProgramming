"""
最佳平方逼近

"""
import func_obj as fo
import sympy as sp


def best_square_approximation(f, domain, num_base_funcs, weight_func=fo.x_0):
    """
    最佳平方逼近
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
            H[i, j] = inner_product_func(fo.x_n(i), fo.x_n(j), domain, weight_func)
    D = sp.Matrix.zeros(n, 1)
    for i in range(n):
        D[i, 0] = inner_product_func(f, fo.x_n(i), domain, weight_func)
    X = sp.symarray('x', n).reshape(n, 1)
    print('H:', H)
    print('D:', D)
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
    x, y = sp.symbols('x y')
    func = lambda k: func1(k) * func2(k) * weight_func(k)
    return sp.integrate(func(x), (x, *domain))
