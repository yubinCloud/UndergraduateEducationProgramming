/*
 * 素因子分解
 */

import java.util.Arrays;
import java.util.List;
import java.util.Objects;
import java.util.stream.IntStream;


public class PrimeFactorDecomposition {
    private final int num;                // 待分解的正整数
    private final Term[] terms;           // 各项的数组

    /**
     * ctor，同时计算出primeFactors和indexes
     * @param num 待分解的正整数
     */
    public PrimeFactorDecomposition(int num) {
        this.num = num;
        List<Integer> primes = Eratosthenes.getPrimes(num);  // 获取不大于num的全部素数

        int[] primeFactors = primes.stream().mapToInt(Integer::intValue).toArray();   // 计算出primeFactors
        int[] indexes = Arrays.stream(primeFactors).map(this::calIndex).toArray();    // 计算出indexes

        int actualSize = indexes.length;

        while (indexes[actualSize - 1] == 0)
            --actualSize;

        terms = new Term[actualSize];
        IntStream.range(0, actualSize).forEach(
                i -> terms[i] = new Term(primeFactors[i], indexes[i]));
    }

    public Term[] getTerms() {
        return terms;
    }

    public int getNum() {
        return num;
    }

    /**
     * 计算num被分解后的素数中prime的次数
     * @param prime 用来分解num的素数
     * @return 对应prime的次数
     */
    private int calIndex(int prime) {
        int tempNum = num;
        int index = 0;
        while (true) {
            if (tempNum % prime == 0) {
                tempNum /= prime;
                ++index;
            } else
                break;
        }
        return index;
    }

    /**
     * 单项类，储存项的系数和项的指数
     */
    static public class Term {
        public int coef;   // 项的系数
        public int index;  // 项的指数

        public Term(int coef, int index) {
            this.coef = coef;
            this.index = index;
        }

        @Override
        public String toString() {
            return String.format("(%d, %d)", coef, index);
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (!(o instanceof Term)) return false;
            Term term = (Term) o;
            return coef == term.coef && index == term.index;
        }

        @Override
        public int hashCode() {
            return Objects.hash(coef, index);
        }

        @Override
        protected Object clone() throws CloneNotSupportedException {
            return super.clone();
        }
    }

    public static void main(String[] args) {
        PrimeFactorDecomposition pfd = new PrimeFactorDecomposition(120);
        System.out.println(Arrays.toString(pfd.getTerms()));
    }
}
