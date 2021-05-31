
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

/***************************************************************************/
bool isSignedStr(const string &str)
{
	return ((str[0] == '-') || (str[0] == '+'));
}

bool isNumberChar(const char c)
{
	return ((c >= '0') && (c <= '9'));
}

bool isValidNumberStr(const string &str)
{
	size_t numStartIndex = 0;
	if (str.empty()) {
		return false;
	}

	if (isSignedStr(str)) {
		numStartIndex = 1;
	}

	if (str.length() <= numStartIndex) {
		return false;
	}

	for (size_t i = numStartIndex; i < str.length(); i++) {
		if (!isNumberChar(str[i])) {
			return false;
		}
	}

	return true;
}

string getStrAbs(const string &str)
{
	return isSignedStr(str) ? str.substr(1) : str;
}


/***************************************************************************/

string calSum(const char a, const char b, int &carry)
{
	int value = a - '0' + b - '0' + carry;
	if (value >= 10) {
		value = (value % 10);
		carry = 1;
	} else {
		carry = 0;
	}
	return to_string(value);
}

string add(string &&a, string &&b)
{
	string result = "";
	int carryFlag = 0;
	int aIndex = a.length() - 1;
	int bIndex = b.length() - 1;

	while (aIndex>=0 && bIndex>=0){
		const string val = calSum(a[aIndex--], b[bIndex--], carryFlag);
		result.append(val);
	}

	if (aIndex > 0) {
		while (aIndex>=0){
			const string val = calSum(a[aIndex--], '0', carryFlag);
			result.append(val);
		}
	}

	if (bIndex > 0) {
		while (bIndex>=0){
			const string val = calSum('0', b[bIndex--], carryFlag);
			result.append(val);
		}
	}

	if (carryFlag == 1) {
		result.append(to_string(1 + '0'));
	}
	reverse(result.begin(), result.end());
	return result;
}

const string bigNumSum(const string &lStr, const string &rStr)
{
	char lSign = '+';
	char rSign = '+';

	if (!isValidNumberStr(lStr))
		return rStr;
	if (!isValidNumberStr(rStr))
		return lStr;

	if (isSignedStr(lStr)) {
		lSign = lStr[0];
	}

	if (isSignedStr(rStr)) {
		rSign = rStr[0];
	}

	if (lSign == rSign) {
		string result = add(getStrAbs(lStr), getStrAbs(rStr));
		if (lSign == '-') {
			return string("-").append(result);
		}
		else {
			return result;
		}
	}


	return  "";
}

/***************************************************************************/
void testIsValidNumberStr(void)
{
	string str = "-";
	cout << str << " is valid number string: " << isValidNumberStr(str) << endl;

	str = "1233456fds";
	cout << str << " is valid number string: " << isValidNumberStr(str) << endl;

	str = "+1233456";
	cout << str << " is valid number string: " << isValidNumberStr(str) << endl;

	str = "-123456";
	cout << str << " is valid number string: " << isValidNumberStr(str) << endl;

	str = "-1";
	cout << str << " is valid number string: " << isValidNumberStr(str) << endl;
}

void testSameSignSum(void)
{
	string a = "123456";
	string b = "123456";
	cout << a << " + " << b << " = " << bigNumSum(a, b) << endl;
}
/***************************************************************************/
int main(int argc, char **argv)
{
	//testIsValidNumberStr();

	testSameSignSum();
}