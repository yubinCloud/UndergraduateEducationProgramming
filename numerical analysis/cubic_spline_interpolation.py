"""
三次样条插值

"""
import sympy as sp
from sympy import Rational as r

def solve_h(X):
    """
    求解 h
    :param X: 一系列的x
    :return: 所有h组成的列表
    """
    H = [X[i] - X[i - 1] for i in range(1, len(X))]
    for i in range(len(H)):
        print('h{} = {}'.format(i + 1, H[i]))
    return H


def solve_nu(H):
    """
    求解 μ
    :param H: 一系列H
    :return:
    """
    N = [H[i] / (H[i] + H[i + 1]) for i in range(len(H) - 1)]
    for i in range(len(N)):
        print('μ{} = {}'.format(i + 1, N[i]))
    return N


def solve_lambda(N):
    """
    求解 λ
    :param N: 所有μ
    :return:
    """
    L = [1 - nu for nu in N]
    for i in range(len(L)):
        print('λ{} = {}'.format(i + 1, L[i]))
    return L


def solve_g(X, Y, H):
    """
    求解 g
    :param X:
    :param Y:
    :param H:
    :return:
    """
    G = [6 / (H[i - 1] + H[i]) * ((Y[i + 1] - Y[i]) / (X[i + 1] - X[i]) - (Y[i] - Y[i - 1]) / (X[i] - X[i - 1]))
         for i in range(1 ,len(X) - 1)]
    for i in range(len(G)):
        print('g{} = {}'.format(i + 1, G[i]))
    return G


def solve_M_1(N, L, G, X, Y, dy0, dyn):
    """
    使用第一边界法
    :param N: μ
    :param L: λ
    :param G: g
    :param dy0:
    :param dyn:
    :return:
    """
    g0 = 6 / H[0] * ((Y[1] - Y[0]) / (X[1] - X[0]) - dy0)
    gn = 6 / H[-1] * (dyn - (Y[-1] - Y[-2]) / (X[-1] - X[-2]))
    G.insert(0, g0)
    G.append(gn)
    n = len(G) - 1
    G = sp.Matrix(G)
    A = sp.zeros(n + 1, n + 1)
    for i in range(n + 1):
        A[i, i] = 2
    A[0, 1], A[n, n - 1] = 1, 1
    for i in range(n - 1):
        A[i + 1, i + 2] = L[i]
        A[i + 1, i] = N[i]
    M = sp.symarray('M', n + 1).reshape(n + 1, 1)
    print('A:')
    print(A)
    print('G:')
    print(G)
    print(sp.solve(A * M - G))


def solve_M_2(N, L, G, ddy0, ddyn):
    """
    第二边界法
    :param N:
    :param L:
    :param G:
    :param ddy0:
    :param ddyn:
    :return:
    """
    G[0] -= N[0] * ddy0
    G[-1] -= L[-1] * ddyn
    n = len(G)  # 此处的n等于 题目中 n - 1，即 x的个数 - 2
    G = sp.Matrix(G)
    A = sp.zeros(n, n)
    for i in range(n):
        A[i, i] = 2
    for i in range(n - 1):
        A[i, i + 1] = L[i]
        A[i + 1, i] = N[i + 1]
    M = sp.symarray('M', n).reshape(n, 1)
    print('A:')
    print(A)
    print('G:')
    print(G)
    print('解为：（显示M_0实际表示M_1，一次类推）')
    print(sp.solve(A * M - G))


if __name__ == '__main__':
    X = [27.7, 28, 29, 30]
    Y = [4.1, 4.3, 4.1, 3.0]
    H = solve_h(X)
    N = solve_nu(H)
    L = solve_lambda(N)
    G = solve_g(X, Y, H)
    solve_M_1(N, L, G, X, Y, 3.0, -4.0)
