
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

/**
将给出的链表中的节点每 k 个一组翻转，返回翻转后的链表
如果链表中的节点数不是 k 的倍数，将最后剩下的节点保持原样
你不能更改节点中的值，只能更改节点本身。
要求空间复杂度O(1)
例如：
给定的链表是 1->2->3->4->5;
对于 2, 你应该返回 2->1->4->3->5
对于 3, 你应该返回 3->2->1->4->5
*/
ListNode *reverseKGroup(ListNode *pHead, const int k)
{
	if (pHead == nullptr || pHead->next == nullptr || k <= 1) {
		return pHead;
	}

	ListNode *pStart = pHead;
	ListNode *pKEnd = pHead;
	ListNode *pNew = nullptr;
	ListNode *pNewEnd = nullptr;
	int count = 1;
	while (pKEnd != nullptr) {
		if (count == k) {
			ListNode *pLastStart = pStart;
			ListNode *pNextStart = pKEnd->next;
			pKEnd->next = nullptr;

			if (pNew == nullptr) {
				pNew = reverseNode(pStart);
			} else {
				pNewEnd->next = reverseNode(pStart);
			}
			pStart = pKEnd = pNextStart;
			pNewEnd = pLastStart;
			count = 1;
			continue;
		} else {
			pKEnd = pKEnd->next;
			count++;
		}
	}
	if (pStart != nullptr && pNew == nullptr) {
		pNew = pStart;
	} else {
		pNewEnd->next = pStart;
	}

	return pNew;
}


ListNode *mergeTwoNode(ListNode *pL1, ListNode *pL2)
{
	ListNode *pTemp = new ListNode(-1);
	ListNode *pBefore = pTemp;
	while (pL1 && pL2) {
		if (pL1->value < pL2->value) {
			pBefore->next = pL1;
			pBefore = pL1;
			pL1 = pL1->next;
		}
		else {
			pBefore->next = pL2;
			pBefore = pL2;
			pL2 = pL2->next;
		}
	}

	pBefore->next = (pL1 == nullptr ? pL2 : pL1);
	ListNode *pHead = pTemp->next;
	delete pTemp;
	return pHead;
}

/*********************************************/

void testReverseNode(void)
{
	vector<int> vec = { 1,2,3,4,5 };
	ListNode *pHead = newListNode(vec);

	printListNode(pHead, "Before reverse");

	ListNode *pReHead = reverseNode(pHead);
	printListNode(pReHead, "After reverse");

	ListNode *p2 = reverseKGroup(pReHead, 2);
	printListNode(p2,"After 2 group reverse");

	ListNode *p3 = reverseKGroup(p2, 3);
	printListNode(p3, "After 3 group reverse");

	deleteListNode(p3);
}

void testMerge(void)
{
	vector<int> vec1 = { 1,3,5,7,9 };
	vector<int> vec2 = { 2,4,6,8,10,11 };
	ListNode *p1 = newListNode(vec1);
	ListNode *p2 = newListNode(vec2);

	ListNode *p3 = mergeTwoNode(p1, p2);
	printListNode(p3, "After merge");

	deleteListNode(p3);

}


int main(int argc, char **argv)
{
	testReverseNode();
	testMerge();
}