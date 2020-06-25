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
    step = (top - bottom) / n  # 步长
    X = [bottom + step * k for k in range(n + 1)]  # 等距节点
    print(X)
    # 计算结果
    A = 2 * sum([f.limit(x, x_num) for x_num in X[1:-1]])
    print(A)
    res = A
    B = f.limit(x, bottom) + f.limit(x, top)
    print(B)
    res += B
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
    bottom, top = interval  # 积分上下限
    step = (top - bottom) / n  # 步长
    X1 = [bottom + step * k for k in range(n + 1)]  # 等距节点
    half_step = step / 2
    X2 = [x_num + half_step for x_num in X1[: -1]]  # 每两个等距节点的中点构成的一维向量
    # 计算结果
    res = 4 * sum([f.limit(x, x_num) for x_num in X2])
    print("T0:")
    print(res)
    T = 2 * sum([f.limit(x, x_num) for x_num in X1])
    print('T1:')
    print(T)
    res += T
    T = f.limit(x, bottom) + f.limit(x, top)
    print("T2")
    print(T)
    res += T
    res *= step / 6
    return res


def compound_cotes(f, x, interval, n):
    """
    复合柯特斯公式
    :param f: 原函数
    :param x: 变量
    :param interval: 积分区间
    :param n: 将积分区间等分成n段
    :return: 近似的积分值
    """
    bottom, top = interval
    step = (top - bottom) / n  # 步长
    X1 = [bottom + step * k for k in range(n + 1)]  # 等距节点
    half_step = step / 2  # 半步长
    X2 = [x_num + half_step for x_num in X1[: -1]]  # x下标为 k + 1/2 的所有节点
    qtr_step = half_step / 2  # 四分之一步长
    X3 = [x_num + qtr_step for x_num in X1[: -1]]  # x下标为 k + 1/4 的所有节点
    X4 = [x_num + qtr_step for x_num in X2]  # x下标为 k + 3/4 的所有节点
    res = 14 * sum([f.limit(x, x_num) for x_num in X1[1:-1]])
    res += 12 * sum([f.limit(x, x_num) for x_num in X2])
    res += 32 * sum([f.limit(x, x_num) for x_num in X3])
    res += 32 * sum([f.limit(x, x_num) for x_num in X4])
    res += 7 * (f.limit(x, bottom) + f.limit(x, top))
    res *= step / 90
    return res


if __name__ == '__main__':
    from sympy.abc import x
    f = x * sp.ln(x ** 2)
    # res1 = compound_trapezoid(f, x, (-1, 1), 10)
    res2 = compound_simpso(f, x, (1, 2), 5)
    # print(f.diff(x).diff(x))
    print(res2)


