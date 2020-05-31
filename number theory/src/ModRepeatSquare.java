/**
 * 模重复平方计算法
 *
 * 问题描述：
 * 在模算数计算中，我们常常要对大整数模m和大整数n，计算bn(mod m).
 * 如果递归计算bn = (bn-1(mod m))·b(mod m)，这种计算较为费事，须作n - 1次乘法。
 * 而使用模平方计算法可以显著降低算法复杂度。
 *
 * 算法描述：
 * 欲求bn(mod m)，设a = 1
 * 1. 先将n转换为二进制，即n = n0 + n12 + n222 + ··· + nk-12k-1
 * 2.从低位到高位对n的二进制表示进行遍历
 * 3.如果nk = 1，则a = a·b (mod m)，b = b2(mod m)；如果nk = 0，则a值保持不变，b = b2(mod m)
 * 4.遍历完成后得到的a值即为所求结果
 */

public class ModRepeatSquare {
    private long b;  // 底数
    private long n;  // 指数
    private long m;  // 模数
    private long result;  // 计算结果

    public ModRepeatSquare(long b, long n, long m) {
        this.b = b;
        this.m = m;
        this.n = n;
        this.result = -1L;
    }

    public long getResult() {
        if(result == -1L) {
            modRepeatSquare();
        }
        return result;
    }

    private void modRepeatSquare() {
        // 将n转化为二进制表示
        String binaryOfN = new StringBuilder(Long.toBinaryString(n)).reverse().toString();
        int k = binaryOfN.length();  // 二进制表示的长度

        long a = 1;  // a初始值

        for(int i = 0; i < k; i++) {
            // 计算 a = a * pow(b, n(i)) % m , 其中n(i)属于{0, 1}
            if(binaryOfN.charAt(i) == '1')
                a = (a * b) % m;
            // 更新b(i) = pow(b(i-1), 2)
            if(i != k-1)
                b = (b * b) % m;
        }
        result = a;
    }

    public static void main(String[] args) {
        ModRepeatSquare mrs = new ModRepeatSquare(12996, 227, 37909);
        System.out.println(mrs.getResult());
    }
}
