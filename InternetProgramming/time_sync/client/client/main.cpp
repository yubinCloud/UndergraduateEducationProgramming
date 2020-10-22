#include <cstdio>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib") //���붯̬���ӿ�
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1


constexpr auto MAX_LINE = 4096l;             //���ջ���������
constexpr auto SEVER_PORT = 13131;          //ʱ��ͬ���������˿ں�
constexpr auto SERVER_IP = "127.0.0.1";     // ������ip��ַ


int main()
{
    char recvData[MAX_LINE + 1];

    // ��ʼ��Windows Sockets DLL,Э��汾��
    WORD wVersion = MAKEWORD(2, 2);
    WSADATA wsaData;
    int res = WSAStartup(wVersion, &wsaData);
    if (res != 0)
    {
        printf("%d  WSAStartup Error!\n", WSAGetLastError());
        return -1;
    }
    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
    {
        printf("Version Error!\n");
        WSACleanup();
        return -1;
    }

    // ���õ�ַ
    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;                        // ����ipЭ��
    server_addr.sin_addr.S_un.S_addr = inet_addr(SERVER_IP); //����ip
    server_addr.sin_port = htons(SEVER_PORT);                //���ö˿�

    //������ʽ�׽���
    SOCKET sock_conn = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_conn == INVALID_SOCKET)
    {
        printf("%d  Socket Error!\n", WSAGetLastError());
        WSACleanup();
        return -1;
    }

    // �������ӷ�����
    res = connect(sock_conn, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr));
    if (res == SOCKET_ERROR)
    {
        printf("%d Connect Error!\n", WSAGetLastError());
        closesocket(sock_conn);
        WSACleanup();
        return -1;
    }

    // ��ս��ջ����� ׼����������
    memset(recvData, 0, sizeof(recvData));
    printf("Recv Data Is:");

    do
    {
        // ��������
        res = recv(sock_conn, recvData, MAX_LINE, 0);
        if (res > 0)
        {
            printf("%s\n", recvData);
        }
        else
        {
            if (res == 0)
            {
                printf("Server is closed!\n");
            }
            else
            {
                printf("%d Recv Error!\n", WSAGetLastError());
            }
        }
    } while (res > 0);

    // ������ �Ͽ����� �ͷ�DLL
    closesocket(sock_conn);
    WSACleanup();
    return 0;
}