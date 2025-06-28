#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "src/Question.h"
#include "src/User.h"

Question::Question() : Post() {};

void Question::display() const
{
  std::cout << "Question by: " << (author ? author->username : "Unknown") << ": " << content << "\n";
  for (const auto &tag : tags)
    std::cout << "#" << tag.name << " ";
  std::cout << "\nVotes: " << votes.size() << "\n";
  for (const auto &answer : answers)
    answer->display();
  for (const auto &comment : comments)
    comment.display();
}