#include <unordered_map>
#include <unordered_set>
#include <map>
#include <string>

class AuthenticationManager
{
  std::unordered_map<std::string, int> tokenToExpiry;
  std::map<int, std::unordered_set<std::string>> expiryTimesToTokens;
  int timeToLive;

public:
  AuthenticationManager(int timeToLive) : timeToLive(timeToLive) {}

  void generate(std::string tokenId, int currentTime)
  {
    if (tokenToExpiry.find(tokenId) != tokenToExpiry.end())
      return;
    tokenToExpiry[tokenId] = currentTime + timeToLive;
    expiryTimesToTokens[currentTime + timeToLive].insert(tokenId);
  }

  void renew(std::string tokenId, int currentTime)
  {
    if (tokenToExpiry.find(tokenId) == tokenToExpiry.end() ||
        tokenToExpiry[tokenId] <= currentTime)
      return;
    int prevExpiry = tokenToExpiry[tokenId];
    tokenToExpiry[tokenId] = currentTime + timeToLive;
    expiryTimesToTokens[prevExpiry].erase(tokenId);
    expiryTimesToTokens[currentTime + timeToLive].insert(tokenId);
  }

  int countUnexpiredTokens(int currentTime)
  {
    auto it = expiryTimesToTokens.upper_bound(currentTime);
    int res = 0;
    while (it != expiryTimesToTokens.end())
    {
      res += it->second.size();
      ++it;
    }
    return res;
  }
};