#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node
{
  Node *next;
  Node *prev;
  int value;
  int key;
  Node(Node *p, Node *n, int k, int val) : prev(p), next(n), key(k), value(val) {};
  Node(int k, int val) : prev(NULL), next(NULL), key(k), value(val) {};
};

class Cache
{

protected:
  map<int, Node *> mp;            // map the key to the node in the linked list
  int cp;                         // capacity
  Node *tail;                     // double linked list tail pointer
  Node *head;                     // double linked list head pointer
  virtual void set(int, int) = 0; // set function
  virtual int get(int) = 0;       // get function
};

class LRUCache : public Cache
{

public:
  LRUCache(int cap)
  {
    this->cp = cap;
    this->head = new Node(-1, -1);
    this->tail = new Node(-1, -1);
    this->head->next = this->tail;
    this->tail->prev = this->head;
  }

  void evict()
  {
    Node *lru = this->head->next;
    if (lru == tail)
      return;
    this->head->next = lru->next;
    lru->next->prev = this->head;
    mp.erase(lru->key);
    delete lru;
    ;
  }

  void set(int key, int value)
  {
    if (mp.find(key) != mp.end())
    {
      Node *node = mp[key];
      node->value = value;
      get(key); // move to back
      return;
    }

    if (mp.size() == this->cp)
    {
      evict();
    }

    Node *newNode = new Node(key, value);
    this->mp[key] = newNode;

    Node *mfu = this->tail->prev;
    mfu->next = newNode;
    newNode->prev = mfu;
    newNode->next = this->tail;
    this->tail->prev = newNode;
  }

  int get(int key)
  {
    if (mp.find(key) == mp.end())
    {
      return -1;
    }
    Node *node = mp[key];

    node->prev->next = node->next;
    node->next->prev = node->prev;

    // update back to the end
    Node *mfu = this->tail->prev;
    mfu->next = node;
    node->prev = mfu;
    node->next = this->tail;
    this->tail->prev = node;

    return node->value;
  }
};

int main()
{
  int n, capacity, i;
  cin >> n >> capacity;
  LRUCache l(capacity);
  for (i = 0; i < n; i++)
  {
    string command;
    cin >> command;
    if (command == "get")
    {
      int key;
      cin >> key;
      cout << l.get(key) << endl;
    }
    else if (command == "set")
    {
      int key, value;
      cin >> key >> value;
      l.set(key, value);
    }
  }
  return 0;
}
