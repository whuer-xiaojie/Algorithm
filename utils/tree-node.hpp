#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef struct TreeNode {
	int value;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :value(x), left(nullptr), right(nullptr) {}
	~TreeNode() { left = nullptr; right = nullptr; }
} TreeNode;

typedef enum ETraversalOrder {
	PRE_ORDER,
	MID_ORDER,
	POST_ORDER
}ETraversalOrder;

void preOrderOut(TreeNode *root)
{
	if (root == nullptr)
		return;
	cout << " " << root->value;
	preOrderOut(root->left);
	preOrderOut(root->right);
}

void midOrderOut(TreeNode *root)
{
	if (root == nullptr)
		return;
	midOrderOut(root->left);
	cout << " " << root->value;
	midOrderOut(root->right);
}

void postOrderOut(TreeNode *root)
{
	if (root == nullptr)
		return;
	postOrderOut(root->left);
	postOrderOut(root->right);
	cout << " " << root->value;
}

void printTreeNode(TreeNode *root, ETraversalOrder order)
{
	if (order == ETraversalOrder::PRE_ORDER) {
		cout << "binary tree preorder: ";
		preOrderOut(root);
		cout << endl;
	} else if (order == ETraversalOrder::MID_ORDER) {
		cout << "binary tree midorder: ";
		midOrderOut(root);
		cout << endl;
	} else {
		cout << "binary tree postorder: ";
		postOrderOut(root);
		cout << endl;
	}
}

void deleteTreeNode(TreeNode *root)
{
	if (root == nullptr)
		return;
	deleteTreeNode(root->left);
	deleteTreeNode(root->right);
	delete root;
	root = nullptr;
}
#endif // !TREE_NODE_H
