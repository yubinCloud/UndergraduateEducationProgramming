/**
 * д����
 * ��ȡ�û������һ��name����������빲���ڴ����
 */

#include <iostream>
#include <string>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>

using std::string;
namespace bip = boost::interprocess;

int main(int argc, char* argv[])
{
	const char* const SHARED_MEMORY_BLOCK_NAME = "MySharedMemory";  // �����ڴ������
	const int SHARED_MEMORY_SIZE = 40;  // �����ڴ��Ĵ�С

	const bip::mapped_region* regionPtr = nullptr;  // �����ڴ���ָ��
	
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

	// ��ȡ�û������name
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


	// �� name д�빲���ڴ���
	void* sharedMemPtr = regionPtr -> get_address();
	std::memcpy(sharedMemPtr, userName.c_str(), userName.size());

	delete regionPtr;

	return 0;
}