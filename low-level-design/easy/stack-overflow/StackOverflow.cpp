#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include "src/StackOverflow.h"

User *StackOverflow::createUser(const std::string &username)
{
  users.push_back(std::make_unique<User>(username));
  User *user = users.back().get();
  user->reputation = 0;
  return user;
}

Question *StackOverflow::postQuestion(User *author, const std::string &title, const std::string &content, const std::vector<Tag> &qtags, int timestamp)
{
  auto q = std::make_unique<Question>();
  q->title = title;
  q->content = content;
  q->author = author;
  q->tags = qtags;
  q->creationDate = timestamp;
  questions.push_back(std::move(q));
  author->questions.push_back(questions.back().get());
  return questions.back().get();
}

Answer *StackOverflow::postAnswer(User *author, Question *question, const std::string &content, int timestamp)
{
  auto a = std::make_unique<Answer>();
  a->content = content;
  a->author = author;
  a->creationDate = timestamp;
  question->answers.push_back(std::move(a));
  author->answers.push_back(question->answers.back().get());
  return question->answers.back().get();
}

void StackOverflow::postComment(User *author, Post *post, const std::string &content, int timestamp)
{
  post->comments.emplace_back(content, author, timestamp);
  author->comments.push_back(&post->comments.back());
}

void StackOverflow::vote(User *voter, Post *post, VoteType type)
{
  if (auto *q = dynamic_cast<Question *>(post))
  {
    q->votes.emplace_back(voter, type);
  }
  else if (auto *a = dynamic_cast<Answer *>(post))
  {
    a->votes.emplace_back(voter, type);
  }
  if (type == VoteType::UPVOTE)
  {
    post->author->reputation += 10;
  }
  else
  {
    post->author->reputation -= 2;
  }
}

std::vector<Question *> StackOverflow::searchByKeyword(const std::string &keyword)
{
  std::vector<Question *> result;
  for (auto &q : questions)
  {
    if (q->title.find(keyword) != std::string::npos || q->content.find(keyword) != std::string::npos)
      result.push_back(q.get());
  }
  return result;
}

std::vector<Question *> StackOverflow::searchByTag(const std::string &tagName)
{
  std::vector<Question *> result;
  for (auto &q : questions)
  {
    for (const auto &tag : q->tags)
    {
      if (tag.name == tagName)
        result.push_back(q.get());
    }
  }
  return result;
}

std::vector<Question *> StackOverflow::searchByUser(const std::string &username)
{
  std::vector<Question *> result;
  for (auto &q : questions)
  {
    if (q->author && q->author->username == username)
      result.push_back(q.get());
  }
  return result;
}