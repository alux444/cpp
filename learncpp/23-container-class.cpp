#include <cassert>
#include <algorithm>

// We should add const overloads of various member functions to properly support const Arrays.

// We should add support for move semantics (via adding a move constructor and move assignment).

// When performing resize or insertion operations, we can move elements instead of copying them.

// When performing resize or insertion operations, move elements only if their move constructor is noexcept, otherwise copy them

// Provide a strong exception safety guarantee for resize or insertion operations

template <typename T>
class Array
{
private:
  int m_length{};
  T *m_data{};

public:
  Array() = default;

  Array(int length) : m_length{length}
  {
    assert(length >= 0 && "Length of array must be non-negative");
    if (length > 0)
      m_data = new T[length]{};
  }

  Array(std::initializer_list<T> list) : Array(list.size())
  {
    // std::copy(list.begin(), list.end(), m_data);
    // alternative: iterator
    for (int count = 0; count < list.size(); ++count)
    {
      m_data[count] = list.begin()[count];
    }
  }

  // no shallow copies
  Array(const Array &) = delete;
  Array &operator=(const Array &list) = delete;

  Array &operator=(std::initializer_list<T> list)
  {
    int length = list.size();
    if (length != m_length)
    {
      delete[] m_data;
      m_length = length;
      m_data = new T[list.size()]{};
    }
    std::copy(list.begin(), list.end(), m_data);
    return *this;
  }

  ~Array()
  {
    delete[] m_data;
    m_data = nullptr;
  }

  void erase()
  {
    delete[] m_data;
    m_data = nullptr;
    m_length = 0;
  }

  T &operator[](int index)
  {
    assert(index >= 0 && index < m_length && "Index out of bounds");
    return m_data[index];
  }

  int getLength() const { return m_length; }

  void reallocate(int newLength)
  {
    erase();
    if (newLength <= 0)
      return;
    m_data = new T[newLength]{};
    m_length = newLength;
  }

  void resize(int newLength)
  {
    if (newLength == m_length)
      return;
    if (newLength <= 0)
    {
      erase();
      return;
    }
    T *data{new T[newLength]};

    if (m_length > 0)
    {
      int toCopy{newLength > m_length ? m_length : newLength};
      std::copy_n(m_data, toCopy, data);
    }

    delete[] m_data;
    m_data = data;
    m_length = newLength;
  }

  Array(const Array &a) : Array(a.getLength())
  {
    std::copy_n(a.m_data, m_length, m_data);
  }

  Array &operator=(const Array &a)
  {
    if (this == &a)
      return *this;
    reallocate(a.getLength());
    std::copy_n(a.m_data, m_length, m_data);
    return *this;
  }

  void insertBefore(T value, int index)
  {
    assert(index >= 0 && index <= m_length && "Index out of bounds");
    T *data{new T[m_length + 1]};
    std::copy_n(m_data, index, data);
    data[index] = value;
    std::copy_n(m_data + index, m_length - index, data + index + 1);
    delete[] m_data;
    m_data = data;
    ++m_length;
  }

  void remove(int index)
  {
    assert(index >= 0 && index < m_length && "Index out of bounds");
    if (m_length == 1)
    {
      erase();
      return;
    }

    T *data{new T[m_length - 1]};
    std::copy_n(m_data, index, data);
    std::copy_n(m_data + index + 1, m_length - index - 1, data + index);

    delete[] m_data;
    m_data = data;
    --m_length;
  }
};