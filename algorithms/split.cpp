#include <string>
#include <vector>
#include <sstream>
#include <iostream>

std::vector<std::string> split(const std::string &str, char delimiter)
{
  std::vector<std::string> result;
  std::stringstream ss(str);
  std::string token;

  while (std::getline(ss, token, delimiter))
  {
    result.push_back(token);
  }

  return result;
}

int main()
{
  std::string str = "one,two,three";
  std::vector<std::string> splitted = split(str, ',');
  for (std::string s : splitted)
    std::cout << s << '\n';
}
