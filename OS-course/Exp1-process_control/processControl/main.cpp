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
    std::cout << "my proc serial num: " << procSerialNum << std::endl;              // ��ӡ�������к�
    std::cout << "Current process ID:" << ::GetCurrentProcessId() << std::endl;     // ��ӡ���� ID

    const int PROC_NUM_LIMIT = 25;
    if (procSerialNum < PROC_NUM_LIMIT)
    {
        cloneProcess(++procSerialNum);   // ��¡�ӽ���
    }

    Sleep(500);

    return 0;
}



/// summary ��¡һ���ӽ���
/// Parameters:
///     processSerialNum: �������кţ��������壩
void cloneProcess(const int processSerialNum)
{
    wchar_t szFilename[MAX_PATH];
    GetModuleFileName(nullptr, szFilename, MAX_PATH);

    wchar_t szCmdLine[MAX_PATH];
    wsprintf(szCmdLine, L"%s %d", szFilename, processSerialNum);

    STARTUPINFO si;
    ZeroMemory(reinterpret_cast <void*> (&si), sizeof(si));
    si.cb = sizeof(si);				// �����Ǳ��ṹ�Ĵ�С

    // ���ص������ӽ��̵Ľ�����Ϣ
    PROCESS_INFORMATION pi;

    // ����ͬ���Ŀ�ִ���ļ��������д������̣����������ӽ��̵�����
    const BOOL procHandler = CreateProcess(
        szFilename,					// �������EXE��Ӧ�ó��������
        szCmdLine,					// ��������Ϊ��һ���ӽ��̵ı�־
        nullptr,						// ȱʡ�Ľ��̰�ȫ��
        nullptr,						// ȱʡ���̰߳�ȫ��
        FALSE,						// ���̳о��
        CREATE_NEW_CONSOLE,			// ʹ���µĿ���̨
        nullptr,						// �µĻ���
        nullptr,						// ��ǰĿ¼
        &si,						// ������Ϣ
        &pi);						// ���صĽ�����Ϣ

    if (procHandler)
    {
        std::cout << "create process successfully." << std::endl;
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
}

