#include <vector>
#include <map>
#include <unordered_map>

struct PriorityAndTaskIdDescendingComparator
{
  bool operator()(const std::pair<int, int> &a, const std::pair<int, int> &b) const
  {
    if (a.first != b.first)
      return a.first > b.first;
    return a.second > b.second;
  }
};

class TaskManager
{
  // ordering by priority
  // priority, taskid : user
  std::map<std::pair<int, int>, int, PriorityAndTaskIdDescendingComparator> priorities;

  // unordered map by ids
  // taskid : user, priority
  std::unordered_map<int, std::pair<int, int>> tasks;

public:
  TaskManager(std::vector<std::vector<int>> &tasks)
  {
    for (const auto &task : tasks)
    {
      int userId = task[0];
      int taskId = task[1];
      int priority = task[2];
      priorities[{priority, taskId}] = userId;
      this->tasks[taskId] = {userId, priority};
    }
  }

  void add(int userId, int taskId, int priority)
  {
    priorities[{priority, taskId}] = userId;
    tasks[taskId] = {userId, priority};
  }

  void edit(int taskId, int newPriority)
  {
    std::pair<int, int> task = tasks[taskId];

    priorities.erase({task.second, taskId});
    priorities[{newPriority, taskId}] = task.first;

    tasks[taskId] = {task.first, newPriority};
  }

  void rmv(int taskId)
  {
    std::pair<int, int> task = tasks[taskId];
    tasks.erase(taskId);
    priorities.erase({task.second, taskId});
  }

  int execTop()
  {
    if (priorities.empty())
      return -1;
    auto it = priorities.begin();
    int taskId = it->first.second;
    priorities.erase(it);

    int user = tasks[taskId].first;
    tasks.erase(taskId);

    return user;
  }
};