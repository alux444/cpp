#include <unordered_map>
#include <vector>
#include <set>
#include <map>
#include <string>

class FoodRatings
{
  std::unordered_map<std::string, std::pair<int, std::string>> foods;
  // food : rating, cuisine
  std::unordered_map<std::string,
                     std::map<int, std::set<std::string>>>
      cuisines;
  // cuisine : ordered map of ratings to lexicographically sorted foods
public:
  FoodRatings(std::vector<std::string> &foods, std::vector<std::string> &cuisines,
              std::vector<int> &ratings)
  {
    for (int i = 0; i < foods.size(); ++i)
    {
      std::string food = foods[i];
      std::string cuisine = cuisines[i];
      int rating = ratings[i];
      this->cuisines[cuisine][rating].insert(food);
      this->foods[food] = {rating, cuisine};
    }
  }

  void changeRating(std::string food, int newRating)
  {
    int prevRating = foods[food].first;
    std::string cuisine = foods[food].second;

    cuisines[cuisine][prevRating].erase(food);

    if (cuisines[cuisine][prevRating].empty())
      cuisines[cuisine].erase(prevRating);

    foods[food].first = newRating;
    cuisines[cuisine][newRating].insert(food);
  }

  std::string highestRated(std::string cuisine)
  {
    const auto &highestRatedIt = --cuisines[cuisine].end();
    return *highestRatedIt->second.begin();
  }
};