//: object/Box.java

/** A box class
 */
public class Box {
    private int seqNumber;  // 箱子序号
    private int weight;  // 货箱的重量
    private boolean isLoaded;  // 是否装入

    private static int curSeqNum = 0;

    public Box(int weight)
    {
        this.seqNumber = curSeqNum++;
        this.weight = weight;
        this.isLoaded = false;
    }

    public int getSeqNumber() {
        return seqNumber;
    }

    public int getWeight() {
        return weight;
    }

    public boolean isLoaded() {
        return isLoaded;
    }

    public void setLoaded(boolean loaded) {
        isLoaded = loaded;
    }
}
