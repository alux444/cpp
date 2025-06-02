#include <map>
#include <unordered_map>
#include <unordered_set>
class StockPrice
{
private:
    // price -> frequency of that price
    std::map<int, int> priceFrequency;

    // timestamp -> price
    std::unordered_map<int, int> timestampMap;

    int latestTimestamp = 0;

public:
    StockPrice() {}

    void update(int timestamp, int price)
    {
        if (timestampMap.count(timestamp))
        {
            int prevPrice = timestampMap[timestamp];
            priceFrequency[prevPrice]--;
            if (priceFrequency[prevPrice] == 0)
                priceFrequency.erase(prevPrice);
        }

        timestampMap[timestamp] = price;
        priceFrequency[price]++;

        if (timestamp > latestTimestamp)
            latestTimestamp = timestamp;
    }

    int current()
    {
        return timestampMap[latestTimestamp];
    }

    int maximum()
    {
        return priceFrequency.rbegin()->first;
    }

    int minimum()
    {
        return priceFrequency.begin()->first;
    }
};
