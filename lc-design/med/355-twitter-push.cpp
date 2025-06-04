#include <unordered_set>
#include <list>
#include <vector>

/* Push to users. O(1) newsFeed() */

struct Tweet
{
  int time;
  int userId;
  int id;
  Tweet(int time, int userId, int id) : time(time), userId(userId), id(id) {}
};

class User
{
public:
  int id;
  std::unordered_set<User *> followedUsers;
  std::unordered_set<User *> followedBy;
  std::list<Tweet *> tweets;
  std::list<Tweet *> newsFeed;

  User(int id) : id(id) {}

  void addTweetToFeed(Tweet *tweet) { newsFeed.push_front(tweet); }

  void mergeTweets(User *other)
  {
    std::list<Tweet *> newTweets{};
    std::list<Tweet *> &otherTweets = other->tweets;
    auto tweets1 = this->newsFeed.begin();
    auto tweets2 = otherTweets.begin();

    while (tweets1 != this->newsFeed.end() ||
           tweets2 != otherTweets.end())
    {
      if (tweets1 == this->newsFeed.end())
      {
        newTweets.push_back(*tweets2);
        ++tweets2;
      }
      else if (tweets2 == otherTweets.end())
      {
        newTweets.push_back(*tweets1);
        ++tweets1;
      }
      else if ((*tweets1)->time > (*tweets2)->time)
      {
        newTweets.push_back(*tweets1);
        ++tweets1;
      }
      else
      {
        newTweets.push_back(*tweets2);
        ++tweets2;
      }
    }

    newsFeed = newTweets;
  }

  void removeTweetsFromUser(User *user)
  {
    for (auto it = newsFeed.begin(); it != newsFeed.end();)
    {
      if ((*it)->userId == user->id)
      {
        it = newsFeed.erase(it);
      }
      else
      {
        ++it;
      }
    }
  }
};

class Twitter
{
private:
  std::unordered_map<int, User *> users;
  int time;

  User *getUser(int userId)
  {
    if (!users.count(userId))
      users[userId] = new User(userId);
    return users[userId];
  }

public:
  Twitter() {}

  void postTweet(int userId, int tweetId)
  {
    User *user = getUser(userId);
    Tweet *newTweet = new Tweet(++time, userId, tweetId);

    user->tweets.push_front(newTweet);
    user->addTweetToFeed(newTweet);

    for (User *follower : user->followedBy)
      follower->addTweetToFeed(newTweet);
  }

  std::vector<int> getNewsFeed(int userId)
  {
    if (users.find(userId) == users.end())
      return {};
    std::vector<int> res;
    int toAdd = 10;
    for (Tweet *tweet : users[userId]->newsFeed)
    {
      res.push_back(tweet->id);
      --toAdd;
      if (toAdd == 0)
        break;
    }
    return res;
  }

  void follow(int followerId, int followeeId)
  {
    User *followee = getUser(followeeId);
    User *follower = getUser(followerId);

    if (follower->followedUsers.count(followee))
      return;

    follower->followedUsers.insert(followee);
    followee->followedBy.insert(follower);

    follower->mergeTweets(followee);
  }

  void unfollow(int followerId, int followeeId)
  {
    // remove the following
    users[followerId]->followedUsers.erase(users[followeeId]);
    users[followeeId]->followedBy.erase(users[followerId]);

    // remove all instances of the followees tweets from the followers feed
    users[followerId]->removeTweetsFromUser(users[followeeId]);
  }
};