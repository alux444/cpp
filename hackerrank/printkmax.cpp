#include <iostream>
#include <deque>
using namespace std;

void printKMax(int arr[], int n, int k)
{
  std::deque<int> indices{};
  for (int i = 0; i < n; i++)
  {
    if (!indices.empty() && indices.front() <= i - k)
    {
      indices.pop_front();
    }
    while (!indices.empty() && arr[indices.back()] < arr[i])
    {
      indices.pop_back();
    }
    indices.push_back(i);

    if (i >= k - 1)
    {
      std::cout << arr[indices.front()] << " ";
    }
  }
  std::cout << std::endl;
}

int main()
{

  int t;
  cin >> t;
  while (t > 0)
  {
    int n, k;
    cin >> n >> k;
    int i;
    int arr[n];
    for (i = 0; i < n; i++)
      cin >> arr[i];
    printKMax(arr, n, k);
    t--;
  }
  return 0;
}