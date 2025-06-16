#include <vector>
#include <array>

class ATM
{
  std::array<int, 5> notes;
  std::array<int, 5> values;

public:
  ATM() : notes{0} { values = {20, 50, 100, 200, 500}; }

  void deposit(std::vector<int> banknotesCount)
  {
    for (int i = 0; i < banknotesCount.size(); ++i)
      notes[i] += banknotesCount[i];
  }

  std::vector<int> withdraw(int amount)
  {
    std::array<int, 5> res{0};

    for (int i = 4; i >= 0; --i)
    {
      if (amount >= values[i])
      {
        int maxNotes = amount / values[i];
        int toUse = std::min(maxNotes, notes[i]);
        res[i] = toUse;
        amount -= toUse * values[i];
      }
    }

    if (amount == 0)
    {
      for (int i = 0; i < 5; ++i)
        notes[i] -= res[i];
      return std::vector<int>(res.begin(), res.end());
    }

    return {-1};
  }
};