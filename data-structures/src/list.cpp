#include <iterator>
#include <stdexcept>

#define DEFAULT_SIZE 100

template <typename T>
class List
{
private:
  T *arr;
  int index;
  int capacity;

  void resize(size_t newCapacity)
  {
    T *newArr = new T[newCapacity];
    for (int i = 0; i < index; i++)
    {
      newArr[i] = this->arr[i];
    }
    delete[] arr;
    this->arr = newArr;
    this->capacity = newCapacity;
  }

public:
  List() : arr(new T[DEFAULT_SIZE]), index(0), capacity(DEFAULT_SIZE) {}
  List(int size) : arr(new T[size]), index(0), capacity(size) {}

  ~List()
  {
    delete[] arr;
  }

  T &operator[](size_t index) // not const, returning the ref that can be written on
  {
    if (index >= this->index)
      throw std::out_of_range("Index out of bounds");
    return this->arr[index];
  }

  const T &operator[](size_t index) const
  {
    if (index >= this->index)
      throw std::out_of_range("Index out of bounds");
    return this->arr[index];
  }

  T *front() const
  {
    if (empty())
      return nullptr;
    return &this->arr[0];
  }

  T *back() const
  {
    if (empty())
      return nullptr;
    return &this->arr[index - 1];
  }

  int size() const
  {
    return this->index;
  }

  bool empty() const
  {
    return this->index == 0;
  }

  void push_back(const T &value)
  {
    if (this->index == this->capacity)
    {
      resize(this->capacity * 2);
    }
    this->arr[index++] = value;
  }

  void insert(const int &pos, const T &value)
  {
    if (pos < 0 || pos > this->index)
      throw std::out_of_range("Invalid index insert position");
    if (this->index == this->capacity)
      resize(this->capacity * 2);
    for (int i = this->index; i > pos; i--)
      arr[i] = arr[i-1];
    arr[pos] = value;
    this->index++;
  }

  void erase(const int &pos)
  {
    if (pos < 0 || pos >= this->index)
      throw std::out_of_range("Invalid index insert position");
    for (int i = pos; i < this->index-1; i++)
      arr[i] = arr[i+1];
    this->index--;
  }
};