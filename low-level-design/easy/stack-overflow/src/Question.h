#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "Post.h"
#include "Answer.h"
#include "Tag.h"
#include "Vote.h"

class Answer;

class Question : public Post
{
public:
  std::vector<std::unique_ptr<Answer>> answers;
  std::vector<Tag> tags;
  std::vector<Vote> votes;
  int creationDate;

  Question();

  void display() const override;
};