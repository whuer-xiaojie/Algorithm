

/*
 实现三个线程同时打印 A B C,每个线程循环10次，要求按照ABCABC...的顺序实现
*/
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

static std::mutex threadMutex;
static std::condition_variable condVar;
static std::uint8_t threadReadFlag;


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

void threadOut(const std::uint8_t a, const std::uint8_t threadIndex)
{
	int count = 0;
	while (count < 10) {
		std::unique_lock<std::mutex> myLock(threadMutex);
		condVar.wait(myLock, [threadIndex] { return threadReadFlag == threadIndex; });
		std::cout << "thread id= " << std::this_thread::get_id() << " :" << a << std::endl;
		threadReadFlag = (threadReadFlag + 1) % 3;
		count++;
		myLock.unlock();
		condVar.notify_all();
	}
}

std::function<bool()> cmp(int a, int b)
{
	return [&a, &b]() { return a > b; };
}

int main(int argc, char **argv)
{
	//std::thread th1(threadA);
	//std::thread th2(threadB);
	//std::thread th3(threadC);

	std::thread th1(threadOut, 'A', 0);
	std::thread th2(threadOut, 'B', 1);
	std::thread th3(threadOut, 'C', 2);

	th1.join();
	th2.join();
	th3.join();

	std::cout << cmp(1, 2)() << std::endl;

	return 0;
}
