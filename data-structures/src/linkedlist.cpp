#include <iostream>

template <typename T>
class Node
{
public:
  T value;
  Node<T> *next;
  Node<T> *prev;
  Node() : next(nullptr), prev(nullptr) {}
  Node(T value) : value(value), next(nullptr), prev(nullptr) {}
};

template <typename T>
class LinkedList
{
public:
  Node<T> *head;
  Node<T> *tail;
  int size;
  LinkedList() : head(new Node<T>()), tail(new Node<T>()), size(0)
  {
    this->head->next = this->tail;
    this->tail->prev = this->head;
  }

  ~LinkedList()
  {
    Node<T> *cur = head;
    while (cur != nullptr)
    {
      Node<T> *next = cur->next;
      delete cur;
      cur = next;
    }
  }

  void push_front(T value)
  {
    Node<T> *newNode = new Node<T>(value);
    newNode->next = this->head->next;
    newNode->prev = this->head;

    this->head->next->prev = newNode;
    this->head->next = newNode;

    this->size++;
  }

  void push_back(T value)
  {
    Node<T> *newNode = new Node<T>(value);
    newNode->next = this->tail;
    newNode->prev = this->tail->prev;

    this->tail->prev->next = newNode;
    this->tail->prev = newNode;

    this->size++;
  }

  Node<T> *peek_front() const
  {
    if (empty())
      return nullptr;
    return this->head->next;
  }

  Node<T> *peek_back() const
  {
    if (empty())
      return nullptr;
    return this->tail->prev;
  }

  int count() const
  {
    return this->size;
  }

  Node<T> *find(T value)
  {
    Node<T> *curNode = this->head->next;
    while (curNode != this->tail)
    {
      if (curNode->value == value)
        return curNode;
      curNode = curNode->next;
    }
    return nullptr;
  }

  bool empty() const
  {
    return this->head->next == this->tail;
  }

  bool erase(int index)
  {
    Node<T> *curNode = this->head->next;
    while (curNode != this->tail && index >= 0)
    {
      if (index == 0)
      {
        this->removeNode(curNode);
        return true;
      }
      curNode = curNode->next;
      index--;
    }
    return false;
  }

  bool erase(Node<T> *node)
  {
    Node<T> *curNode = this->head->next;
    while (curNode != this->tail)
    {
      if (curNode == node)
      {
        this->removeNode(curNode);
        return true;
      }
      curNode = curNode->next;
    }
    return false;
  }

  void print_list() const
  {
    Node<T> *curNode = this->head->next;
    std::cout << '[';
    while (curNode != this->tail)
    {
      std::cout << curNode->value << " ";
      curNode = curNode->next;
    }
    std::cout << ']' << std::endl;
  }

private:
  void removeNode(Node<T> *node)
  {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
    this->size--;
  }
};