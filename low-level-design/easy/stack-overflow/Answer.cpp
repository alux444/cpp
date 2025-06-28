#include <string>
#include <vector>
#include <iostream>
#include "src/Answer.h"
#include "src/User.h"

Answer::Answer() : Post() {};

void Answer::display() const
{
  std::cout << "Answer by: " << (author ? author->username : "Unknown") << ": " << content << "\n";
  std::cout << "Votes: " << votes.size() << "\n";
  for (const auto &comment : comments)
    comment.display();
}