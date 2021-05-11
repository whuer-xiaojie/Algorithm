#include <iostream>
#include <string>

const std::uint32_t MAX_H = 1000000000;

static std::int32_t find(const std::int32_t *arr, const std::int32_t len)
{
	int resCount = 0;
	for (int i = 0; i < len; i++) {
		std::int32_t count = 0;
		std::double_t leftK = MAX_H;
		for (int left = i - 1; left >= 0; left--) {
			std::double_t lk = ((std::double_t)(arr[i] - arr[left])) / (i - left);
			if (lk < leftK) {
				leftK = lk;
				count++;
			}
		}
		std::double_t rightK = MAX_H;
		for (int right = i + 1; right < len; right++) {
			std::double_t rk = ((std::double_t)(arr[i] - arr[right])) / (right - i);
			if (rk < rightK) {
				rightK = rk;
				count++;
			}
		}
		if (resCount < count) {
			resCount = count;
		}
	}
	return resCount;
}

int main(int argc, char**argv)
{
	std::int32_t N; 
	std::cin >> N;
	std::int32_t *inputArr = new std::int32_t[N];
	for (int i = 0; i < N; i++) {
		std::cin >> inputArr[i];
	}
	/*
	std::int32_t N = 50;
	std::int32_t inputArr[50] = {
		28245910, 24373808, 24227271, 177661840 ,89752077,
		7034502 ,14048463 ,47728590,162154837 ,117649003,
		17118127 ,49050164, 38094014,115654962 ,2809921,
		3643075, 154611592, 186705144, 20184302, 18629682,
		181259776 ,15584493 ,92508680, 9206447, 30830417 ,
		207727851, 117996845, 69304158,42505775 ,68503901,
		2211738 ,16177170, 2758269, 83082946, 30914114,
		182454573 ,73942300,57261444, 98527746, 18637564,
		14790782 ,7602301, 108545391, 15387349,64632831,
		8690880 ,218034287, 148358518 ,3931713 ,72424424
	};

	std::int32_t N = 17;
	std::int32_t inputArr[17] = {
		1, 2, 3, 1000000000, 1, 1 ,1, 1 ,100, 500000000, 499999999, 1, 1 ,1, 1 ,1 ,1
	};
	*/

	std::int32_t count = find(inputArr, N);
	std::cout << count << std::endl;

	return 0;

}
