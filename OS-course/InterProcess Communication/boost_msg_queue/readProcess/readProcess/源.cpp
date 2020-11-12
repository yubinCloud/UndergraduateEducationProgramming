#include <boost/interprocess/ipc/message_queue.hpp>
#include <iostream>

using namespace boost::interprocess;

int main()
{
    const char* const MSG_QUEUE_NAME = "msg_queue";  // 消息队列的名称
	
    try {
        // Open a message queue.
        message_queue mq(open_only, MSG_QUEUE_NAME);

        unsigned int priority;
        message_queue::size_type recvd_size;

        // Receive 100 numbers
        for (int i = 0; i < 100; ++i) {
            int number;
            mq.receive(&number, sizeof(number), recvd_size, priority);
            if (number != i || recvd_size != sizeof(number))
                return 1;
        }
    }
    catch (interprocess_exception& ex) {
        message_queue::remove(MSG_QUEUE_NAME);
        std::cout << ex.what() << std::endl;
        return 1;
    }
    message_queue::remove(MSG_QUEUE_NAME);
    return 0;
}