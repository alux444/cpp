#include "src/StackOverflow.h"
#include <iostream>

int main()
{
  StackOverflow so;

  // Create users
  User *alice = so.createUser("alice");
  User *bob = so.createUser("bob");

  // Create tags
  Tag cppTag(1, "cpp");
  Tag designTag(2, "design");

  // Post a question
  Question *q1 = so.postQuestion(alice, "How to use virtual functions in C++?", "I want to understand virtual functions.", {cppTag, designTag}, 1000);

  // Bob answers
  Answer *a1 = so.postAnswer(bob, q1, "You use the 'virtual' keyword in the base class.", 1001);

  // Alice comments on Bob's answer
  so.postComment(alice, a1, "Thanks, that's helpful!", 1002);

  // Bob upvotes Alice's question
  so.vote(bob, q1, VoteType::UPVOTE);

  // Search by tag
  auto cppQuestions = so.searchByTag("cpp");
  std::cout << "Questions tagged 'cpp':\n";
  for (auto *q : cppQuestions)
  {
    q->display();
  }

  // Show reputation
  std::cout << "Alice's reputation: " << alice->reputation << "\n";
  std::cout << "Bob's reputation: " << bob->reputation << "\n";
}