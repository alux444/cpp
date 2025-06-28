#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "Post.h"
#include "Vote.h"

class Answer : public Post
{
public:
  std::vector<Vote> votes;
  int creationDate;

  Answer();

  void display() const override;
};