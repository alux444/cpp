#include <vector>

// fixed size
template <typename W, typename T>
W sliding_window_fixed(std::vector<T> input, int window_size)
{
  W ans = window = std::vector<T>(input.begin(), input.begin() + window_size);
  for (int right = window_size; right < input.size(); ++right)
  {
    int left = right - window_size;
    remove input[left] from window
        append input[right] to window
            ans = optimal(ans, window);
    return ans;
  }
}

// longest
template <typename W, typename T>
W sliding_window_flexible_longest(std::vector<T> input)
{
  initialize window, ans int left = 0;
  for (int right = 0; right < input.size(); ++right)
  {
    append input[right] to window while (invalid(window))
    {
      remove input[left] from window++ left;
    }
    ans = std::max(ans, window); // window is guaranteed to be valid here
  }
  return ans;
}

template <typename W, typename T>
W sliding_window_flexible_shortest(std::vector<T> input)
{
  initialize window, ans int left = 0;
  for (int right = 0; right < input.size(); ++right)
  {
    append input[right] to window while (valid(window))
    {
      ans = std::min(ans, window); // window is guaranteed to be valid here
      remove input[left] from window++ left;
    }
  }
  return ans;
}
