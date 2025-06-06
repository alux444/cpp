#include <queue>

struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
                                                     right(right) {}
};
class CBTInserter
{
  TreeNode *root;
  std::queue<TreeNode *> q;

public:
  CBTInserter(TreeNode *root) : root(root)
  {
    std::queue<TreeNode *> queue;
    queue.push(root);
    while (!queue.empty())
    {
      TreeNode *node = queue.front();
      queue.pop();
      if (!node->left || !node->right)
        q.push(node); // highest lvl nodes pushed into our q first
      if (node->left)
        queue.push(node->left);
      if (node->right)
        queue.push(node->right);
    }
  }

  int insert(int val)
  {
    TreeNode *top = q.front();
    TreeNode *newNode = new TreeNode(val);
    if (!top->left)
    {
      top->left = newNode;
    }
    else
    {
      top->right = newNode;
      q.pop();
    }
    q.push(newNode);
    return top->val;
  }

  TreeNode *get_root()
  {
    return root;
  }
};