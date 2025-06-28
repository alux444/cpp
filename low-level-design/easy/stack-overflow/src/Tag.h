#pragma once
#include <string>

class Tag
{
public:
  int id;
  std::string name;

  Tag(int id, const std::string &name);
};