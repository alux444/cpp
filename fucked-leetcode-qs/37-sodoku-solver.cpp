#include <vector>
using namespace std;

class Solution

{
public:
  void solveSudoku(vector<vector<char>> &board)
  {
    solve(board);
  }

  bool solve(vector<vector<char>> &board)
  {
    for (int r = 0; r < 9; ++r)
    {
      for (int c = 0; c < 9; ++c)
      {
        if (board[r][c] == '.')
        {
          for (char num = '1'; num <= '9'; ++num)
          {
            if (isValid(board, r, c, num))
            {
              board[r][c] = num;
              if (solve(board))
                return true;
              board[r][c] = '.';
            }
          }
          return false;
        }
      }
    }
    return true;
  }

  bool isValid(vector<vector<char>> &board, int r, int c, char num)
  {
    for (int i = 0; i < 9; ++i)
    {
      if (board[r][i] == num || board[i][c] == num)
        return false;
    }
    int startR = (r / 3) * 3;
    int startC = (c / 3) * 3;
    for (int i = startR; i < startR + 3; ++i)
    {
      for (int j = startC; j < startC + 3; ++j)
      {
        if (board[i][j] == num)
          return false;
      }
    }
    return true;
  }
};