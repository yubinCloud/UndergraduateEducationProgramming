import java.util.Objects;

/*
无向图的边
 */
public class Edge {
    private int headVexId;  // 头顶点id
    private int tailVexId;  // 尾顶点id
    private double weight;  // 权重

    public Edge(int headVexId, int tailVexId) {
        this.headVexId = headVexId;
        this.tailVexId = tailVexId;
    }

    public Edge(int headVexId, int tailVexId, double weight) {
        this(headVexId, tailVexId);
        this.weight = weight;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Edge)) return false;
        Edge edge = (Edge) o;
        return (headVexId == edge.headVexId && tailVexId == edge.tailVexId) ||
                (headVexId == edge.tailVexId && tailVexId == edge.headVexId);
    }

    @Override
    public int hashCode() {
        return Objects.hash(headVexId) + Objects.hash(tailVexId);
    }

    public double getWeight() {
        return weight;
    }

    public void setWeight(double weight) {
        this.weight = weight;
    }

    public int getHeadVexId() {
        return headVexId;
    }

    public int getTailVexId() {
        return tailVexId;
    }
}
