#include <string>
#include <iostream>
#include <algorithm>

std::string trim(std::string &s)
{
  auto start = std::find_if(s.begin(), s.end(), [](char ch) -> bool
                            { return !std::isspace(ch); });
  auto end = std::find_if(s.rbegin(), s.rend(), [](char ch) -> bool
                          { return !std::isspace(ch); })
                 .base(); // return back to normal iterator
  if (start >= end)
    return "";

  return std::string(start, end);
};

int main()
{
  std::string s = " hel lo lo lo";
  std::cout << s << "\n";
  std::cout << trim(s) << "\n";
  s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
  std::cout << s << "\n";
}