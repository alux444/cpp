#include <catch2/catch_all.hpp>
#include "../src/hashmap.cpp"
#include <string>

TEST_CASE("HashMap basic insert and at", "[hashmap][int]") {
    HashMap<int, std::string> map;
    REQUIRE(map.empty());
    map.insert(1, "one");
    map.insert(2, "two");
    REQUIRE(map.size() == 2);
    REQUIRE(map.at(1) == "one");
    REQUIRE(map.at(2) == "two");
}

TEST_CASE("HashMap overwrite value", "[hashmap][int]") {
    HashMap<int, std::string> map;
    map.insert(1, "one");
    map.insert(1, "uno");
    REQUIRE(map.size() == 1);
    REQUIRE(map.at(1) == "uno");
}

TEST_CASE("HashMap contains and erase", "[hashmap][int]") {
    HashMap<int, std::string> map;
    map.insert(1, "one");
    map.insert(2, "two");
    REQUIRE(map.contains(1));
    REQUIRE(map.contains(2));
    REQUIRE(map.erase(1));
    REQUIRE_FALSE(map.contains(1));
    REQUIRE(map.size() == 1);
    REQUIRE_FALSE(map.erase(3)); // non-existent key
}

TEST_CASE("HashMap throws on missing key", "[hashmap][int]") {
    HashMap<int, std::string> map;
    map.insert(1, "one");
    REQUIRE_THROWS_AS(map.at(2), std::out_of_range);
}

TEST_CASE("HashMap works with string keys", "[hashmap][string]") {
    HashMap<std::string, int> map;
    map.insert("a", 1);
    map.insert("b", 2);
    REQUIRE(map.at("a") == 1);
    REQUIRE(map.at("b") == 2);
    REQUIRE(map.contains("a"));
    REQUIRE(map.erase("a"));
    REQUIRE_FALSE(map.contains("a"));
}

TEST_CASE("HashMap operator[] inserts default and returns reference", "[hashmap][operator[]]") {
    HashMap<int, std::string> map;
    REQUIRE(map.size() == 0);
    // Accessing a missing key should insert a default value
    std::string& ref = map[42];
    REQUIRE(map.size() == 1);
    REQUIRE(ref == "");
    // Assign through operator[]
    map[42] = "forty-two";
    REQUIRE(map.at(42) == "forty-two");
}