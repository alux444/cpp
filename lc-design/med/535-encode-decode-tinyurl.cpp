#include <string>
#include <map>

class Solution
{
public:
  std::unordered_map<std::string, std::string> map;
  std::string baseUrl = "http://tinyurl.com/";

  std::string generateKey()
  {
    std::string str = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890";
    std::string key = "";
    int c = time(0);
    while (c)
    {
      key = key + str[c % str.size()];
      c /= str.size();
    }
    return key;
  }

  std::string encode(std::string longUrl)
  {
    std::string shortenedUrl = generateKey();
    map[shortenedUrl] = longUrl;
    return shortenedUrl;
  }

  std::string decode(std::string shortUrl)
  {
    return map[shortUrl];
  }
};