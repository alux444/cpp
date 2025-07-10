#include <vector>
#include <unordered_set>

using namespace std;

class Solution
{
public:
  vector<vector<string>> solveNQueens(int n)
  {
    unordered_set<int> cols;
    unordered_set<int> posRows; // r + c
    unordered_set<int> negRows; // r - c
    vector<vector<string>> res;
    vector<vector<char>> board;
    board.resize(n, vector<char>(n, '.'));
    backtrack(res, cols, posRows, negRows, 0, n, board);
    return res;
  }

  void backtrack(
      vector<vector<string>> &res,
      unordered_set<int> &cols,
      unordered_set<int> &posRows,
      unordered_set<int> &negRows,
      int row,
      int n,
      vector<vector<char>> &board)
  {
    if (row == n)
    {
      vector<string> cur{};
      for (vector<char> &r : board)
      {
        string s = {r.begin(), r.end()};
        cur.push_back(s);
      }
      res.push_back(cur);
      return;
    }
    // col
    for (int c = 0; c < n; ++c)
    {
      if (!cols.count(c) && !posRows.count(row + c) && !negRows.count(row - c))
      {
        board[row][c] = 'Q';
        cols.insert(c);
        posRows.insert(row + c);
        negRows.insert(row - c);
        backtrack(res, cols, posRows, negRows, row + 1, n, board);
        board[row][c] = '.';
        cols.erase(c);
        posRows.erase(row + c);
        negRows.erase(row - c);
      }
    }
  }
};