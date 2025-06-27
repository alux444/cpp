#include <vector>

void two_pointers_same(std::vector<int> &arr)
{
  int slow = 0, fast = 0;
  while (fast < arr.size())
  {
    // Process current elements
    int current = process(arr[slow], arr[fast]);

    // Update pointers based on condition
    if (condition(arr[slow], arr[fast]))
    {
      slow++;
    }

    // Fast pointer always moves forward
    fast++;
  }
}

void two_pointers_opposite(std::vector<int> &arr)
{
  int left = 0, right = arr.size() - 1;
  while (left < right)
  {
    // Process current elements
    int current = process(arr[left], arr[right]);

    // Update pointers based on condition
    if (condition(arr[left], arr[right]))
    {
      left++;
    }
    else
    {
      right--;
    }
  }
}
