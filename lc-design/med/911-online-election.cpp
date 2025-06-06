#include <vector>
#include <unordered_map>

class TopVotedCandidate
{
  std::unordered_map<int, int> map; // time : person leading
  std::vector<int> times;

public:
  TopVotedCandidate(std::vector<int> &persons, std::vector<int> &times) : times(times)
  {
    int n = times.size();
    int top = -1;
    std::unordered_map<int, int> votes; // person : votes
    for (int i = 0; i < n; i++)
    {
      int person = persons[i];
      int time = times[i];
      ++votes[person];
      if (votes[person] >= votes[top])
        top = person;
      map[times[i]] = top;
    }
  }

  int q(int t)
  {
    return map[*--std::upper_bound(times.begin(), times.end(), t)];
  }
};