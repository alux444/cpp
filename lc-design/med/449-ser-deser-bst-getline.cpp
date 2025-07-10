#include <string>
#include <queue>
#include <sstream>

using namespace std;

struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec
{
public:
  // Encodes a tree to a single string.
  string serialize(TreeNode *root)
  {
    queue<TreeNode *> q{};
    q.push(root);
    string res = "";
    while (!q.empty())
    {
      TreeNode *top = q.front();
      q.pop();
      if (top)
      {
        res += to_string(top->val) + ",";
        q.push(top->left);
        q.push(top->right);
      }
      else
      {
        res += "#,";
      }
    }
    return res;
  }

  // Decodes your encoded data to tree.
  TreeNode *deserialize(string data)
  {
    if (data == "#,")
      return nullptr;

    stringstream ss(data);
    string token;
    getline(ss, token, ',');
    TreeNode *root = new TreeNode(stoi(token));
    queue<TreeNode *> q{};
    q.push(root);

    while (!q.empty())
    {
      TreeNode *top = q.front();
      q.pop();
      if (!getline(ss, token, ','))
        break;
      if (token != "#")
      {
        TreeNode *left = new TreeNode(stoi(token));
        top->left = left;
        q.push(left);
      }
      if (!getline(ss, token, ','))
        break;
      if (token != "#")
      {
        TreeNode *right = new TreeNode(stoi(token));
        top->right = right;
        q.push(right);
      }
    }

    return root;
  }
};