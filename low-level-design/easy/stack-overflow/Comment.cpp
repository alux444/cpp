#include <string>
#include <iostream>
#include "src/User.h"
#include "src/Comment.h"

int Comment::nextId = 1;

Comment::Comment()
    : id(nextId++) {};

Comment::Comment(const std::string &content, User *author, int timestamp)
    : id(nextId++), content(content), author(author), timestamp(timestamp) {};

void Comment::display() const
{
  std::cout << "Comment by " << (author ? author->username : "Unknown") << ": " << content << "\n";
};