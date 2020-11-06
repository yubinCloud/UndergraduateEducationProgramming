import java.util.ArrayList;
import java.util.List;

public class Loading {
    private List<Box> boxes;  // 箱子的集合
    private int sumWeight;  // 所有箱子的总重量
    private int firstShipLoad;  // 第一条船的载重
    private int secondShipLoad;  // 第二条船的载重
    private boolean isSolvable;  // 是否有解决方案

    // constructor
    public Loading(int[] weights, int load1, int load2) {
        isSolvable = false;
        this.firstShipLoad = load1;
        this.secondShipLoad = load2;
        this.sumWeight = 0;
        this.boxes = new ArrayList<>();
        for (int weight: weights) {
            Box aBox = new Box(weight);
            boxes.add(aBox);
            sumWeight += weight;
        }
        loading();
    }

    // 获取解决方案
    public boolean[] getSolution() {
        if (isSolvable) {
            boolean[] sol = new boolean[boxes.size()];
            for (int i = 0; i < sol.length; i++) {
                sol[i] = boxes.get(i).isLoaded();
            }
            return sol;
        } else {
            return new boolean[0];
        }
    }

    // 回溯算法
    private void loading() {
        boolean[] solution = new boolean[boxes.size()];  // 用来记录解

        int curGap = firstShipLoad;  // 当前空隙
        int bestGap = firstShipLoad;  // 最小空隙
        int iter = 0;  // 当前访问的箱子节点
        do {
            while (iter < boxes.size()) {
                // Judge if we can load it.
                if (boxes.get(iter).getWeight() <= curGap) {
                    // load it
                    curGap -= boxes.get(iter).getWeight();
                    boxes.get(iter).setLoaded(true);
                    ++iter;
                } else {
                    // not to load it
                    boxes.get(iter).setLoaded(false);
                    iter++;
                }
            }
            // update bestGap
            if (curGap < bestGap) {
                recordSolution(solution);  // record the current solution
                bestGap = curGap;
            }
            iter--;
            int[] backtrackRes = backtrack(iter, curGap);  // backtrack
            iter = backtrackRes[0];
            curGap = backtrackRes[1];

            // Judge if the root node is returned
            if (iter == 0) {
                for (int i = 0; i < boxes.size(); i++) {
                    boxes.get(i).setLoaded(solution[i]);
                }
                break;
            }
        } while (true);

        // Judge if the problem is solvable.
        int firstShipWeight = boxes.stream().filter(Box::isLoaded).mapToInt(Box::getWeight).sum();
        isSolvable = (sumWeight - firstShipWeight <= secondShipLoad);
    }

    // 将当前的解决方案记录下来
    private void recordSolution(boolean[] sol) {
        for (int i = 0; i < boxes.size(); i++) {
            sol[i] = boxes.get(i).isLoaded();
        }
    }

    // 向上回溯到上一个被装入的箱子
    private int[] backtrack(int iter, int curGap) {
        while (iter > 0 && !boxes.get(iter).isLoaded()) {
            iter--;
        }
        if (boxes.get(iter).isLoaded()) {
            boxes.get(iter).setLoaded(false);
            curGap += boxes.get(iter).getWeight();
            iter++;
        }
        return new int[]{iter, curGap};
    }


    public static void main(String[] args) {
        int[] weights = {90, 80, 40, 30, 20, 12, 10};
        Loading loading = new Loading(weights, 152, 130);
        boolean[] sol = loading.getSolution();
        for (boolean b: sol)
            System.out.println(b);
    }
}
