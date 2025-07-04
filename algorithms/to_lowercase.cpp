#include <string>

void to_lowercase(std::string &s)
{
  std::transform(s.begin(), s.end(), s.begin(), [](const char &a)
                 { return std::tolower(a); });
}