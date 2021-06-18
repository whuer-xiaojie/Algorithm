
#include <iostream>
#include <vector>
#include "../utils/tree-node.hpp"


int getValueIndex(const vector<int> &vec, const int value)
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

TreeNode *reconstructTree(const vector<int> &preOrderArr, const vector<int> &midOrderArr)
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

	TreeNode *root = new TreeNode(preOrderArr[0]);
	root->left = reconstructTree(leftPreArr, leftMidArr);
	root->right = reconstructTree(rightPreArr, rightMidArr);
	return root;
}

TreeNode *reconstructTree(const vector<int> &preOrderArr, const int preStart, const int preEnd,
	const vector<int> &midOrderArr, const int midStart, const int midEnd)
{
	if (preOrderArr.empty() || (preStart >= preEnd) || (midStart >= midEnd)) {
		return nullptr;
	}

	int rootIndex = getValueIndex(midOrderArr, preOrderArr[preStart]);
	int leftNodeCount = rootIndex - midStart + 1;
	TreeNode *root = new TreeNode(preOrderArr[preStart]);
	root->left = reconstructTree(preOrderArr, preStart + 1, preStart + leftNodeCount,
		midOrderArr, midStart, rootIndex);
	root->right = reconstructTree(preOrderArr, preStart + leftNodeCount, preEnd,
		midOrderArr, rootIndex + 1, midEnd);
	return root;
}


bool doesTree1HasTree2(TreeNode *root1, TreeNode *root2)
{
	if (root2 == nullptr)
		return true;
	if (root1 == nullptr || root1->value != root2->value)
		return false;
	return doesTree1HasTree2(root1->left, root2->left) && doesTree1HasTree2(root1->right, root2->right);
}

bool hasSubTree(TreeNode *root1, TreeNode *root2)
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

int getTreeDepth(TreeNode *root)
{
	if (root == nullptr)
		return 0;
	int left = getTreeDepth(root->left);
	int right = getTreeDepth(root->right);
	return left > right ? left + 1 : right + 1;
}

void testTreeOrder(void)
{
	TreeNode *root = new TreeNode(2);
	root->left = new TreeNode(1);
	root->right = new TreeNode(3);

	printTreeNode(root, ETraversalOrder::PRE_ORDER);
	printTreeNode(root, ETraversalOrder::MID_ORDER);
	printTreeNode(root, ETraversalOrder::POST_ORDER);

	deleteTreeNode(root);
}


void testReconstructTree(void)
{
	const vector<int> preOrder = { 1,2,4,7,3,5,6,8 };
	const vector<int> midOrder = { 4,7,2,1,5,3,8,6 };

	TreeNode *root1 = reconstructTree(preOrder, midOrder);
	printTreeNode(root1, ETraversalOrder::PRE_ORDER);
	printTreeNode(root1, ETraversalOrder::MID_ORDER);
	printTreeNode(root1, ETraversalOrder::POST_ORDER);

	TreeNode *root2 = reconstructTree(preOrder, 0, preOrder.size(), midOrder, 0, midOrder.size());
	printTreeNode(root2, ETraversalOrder::PRE_ORDER);
	printTreeNode(root2, ETraversalOrder::MID_ORDER);
	printTreeNode(root2, ETraversalOrder::POST_ORDER);

	deleteTreeNode(root1);
	deleteTreeNode(root2);
}


int main(int argc, char **argv)
{
	//testTreeOrder();
	testReconstructTree();
	return 0;
}