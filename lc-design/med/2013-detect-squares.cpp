#include <map>
#include <vector>

class DetectSquares {
private:
    std::map<std::pair<int, int>, int> map; 
    // std::map doesn't need a hash, only a defined order (operator<)
    // but std::unordered_map needs a hash, so would have to define a custom fn 

public:
    DetectSquares() {}

    void add(std::vector<int> point) {
        map[{point[0], point[1]}]++;
    }

    int count(std::vector<int> point) {
        int x = point[0];
        int y = point[1];
        int count = 0;

        for (auto &[point, _] : map)
        {
            if (
                point.first != x && // cant have same x or y
                point.second != y &&
                (std::abs(point.first - x) == std::abs(point.second - y)) // difference between the x and y axis have to be the same for a square
            ) {
                int point1 = map[{point.first, point.second}];
                int point2 = map[{point.first, y}];
                int point3 = map[{x, point.second}];
                count += point1*point2*point3;
            }
        }
        return count;
    }
};