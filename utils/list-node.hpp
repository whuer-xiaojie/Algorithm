#ifndef LIST_NODE_H
#define LIST_NODE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef struct ListNode {
	int value;
	struct ListNode *next;
	ListNode(int x) :value(x), next(nullptr) {}
	ListNode() { next = nullptr; }
} ListNode;

void printListNode(ListNode *pHead, const string &msg)
{
	cout << msg << ": ";
	while (pHead) {
		cout << pHead->value << " ";
		pHead = pHead->next;
	}
	cout << endl;
}

ListNode *newListNode(const vector<int> &vec)
{
	if (vec.empty()) {
		return nullptr;
	}

	ListNode *pHead = new ListNode(vec[0]);
	ListNode *pTemp = pHead;
	for (size_t i = 1; i < vec.size(); i++) {
		pTemp->next = new ListNode(vec[i]);
		pTemp = pTemp->next;
	}

	return pHead;
}

void deleteListNode(ListNode *pHead)
{
	while (pHead) {
		ListNode *temp = pHead;
		pHead = pHead->next;
		delete pHead;
	}
}

#endif // !LIST_NODE_H

