#include <vector>
#include <algorithm>

class ExamRoom
{
  int n;
  std::vector<int> seats;

public:
  ExamRoom(int n) : n(n)
  {
  }

  int seat()
  {
    if (seats.size() == 0)
    {
      seats.push_back(0);
      return 0;
    }
    int dist = std::max(seats[0], n - 1 - seats.back());
    // dist between 0 to 1st person and last person to the last seat

    // check between everyone
    for (int i = 0; i < seats.size() - 1; i++)
    {
      int diff = (seats[i + 1] - seats[i]) / 2;
      dist = std::max(diff, dist);
    }

    if (dist == seats[0]) // first seat is best
    {
      seats.insert(seats.begin(), 0);
      return 0;
    }

    // find the index with the best diff
    for (int i = 0; i < seats.size() - 1; i++)
    {
      int diff = (seats[i + 1] - seats[i]) / 2;
      if (diff == dist)
      {
        int index = (seats[i + 1] + seats[i]) / 2;
        seats.insert(seats.begin() + i + 1, index);
        return index;
      }
    }

    // the max must be the end
    seats.push_back(n - 1);
    return n - 1;
  }

  void leave(int p)
  {
    auto it = std::find(seats.begin(), seats.end(), p);
    if (it != seats.end())
      seats.erase(it);
  }
};