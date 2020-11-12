import java.util.*;

/**
 * 进程的PCB表
 */
public class PCB {
    private String name;  // 进程的名字
    private final String pid;  // 进程的id
    private int priority;  // 进程的优先级
    private final List<Memory> memoryList;  // 进程的内存链表
    private final Set<RCB> resources;  // 需要使用的其他所有资源
    public ProcessStatus statusCode;  // 进程的状态
    public Queue<PCB> readyQueue;  // 就绪队列
    private RCB rcbPtr;  // 阻塞该进程的资源
    private final PCB parentProc;  // 该进程的父进程
    private final List<PCB> subProcList;  // 该进程的子进程

    /**
     * PCB constructor，模拟创建出一个进程
     * @param name 进程名字
     * @param priority 进程的优先级
     * @param readyQueue 该进程所在的进程队列
     * @param parentProc 父进程
     */
    public PCB(String name, int priority, Queue<PCB> readyQueue, PCB parentProc) {
        this.name = name;
        this.pid = UUID.randomUUID().toString();
        this.priority = priority;
        this.memoryList = new LinkedList<>();
        this.resources = new HashSet<>();
        this.statusCode = ProcessStatus.READY;
        this.readyQueue = readyQueue;
        this.parentProc = parentProc;
        this.subProcList = new ArrayList<>();
    }

    public String getName() {
        return name;
    }

    public String getPid() {
        return pid;
    }

    public int getPriority() {
        return priority;
    }

    public List<Memory> getMemoryList() {
        return memoryList;
    }

    public Set<RCB> getResources() {
        return resources;
    }



    public RCB getRcbPtr() {
        return rcbPtr;
    }

    public PCB getParentProc() {
        return parentProc;
    }

    public List<PCB> getSubProcList() {
        return subProcList;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setPriority(int priority) {
        this.priority = priority;
    }

    public void setRcbPtr(RCB rcb) {
        this.rcbPtr = rcb;
    }

    @Override
    public String toString() {
        return String.format("Process[name: %s, status: %s, pid: %s", name, statusCode, pid);
    }

    /**
     * 申请资源的使用
     * @param rcb 资源的RCB
     * @return 若申请成功则返回 true，若资源不可用导致阻塞则返回 false
     */
    public boolean requestResource(RCB rcb) {
        if (rcb == null)
            throw new IllegalArgumentException();
        // 如果资源可用
        if (rcb.isFree()) {
            rcb.setFreeStatus(false);  // 分配该资源
            this.resources.add(rcb);  // 将该资源加入进程的资源列表中
            return true;
        }
        // 如果资源不可用
        else {
            if (this.statusCode == ProcessStatus.READY)
                this.readyQueue.remove(this);  // 将进程从就绪队列中删除
            this.statusCode = ProcessStatus.BLOCK;  // 将该进程标识为阻塞状态
            this.rcbPtr = rcb;  // 指向所请求资源的RCB
            rcb.getWaitQueue().add(this);  // 插入资源等待队列
            return false;
        }
    }

    /**
     * 释放一个资源 RCB
     * @param rcb 所要释放的资源
     * @param readyQueues 释放该资源成功后，如果有重新获得该资源的进程，便从该参数中选取合适优先级的队列并把就绪的队列放入该队列
     * @return 如果该进程不存在该rcb资源，则返回false，成功释放则返回true
     */
    public boolean releaseResource(RCB rcb, List<Queue<PCB>> readyQueues) {
        if (rcb == null)
            throw new IllegalArgumentException();
        if (!resources.contains(rcb))
            return false;
        resources.remove(rcb);  // 资源列表中移除该资源

        PCB proc = rcb.getWaitQueue().poll();
        if (proc == null) {  // 如果资源等待队列为空
            rcb.setFreeStatus(true);  // 让资源处于空闲状态
        }
        else {
            proc.statusCode = ProcessStatus.READY;  // 设为就绪状态
            proc.readyQueue = readyQueues.get(proc.getPriority());  // proc 的状态队列改为就绪队列
            proc.readyQueue.add(proc);  // 进程 proc 插入就绪队列
            proc.rcbPtr = null;  // 不再请求任何资源
        }
        return true;
    }

    public boolean startRun() {
        if (statusCode != ProcessStatus.READY)
            return false;
        readyQueue.remove(this);
        readyQueue = null;
        statusCode = ProcessStatus.RUNNING;
        return true;
    }

    public boolean stopRun(Queue<PCB> readyQueue) {
        if (statusCode != ProcessStatus.RUNNING)
            return false;
        this.readyQueue = readyQueue;
        readyQueue.add(this);
        statusCode = ProcessStatus.READY;
        return true;
    }


    public void terminate() {
        if (statusCode == ProcessStatus.READY) {
            readyQueue.remove(this);
        }
        else if (statusCode == ProcessStatus.BLOCK) {
            getRcbPtr().getWaitQueue().remove(this);
        }
    }
}
