#include <string>
#include <queue>
#include <sstream>

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
  std::string serialize(TreeNode *root)
  {
    std::ostringstream oss{};
    serialDfs(root, oss);
    return oss.str();
  }

  void serialDfs(TreeNode *root, std::ostringstream &oss)
  {
    if (!root)
    {
      oss << '#' << ',';
      return;
    }
    oss << root->val << ',';
    serialDfs(root->left, oss);
    serialDfs(root->right, oss);
  }

  // Decodes your encoded data to tree.
  TreeNode *deserialize(std::string data)
  {
    std::queue<std::string> q{};
    size_t curPos = 0;
    size_t nextPos = 0;
    for (nextPos = data.find(','); nextPos != std::string::npos; nextPos = data.find(',', curPos))
    {
      q.push(data.substr(curPos, nextPos - curPos));
      curPos = nextPos + 1;
    }
    return deserial(q);
  }

  TreeNode *deserial(std::queue<std::string> &q)
  {
    std::string cur = q.front();
    q.pop();
    if (cur == "#")
      return NULL;
    TreeNode *newNode = new TreeNode(std::stoi(cur));
    newNode->left = deserial(q);
    newNode->right = deserial(q);
    return newNode;
  }
};