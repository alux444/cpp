#pragma once

class User;

enum class VoteType
{
  UPVOTE,
  DOWNVOTE
};

class Vote
{
public:
  User *voter;
  VoteType type;

  Vote(User *voter, VoteType type);
};