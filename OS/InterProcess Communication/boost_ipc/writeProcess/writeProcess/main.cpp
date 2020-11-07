/**
 * 写进程
 * 读取用户输入的一个name，并将其放入共享内存块中
 */

#include <iostream>
#include <string>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>

using std::string;
namespace bip = boost::interprocess;

int main(int argc, char* argv[])
{
	const char* const SHARED_MEMORY_BLOCK_NAME = "MySharedMemory";  // 共享内存的名字
	const int SHARED_MEMORY_SIZE = 40;  // 共享内存块的大小

	const bip::mapped_region* regionPtr = nullptr;  // 共享内存块的指针
	
	try {
		// create a shared memory object.
		bip::shared_memory_object sharedMem(bip::create_only, SHARED_MEMORY_BLOCK_NAME, bip::read_write);

		// setting the size of the shared memory.
		sharedMem.truncate(SHARED_MEMORY_SIZE);

		// map the shared memory to current process
		regionPtr = new bip::mapped_region(sharedMem, bip::read_write);
	}
	catch (bip::interprocess_exception& e) {
		std::cout << e.what() << std::endl;
		return -1;
	}

	// 读取用户输入的name
	std::cout << "Please input your name: (Don't exceed 30 characters)" << std::endl;
	string userName;
	while (true) {
		std::getline(std::cin, userName);
		if (userName.size() > 30) {
			std::cout << "The name which you input has exceeded 30 characters. Please try again: " << std::endl;
			continue;
		}
		else {
			break;
		}
	}


	// 将 name 写入共享内存区
	void* sharedMemPtr = regionPtr -> get_address();
	std::memcpy(sharedMemPtr, userName.c_str(), userName.size());

	delete regionPtr;

	return 0;
}