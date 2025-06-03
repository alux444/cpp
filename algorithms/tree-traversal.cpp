#include <iostream>

struct Node
{
  int val;
  Node *left;
  Node *right;
  Node(int val) : val(val) {}
};

/* All dfs variants */

// when in BST, we visit in non-decreasing order
void inorderTraversal(Node *node)
{
  inorderTraversal(node->left);
  std::cout << node->val << '\n';
  inorderTraversal(node->right);
}

// used to delete tree from leaf to root
void postorderTraversal(Node *node)
{
  postorderTraversal(node->left);
  postorderTraversal(node->right);
  std::cout << node->val << '\n';
}

// used for copying trees
void preorderTraversal(Node *node)
{
  std::cout << node->val << '\n';
  preorderTraversal(node->left);
  preorderTraversal(node->right);
}