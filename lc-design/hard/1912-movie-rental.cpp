#include <vector>
#include <map>
#include <set>

struct Movie
{
  int id;
  int price;
  int shopId;
  Movie() = default;
  Movie(int id, int price, int shopId)
      : id(id), price(price), shopId(shopId) {}
};

struct PriceComparator
{
  bool operator()(const Movie &a, const Movie &b) const
  {
    if (a.price != b.price)
      return a.price < b.price;
    if (a.shopId != b.shopId)
      return a.shopId < b.shopId;
    return a.id < b.id;
  }
};

class MovieRentingSystem
{
  std::vector<std::unordered_map<int, Movie>> shops;
  // shop id (index) : movie id : Movie
  std::unordered_map<int, std::set<std::pair<int, int>>> unrentedMovies;
  // movie id : price, shop id
  std::set<Movie, PriceComparator> rentedMovies;

public:
  MovieRentingSystem(int n, std::vector<std::vector<int>> &entries)
  {
    shops.resize(n);
    for (std::vector<int> &entry : entries)
    {
      int shop = entry[0];
      int movie = entry[1];
      int price = entry[2];
      Movie mov(movie, price, shop);
      shops[shop][movie] = mov;
      unrentedMovies[movie].insert({price, shop});
    }
  }

  std::vector<int> search(int movie)
  {
    int toGet = 5;
    auto it = unrentedMovies[movie].begin();
    std::vector<int> res{};
    while (toGet > 0 && it != unrentedMovies[movie].end())
    {
      res.push_back((*it).second);
      ++it;
      --toGet;
    }
    return res;
  }

  void rent(int shop, int movie)
  {
    Movie &mov = shops[shop][movie];
    auto &unrented = unrentedMovies[movie];
    unrented.erase(unrented.find({mov.price, mov.shopId}));
    rentedMovies.insert(mov);
  }

  void drop(int shop, int movie)
  {
    Movie &mov = shops[shop][movie];
    unrentedMovies[movie].insert({mov.price, mov.shopId});
    rentedMovies.erase(rentedMovies.find(mov));
  }

  std::vector<std::vector<int>> report()
  {
    int toGet = 5;
    auto it = rentedMovies.begin();
    std::vector<std::vector<int>> res{};
    while (toGet > 0 && it != rentedMovies.end())
    {
      Movie movie = *it;
      res.push_back({movie.shopId, movie.id});
      ++it;
      --toGet;
    }
    return res;
  }
};