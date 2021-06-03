
#include <iostream>
#include <string>
#include <vector>

#include "../utils/list-node.hpp"

using namespace std;

ListNode* reverseNode(ListNode *pHead)
{
	if (pHead == nullptr || pHead->next == nullptr)
		return pHead;

	ListNode *pBefore = nullptr;
	ListNode *pNow = pHead;
	ListNode *pAfter = nullptr;

	while (pNow) {
		pAfter = pNow->next;
		pNow->next = pBefore;
		pBefore = pNow;
		pNow = pAfter;
	}

	return pBefore;
}

/*********************************************/

void testReverseNode(void)
{
	vector<int> vec = { 1,2,3,4,5 };
	ListNode *pHead = newListNode(vec);

	printListNode(pHead, "Before reverse");

	ListNode *pReHead = reverseNode(pHead);
	printListNode(pReHead, "After reverse");

	deleteListNode(pHead);
}


int main(int argc, char **argv)
{
	testReverseNode();
}