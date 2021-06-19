
#include "../utils/tree-node.hpp"
#include <iostream>
#include <vector>
#include <queue>
#include <string>


using namespace std;

int getValueIndex(const vector<int>& vec, const int value)
{
	int index = -1;
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] == value) {
			index = i;
			break;
		}
	}
	return index;
}

/*********************************************/
/*
	���� ǰ����� && ������� �ع����������������������ظ�Ԫ�أ�
*/
TreeNode* reconstructTree(const vector<int>& preOrderArr, const vector<int>& midOrderArr)
{
	if (preOrderArr.empty()) {
		return nullptr;
	}

	vector<int> leftPreArr, rightPreArr, leftMidArr, rightMidArr;
	int rootIndex = getValueIndex(midOrderArr, preOrderArr[0]);

	for (int i = 0; i < rootIndex; i++) {
		leftMidArr.emplace_back(midOrderArr[i]);
		leftPreArr.emplace_back(preOrderArr[i + 1]);
	}

	for (int i = rootIndex + 1; i < preOrderArr.size(); i++) {
		rightMidArr.emplace_back(midOrderArr[i]);
		rightPreArr.emplace_back(preOrderArr[i]);
	}

	TreeNode* root = new TreeNode(preOrderArr[0]);
	root->left = reconstructTree(leftPreArr, leftMidArr);
	root->right = reconstructTree(rightPreArr, rightMidArr);
	return root;
}
/*
	���� ǰ����� && ������� �ع����������������������ظ�Ԫ�أ�
*/

TreeNode* reconstructTree(const vector<int>& preOrderArr, const int preStart, const int preEnd,
	const vector<int>& midOrderArr, const int midStart, const int midEnd)
{
	if (preOrderArr.empty() || (preStart >= preEnd) || (midStart >= midEnd)) {
		return nullptr;
	}

	int rootIndex = getValueIndex(midOrderArr, preOrderArr[preStart]);
	int leftNodeCount = rootIndex - midStart + 1;
	TreeNode* root = new TreeNode(preOrderArr[preStart]);
	root->left = reconstructTree(preOrderArr, preStart + 1, preStart + leftNodeCount,
		midOrderArr, midStart, rootIndex);
	root->right = reconstructTree(preOrderArr, preStart + leftNodeCount, preEnd,
		midOrderArr, rootIndex + 1, midEnd);
	return root;
}

/*********************************************/
bool doesTree1HasTree2(TreeNode* root1, TreeNode* root2)
{
	if (root2 == nullptr)
		return true;
	if (root1 == nullptr || root1->value != root2->value)
		return false;
	return doesTree1HasTree2(root1->left, root2->left) && doesTree1HasTree2(root1->right, root2->right);
}

/*
	�������Ŷ�����A��B���ж�B�ǲ���A���ӽṹ����PS������Լ��������������һ�������ӽṹ��
*/
bool hasSubTree(TreeNode* root1, TreeNode* root2)
{
	bool hasSub = false;
	if (root1 != nullptr && root2 != nullptr) {
		if (root1->value == root2->value) {
			hasSub = doesTree1HasTree2(root1, root2);
		}
		if (!hasSub)
			hasSub = hasSubTree(root1->left, root2);
		if (!hasSub)
			hasSub = hasSubTree(root1->right, root2);
	}
	return hasSub;
}

/*********************************************/
/*
	����һ�ö����������������ȡ��Ӹ���㵽Ҷ������ξ����Ľ�㣨������Ҷ��㣩�γ�����һ��·�����·���ĳ���Ϊ������ȡ�
*/
int getTreeDepth(TreeNode* root)
{
	if (root == nullptr)
		return 0;
	int left = getTreeDepth(root->left);
	int right = getTreeDepth(root->right);
	return left > right ? left + 1 : right + 1;
}

/*********************************************/
void preOrder(TreeNode* root, vector<int>& vec)
{
	if (root == nullptr) {
		return;
	}
	vec.emplace_back(root->value);
	preOrder(root->left, vec);
	preOrder(root->right, vec);
}

void rightFirstPreOrder(TreeNode* root, vector<int>& vec)
{
	if (root == nullptr)
		return;
	vec.emplace_back(root->value);
	rightFirstPreOrder(root->right, vec);
	rightFirstPreOrder(root->left, vec);
}

bool isMirrorTree(TreeNode* root1, TreeNode* root2)
{
	vector<int> vec1, vec2;
	preOrder(root1, vec1);
	rightFirstPreOrder(root2, vec2);
	if (vec1.size() != vec2.size()) {
		return false;
	}
	for (int i = 0; i < vec1.size(); i++) {
		if (vec1[i] != vec2[i])
			return false;
	}
	return true;
}

/*
	���������Ķ�����������任ΪԴ�������ľ���
	����������Ϊ�����������
		8                   8
	   / \                 / \
	  6   10              10  6
	 / \  / \            / \  / \
	5   7 9  11         11  9 7  5
*/
TreeNode* newMirrorTree(TreeNode* root)
{
	if (root == nullptr)
		return nullptr;
	TreeNode* r = new TreeNode(root->value);
	r->left = newMirrorTree(root->right);
	r->right = newMirrorTree(root->left);
	return r;
}

/*********************************************/
/*
	�������´�ӡ����������ÿ���ڵ㣬ͬ��ڵ�������Ҵ�ӡ
*/
vector<int> printTreeFromTop2Bottom(TreeNode *root)
{
	vector<int> vec;
	if (root == nullptr)
		return vec;
	queue<TreeNode *> queTree;
	queTree.push(root);
	while (!queTree.empty()) {
		TreeNode *pTemp = queTree.front();
		vec.emplace_back(pTemp->value);
		if (pTemp->left != nullptr) {
			queTree.push(pTemp->left);
		}
		if (pTemp->right != nullptr) {
			queTree.push(pTemp->right);
		}
		queTree.pop();
	}
	return vec;
}
/*********************************************/
void testTreeOrder(void)
{
	TreeNode* root = new TreeNode(2);
	root->left = new TreeNode(1);
	root->right = new TreeNode(3);

	printTreeNode(root, ETraversalOrder::PRE_ORDER);
	printTreeNode(root, ETraversalOrder::MID_ORDER);
	printTreeNode(root, ETraversalOrder::POST_ORDER);

	deleteTreeNode(root);
}

void testReconstructTree(void)
{
	const vector<int> preOrder = { 1, 2, 4, 7, 3, 5, 6, 8 };
	const vector<int> midOrder = { 4, 7, 2, 1, 5, 3, 8, 6 };

	TreeNode* root1 = reconstructTree(preOrder, midOrder);
	printTreeNode(root1, ETraversalOrder::PRE_ORDER);
	printTreeNode(root1, ETraversalOrder::MID_ORDER);
	printTreeNode(root1, ETraversalOrder::POST_ORDER);

	TreeNode* root2 = reconstructTree(preOrder, 0, preOrder.size(), midOrder, 0, midOrder.size());
	printTreeNode(root2, ETraversalOrder::PRE_ORDER);
	printTreeNode(root2, ETraversalOrder::MID_ORDER);
	printTreeNode(root2, ETraversalOrder::POST_ORDER);

	deleteTreeNode(root1);
	deleteTreeNode(root2);
}

void testMirrorTree(void)
{
	const vector<int> preOrder = { 1, 2, 4, 7, 3, 5, 6, 8 };
	const vector<int> midOrder = { 4, 7, 2, 1, 5, 3, 8, 6 };

	TreeNode* root = reconstructTree(preOrder, midOrder);
	TreeNode* mirrorRoot = newMirrorTree(root);

	printTreeNode(root, ETraversalOrder::PRE_ORDER);
	printTreeNode(mirrorRoot, ETraversalOrder::PRE_ORDER);

	bool isMirror = isMirrorTree(root, mirrorRoot);
	if (isMirror)
		cout << "tree1 and tree2 is mirror tree" << endl;
	else
		cout << "tree1 and tree2 not mirror tree" << endl;

	deleteTreeNode(root);
	deleteTreeNode(mirrorRoot);
}

void testPrintFromTop2Bottom(void)
{
	const vector<int> preOrder = { 8,6,5,7,10,9,11 };
	const vector<int> midOrder = { 5,6,7,8,9,10,11 };
	TreeNode* root = reconstructTree(preOrder, midOrder);

	vector<int> &&vec = printTreeFromTop2Bottom(root);

	cout << "print tree form top to bottom result:";
	for (int i = 0; i < vec.size(); i++) {
		cout << " " << vec[i];
	}
	cout << endl;

	deleteTreeNode(root);
}
/*********************************************/
int main(int argc, char** argv)
{
	//testTreeOrder();
	//testReconstructTree();
	//testMirrorTree();
	testPrintFromTop2Bottom();
	return 0;
}