
#include <iostream>
#include <vector>


int maxIncreaseChildArrLen(const std::vector<int> &arr)
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

void testMaxIncreaseChildArrLen(void)
{
	std::vector<int> arr = { 1,7,2,4,5,3,1,2,8,9 };
	std::cout << maxIncreaseChildArrLen(arr) << std::endl;
}

int main(int argc, char **argv)
{
	testMaxIncreaseChildArrLen();
	return 0;
}
