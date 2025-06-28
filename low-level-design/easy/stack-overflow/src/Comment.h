#pragma once
#include <string>

class User;

class Comment
{
public:
  int id;
  std::string content;
  User *author;
  int timestamp;

  Comment();
  Comment(const std::string& content, User* author, int timestamp);

  void display() const;
private:
  static int nextId;
};