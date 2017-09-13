#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

int maxSum = INT_MIN;

int maxSumToBottom(TreeNode *root) {
  if (root == nullptr) {
    return 0;
  }

  int leftSum = maxSumToBottom(root->left);
  int rightSum = maxSumToBottom(root->right);

  if (leftSum < 0) {
    leftSum = 0;
  }

  if (rightSum < 0) {
    rightSum = 0;
  }

  if (leftSum + rightSum + root->val > maxSum) {
    maxSum = leftSum + rightSum + root->val;
  }

  return leftSum > rightSum ? leftSum + root->val : rightSum + root->val;
}

int maxPathSum(TreeNode* root) {
  maxSumToBottom(root);
  return maxSum;
}

int main(int argc, char **argv) {
  auto root = new TreeNode(2);
  root->left = new TreeNode(1);
  root->right = new TreeNode(3);
  cout << maxPathSum(root) << endl;
  system("pause");
}