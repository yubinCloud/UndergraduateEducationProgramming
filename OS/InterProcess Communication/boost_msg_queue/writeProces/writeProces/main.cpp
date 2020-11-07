#include <boost/interprocess/ipc/message_queue.hpp>
#include <iostream>

using namespace boost::interprocess;

int main()
{
    const char* const MSG_QUEUE_NAME = "msg_queue";  // 消息队列的名称
    try {
        //Erase previous message queue
        message_queue::remove(MSG_QUEUE_NAME);

        //Create a message_queue.
        message_queue mq(create_only, MSG_QUEUE_NAME, 100, sizeof(int));

    	
        //Send 100 numbers
        for (int i = 0; i < 100; ++i) {
            mq.send(&i, sizeof(i), 0);
        }
    }
    catch (interprocess_exception& ex) {
        std::cout << ex.what() << std::endl;
        return 1;
    }

    return 0;
}