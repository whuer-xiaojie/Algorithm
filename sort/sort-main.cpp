#include <iostream>
#include <vector>
#include <string>


void swapNum(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

void printVector(const std::vector<int> &a, const std::string &str)
{
	std::cout << str << std::endl;
	for (size_t i = 0; i < a.size(); i++) {
		std::cout << " a[" << i << "]=" << a[i];
	}
	std::cout << std::endl;
}


void bubbleSort(std::vector<int> &a)
{
	for (size_t i = 0; i < a.size() - 1; i++) {
		for (size_t j = 0; j < a.size() - 1 - i; j++) {
			if (a[j] > a[j + 1]) {
				swapNum(a[j], a[j + 1]);
			}
		}
	}
}

void insertSort(std::vector<int> &a)
{
	for (size_t i = 1; i < a.size(); i++) {
		int temp = a[i];
		int j = i - 1;
		while (j >= 0 && a[j] > temp) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = temp;
	}
}

int partition(std::vector<int>& a, int left, int right)
{
	if (left < 0 || right >= a.size()) {
		return -1;
	}
	int key = a[left];
	while (left < right) {
		while (left < right && a[right] >= key) {
			right--;
		}
		a[left] = a[right];
		while (left < right && a[left] <= key) {
			left++;
		}
		a[right] = a[left];
	}
	a[left] = key;
	return left;
}

void quickSort(std::vector<int>& a, int left, int right)
{
	if (left >= right) {
		return;
	}

	int index = partition(a, left, right);
	quickSort(a, left, index - 1);
	quickSort(a, index + 1, right);
}

int main(int argc, char **argv)
{
	std::vector<int> arr = { 0,1,2,5,4,3,9,8,6,7 };

	//printVector(a, "Before bubble sort:");
	//bubbleSort(a);
	//printVector(a, "After buble sort");

	//printVector(a, "Before insert sort:");
	//insertSort(a);
	//printVector(a, "After insert sort");

	printVector(arr, "Before quick sort:");
	quickSort(arr, 0, arr.size() - 1);
	printVector(arr, "After quick sort");

	return 0;
}

