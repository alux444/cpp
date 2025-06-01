#include <string>

class Node
{
public:
  std::string url;
  Node *next;
  Node *prev;

  Node() : next(nullptr), prev(nullptr) {}
  Node(std::string url) : url(url), next(nullptr), prev(nullptr) {}
};

class BrowserHistory
{
private:
  Node *head;
  Node *cur;

  void removeNodes(Node *node)
  {
    while (node)
    {
      Node *next = node->next;
      delete node;
      node = next;
    }
  }

public:
  BrowserHistory(std::string homepage) : head(new Node(homepage)) { cur = head; }

  ~BrowserHistory() { removeNodes(head); }

  void visit(std::string url)
  {
    if (cur->next)
      removeNodes(cur->next);
    Node *newNode = new Node(url);
    cur->next = newNode;
    newNode->prev = cur;
    cur = newNode;
  }

  std::string back(int steps)
  {
    while (cur->prev && steps--)
      cur = cur->prev;
    return cur->url;
  }

  std::string forward(int steps)
  {
    while (cur->next && steps--)
      cur = cur->next;
    return cur->url;
  }
};