#include <iostream>

// Define the structs Workshops and Available_Workshops.
// Implement the functions initialize and CalculateMaxWorkshops

struct Workshop
{
  int startTime;
  int duration;
  int endTime;
  Workshop() : startTime(0), duration(0), endTime(0) {}
  Workshop(int startTime, int duration, int endTime) : startTime(startTime), duration(duration), endTime(endTime) {}
};

struct Available_Workshops
{
  int n;
  Workshop *workshops;

  Available_Workshops(int count) : n(count), workshops(new Workshop[n]) {}
};

Available_Workshops *initialize(int start_time[], int duration[], int n)
{
  Available_Workshops *pAW = new Available_Workshops(n);
  for (int i = 0; i < n; i++)
  {
    pAW->workshops[i] = Workshop(start_time[i], duration[i], start_time[i] + duration[i]);
  }
  return pAW;
};

int CalculateMaxWorkshops(Available_Workshops *pAW)
{
  std::sort(pAW->workshops, pAW->workshops + pAW->n, [](const Workshop &a, const Workshop &b)
            { return a.endTime < b.endTime; });

  int maxWorkshops{};
  int curEnd{};
  for (int i = 0; i < pAW->n; i++)
  {
    if (pAW->workshops[i].startTime >= curEnd)
    {
      curEnd = pAW->workshops[i].endTime;
      maxWorkshops++;
    }
  }
  return maxWorkshops;
};

int main(int argc, char *argv[])
{
  int n; // number of workshops
  std::cin >> n;
  // create arrays of unknown size n
  int *start_time = new int[n];
  int *duration = new int[n];

  for (int i = 0; i < n; i++)
  {
    std::cin >> start_time[i];
  }
  for (int i = 0; i < n; i++)
  {
    std::cin >> duration[i];
  }

  Available_Workshops *ptr;
  ptr = initialize(start_time, duration, n);
  std::cout << CalculateMaxWorkshops(ptr) << std::endl;
  return 0;
}
