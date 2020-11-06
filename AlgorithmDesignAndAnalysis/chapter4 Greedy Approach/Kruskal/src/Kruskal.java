import java.util.Comparator;

public class Kruskal {
    private Graph graph;
    private Graph sol;

    public Kruskal(Graph graph) {
        this.graph = graph;
        sol = new Graph();
        kruskal();
    }

    public Graph getSol() {
        return sol;
    }

    /*
    Kruskal算法
     */
    private void kruskal() {
        graph.edges.sort(Comparator.comparingDouble(Edge::getWeight));  // 权按照由小到大排序
        int vexNum = graph.vertices.size();
        for(Edge edge: graph.edges) {
            if(sol.edges.size() == vexNum - 1)
                break;
            if(isCrossEdge(edge))
        }
    }

    /*
    判断一条边是否为跨边
     */
    private boolean isCrossEdge(Edge edge) {
        return true;
    }
}
