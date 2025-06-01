#include <vector>

class SubrectangleQueries
{
private:
  std::vector<std::vector<int>> rectangle;

public:
  SubrectangleQueries(std::vector<std::vector<int>> &rectangle) : rectangle(rectangle) {}

  void updateSubrectangle(int row1, int col1, int row2, int col2, int newValue)
  {
    for (int r = row1; r <= row2; r++)
    {
      for (int c = col1; c <= col2; c++)
        rectangle[r][c] = newValue;
    }
  }

  int getValue(int row, int col)
  {
    return rectangle[row][col];
  }
};