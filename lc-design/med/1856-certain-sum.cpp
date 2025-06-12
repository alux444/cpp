#include <unordered_map>
#include <vector>

class FindSumPairs
{
  std::unordered_map<int, int> nums2cnt;
  std::vector<int> nums2;
  std::vector<int> nums1;

  // only bc nums1 len <<<<< nums2 len
public:
  FindSumPairs(std::vector<int> &nums1, std::vector<int> &nums2) : nums1(nums1), nums2(nums2)
  {
    for (int num : nums2)
      nums2cnt[num]++;
  }

  void add(int index, int val)
  {
    int prev = nums2[index];
    nums2cnt[prev]--;
    nums2[index] += val;
    nums2cnt[prev + val]++;
  }

  int count(int tot)
  {
    int sum = 0;
    for (int num : nums1)
    {
      int need = tot - num;
      sum += nums2cnt[need];
    }
    return sum;
  }
};