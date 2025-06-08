#include <unordered_map>
#include <vector>

class TweetCounts
{
  std::unordered_map<std::string, std::vector<int>> tweets;
  // tweetName : vector of times
public:
  TweetCounts() : tweets{} {}

  void recordTweet(std::string tweetName, int time)
  {
    std::vector<int> &times = tweets[tweetName];
    times.insert(std::upper_bound(times.begin(), times.end(), time),
                 time);
  }

  std::vector<int> getTweetCountsPerFrequency(std::string freq, std::string tweetName,
                                              int startTime, int endTime)
  {
    int interval = freq == "minute" ? 60
                   : freq == "hour" ? 60 * 60
                   : freq == "day"
                       ? 24 * 60 * 60
                       : -1;
    std::vector<int> res{};
    const std::vector<int> &times = tweets[tweetName];
    auto prevIt = std::upper_bound(times.begin(), times.end(), --startTime);
    // next iterator above the startTime -1 (so first value above startTime);

    while (startTime != endTime)
    {
      startTime = std::min(endTime, startTime + interval);
      auto nextIt = upper_bound(prevIt, times.end(), startTime);
      res.push_back(nextIt - prevIt);
      prevIt = nextIt;
    }
    return res;
  }
};