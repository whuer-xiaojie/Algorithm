

/*
	计算24点是一种扑克牌益智游戏，随机抽出4张扑克牌

	通过加(+)，减(-)，乘(*), 除(/)四种运算法则计算得到整数24，

	本问题中，扑克牌通过如下字符或者字符串表示，其中，小写joker表示小王，大写JOKER表示大王：

	3 4 5 6 7 8 9 10 J Q K A 2 joker JOKER

	本程序要求实现：输入4张牌，输出一个算式，算式的结果为24点。

	详细说明：
	1.运算只考虑加减乘除运算，没有阶乘等特殊运算符号，友情提醒，整数除法要当心；
	2.牌面2~10对应的权值为2~10, J、Q、K、A权值分别为为11、12、13、1；
	3.输入4张牌为字符串形式，以一个空格隔开，首尾无空格；如果输入的4张牌中包含大小王，则输出字符串“ERROR”，表示无法运算；
	4.输出的算式格式为4张牌通过 +, - ,* ,/,四个运算符相连，中间无空格，4张牌出现顺序任意，只要结果正确；
	5.输出算式的运算顺序从左至右，不包含括号，如1 + 2 + 3 * 4的结果为24
	6.如果存在多种算式都能计算得出24，只需输出一种即可，如果无法得出24，则输出“NONE”表示无解。

*/
#include <iostream>
#include <string>
#include <vector>

const std::uint8_t MAX_INPUT_STR_COUNT = 4;
const std::uint8_t DIST_NUMBER = 24;
const std::double_t PRECISION_DOUBLE = 1e-6;

std::string inputStrArr[MAX_INPUT_STR_COUNT];
std::double_t inputNumArr[MAX_INPUT_STR_COUNT];
//std::vector<std::string> allExpVec;

static inline bool doubleEqual(const std::double_t a, const std::double_t b)
{
	std::double_t temp = a - b;
	return ((temp <= PRECISION_DOUBLE) && (temp >= (0 - PRECISION_DOUBLE)));
}

static inline bool isDistValue(const std::double_t value)
{
	return doubleEqual(value, DIST_NUMBER);
}

static inline std::double_t getCardNum(const std::string &str)
{
	if (str == "J") {
		return 11.0;
	}
	else if (str == "Q") {
		return 12.0;
	}
	else if (str == "K") {
		return 13.0;
	}
	else if (str == "A") {
		return 1.0;
	}
	else {
		return std::atof(str.c_str());
	}
}

static inline bool isJoker(const std::string &str)
{
	return (str == "joker" || str == "JOKER");
}

static inline std::double_t calNum(const std::double_t a, const std::double_t b, const std::uint8_t op)
{
	if (op == '+') {
		return (a + b);
	}
	else if (op == '-') {
		return (a - b);
	}
	else if (op == '*') {
		return (a * b);
	}
	else {
		return (a / b);
	}
}

static bool findExpress(const std::uint8_t n)
{
	if (n == 1) {
		//std::cout << "n=1 value= " << inputNumArr[0] << " is dist num:"<< isDistValue(inputNumArr[0]) <<std::endl;
		//if (isDistValue(inputNumArr[0])) {
		//	allExpVec.push_back(inputStrArr[0]);
		//}
		return isDistValue(inputNumArr[0]);
	}

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			std::double_t a = inputNumArr[i];
			std::double_t b = inputNumArr[j];
			inputNumArr[j] = inputNumArr[n - 1];

			std::string expa = inputStrArr[i];
			std::string expb = inputStrArr[j];
			inputStrArr[j] = inputStrArr[n - 1];

			inputNumArr[i] = calNum(a, b, '+');
			inputStrArr[i] = expa + "+" + expb;
			if (findExpress(n - 1)) {
				return true;
			}

			inputNumArr[i] = calNum(a, b, '-');
			inputStrArr[i] = expa + "-" + expb;
			if (findExpress(n - 1)) {
				return true;
			}

			inputNumArr[i] = calNum(a, b, '*');
			inputStrArr[i] = expa + "*" + expb;
			if (findExpress(n - 1)) {
				return true;
			}

			if (!doubleEqual(b, 0.0)) {
				inputNumArr[i] = calNum(a, b, '/');
				inputStrArr[i] = expa + "/" + expb;
				if (findExpress(n - 1)) {
					return true;
				}
			}

			inputNumArr[i] = a;
			inputNumArr[j] = b;
			inputStrArr[i] = expa;
			inputStrArr[j] = expb;
			return false;
		}
	}
}

int main(int argc, char **argv)
{

	std::cout << "Please input 4 card's number:" << std::endl;
	for (int i = 0; i < MAX_INPUT_STR_COUNT; i++) {
		std::cin >> inputStrArr[i];
		if (isJoker(inputStrArr[i])) {
			std::cout << "ERROR" << std::endl;
			return -1;
		}
		std::double_t num = getCardNum(inputStrArr[i]);
		if (doubleEqual(num, 0.0)) {
			//throw std::exception("Invalid input card number!");
			std::cout << "ERROR" << std::endl;
			return -1;
		}
		inputNumArr[i] = num;
	}

	bool hasExp = findExpress(MAX_INPUT_STR_COUNT);
	//for (int i = 0; i < allExpVec.size(); i++) {
	//	std::cout << allExpVec[i] << std::endl;
	//}
	if (hasExp) {
		std::cout << inputStrArr[0] << std::endl;
	}
	else {
		std::cout << "None" << std::endl;
	}

	return 0;
}
