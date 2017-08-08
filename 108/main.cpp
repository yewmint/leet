#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  
};

TreeNode* sortedArrayToBST(vector<int>& nums) {
  int len = nums.size();
  if (len == 0) {
    return NULL;
  }
  int centralIdx = len / 2;

  int rootVal = nums[centralIdx];
  auto root = new TreeNode(rootVal);

  auto bit = nums.begin();
  auto eit = nums.end();
  vector<int> left(bit, bit + centralIdx);
  vector<int> right(bit + centralIdx + 1, eit);

  root->left = sortedArrayToBST(left);
  root->right = sortedArrayToBST(right);

  return root;
}

int main(int argc, char **argv) {

}