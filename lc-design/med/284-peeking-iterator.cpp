#include <vector>

class Iterator
{
  int data;

public:
  Iterator(const std::vector<int> &nums);
  Iterator(const Iterator &iter);

  // Returns the next element in the iteration.
  int next();

  // Returns true if the iteration has more elements.
  bool hasNext() const;
};

class PeekingIterator : public Iterator
{
  int peeked;
  bool hasPeeked;

public:
  PeekingIterator(const std::vector<int> &nums) : Iterator(nums)
  {
    // Initialize any member here.
    // DO NOT save a copy of nums and manipulate it directly.
    // You should only use the Iterator interface methods.
    if (Iterator::hasNext())
    {
      peeked = Iterator::next();
      hasPeeked = true;
    }
  }

  // Returns the next element in the iteration without advancing the iterator.
  int peek()
  {
    if (hasPeeked)
    {
      return peeked;
    }
    // have not peeked
    peeked = Iterator::next();
    hasPeeked = true;
    return peeked;
  }

  // hasNext() and next() should behave the same as in the Iterator interface.
  // Override them if needed.
  int next()
  {
    if (hasPeeked)
    {
      hasPeeked = false;
      return peeked;
    }
    // hasn't peeked
    return Iterator::next();
  }

  bool hasNext() const
  {
    return (!hasPeeked && Iterator::hasNext()) || (hasPeeked);
  }
};