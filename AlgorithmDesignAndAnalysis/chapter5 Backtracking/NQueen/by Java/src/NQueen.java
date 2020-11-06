import java.util.ArrayList;
import java.util.List;

public class NQueen {
    private int N;  // 表示皇后数
    List<List<Integer>> sols;  // 全部可行解的集合

    // constructor
    public NQueen(int N) {
        this.N = N;
        sols = new ArrayList<>();
        calculateSols();
    }

    // get the all solutions
    public List<List<Integer>> getSols() {
        return sols;
    }

    // calculate all solutions
    private void calculateSols() {
        SearchTree root = new SearchTree(-1); // 根节点
        root.buildTree(N, 0);  // 建造出一棵树
        int[] path = new int[N];
        for (int i = 0; i < N; i++) {
            depthFirstTraversal(root.getChildren().get(i), 1, path);
        }
    }

    // DFS
    private void depthFirstTraversal(SearchTree tree, int curDepth, int[] path) {
        path[curDepth - 1] = tree.getData();
        if (hasAttack(path, curDepth))
            return;
        if (curDepth == N) {
            ArrayList<Integer> sol = new ArrayList<>();
            for (int i: path)
                sol.add(i);
            sols.add(sol);
            return;
        }
        for (int i = 0; i < N; i++) {
            depthFirstTraversal(tree.getChildren().get(i), curDepth + 1, path);
        }
    }

    // Check for queen attacks.
    private boolean hasAttack(final int[] path, int curDepth) {
        int curRow = curDepth - 1;
        int curCol = path[curRow];
        for(int row = 0; row < curRow; row++) {
            int col = path[row];
            if(curCol == col || curCol + curRow == col + row || curCol - curRow == col - row)
                return true;
        }
        return false;
    }

    public static void main(String[] args) {
        NQueen fourQueen = new NQueen(8);
        List<List<Integer>> sol = fourQueen.getSols();
        for (List list: sol)
            System.out.println(list);
    }
}
