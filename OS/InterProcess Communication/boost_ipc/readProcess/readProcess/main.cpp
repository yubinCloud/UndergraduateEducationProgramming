/**
 * 读进程
 * 从共享内存区中读取一个name并打印
 */

#include <string>
#include <iostream>

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>

using std::string;
namespace bip = boost::interprocess;

int main(int argc, char* argv[])
{
	const char* const SHARE_MEMORY_BLOCK_NAME = "MySharedMemory";  // 共享内存块的名字

	const bip::mapped_region* regionPtr = nullptr;
	
	try {
		// opening an existing shared memory object 
		const bip::shared_memory_object sharedMem(bip::open_only, SHARE_MEMORY_BLOCK_NAME, bip::read_only);

		// map shared memory object in current address space
		regionPtr = new bip::mapped_region(sharedMem, bip::read_only);
	}
	catch (bip::interprocess_exception& e) {
		std::cout << e.what() << std::endl;
		return -1;
	}

	const std::string myName(static_cast<char*>(regionPtr->get_address()));
	std::cout << "name:" << myName << std::endl;

	// 删除共享内存池
	const bool isRemoved = bip::shared_memory_object::remove(SHARE_MEMORY_BLOCK_NAME);
	if (isRemoved) {
		std::cout << "Share memory [" << SHARE_MEMORY_BLOCK_NAME << "] removed successfully." << std::endl;
	} else {
		std::cout << "Share memory [" << SHARE_MEMORY_BLOCK_NAME << "] removed fail." << std::endl;
	}
	
	delete regionPtr;
	return 0;
}
