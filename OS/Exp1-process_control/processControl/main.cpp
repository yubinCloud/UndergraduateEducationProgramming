#include <iostream>
#include <windows.h>
#include <cstring>

void cloneProcess(const int processSerialNum);


int main(int argc, char* argv[])
{
    int procSerialNum = 0;  //
    if (argc > 1) {
        procSerialNum = atoi(argv[1]);
    }
    std::cout << "my proc serial num: " << procSerialNum << std::endl;              // 打印进程序列号
    std::cout << "Current process ID:" << ::GetCurrentProcessId() << std::endl;     // 打印进程 ID

    const int PROC_NUM_LIMIT = 25;
    if (procSerialNum < PROC_NUM_LIMIT)
    {
        cloneProcess(++procSerialNum);   // 克隆子进程
    }

    Sleep(500);

    return 0;
}



/// summary 克隆一个子进程
/// Parameters:
///     processSerialNum: 进程序列号（自主定义）
void cloneProcess(const int processSerialNum)
{
    wchar_t szFilename[MAX_PATH];
    GetModuleFileName(nullptr, szFilename, MAX_PATH);

    wchar_t szCmdLine[MAX_PATH];
    wsprintf(szCmdLine, L"%s %d", szFilename, processSerialNum);

    STARTUPINFO si;
    ZeroMemory(reinterpret_cast <void*> (&si), sizeof(si));
    si.cb = sizeof(si);				// 必须是本结构的大小

    // 返回的用于子进程的进程信息
    PROCESS_INFORMATION pi;

    // 利用同样的可执行文件和命令行创建进程，并赋于其子进程的性质
    const BOOL procHandler = CreateProcess(
        szFilename,					// 产生这个EXE的应用程序的名称
        szCmdLine,					// 告诉其行为像一个子进程的标志
        nullptr,						// 缺省的进程安全性
        nullptr,						// 缺省的线程安全性
        FALSE,						// 不继承句柄
        CREATE_NEW_CONSOLE,			// 使用新的控制台
        nullptr,						// 新的环境
        nullptr,						// 当前目录
        &si,						// 启动信息
        &pi);						// 返回的进程信息

    if (procHandler)
    {
        std::cout << "create process successfully." << std::endl;
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
}

