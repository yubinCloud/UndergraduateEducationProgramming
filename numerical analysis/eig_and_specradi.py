"""
求矩阵的特征值和谱半径

"""
import numpy as np
from sympy.abc import lamda


def eig_and_specradi(A):
    """
    求矩阵M的特征值和谱半径
    :param A: 待处理的矩阵
    :return: (特征值, 谱半径)
    """
    # 计算出 Lambda * I - A
    A_ = A.tolist()
    I = np.identity(len(A_))
    print("lambda * I - A：")
    print(lamda * I - A_)
    # 计算出特征值和谱半径
    eigs, _ = np.linalg.eig(A)
    radius = np.max(eigs)
    print("特征值：", eigs)
    print("谱半径：", radius)
    return eigs, radius


if __name__ == '__main__':
    A = np.array([
        [0.1, 1],
        [0.8, -0.1]
    ])
    eigs, r = eig_and_specradi(A)
