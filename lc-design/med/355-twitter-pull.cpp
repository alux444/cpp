#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

/* Pull from users. Less efficient newsFeed() */

struct CompareByTime
{
  bool operator()(std::vector<int> a, std::vector<int> b)
  {
    return b[1] > a[1];
  }
};

struct User
{
  std::unordered_set<int> following;
  std::unordered_set<int> followed;
  std::vector<std::vector<int>> tweets; // ordered by tweet ids asc

  User() : following{}, followed{}, tweets{} {}
};

class Twitter
{
private:
  int time;
  std::unordered_map<int, User *> users; // user id : user
public:
  Twitter() : users{}, time(0) {}

  // O(1)
  void postTweet(int userId, int tweetId)
  {
    if (users.find(userId) == users.end())
      users[userId] = new User();
    User *user = users[userId];
    user->tweets.push_back({tweetId, ++time});
  }

  // iterate through every follower
  std::vector<int> getNewsFeed(int userId)
  {
    if (users.find(userId) == users.end())
      return {};

    std::priority_queue<
        std::vector<int>,              // value type
        std::vector<std::vector<int>>, // container type
        CompareByTime>
        pq;
    for (std::vector<int> tweet : users[userId]->tweets)
      pq.push(tweet);
    for (int followingId : users[userId]->following)
    {
      for (std::vector<int> tweet : users[followingId]->tweets)
        pq.push(tweet);
    }
    // O(logn * users * tweets)
    int toAdd = 10;
    std::vector<int> res{};
    // O(10 logn);
    while (!pq.empty() && toAdd > 0)
    {
      res.push_back(pq.top()[0]);
      pq.pop();
      toAdd--;
    }
    return res;
  }

  // O(1)
  void follow(int followerId, int followeeId)
  {
    if (users.find(followerId) == users.end())
      users[followerId] = new User();
    if (users.find(followeeId) == users.end())
      users[followeeId] = new User();

    users[followerId]->following.insert(followeeId);
    users[followeeId]->followed.insert(followerId);
  }

  // O(1)
  void unfollow(int followerId, int followeeId)
  {
    users[followerId]->following.erase(followeeId);
    users[followeeId]->followed.erase(followerId);
  }
};