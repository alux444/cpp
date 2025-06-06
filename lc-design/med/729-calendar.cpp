#include <map>

class MyCalendar
{
    std::map<int, int> calendar; // start : end
public:
    MyCalendar() {}

    bool book(int startTime, int endTime)
    {
        auto next = calendar.lower_bound(startTime); // binary search
        if (next != calendar.end() && next->first < endTime)
            return false; // if the start time is less than the end time, there's overlap
        if (next != calendar.begin() && prev(next)->second > startTime)
            return false; // if the end time is greater than the start time, there's overlap
        calendar[startTime] = endTime;
        return true;
    }
};