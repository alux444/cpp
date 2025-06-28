#pragma once

#include <vector>
#include <string>
#include "User.h"
#include "Question.h"
#include "Answer.h"
#include "Comment.h"
#include "Tag.h"
#include "Vote.h"

class StackOverflow
{
  std::vector<std::unique_ptr<User>> users;
  std::vector<std::unique_ptr<Question>> questions;
  std::vector<Tag> tags;

public:
  User *createUser(const std::string &username);

  Question *postQuestion(User *author, const std::string &title, const std::string &content, const std::vector<Tag> &qtags, int timestamp);

  Answer *postAnswer(User *author, Question *question, const std::string &content, int timestamp);

  void postComment(User *author, Post *post, const std::string &content, int timestamp);

  void vote(User *voter, Post *post, VoteType type);

  std::vector<Question *> searchByKeyword(const std::string &keyword);

  std::vector<Question *> searchByTag(const std::string &tagName);

  std::vector<Question *> searchByUser(const std::string &username);
};