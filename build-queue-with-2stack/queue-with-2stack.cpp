
/*
*使用两个栈实现队列
*/
#include <iostream>;
#include <stack>;

static std::stack<int> stack1;
static std::stack<int> stack2;
static std::size_t queue_size = 0;


static void push(int node)
{
	stack1.push(node);
	queue_size++;
}

static int pop()
{
	if (!stack1.empty()) {
		while (!stack1.empty()) {
			stack2.push(stack1.top());
			stack1.pop();
		}
	}
	if (!stack2.empty()) {
		int node = stack2.top();
		queue_size--;
		stack2.pop();
		return node;
	}
	return -1;
}

int main(int argc, char **argv)
{
	int pushNum;
	int temp;
	std::cout << "Please input queue size: " << std::endl;
	std::cin >> pushNum;

	std::cout << "Please input queue member: " << std::endl;
	for (int i = 0; i < pushNum; i++) {
		std::cin >> temp;
		push(temp);
	}
	
	std::cout << "pop queue: " << std::endl;
	for (int i = 0; i < pushNum; i++) {
		std::cout << pop() << " ";
	}
	std::cout << std::endl;
	return 0;
}
