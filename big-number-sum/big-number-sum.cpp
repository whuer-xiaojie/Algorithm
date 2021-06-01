
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

//0=>a==b 1=>a>b -1=>a<b 
int compareAbs(const string &a, const string &b)
{
	if (a.length() > b.length()) {
		return 1;
	} else if (a.length() < b.length()) {
		return -1;
	} else {
		for (size_t i = 0; i <a.length(); i++) {
			if (a[i] > b[i]) {
				return 1;
			} else if (a[i] < b[i]) {
				return -1;
			}
		}
	}
	return 0;
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

string add(const string &a, const string &b, const char resultSign)
{
	string result = "";
	int carryFlag = 0;
	int aIndex = a.length() - 1;
	int bIndex = b.length() - 1;

	while (aIndex >= 0 && bIndex >= 0) {
		const string val = calSum(a[aIndex--], b[bIndex--], carryFlag);
		result.append(val);
	}

	while (aIndex >= 0) {
		const string val = calSum(a[aIndex--], '0', carryFlag);
		result.append(val);
	}
	
	while (bIndex >= 0) {
		const string val = calSum('0', b[bIndex--], carryFlag);
		result.append(val);
	}
	
	if (carryFlag == 1) {
		result.append(to_string(1));
	}
	reverse(result.begin(), result.end());
	return resultSign == '+' ? result : string("-").append(result);
}

/***************************************************************************/
string calSub(const char a, const char b, int &borrowFlag)
{
	if ((a - borrowFlag) >= b) {
		int val = a - b - borrowFlag;
		borrowFlag = 0;
		return to_string(val);
	} else {
		int val = a + 10 - b - borrowFlag;
		borrowFlag = 1;
		return to_string(val);
	}
}

string subtract(const string &a, const string &b, const char resultSign)
{
	string result = "";
	int borrowFlag = 0;
	int aIndex = a.length() - 1;
	int bIndex = b.length() - 1;
	while (aIndex>=0 && bIndex>=0){
		const string val = calSub(a[aIndex--], b[bIndex--], borrowFlag);
		result.append(val);
	}

	while (aIndex >= 0){
		const string val = calSub(a[aIndex--], '0', borrowFlag);
		result.append(val);
	}

	reverse(result.begin(), result.end());
	size_t index;
	for (index = 0; index < result.length(); index++) {
		if (result[index] != '0') {
			break;
		}
	}

	return resultSign == '+' ? result.substr(index) : string("-").append(result.substr(index));
}


/***************************************************************************/
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

	const string &&lAbs = getStrAbs(lStr);
	const string &&rAbs = getStrAbs(rStr);
	if (lSign == rSign) {//same sign
		return add(lAbs, rAbs, lSign);
	} else {//positive && negative 
		const int cmpResult = compareAbs(lAbs, rAbs);
		if (cmpResult == 0) {//lAbs==rAbs
			return string("0");
		} else if(cmpResult == 1){//lAbs>rAbs
			return subtract(lAbs, rAbs, lSign);
		} else {//lAbs<rAbs
			return subtract(rAbs, lAbs, rSign);
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

void testBigNumberSum(void)
{
	string a = "123456";
	string b = "123456";
	cout << a << " + " << b << " = " << bigNumSum(a, b) << endl;

	a = "9999";
	b = "111";
	cout << a << " + " << b << " = " << bigNumSum(a, b) << endl;

	a = "-9999";
	b = "-111";
	cout << a << " + " << b << " = " << bigNumSum(a, b) << endl;

	a = "-9666";
	b = "999";
	cout << a << " + " << b << " = " << bigNumSum(a, b) << endl;

	a = "111";
	b = "-999";
	cout << a << " + " << b << " = " << bigNumSum(a, b) << endl;

	a = "555";
	b = "-44444";
	cout << a << " + " << b << " = " << bigNumSum(a, b) << endl;

	a = "44444";
	b = "-44440";
	cout << a << " + " << b << " = " << bigNumSum(a, b) << endl;
}
/***************************************************************************/
int main(int argc, char **argv)
{
	//testIsValidNumberStr();

	testBigNumberSum();
}
