**1.1** **背景知识**

  Windows 所创建的每个进程都从调用CreateProcess() API函数开始，该函数的任务是在对象管理器子系统内初始化进程对象。每一进程都以调用ExitProcess()或TerminateProcess() API函数终止。通常应用程序的框架负责调用ExitProcess()函数，对于C++运行库来说，这一调用发生在应用程序的main()函数返回之后。

   \1. 创建进程

   CreateProcess()调用的核心参数是可执行文件运行时的文件名及其命令行。表1-1详细地列出了每个参数的类型和名称。

**表1-1** **实验记录**表

| 参数名称                                    | 使用目的                                                     |
| ------------------------------------------- | ------------------------------------------------------------ |
| LPCTSTR lpApplivationNAME                   | 全部或部分地指明包括可执行代码的EXE文件的文件名              |
| LPCTSTR lpCommandLine                       | 向可执行文件发送的参数                                       |
| LPSECURIITY_ATTRIBUTES  lpProcessAttributes | 返回进程句柄的安全属性，主要指明这一句柄是否应该由其他子进程所继承。 |
| LPSECURIITY_ATTRIBUTES  lpThreadAttributes  | 返回进程的主线程的句柄的安全属性                             |
| BOOL bInheritHandle                         | 一种标志，告诉系统允许新进程继承创建者进程的句柄             |
| DWORD dwCreationFlage                       | 特殊的创建标志（如CREATE_SUSPENDED）的位标记                 |
| LPVOID lpEnvironment                        | 向新进程发送的一套环境变量；如为null值则发送调用者环境       |
| LPCTSTR lpCurrentDirectory                  | 新进程的启动目录                                             |
| STARTUPINFO lpStartupInfo                   | STARTUPINFO结构，包括新进程的输入和输出配置的详情            |
| LPPROCESS_INFORMATION lpProcessInformation  | 调用的结果块；发送新应用程序的进程和主线程的句柄和ID         |

 

  可以指定第一个参数，即应用程序的名称，其中包括相对于当前进程的当前目录的全路径或者利用搜索方法找到路径；lpCommandLine参数允许调用者向新应用程序发送数据；接下来的三个参数与进程和它的主线程以及返回的指向该对象的句柄的安全性有关。

   然后是标志参数，用以在dwCreationFlags参数中指明系统应该给予新进程什么行为。经常使用的标志是CREATE_SUSPNDED，告诉主线程立刻暂停。当准备好时，应该使用ResumeThread() API来启动进程。另一个常用的标志是CREATE_NEW_CONSOLE，告诉新进程启动自己的控制台窗口，而不是利用父窗口，这一参数还允许设置进程的优先级，用以向系统指明，相对于系统中所有其他的活动进程来说，给此进程多少CPU时间。

   接着是CreateProcess()函数调用所需要的三个通常使用缺省值的参数，第一个参数是lpEnvironment参数，指明为新进程提供的环境；第二个参数是lpCurrentDirectory,可用于向主创进程发送与缺省目录不同的新进程使用的特殊的当前目录；第三个参数是STARTUPINFO数据结构中所必需的，用于在必要时指明新应用程序的主窗口的外观。

  CreateProcess（）的最后一个参数是用于新进程对象及其主线程的句柄和ID的返回值缓冲区，以PROCESS_INFORMATION结构中返回的句柄调用Close_Handle() API函数是重要的，因为如果不将这些句柄关闭的话，有可能危及主创进程终止之前的任何未释放的资源。

   \2. 正在运行的进程

   如果一个进程程拥有至少一个执行线程，则为正在系统中运行的进程。通常这种进程使用主线程来指示它的存在，当主线程结束时，调用Exitprocess() API函数，通知系统终止它所拥有的所有正在运行、准备运行或正在挂起的其他线程。当进程正在运行时，可以查看它的许多特性，其中少数特性也允许加以修改。

  首先可查看的进程特性是系统进程标识符（PID），可利用GetCurrentProcessId() API函数来查看，与GetCurrentProcess()相似，对该函数的调用不能失败，但返回的PID在整个系统中都可使用，其他可显示当前进程信息的API函数还有GetStartInfo()和GetprocessShutdownParameters(),可给出进程存活期内的配置详情。

  通常，一个进程需要它运行期环境的信息，例如API函数GetModuleFileName()和GetcommandLine(),可以给出CreateProcess()中的参数以启动应用程序。在创建应用程序时可使用的另一个API函数是IsDebuggerPresent()。

  可利用API函数GetGuiResources()来查看进程的GUI资源，此函数既可返回指定进程中的打开的GUI对象的数目，也可返回指定进程中打开的USER对象的数目。进程的其他性能信息可通过GetProcessIoCounters()、GetProcessPriorityBoost（）、GetProcessTimes()和GetProcessWorkingSetSize() API得到，以上这几个API函数都只需要具有PROCESS_QUERY_INFORMATION访问权限的指向所感兴趣进程的句柄。

  另一个可用于进程信息查询的API函数是GetProcessVersion(),此函数只需感兴趣进程的PID（进程标识号）。

  \3. 终止进程

  所有进程都是以调用ExitProcess()或者TerminateProcess()函数结束的，但最好使用前者而不要使用后者，因为进程是在完成了它的所有的关闭“职责”之后以正常的终止方式来调用前者的。而外部进程通常调用后者即突然终止进程的进行，由于关闭时的途径不太正常，有可能引起错误的行为。

  TerminateProcess() API函数只要打开带有PROCESS_TERMINATE访问权的对象，就可以终止进程，并向系统返回指定的代码，这是一种“野蛮”的终止进程的方式，但是有时却是需要的。

  如果开发人员确实有机会来设计“谋杀”（终止别的进程的进程）和“受害”进程（被终止的进程）时，应该创建一个进程间通信的内核对象，如一个互斥程序，这样一来，“受害”进程只在等待或同期性地测试它是否应该终止。

 

**1.2** **实验目的**

 

  1）通过创建进程、观察正在运行的进程和终止进程的程序设计和调试操作，进一步熟悉操作系统的进程概念，理解Windows进程的“一生”。

  2）通过编写和分析实验程序，学习创建进程、观察进程和终止进程的程序设计方法。