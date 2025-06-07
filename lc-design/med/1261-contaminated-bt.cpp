#include <unordered_set>

struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class FindElements
{
  std::unordered_set<int> foundValues;

private:
  void recover(TreeNode *node)
  {
    if (!node)
      return;
    foundValues.insert(node->val);
    if (node->left)
    {
      node->left->val = (2 * node->val) + 1;
      recover(node->left);
    }
    if (node->right)
    {
      node->right->val = (2 * node->val) + 2;
      recover(node->right);
    }
  }

public:
  FindElements(TreeNode *root)
  {
    root->val = 0;
    recover(root);
  }

  bool find(int target) { return foundValues.count(target); }
};