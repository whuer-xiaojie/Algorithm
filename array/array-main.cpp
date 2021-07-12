
#include <iostream>
#include <vector>

/*********************************************/
int maxIncreaseSubArrLen(const std::vector<int> &arr)
{
	int maxCount = 0;
	std::vector<int> countVec(arr.size(), 1);

	for (int i = 1; i < arr.size(); i++) {
		for (int j = 0; j < i; j++) {
			if ((arr[i] > arr[j]) && (countVec[i] < countVec[j] + 1)) {
				countVec[i] = countVec[j] + 1;
			}
		}
		if (countVec[i] > maxCount) {
			maxCount = countVec[i];
		}
	}

	return maxCount;
}

/*********************************************/
int findMaxSumCrossSubArr(const std::vector<int> &arr, const int low, const int mid, const int high)
{
	int leftSum = 0;
	int sum = 0;
	int rightSum = 0;
	for (int i = mid; i >= low; i--) {
		sum += arr[i];
		if (sum > leftSum) {
			leftSum = sum;
		}
	}
	sum = 0;
	for (int i = mid + 1; i <= high; i++) {
		sum += arr[i];
		if (sum > rightSum) {
			rightSum = sum;
		}
	}
	return leftSum + rightSum;
}

int findMaxSumSubArr(const std::vector<int> &arr, const int low, const int high)
{
	if (low >= high) {
		return arr[high];
	}
	const int mid = (low + high) >> 1;
	const int leftSum = findMaxSumSubArr(arr, low, mid);
	const int rightSum = findMaxSumSubArr(arr, mid + 1, high);
	const int crossSum = findMaxSumCrossSubArr(arr, low, mid, high);
	if (leftSum >= rightSum && leftSum >= crossSum) {
		return leftSum;
	} else if (rightSum >= leftSum && rightSum >= crossSum) {
		return rightSum;
	} else {
		return crossSum;
	}
}

int findMaxSumSubArr(const std::vector<int> &arr)
{
	int maxSum = 0;
	int curSum = 0;
	for (int i = 0; i < arr.size(); i++) {
		if (curSum < 0) {
			curSum = arr[i];
		} else {
			curSum += arr[i];
		}
		if (curSum > maxSum) {
			maxSum = curSum;
		}
	}
	return maxSum;
}
/*********************************************/
void testMaxIncreaseSubArrLen(void)
{
	std::vector<int> arr = { 1,7,2,4,5,3,1,2,8,9 };
	std::cout << maxIncreaseSubArrLen(arr) << std::endl;
}

void testFindMaxSumSubArr(void)
{
	std::vector<int> arr = { -1,7,-2,4,5,-3,1,2,-8,-9,2 };
	std::cout << findMaxSumSubArr(arr, 0, arr.size() - 1) << std::endl;
	std::cout << findMaxSumSubArr(arr) << std::endl;

	std::vector<int> arr1 = { -1,7,-2,4,5,3,1,2,-8,-9,2 };
	std::cout << findMaxSumSubArr(arr1, 0, arr1.size() - 1) << std::endl;
	std::cout << findMaxSumSubArr(arr1) << std::endl;

	std::vector<int> arr2 = { -1,-7,-2,4,-5,-3,1,2,8,9,2 };
	std::cout << findMaxSumSubArr(arr2, 0, arr2.size() - 1) << std::endl;
	std::cout << findMaxSumSubArr(arr2) << std::endl;
}
/*********************************************/
int main(int argc, char **argv)
{
	//testMaxIncreaseSubArrLen();
	testFindMaxSumSubArr();
	return 0;
}
