import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Map;
import java.util.function.BiConsumer;

/**
 * 用于用户界面操作的shell
 */
public class Shell {

    /**
     * 用来创建一个进程
     * @param processScheduler 进程调度器
     * @param cmdArgs  命令行参数
     */
    private static void createProcHandler(ProcessScheduler processScheduler, String[] cmdArgs) {
        // 获取进程的名称
        if (cmdArgs.length < 2) {
            System.out.println(lackArgsTip());
            return;
        }
        String procName = cmdArgs[1];
        // 获取进程的优先级
        int priority = 0;
        if (cmdArgs.length > 2) {
            try {
                priority = Integer.parseInt(cmdArgs[2]);
            } catch (NumberFormatException e) {
                System.out.println("优先级的值格式不正确");
                return;
            }
        }
        // 创建进程
        try {
            processScheduler.createProcess(procName, priority);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }


    /**
     * 申请资源
     * @param processScheduler 进程调度器
     * @param cmdArgs 命令行参数
     */
    private static void requestResourceHandler(ProcessScheduler processScheduler, String[] cmdArgs) {
        if (cmdArgs.length < 2) {
            System.out.println("缺少资源的RID");
        }
        String rid = cmdArgs[1];
        PCB runningProc = processScheduler.getRunningProcess();
        if (runningProc == null) {
            return;
        }
        // 让进程申请资源
        try {
            processScheduler.letProcRequestResource(runningProc, rid);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }


    /**
     * 关闭一个进程
     * @param processScheduler 进程调度器
     * @param cmdArgs 命令行参数
     */
    private static void killProcHandler(ProcessScheduler processScheduler, String[] cmdArgs) {
        if (cmdArgs.length < 2) {
            System.out.println("缺少进程的PID");
        }
        String pid = cmdArgs[1];
        PCB runningProc = processScheduler.getRunningProcess();
        if (runningProc == null) {
            return;
        }
        // 让进程释放资源
        try {
            processScheduler.destroyProcess(pid);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    /**
     * 释放一个进程的资源
     * @param processScheduler 进程调度器
     * @param cmdArgs 命令行参数
     */
    private static void releaseResourceHandler(ProcessScheduler processScheduler, String[] cmdArgs) {
        if (cmdArgs.length < 2) {
            System.out.println("缺少资源的RID");
        }
        String rid = cmdArgs[1];
        PCB runningProc = processScheduler.getRunningProcess();
        if (runningProc == null) {
            return;
        }
        // 让进程释放资源
        try {
            processScheduler.letProcReleaseResource(runningProc, rid);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    /**
     * 创建一个资源
     * @param processScheduler 调度器
     * @param cmdArgs 命令行参数
     */
    private static void createResourceHandler(ProcessScheduler processScheduler, String[] cmdArgs) {
        if (cmdArgs.length < 2) {
            System.out.println("缺少资源的名称");
        }
        String resourceName = cmdArgs[1];
        processScheduler.createResource(resourceName);
    }

    private static void lookAllProc(ProcessScheduler processScheduler) {
        for (PCB pcb: processScheduler.getPcbs()) {
            System.out.print("*- ");
            System.out.println(pcb);
        }
    }

    private static void lookAllResource(ProcessScheduler processScheduler) {
        for (RCB rcb: processScheduler.getRcbs()) {
            System.out.print("*- ");
            System.out.println(rcb);
        }
    }

    private static void lookAllProcAndResourceHandler(ProcessScheduler processScheduler, String[] cmdArgs) {
        if (cmdArgs.length > 2) {
            String requirePrintType = cmdArgs[1];
            if (requirePrintType.equals("p")) {
                lookAllProc(processScheduler);
            } else {
                lookAllResource(processScheduler);
            }
        } else {
            lookAllProc(processScheduler);
            lookAllResource(processScheduler);
        }
        processScheduler.scheduleProc();
    }

    private static void findResource(ProcessScheduler processScheduler, String[] cmdArgs) {
        if (cmdArgs.length < 2) {
            System.out.println("缺少待查询资源的RID");
            return;
        }
        String rid = cmdArgs[1];
        RCB rcb = processScheduler.getMapRidToRcb().get(rid);
        if (rcb == null) {
            System.out.println("未查询到该资源");
            return;
        }
        PCB resultPcb = null;  // 需要找的PCB
        for (PCB pcb: processScheduler.getPcbs()) {
            if (pcb.getResources().contains(rcb)) {
                resultPcb = pcb;
                break;
            }
        }
        if (resultPcb == null) {
            System.out.println("未查询到该资源");
        } else {
            System.out.printf("Resource \"%s\" are used by \"%s\"%n", rcb.getName(), resultPcb.getName());
        }
    }

    private static final Map<String, BiConsumer<ProcessScheduler, String[]>> cmdToFunc = new HashMap<>() {{
        put("cr", Shell::createProcHandler);
        put("rq", Shell::requestResourceHandler);
        put("kill", Shell::killProcHandler);
        put("rel", Shell::releaseResourceHandler);
        put("crR", Shell::createResourceHandler);
        put("ls", Shell::lookAllProcAndResourceHandler);
        put("fr", Shell::findResource);
    }};


    private static String lackArgsTip() {
        return "Lacking necessary parameters";
    }

    public static void main(String[] args) throws IOException {
        ProcessScheduler processScheduler = ProcessScheduler.getInstance();

        System.out.println("Welcome to process manage program.");
        BufferedReader scanner = new BufferedReader(new InputStreamReader(System.in));

        String cmd;
        while (true) {
            System.out.println("* " + processScheduler.getRunningProcInfo());
            System.out.print("> ");
            cmd = scanner.readLine();  // 读取用户的输入
            // 将输入的命令字符串划分成一系列的单词
            String[] cmdArgs = cmd.split(" ");
            for (int i = 0; i < cmdArgs.length; i++) {
                cmdArgs[i] = cmdArgs[i].strip();
            }
            String mainCmd = cmdArgs[0];  // 主命令
            if (mainCmd.equals("quit"))
                break;
            var func = cmdToFunc.get(mainCmd);
            if (func == null) {
                System.out.println("未找到输入的主命令");
                continue;
            }
            func.accept(processScheduler, cmdArgs);
        }
    }
}
