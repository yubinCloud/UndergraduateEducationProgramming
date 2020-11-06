import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class Graph {
    public Set<Vertex> vertices;  // 顶点集合
    public List<Edge> edges;  // 边的集合

    public Graph() {
        vertices = new HashSet<>();
        edges = new ArrayList<>();
    }

    public Graph(int vexNum) {
        this();
        for (int i = 0; i < vexNum; i++) {
            vertices.add(new Vertex(i));
        }
    }

    public void addEdge(int vex1, int vex2, double weight) {
        edges.add(new Edge(vex1, vex2, weight));
    }
}
