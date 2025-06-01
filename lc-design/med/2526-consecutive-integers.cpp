class DataStream
{
private:
  int value;
  int count;
  int k;

public:
  DataStream(int value, int k) : value(value), k(k), count(0) {}

  bool consec(int num)
  {
    num == value ? count++ : count = 0;
    return count >= k;
  }
};