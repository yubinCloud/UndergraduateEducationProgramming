import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.UUID;

/**
 * 进程运行所需要的资源
 */
public class RCB {
    private final String rid;  // 资源的id
    private final String name;  // 资源的名称
    private boolean freeStatus;  // 表示是否空闲, true表示空闲
    private final Queue<PCB> waitQueue;  // 等待队列，表示被本资源阻塞的进程链表

    /**
     * 指定了RID的RCB ctor
     * @param rid 资源的rid
     */
    public RCB(String rid, String resourceName) {
        this.rid = rid;
        this.name = resourceName;
        this.freeStatus = true;
        this.waitQueue = new PriorityQueue<>(Comparator.comparingInt(PCB::getPriority));
    }

    /**
     * 不指定RID的RCB ctor
     */
    public RCB(String rid) {
        this(rid, rid);
    }

    /**
     * 不指定RID和name的RCB ctor
     */
    public RCB() {
        this(UUID.randomUUID().toString());
    }

    public String getRid() {
        return rid;
    }

    public String getName() {
        return name;
    }

    public Queue<PCB> getWaitQueue() {
        return waitQueue;
    }

    public boolean isFree() {
        return freeStatus;
    }

    public void setFreeStatus(boolean free) {
        freeStatus = free;
    }

    @Override
    public String toString() {
        return String.format("Resource[name: %s, isFree: %b, rid: %s]", name, freeStatus, rid);
    }

    public PCB pollPcbTableFromQueue() {
        if (waitQueue.isEmpty())
            return null;
        return waitQueue.poll();
    }

    public void addPcbIntoQueue(PCB pcb) {
        if (pcb == null)
            return;
        waitQueue.add(pcb);
    }
}
