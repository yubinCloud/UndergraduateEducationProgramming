import java.util.*;

/**
 * 进程的调度器
 */
public class ProcessScheduler {
    private PCB runningProcess;  // 当前正在运行的进程
    private final List<Queue<PCB>> readyQueues;  // 所有的就绪队列
    private final Map<String, RCB> ridToRcb;  // RID -> RCB
    private final Map<String, PCB> pidToPcb;  // PID -> PCB
    private final Set<RCB> rcbs;  // 存储所有RCB
    private final Set<PCB> pcbs;  // 存储所有PCB
    private final PCB rootProc;  // 根进程



    private ProcessScheduler() {
        readyQueues = new ArrayList<>();
        for (int i = 0; i < 5; i++) {
            readyQueues.add(new LinkedList<>());
        }
        ridToRcb = new HashMap<>();
        pidToPcb = new HashMap<>();
        rcbs = new HashSet<>();
        pcbs = new HashSet<>();

        rootProc = new PCB("init", 0, readyQueues.get(0), null);  // init 根进程
        pcbs.add(rootProc);
        pidToPcb.put(rootProc.getPid(), rootProc);
        rootProc.startRun();
        runningProcess = rootProc;
    }

    private static ProcessScheduler procScheduler = null;

    /**
     * 获取进程调度器的唯一实例
     * @return ProcessScheduler的唯一实例
     */
    public static ProcessScheduler getInstance() {
        if (procScheduler == null)
            procScheduler = new ProcessScheduler();
        return procScheduler;
    }

    public PCB getRunningProcess() {
        return runningProcess;
    }

    /**
     * 获取当前正在运行的进程的一行信息
     * @return 一条提示哪个进程正在运行的信息
     */
    public String getRunningProcInfo() {
        return String.format("Process \"%s\" is running, pid: %s", runningProcess.getName(), runningProcess.getPid());
    }

    public PCB getRootProc() {
        return rootProc;
    }

    public Set<RCB> getRcbs() {
        return rcbs;
    }

    public Set<PCB> getPcbs() {
        return pcbs;
    }

    public Map<String, RCB> getMapRidToRcb() {
        return ridToRcb;
    }

    public Map<String, PCB> getMapPidToPcb() {
        return pidToPcb;
    }

    /**
     * 按照“先来先服务”和优先级“从高到低”的方式调度就绪队列
     * @return 调度前后是否发生正在运行的进程的更换
     */
    public boolean scheduleProc() throws NullPointerException {
        int curRunningProcPriority = runningProcess == null ? 0: runningProcess.getPriority();  // 当前正在运行的进程的优先级
        boolean hasChanged = false;
        for (int i = readyQueues.size() - 1; i >= curRunningProcPriority; i--) {
            if (readyQueues.get(i).isEmpty())
                continue;
            PCB nextProc = readyQueues.get(i).poll();  // 调度下一个要运行的进程
            if (nextProc != runningProcess)
                hasChanged = true;
            // 令 nextProc 开始运行
            if (runningProcess != null)
                runningProcess.stopRun(readyQueues.get(curRunningProcPriority));
            nextProc.startRun();
            runningProcess = nextProc;
            break;
        }
        return hasChanged;
    }

    /**
     * 命令一个进程释放某个资源
     * @param pcb 所命令的进程的PCB
     * @param rcb 所要释放的资源的RCB
     * @return 任务完成后正在运行的PCB
     */
    public PCB letProcReleaseResource(PCB pcb, RCB rcb) {
        if (pcb == null) {
            throw new NullPointerException("Null pcb can't release resource.");
        }
        if (rcb == null) {
            throw new NullPointerException("Pcb can't release null resource.");
        }
        pcb.releaseResource(rcb, readyQueues);
        scheduleProc();
        return runningProcess;
    }

    public PCB letProcReleaseResource(PCB pcb, String rid) {
        RCB rcb = ridToRcb.get(rid);
        if (rcb == null)
            throw new IllegalArgumentException("Don't have this rid.");
        return letProcReleaseResource(pcb, rcb);
    }

    /**
     * 命令一个进程申请一个资源
     * @param pcb 所命令的进程
     * @param rcb 所要申请的资源
     */
    public void letProcRequestResource(PCB pcb, RCB rcb) {
        if (pcb == null) {
            throw new NullPointerException("Null pcb can't request resource.");
        }
        if (rcb == null) {
            throw new NullPointerException("Pcb can't request null resource.");
        }
        boolean reqResult = pcb.requestResource(rcb);  // 申请结果
        if (!reqResult) {
            scheduleProc();
        }
    }

    public void letProcRequestResource(PCB pcb, String rid) {
        RCB rcb = ridToRcb.get(rid);
        if (rcb == null)
            throw new IllegalArgumentException("Don't have this rid.");
        letProcRequestResource(pcb, rcb);
    }

    /**
     * 创建一个进程
     * @param procName 新进程的名字
     * @param priority 新进程的优先级
     * @return 所创建的新进程的PCB
     */
    public PCB createProcess(String procName, int priority) {
        PCB newProc = new PCB(procName, priority, readyQueues.get(priority), runningProcess);  // 创建新PCB
        newProc.readyQueue.add(newProc);  // 加入相应的优先级队列中
        pcbs.add(newProc);  // 使该进程被调度器统一管理
        pidToPcb.put(newProc.getPid(), newProc);  // 实现由pid -> proc 的映射
        scheduleProc();  // 调度器进行一次调度
        return newProc;
    }

    public PCB createProcess(String procName) {
        return createProcess(procName, 0);
    }

    /**
     * 销毁一个进程，调用此函数后应该再将其引用指向null
     * @param pcb 所要销毁的进程的 PCB
     */
    public void destroyProcess(PCB pcb) {
        if (pcb == null)
            return;
        if (pcb == getRootProc()) {
            throw new IllegalArgumentException("The root process is not allowed to terminate.");
        }
        if (pcb == runningProcess) {
            pcb.stopRun(readyQueues.get(pcb.getPriority()));
            runningProcess = null;
        }
        pcb.terminate();
        pcbs.remove(pcb);
        pidToPcb.remove(pcb.getPid());
        scheduleProc();
    }

    public void destroyProcess(String pid) {
        PCB pcb = pidToPcb.get(pid);
        if (pcb == null)
            throw new IllegalArgumentException("Can't find this pid.");
        destroyProcess(pcb);
    }

    /**
     * 创建一个资源
     * @param resourceName 资源名称
     * @return 新创建的 RCB
     */
    public RCB createResource(String resourceName) {
        RCB newRcb = new RCB(UUID.randomUUID().toString(), resourceName);
        rcbs.add(newRcb);
        ridToRcb.put(newRcb.getRid(), newRcb);
        scheduleProc();
        return newRcb;
    }
}
