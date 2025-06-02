#include <unordered_map>

struct Node
{
  Node *next;
  Node *prev;
  int val;
  int key;
  Node() : val(-1), key(-1), next(nullptr), prev(nullptr) {}
  Node(int val, int key) : val(val), key(key), next(nullptr), prev(nullptr) {}
};

class LRUCache
{
  std::unordered_map<int, Node *> nodes;
  Node *head;
  Node *tail;
  int capacity;

public:
  LRUCache(int capacity) : capacity(capacity)
  {
    head = new Node();
    tail = new Node();
    head->next = tail;
    tail->prev = head;
  }

  int get(int key)
  {
    if (nodes.find(key) == nodes.end())
      return -1;
    Node *res = nodes[key];
    // remove from where it is
    res->next->prev = res->prev;
    res->prev->next = res->next;
    // bump to start (MFU)
    head->next->prev = res;
    res->next = head->next;
    head->next = res;
    res->prev = head;

    return res->val;
  }

  void put(int key, int value)
  {
    if (nodes.find(key) != nodes.end())
    {
      // if we're just replacing a value
      nodes[key]->val = value;
      get(key);
      return;
    }
    if (nodes.size() == capacity)
    {
      // evict LFU
      Node *lfu = tail->prev;

      tail->prev = lfu->prev;
      tail->prev->next = tail;

      nodes.erase(lfu->key);
      delete lfu;
    }
    Node *node = new Node(value, key);
    nodes[key] = node;
    node->next = head->next;
    head->next->prev = node;
    head->next = node;
    node->prev = head;
  }
};