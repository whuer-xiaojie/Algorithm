

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex threadMutex;
std::condition_variable condVar;
std::uint8_t threadReadFlag;


void threadA()
{
	int count = 0;
	while (count < 10) {
		std::unique_lock<std::mutex> myLock(threadMutex);
		while (threadReadFlag != 0) {
			condVar.wait(myLock);
		}
		std::cout << __FUNCTION__ << " :A" << std::endl;
		threadReadFlag = 1;
		count++;
		myLock.unlock();
		condVar.notify_all();
	}
}

void threadB()
{
	int count = 0;
	while (count < 10) {
		std::unique_lock<std::mutex> myLock(threadMutex);
		while (threadReadFlag != 1) {
			condVar.wait(myLock);
		}
		std::cout << __FUNCTION__ << " :B" << std::endl;
		threadReadFlag = 2;
		count++;
		myLock.unlock();
		condVar.notify_all();
	}
}

void threadC()
{
	int count = 0;
	while (count < 10) {
		std::unique_lock<std::mutex> myLock(threadMutex);
		while (threadReadFlag != 2) {
			condVar.wait(myLock);
		}
		std::cout << "threadA:" << "C" << std::endl;
		threadReadFlag = 0;
		count++;
		myLock.unlock();
		condVar.notify_all();
	}
}

void threadOut(std::uint8_t a)
{
	std::uint8_t index = a - 'A';
	int count = 0;
	while (count < 10) {
		std::unique_lock<std::mutex> myLock(threadMutex);
		condVar.wait(myLock, [index] { return threadReadFlag == index; });
		std::cout << "thread id= " << std::this_thread::get_id() << " :" << a << std::endl;
		threadReadFlag = (threadReadFlag + 1) % 3;
		count++;
		myLock.unlock();
		condVar.notify_all();
	}
}


int main(int argc, char **argv)
{
	//std::thread th1(threadA);
	//std::thread th2(threadB);
	//std::thread th3(threadC);

	std::thread th1(threadOut, 'A');
	std::thread th2(threadOut, 'B');
	std::thread th3(threadOut, 'C');

	th1.join();
	th2.join();
	th3.join();

	return 0;
}