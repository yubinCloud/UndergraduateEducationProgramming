/*
 * Eratosthenes素数筛选法求素数
 */

import java.util.ArrayList;
import java.util.List;

public class Eratosthenes {
    private final int N;  // 求不超过N的全部素数
    private final int border;  // border = floor(sqrt(N))
    private List<Integer> primeList;  // 计算出的全部素数

    /**
     * 直接获取不大于N的全部素数
     * @param N 范围
     * @return 包含全部不大于N的素数的List， 具体类型为ArrayList
     */
    static public List<Integer> getPrimes(int N) {
        return new Eratosthenes(N).primeList;
    }

    /**
     * ctor
     * @param N 所求范围的最大值
     */
    private Eratosthenes(int N) {
        this.N = N;
        this.border = (int) Math.floor(Math.sqrt(N));
        primeList = new ArrayList<>();
        if (N > 0)
            eratosthenes();
    }

    /**
     * eratosthenes筛选法求出不超过N的全部素数并放入primeList中
     */
    private void eratosthenes() {
        int[] nums = new int[N + 1];
        // 初始化全部数
        for(int i = 0; i <= N; i++) {
            nums[i] = i;
        }
        nums[1] = 0;  // 1不是素数
        int curPrime = 2;  // 当前一轮筛选所用的素数，首位素数为2
        // 将border之内的素数全部遍历一遍并逐轮筛选
        while (curPrime <= border) {
            for (int num = curPrime * 2; num <= N; num += curPrime) {
                nums[num] = 0;
            }
            primeList.add(curPrime);
            curPrime = nextPrime(nums, curPrime);
        }
        // 将筛选后剩下的全部素数挑选出来
        while(curPrime <= N) {
            primeList.add(curPrime);
            curPrime = nextPrime(nums, curPrime);
        }
    }

    /**
     * 求出不大于N的下一个素数
     * @param nums 被筛选的数组
     * @param curPrime  当前的素数
     * @return  nums中相对于curPrime的下一个素数
     */
    private int nextPrime(int[] nums, int curPrime) {
        ++curPrime;
        while(curPrime <= N && nums[curPrime] == 0)
            ++curPrime;
        return curPrime;
    }

    @Override
    public String toString() {
        return String.format("{N = %d, primes = %s}", N, primeList);
    }

    public static void main(String[] args) {
        List<Integer> primes = Eratosthenes.getPrimes(50);
        System.out.println(primes);
    }
}
