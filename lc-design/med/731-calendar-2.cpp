#include <vector>

class MyCalendarTwo
{
  std::vector<std::array<int, 2>> bookings;
  std::vector<std::array<int, 2>> overlappingBookings;

  bool isOverlapped(int s1, int e1, int s2, int e2)
  {
    // [s1,e1] [s2,e2] overlapping or not
    return !(e1 <= s2 || e2 <= s1);
  }

  std::array<int, 2> getOverlapped(int s1, int e1, int s2, int e2)
  {
    return {std::max(s1, s2), std::min(e1, e2)};
  }

public:
  MyCalendarTwo() {}

  bool book(int startTime, int endTime)
  {
    // check overlapping
    for (const auto &[start, end] : overlappingBookings)
    {
      if (isOverlapped(startTime, endTime, start, end))
        return false;
    }

    for (const auto &[start, end] : bookings)
    {
      if (isOverlapped(startTime, endTime, start, end))
      {
        overlappingBookings.push_back(
            getOverlapped(startTime, endTime, start, end));
      }
    }

    bookings.push_back({startTime, endTime});
    return true;
  }
};