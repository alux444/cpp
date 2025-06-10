#include <string>
#include <set>

struct Location
{
  std::string name;
  int score;
  Location(std::string name, int score) : name(name), score(score) {}
};

struct LocComparator
{
  bool operator()(const Location &a, const Location &b) const
  {
    if (a.score == b.score)
      return a.name < b.name; // lexico smallest -> highest
    return a.score > b.score; // score by max
  }
};

class SORTracker
{
  std::set<Location, LocComparator> locations;
  std::set<Location, LocComparator>::iterator kthGetIter;
  bool isFirstGetCalled;

public:
  SORTracker() : isFirstGetCalled(false)
  {
  }

  void add(std::string name, int score)
  {
    Location loc = Location(name, score);

    bool decrementIter = false;
    if (isFirstGetCalled)
    {
      if (LocComparator()(loc, *kthGetIter))
        decrementIter = true;
      // if this loc is better - it's going to be inserted BEFORE out iterator
      // so update the iterator to the correct value as needed
    }
    locations.insert(loc);
    if (decrementIter && kthGetIter != locations.begin())
      --kthGetIter;
  }

  std::string get()
  {
    if (!isFirstGetCalled)
    {
      kthGetIter = locations.begin();
      isFirstGetCalled = true;
    }
    else
    {
      ++kthGetIter;
    }
    return kthGetIter->name;
  }
};