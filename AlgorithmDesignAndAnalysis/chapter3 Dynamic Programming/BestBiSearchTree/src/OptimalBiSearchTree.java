import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;

public class OptimalBiSearchTree {
    private ArrayList<Character> datas;  // 数据集
    private ArrayList<Double> probabilities;  // 概率集合
    private ArrayList<ArrayList<Double>> memo; // 备忘录，memo[i][j]记录datas[i...j]的最少平均比较次数
    private ArrayList<ArrayList<Integer>> mark;  // 标记, memo[i][j]表示在求datas[i...j]的最优情况时对应根节点的在datas的下标

    // 构造器
    public OptimalBiSearchTree(ArrayList<Character> datas, ArrayList<Double> probabilities) {
        this.datas = datas;
        this.probabilities = probabilities;
        memo = new ArrayList<>();
        mark = new ArrayList<>();

        for(int i = 0; i < datas.size(); i++)
        {
            memo.add(new ArrayList<>(Collections.nCopies(datas.size(), 0.0)));
            mark.add(new ArrayList<>(Collections.nCopies(datas.size(), 0)));
        }

    }

    // 求 datas[left...right]的对应概率之和（包括各数据节点和两边的空隙）
    private double subProbablitiesSum(final int left, final int right) {
        double res = 0;
        int begin = 2 * left;
        int end = 2 * right + 2;

        for(int i = begin; i <= end; i++)
        {
            res += probabilities.get(i);
        }

        return res;
    }

    // 获取memo[i][j]的值，当越界时返回0，当j=i-1时返回0
    private double getMemo(int i, int j) {
        if(j == i - 1)
            return 0;
        if(i < 0 && j < 0)
            return 0;

        return memo.get(i).get(j);
    }

    // 将memo[i][j]设为value
    private void setMemo(int i, int j, double value) {
        memo.get(i).set(j, value);
    }

    // 获取标记函数mark[i][j]的值
    private int getMark(int i, int j) {
        return mark.get(i).get(j);
    }

    // 将mark[i][j]设为value
    private void setMark(int i, int j, int value) {
        mark.get(i).set(j, value);
    }

    // 计算规模为scale的子问题
    private void calculateScale(int scale) {
        for(int lBorder = 0; lBorder + scale - 1 < datas.size(); lBorder++) {
            int rBorder = lBorder + scale - 1;
            double min = Double.MAX_VALUE;
            // 依次将各点作为根节点计算
            for(int root = lBorder; root <= rBorder; ++root) {
                double temp = getMemo(lBorder, root - 1) + getMemo(root + 1, rBorder);
                if(temp < min) {
                    min = temp;
                    setMark(lBorder, rBorder, root);
                }
            }
            setMemo(lBorder, rBorder, min + subProbablitiesSum(lBorder, rBorder));
        }
    }

    // 将规模由1递增至最大
    private void calculateAllScale() {
        for(int scale = 1; scale <= datas.size(); scale++)
        {
            calculateScale(scale);
        }
    }

    // 获取标记数组
    public ArrayList<ArrayList<Integer>> getMarkArray() {
        return mark;
    }

    public void printResult() {
        calculateAllScale();
        System.out.println("平均比较次数最少为" + getMemo(0, datas.size() - 1));

        ArrayList<ArrayList<Integer>> marks = getMarkArray();

        for(int i = 0; i < marks.size(); i++) {
            for (int j = 0; j < marks.get(i).size(); j++) {
                System.out.print(String.format("mark[%d][%d]: %d  ", i, j, getMark(i, j)));
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        ArrayList<Character> datas = new ArrayList<>(Arrays.asList('A', 'B', 'C', 'D', 'E'));
        ArrayList<Double> probablities = new ArrayList<>(
                Arrays.asList(0.04, 0.1, 0.02, 0.3, 0.02, 0.1, 0.05, 0.2, 0.06, 0.1, 0.01));
        OptimalBiSearchTree tree = new OptimalBiSearchTree(datas, probablities);

        tree.printResult();
    }
}
