import func_obj as fo
import math
from best_square_approximation import best_square_approximation

if __name__ == '__main__':
    a = best_square_approximation(fo.x_n(0.5), (0.25, 1), 2)
    print(a)
