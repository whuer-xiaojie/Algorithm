
#include <iostream>
#include <string>
#include <vector>

#include "../utils/list-node.hpp"

using namespace std;

ListNode *reverseNode(ListNode *pHead)
{
	if (pHead == nullptr || pHead->next == nullptr) return pHead;

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

/*
	将给出的链表中的节点每 k 个一组翻转，返回翻转后的链表 
	如果链表中的节点数不是 k 的倍数，将最后剩下的节点保持原样 
	你不能更改节点中的值，只能更改节点本身。要求空间复杂度O(1)
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

/*
	题目：输入两个递增排序的链表，合并这两个链表并使新链表中的节点仍然是递增排序的。
	
	示例1：
	输入：1->2->4, 1->3->4
	输出：1->1->2->3->4->4
	
	限制：
	0 <= 链表长度 <= 1000
*/
ListNode *mergeTwoNode(ListNode *pL1, ListNode *pL2)
{
	ListNode *pTemp = new ListNode(-1);
	ListNode *pBefore = pTemp;
	while (pL1 && pL2) {
		if (pL1->value < pL2->value) {
			pBefore->next = pL1;
			pBefore = pL1;
			pL1 = pL1->next;
		} else {
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

/*
	输入一个链表，输出该链表中倒数第k个结点。
*/
ListNode *lastKthNode(ListNode *pHead, int k)
{
	if (pHead == nullptr || k <= 0) {
		return nullptr;
	}

	ListNode *pAfter = pHead;
	ListNode *pBefore = pHead;
	for (int i = 0; i < k; i++) {
		if (pBefore == nullptr) {
			return nullptr;
		}
		pBefore = pBefore->next;
	}
	while (pBefore != nullptr) {
		pBefore = pBefore->next;
		pAfter = pAfter->next;
	}
	return pAfter;
}

/*
	在一个排序的链表中，存在重复的结点，请删除该链表中重复的结点，重复的结点不保留，
	返回链表头指针。 
	例如:
	1->2->3->3->4->4->5
    处理后为 1->2->5
*/
ListNode *deleteAllDumpNode(ListNode *pHead)
{
	if (pHead == nullptr) {
		return nullptr;
	}
	ListNode *pNew = new ListNode(-1);
	ListNode *pBefore = pNew;
	ListNode *pNow = pHead;
	ListNode *pAfter = nullptr;
	while (pNow != nullptr) {
		pAfter = pNow->next;
		if (pAfter != nullptr && pNow->value == pAfter->value) {
			while (pAfter != nullptr) {
				if (pNow->value != pAfter->value) {
					break;
				}
				ListNode *pTemp = pAfter;
				pAfter = pAfter->next;
				delete pTemp;
			}
			delete pNow;
			pNow = pAfter;
			pBefore->next = pNow;
			pBefore = pNow;
		} else {
			pBefore->next = pNow;
			pBefore = pNow;
			pNow = pAfter;
		}
	}
	pBefore = pNew;
	pHead = pNew->next;
	delete pBefore;
	return pHead;
}

/*
	在一个排序的链表中，存在重复的结点，请删除该链表中重复的结点，重复的结点保留一个，
	返回链表头指针。 例如，链表1->2->3->3->4->4->5
    处理后为 1->2->3->4->5
*/
ListNode *deleteDumpNode(ListNode *pHead)
{
	if (pHead == nullptr) {
		return nullptr;
	}
	ListNode *pCur = pHead;
	ListNode *pNext = nullptr;
	while (pCur != nullptr) {
		pNext = pCur->next;
		if (pNext != nullptr && pNext->value == pCur->value) {
			while (pNext != nullptr) {
				if (pNext->value != pCur->value) {
					break;
				}
				ListNode *pTemp = pNext;
				pNext = pNext->next;
				delete pTemp;
			}
			pCur->next = pNext;
		}
		pCur = pNext;
	}
	return pHead;
}
/*********************************************/

void testReverseNode(void)
{
	vector<int> vec = { 1, 2, 3, 4, 5 };
	ListNode *pHead = newListNode(vec);

	printListNode(pHead, "Before reverse");

	ListNode *pReHead = reverseNode(pHead);
	printListNode(pReHead, "After reverse");

	ListNode *p2 = reverseKGroup(pReHead, 2);
	printListNode(p2, "After 2 group reverse");

	ListNode *p3 = reverseKGroup(p2, 3);
	printListNode(p3, "After 3 group reverse");

	deleteListNode(p3);
}

void testMerge(void)
{
	vector<int> vec1 = { 1, 3, 5, 7, 9 };
	vector<int> vec2 = { 2, 4, 6, 8, 10, 11 };
	ListNode *p1 = newListNode(vec1);
	ListNode *p2 = newListNode(vec2);

	ListNode *p3 = mergeTwoNode(p1, p2);
	printListNode(p3, "After merge");

	deleteListNode(p3);
}

void testLastKthNode(void)
{
	vector<int> vec = { 2, 4, 6, 8, 10, 11 };
	ListNode *p1 = newListNode(vec);

	ListNode *p = lastKthNode(p1, 7);
	if (p != nullptr)
		cout << p->value << endl;
	else
		cout << "invalid last k node" << endl;

	deleteListNode(p1);
}

void testDeleteDumpNode(void)
{
	vector<int> vec = { 2, 2, 2, 4, 6, 8, 10, 11 };
	ListNode *p1 = newListNode(vec);
	ListNode *p = deleteAllDumpNode(p1);
	printListNode(p, "After delete all dump");
	deleteListNode(p);

	vector<int> vec2 = { 2, 2, 2, 4, 6, 6, 6, 8, 10, 11, 11, 11, 11 };
	ListNode *p2 = newListNode(vec2);
	p = deleteAllDumpNode(p2);
	printListNode(p, "After delete all dump");
	deleteListNode(p);

	vector<int> vec3 = { 2, 2, 2, 4, 6, 6, 6, 8, 10, 11, 11, 11, 11 };
	ListNode *p3 = newListNode(vec3);
	p = deleteDumpNode(p3);
	printListNode(p, "After delete dump");
	deleteListNode(p);
}

int main(int argc, char **argv)
{
	// testReverseNode();
	// testMerge();
	// testLastKthNode();
	testDeleteDumpNode();
}