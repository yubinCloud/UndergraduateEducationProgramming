import java.util.ArrayList;
import java.util.List;

public class SearchTree {
    private int data;  // 与父节点相连的边上的信息
    private List<SearchTree> children;  // 孩子节点的列表

    // constructor
    public SearchTree(int data) {
        this.data = data;
        this.children = new ArrayList<>();
    }

    // add a child
    public void addChild(SearchTree child) {
        children.add(child);
    }

    // get the children's list
    public List<SearchTree> getChildren() {
        return children;
    }

    // get the data of this node
    public int getData() {
        return data;
    }

    // build a tree based on this root according to N
    public void buildTree(final int N, final int curDepth) {
        if (curDepth == N + 1)
            return;

        for (int i = 0; i < N; i++) {
            SearchTree aTree = new SearchTree(i);
            this.addChild(aTree);
            aTree.buildTree(N, curDepth + 1);
        }
    }
}