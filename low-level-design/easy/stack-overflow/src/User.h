#pragma once

#include <string>
#include <vector>
#include <memory>

class Question;
class Answer;
class Comment;

class User
{
public:
  int id;
  std::string username;
  int reputation;
  std::vector<Question *> questions;
  std::vector<Answer *> answers;
  std::vector<Comment *> comments;

  User(std::string username);

private:
  static int nextId;
};