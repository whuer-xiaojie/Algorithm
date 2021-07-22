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
	//建立父节点指标和子节点指标
	int dad = start;
	int son = dad * 2 + 1;
	while (son <= end) { //若子节点指标在范围内才做比较
		if (son + 1 <= end && arr[son] < arr[son + 1]) //先比较两个子节点大小，选择最大的
			son++;
		if (arr[dad] > arr[son]) //如果父节点大于子节点代表调整完毕，直接跳出函数
			return;
		else { //否则交换父子内容再继续子节点和孙节点比较
			swapNum(arr[dad], arr[son]);
			dad = son;
			son = dad * 2 + 1;
		}
	}
}

void heap_sort(int arr[], int len)
{
	int i;
	//初始化，i从最后一个父节点开始调整
	for (i = len / 2 - 1; i >= 0; i--)
		max_heapify(arr, i, len - 1);
	//先将第一个元素和已排好元素前一位做交换，再从新调整，直到排序完毕
	for (i = len - 1; i > 0; i--) {
		swapNum(arr[0], arr[i]);
		max_heapify(arr, 0, i - 1);
	}
}


/*********************************************/
inline int parentIndex(const int i)
{
	return (i - 1) / 2;
}
inline int leftIndex(const int i)
{
	return 2 * i + 1;
}

inline int rightIndex(const int i)
{
	return 2 * i + 2;
}

void max_heapify(std::vector<int>&arr, const int i, const int heapSize)
{
	const int lIndex = leftIndex(i);
	const int rIndex = rightIndex(i);
	int maxIndex = i;
	if (lIndex < heapSize && arr[i] < arr[lIndex]) {
		maxIndex = lIndex;
	}
	if (rIndex < heapSize && arr[maxIndex] < arr[rIndex]) {
		maxIndex = rIndex;
	}

	if (maxIndex != i) {
		swapNum(arr[i], arr[maxIndex]);
		max_heapify(arr, maxIndex, heapSize);
	}
}

void build_max_heap(std::vector<int>&arr)
{
	int heapSize = arr.size();
	for (int i = (heapSize - 1) / 2; i >= 0; i--) {
		max_heapify(arr, i, heapSize);
	}
}

void heap_sort(std::vector<int>&arr)
{
	build_max_heap(arr);
	int heapSize = arr.size();
	for (int i = arr.size() - 1; i > 0; i--) {
		swapNum(arr[0], arr[i]);
		max_heapify(arr, 0, --heapSize);
	}
}

/*********************************************/
std::vector<int> count_sort(const std::vector<int> &arr, const int maxNumOfArr)
{
	std::vector<int> countArr(maxNumOfArr + 1, 0);
	std::vector<int> resArr(arr.size(), 0);

	for (int i = 0; i < arr.size(); i++) {
		countArr[arr[i]]++;
	}

	for (int i = 1; i < countArr.size(); i++) {
		countArr[i] += countArr[i - 1];
	}

	for (int i = arr.size() - 1; i >= 0; i--) {
		resArr[countArr[arr[i]] - 1] = arr[i];
		countArr[arr[i]]--;
	}
	return resArr;
}

/*********************************************/
int getArrayMaxBit(const std::vector<int> &arr)
{
	int maxNum = 0;
	int bits = 1;
	for (int i = 0; i < arr.size(); i++) {
		if (arr[i] > maxNum) {
			maxNum = arr[i];
		}
	}
	while (maxNum >= 10) {
		maxNum /= 10;
		bits++;
	}
	return bits;
}

void radix_sort(std::vector<int> &arr)
{
	int bits = getArrayMaxBit(arr);
	std::vector<int> tempArr(arr);
	int radix = 1;

	for (int i = 0; i < bits; i++) {
		std::vector<int> countArr(10, 0);
		for (int j = 0; j < arr.size(); j++) {
			int k = (arr[j] / radix) % 10;
			countArr[k]++;
		}

		for (int j = 1; j < countArr.size(); j++) {
			countArr[j] += countArr[j - 1];
		}

		for (int j = arr.size() - 1; j >= 0; j--) {
			int k = (arr[j] / radix) % 10;
			tempArr[countArr[k] - 1] = arr[j];
			countArr[k]--;
		}

		for (int j = 0; j < tempArr.size(); j++) {
			arr[j] = tempArr[j];
		}

		radix *= 10;
	}
}
/*********************************************/
void test_radix_sort(void)
{
	std::vector<int> arr = { 0,123,11,134,256,54,425,0,34,956,843,623,72 };
	printVector(arr, "Before radix sort:");
	radix_sort(arr);
	printVector(arr, "After radix sort");
}
/*********************************************/
int main(int argc, char **argv)
{
	std::vector<int> arr = { 0,1,1,1,2,5,4,0,3,9,8,6,7 };

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

	//printVector(arr, "Before heap sort:");
	//heapSort(arr);
	//printVector(arr, "After heap sort");

	//printVector(arr, "Before heap sort:");
	//heap_sort(arr);
	//printVector(arr, "After heap sort");

	printVector(arr, "Before count sort:");
	auto res = count_sort(arr, 9);
	printVector(res, "After count sort");

	test_radix_sort();
	return 0;
}

