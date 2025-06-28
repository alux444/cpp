#pragma once

#include <vector>
#include "Comment.h"
#include "Tag.h"

class User;

class Post
{
public:
  Post();
  virtual ~Post() = default;

  virtual void display() const = 0;

  int id;
  std::string title;
  std::string content;
  User *author;
  std::vector<Comment> comments;
  std::vector<Tag> tags;
  int votes;
  int timestamp;

private:
  static int nextId;
};