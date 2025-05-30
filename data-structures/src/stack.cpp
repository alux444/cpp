#include <iostream>
#include <stdexcept>

#define MAX_SIZE 100

template <typename T>
class Stack
{
private:
  int frontIndex;
  int backIndex;
  int count;
  T arr[MAX_SIZE];

public:
  Stack() : frontIndex(-1), backIndex(-1), count(0) {}

  void push(const T &value)
  {
    if (this->empty())
    {
      this->frontIndex = 0;
      this->backIndex = 0;
      arr[frontIndex] = value;
      this->count++;
      return;
    }

    // circular increment
    this->backIndex = (this->backIndex + 1) % MAX_SIZE;
    if (this->backIndex == this->frontIndex)
    {
      std::cout << "Stack is full" << std::endl;
      this->backIndex = (this->backIndex - 1) % MAX_SIZE;
      return;
    }
    arr[backIndex] = value;
    this->count++;
  }

  T pop()
  {
    if (empty())
    {
      std::cout << "Queue is empty" << std::endl;
      throw std::out_of_range("Queue is empty");
    }
    T res = arr[backIndex];

    if (this->frontIndex == this->backIndex)
    {
      this->frontIndex = -1;
      this->backIndex = -1;
    }
    else
    {
      this->backIndex = (this->backIndex - 1) % MAX_SIZE;
    }

    this->count--;
    return res;
  }

  bool full() const
  {
    return this->count == MAX_SIZE;
  }

  bool empty() const
  {
    return this->count == 0;
  }

  int size() const
  {
    return this->count;
  }
};