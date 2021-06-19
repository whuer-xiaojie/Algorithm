
#include <iostream>

#include <vector>


/**
有一个整数数组，请你根据快速排序的思路，找出数组中第K大的数。

给定一个整数数组a,同时给定它的大小n和要找的K(K在1到n之间)，请返回第K大的数，保证答案存在。

输入
[1,3,5,2,2],5,3

返回值
2
*/
using namespace std;


int partition(vector<int> &a, int left, int right)
{
	int key = a[left];
	while (left < right) {
		while ((left < right) && (a[right] <= key))
			right--;
		a[left] = a[right];
		while (left < right && a[left] >= key)
			left++;
		a[right] = a[left];
	}
	a[left] = key;
	return left;
}

void printVec(const vector<int> &a, int index)
{
	const int temp = a[index];
	cout << "before " << index << endl;
	for (int i = 0; i < a.size() && i <= index; i++) {
		cout << " a[" << i << "]= ";
		if (temp >= a[i]) {
			cout << a[i];
		} else {
			cout << "error";
		}
	}
	cout << endl;

	cout << "after " << index << endl;
	for (int i = index + 1; i < a.size(); i++) {
		cout << " a[" << i << "]= ";
		if (temp <= a[i]) {
			cout << a[i];
		} else {
			cout << "error";
		}
	}
	cout << endl;
}

int quickFind(vector<int> &a, int left, int right, int k)
{

	if (left == right) {
		return -1;
	}

	int index = partition(a, left, right);
	printVec(a, index);
	cout << "index= " << index << " k= " << k << endl;
	cout << "left= " << left << " right= " << right << endl;
	if (index == (k - 1))
		return a[index];
	else if (index < k - 1)
		return quickFind(a, index + 1, right, k);
	else
		return quickFind(a, left, index - 1, k);
	//quickFind(a, index + 1, right, k);
	//quickFind(a, left, index - 1, k);
}

int findKth(vector<int> &a, int n, int K)
{
	// write code here
	return quickFind(a, 0, n - 1, K);
}

int main(int argc, char** argv)
{
	vector<int> a = {
		1332802,1177178,1514891,871248,753214,123866,1615405,328656,1540395,968891,
		1884022,252932,1034406,1455178,821713,486232,860175,1896237,852300,566715,
		1285209,1845742,883142,259266,520911,1844960,218188,1528217,332380,261485,
		1111670,16920,1249664,1199799,1959818,1546744,1904944,51047,1176397,190970,
		48715,349690,673887,1648782,1010556,1165786,937247,986578,798663
	};

	cout << "a.size=" << a.size() << endl;
	cout << findKth(a, 49, 24) << endl;
	return 0;

}