/**
 * 进程运行的一个内存
 */

public class Memory {
    private final byte[] mem;

    public Memory(int memSize) {
        mem = new byte[memSize];
    }

    public byte[] getMem() {
        return mem;
    }
}
