#include <catch2/catch_all.hpp>
#include "../src/hashset.cpp"
#include <string>

TEST_CASE("HashSet basic insert and contains", "[hashset][int]") {
    HashSet<int> set;
    REQUIRE(set.empty());
    REQUIRE(set.insert(1));
    REQUIRE(set.insert(2));
    REQUIRE_FALSE(set.insert(1)); // duplicate
    REQUIRE(set.size() == 2);
    REQUIRE(set.contains(1));
    REQUIRE(set.contains(2));
    REQUIRE_FALSE(set.contains(3));
}

TEST_CASE("HashSet erase elements", "[hashset][int]") {
    HashSet<int> set;
    set.insert(10);
    set.insert(20);
    set.insert(30);
    REQUIRE(set.size() == 3);
    REQUIRE(set.erase(20));
    REQUIRE_FALSE(set.contains(20));
    REQUIRE(set.size() == 2);
    REQUIRE_FALSE(set.erase(99)); // not present
}

TEST_CASE("HashSet works with string values", "[hashset][string]") {
    HashSet<std::string> set;
    set.insert("apple");
    set.insert("banana");
    REQUIRE(set.contains("apple"));
    REQUIRE(set.contains("banana"));
    REQUIRE_FALSE(set.contains("pear"));
    REQUIRE(set.erase("apple"));
    REQUIRE_FALSE(set.contains("apple"));
    REQUIRE(set.size() == 1);
}