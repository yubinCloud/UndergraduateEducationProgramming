/*
求最大公因数和最小公倍数
 */

import java.util.Arrays;

public class GcdAndLcm {
    private final int num1;
    private final int num2;
    private int gcd;  // 最大公因数
    private int lcm;  // 最小公倍数
    private boolean hasSolved;  // 标志问题已求解

    /**
     * 初始化对象
     * @param num1 第一个数
     * @param num2 第二个数
     */
    public GcdAndLcm(int num1, int num2) {
        this.num1 = num1;
        this.num2 = num2;
        hasSolved = false;
        gcd = 1;
        lcm = 1;
    }

    public int getGcd() {
        if (!hasSolved)
            calGcdAndLcm();
        return gcd;
    }

    public int getLcm() {
        if (!hasSolved)
            calGcdAndLcm();
        return lcm;
    }

    /**
     * 计算gcd和lcm
     */
    private void calGcdAndLcm() {
        // 对num1和num2进行分解因子
        PrimeFactorDecomposition.Term[] terms1 = new PrimeFactorDecomposition(num1).getTerms();
        PrimeFactorDecomposition.Term[] terms2 = new PrimeFactorDecomposition(num2).getTerms();

        // 使terms1的长度不大于terms2
        if (terms1.length > terms2.length) {
            PrimeFactorDecomposition.Term[] temp = terms2;
            terms2 = terms1;
            terms1 = temp;
        }

        int[] minIndexes = new int[terms2.length];
        int[] maxIndexes = Arrays.stream(terms2).mapToInt(term -> term.index).toArray();

        for (int i = 0; i < terms1.length; ++i) {
            if (terms1[i].index > terms2[i].index) {
                maxIndexes[i] = terms1[i].index;
                minIndexes[i] = terms2[i].index;
            }
            else
                minIndexes[i] = terms1[i].index;
        }

        for (int i = 0; i < terms2.length; i++) {
            gcd *= (int) Math.pow(terms2[i].coef, minIndexes[i]);
            lcm *= (int) Math.pow(terms2[i].coef, maxIndexes[i]);
        }

        this.hasSolved = true;
    }


    static public void main(String[] args) {
        GcdAndLcm gcdAndLcm = new GcdAndLcm(12, 16);
        System.out.println(gcdAndLcm.getGcd());
        System.out.println(gcdAndLcm.getLcm());
    }
}
