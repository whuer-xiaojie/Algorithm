#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


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

/*********************************************/
void bubbleSort(std::vector<int> &a)
{
	for (size_t i = 0; i < a.size() - 1; i++) {
		bool changed = false;
		for (size_t j = 0; j < a.size() - 1 - i; j++) {
			if (a[j] > a[j + 1]) {
				swapNum(a[j], a[j + 1]);
				changed = true;
			}
		}
		if (!changed)
			break;
	}
}

/*********************************************/
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

/*********************************************/
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

/*********************************************/
void merge(std::vector<int>& arr, int l1, int r1, int l2, int r2)
{
	int i = l1;
	int j = l2;
	std::vector<int> temp;
	while (i <= r1 && j <= r2) {
		if (arr[i] < arr[j]) {
			temp.push_back(arr[i++]);
		} else {
			temp.push_back(arr[j++]);
		}
	}

	while (i <= r1) {
		temp.push_back(arr[i++]);
	}

	while (j <= r2) {
		temp.push_back(arr[j++]);
	}

	for (size_t i = 0; i < temp.size(); i++) {
		arr[l1 + i] = temp[i];
	}
}

void mergeSort(std::vector<int>& arr, int start, int end)
{
	if (start < end) {
		int mid = (start + end) >> 1;
		mergeSort(arr, start, mid);
		mergeSort(arr, mid + 1, end);
		merge(arr, start, mid, mid + 1, end);
	}
}

/*********************************************/
void heapSort(std::vector<int>& arr)
{
	std::make_heap(arr.begin(), arr.end());
	printVector(arr, "after make heap:");
	std::sort_heap(arr.begin(), arr.end());
}

void max_heapify(int arr[], int start, int end)
{
	//�������ڵ�ָ����ӽڵ�ָ��
	int dad = start;
	int son = dad * 2 + 1;
	while (son <= end) { //���ӽڵ�ָ���ڷ�Χ�ڲ����Ƚ�
		if (son + 1 <= end && arr[son] < arr[son + 1]) //�ȱȽ������ӽڵ��С��ѡ������
			son++;
		if (arr[dad] > arr[son]) //������ڵ�����ӽڵ���������ϣ�ֱ����������
			return;
		else { //���򽻻����������ټ����ӽڵ����ڵ�Ƚ�
			swapNum(arr[dad], arr[son]);
			dad = son;
			son = dad * 2 + 1;
		}
	}
}
void heap_sort(int arr[], int len)
{
	int i;
	//��ʼ����i�����һ�����ڵ㿪ʼ����
	for (i = len / 2 - 1; i >= 0; i--)
		max_heapify(arr, i, len - 1);
	//�Ƚ���һ��Ԫ�غ����ź�Ԫ��ǰһλ���������ٴ��µ�����ֱ���������
	for (i = len - 1; i > 0; i--) {
		swapNum(arr[0], arr[i]);
		max_heapify(arr, 0, i - 1);
	}
}
/*********************************************/
int main(int argc, char **argv)
{
	std::vector<int> arr = { 0,1,1,2,5,4,3,9,8,6,7 };

	//printVector(arr, "Before bubble sort:");
	//bubbleSort(arr);
	//printVector(arr, "After buble sort");

	//printVector(arr, "Before insert sort:");
	//insertSort(arr);
	//printVector(arr, "After insert sort");

	//printVector(arr, "Before quick sort:");
	//quickSort(arr, 0, arr.size() - 1);
	//printVector(arr, "After quick sort");

	//printVector(arr, "Before quick sort:");
	//mergeSort(arr, 0, arr.size() - 1);
	//printVector(arr, "After quick sort");

	printVector(arr, "Before heap sort:");
	heapSort(arr);
	printVector(arr, "After heap sort");

	return 0;
}

