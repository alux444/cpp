#include <unordered_set>
#include <unordered_map>
#include <string>

struct Node
{
  int freq;
  Node *next;
  Node *prev;
  std::unordered_set<std::string> keys;
  Node(int freq) : freq(freq), next(nullptr), prev(nullptr) {};
};

class AllOne
{
  Node *head;
  Node *tail;
  std::unordered_map<std::string, Node *> keys;

  void removeNode(Node *node)
  {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
  }

public:
  AllOne()
  {
    head = new Node(-1);
    tail = new Node(-1);
    head->next = tail;
    tail->prev = head;
  }

  void inc(std::string key)
  {
    if (keys.find(key) == keys.end())
    {
      // add new
      if (head->next->freq != 1)
      {
        // create the missing freq node
        Node *node = new Node(1);

        node->prev = head;
        node->next = head->next; // +

        head->next->prev = node;
        head->next = node; // +
      }
      head->next->keys.insert(key);
      keys[key] = head->next;
      return;
    } // +

    // update val
    Node *prevNode = keys[key];
    int newFreq = prevNode->freq + 1;
    prevNode->keys.erase(key);

    if (prevNode->next->freq != newFreq)
    {
      // create the missing freq node
      Node *node = new Node(newFreq);

      node->prev = prevNode;
      node->next = prevNode->next;

      prevNode->next->prev = node;
      prevNode->next = node;
    }

    // update to new val
    Node *newNode = prevNode->next;
    newNode->keys.insert(key);
    keys[key] = newNode;

    if (prevNode->keys.empty())
      removeNode(prevNode);
  }

  void dec(std::string key)
  {
    keys[key]->keys.erase(key);

    if (keys[key]->freq == 1)
    {
      // remove
      keys.erase(key);
      if (head->next->keys.empty())
        removeNode(head->next);
      return;
    }

    // decrement
    Node *prevNode = keys[key];
    int newFreq = prevNode->freq - 1;

    if (prevNode->prev->freq != newFreq)
    {
      Node *newNode = new Node(newFreq);

      newNode->next = prevNode;
      newNode->prev = prevNode->prev;

      prevNode->prev->next = newNode;
      prevNode->prev = newNode;
    }

    keys[key] = prevNode->prev;
    prevNode->prev->keys.insert(key);

    if (prevNode->keys.empty())
      removeNode(prevNode);
  }

  std::string getMinKey()
  {
    if (head->next == tail)
      return "";
    return *head->next->keys.begin();
  }

  std::string getMaxKey()
  {
    if (tail->prev == head)
      return "";
    return *tail->prev->keys.begin();
  }
};