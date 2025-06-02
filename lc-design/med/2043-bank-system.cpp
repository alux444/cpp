#include <vector>

class Bank
{
  std::vector<long long> balance;

public:
  Bank(std::vector<long long> &balance)
  {
    this->balance = balance;
  }

  bool isValidAccount(int account)
  {
    return account >= 0 && account < balance.size();
  }

  bool transfer(int account1, int account2, long long money)
  {
    account1--;
    account2--;

    if (!isValidAccount(account1) || !isValidAccount(account2))
      return false;
    if (balance[account1] < money)
      return false;

    balance[account2] += money;
    balance[account1] -= money;
    return true;
  }

  bool deposit(int account, long long money)
  {
    account--;

    if (!isValidAccount(account))
      return false;

    balance[account] += money;
    return true;
  }

  bool withdraw(int account, long long money)
  {
    account--;
    if (!isValidAccount(account) || balance[account] < money)
      return false;
    balance[account] -= money;
    return true;
  }
};