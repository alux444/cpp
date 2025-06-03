#include <stack>

struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class BSTIterator
{
  std::stack<TreeNode *> stack;

public:
  BSTIterator(TreeNode *root)
  {
    add(root);
  }

  void add(TreeNode *node)
  {
    while (node)
    {
      stack.push(node);
      node = node->left;
    }
  }

  int next()
  {
    TreeNode *popped = stack.top();
    stack.pop();
    add(popped->right);
    return popped->val;
  }

  bool hasNext()
  {
    return !stack.empty();
  }
};