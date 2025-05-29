#include <catch2/catch_all.hpp>
#include "../src/list.cpp"
#include <string>

TEST_CASE("List<int> basic push_back and access", "[list][int]") {
    List<int> l;
    REQUIRE(l.empty());
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    REQUIRE(l.size() == 3);
    REQUIRE(*l.front() == 1);
    REQUIRE(*l.back() == 3);
    REQUIRE(l[0] == 1);
    REQUIRE(l[1] == 2);
    REQUIRE(l[2] == 3);
}

TEST_CASE("List<int> insert at various positions", "[list][int]") {
    List<int> l;
    l.push_back(1);
    l.push_back(3);
    l.insert(1, 2); // Insert 2 at position 1
    REQUIRE(l.size() == 3);
    REQUIRE(l[0] == 1);
    REQUIRE(l[1] == 2);
    REQUIRE(l[2] == 3);

    l.insert(0, 0); // Insert 0 at front
    REQUIRE(l[0] == 0);
    REQUIRE(l.size() == 4);

    l.insert(l.size(), 4); // Insert at end
    REQUIRE(l[l.size()-1] == 4);
    REQUIRE(l.size() == 5);
}

TEST_CASE("List<int> erase elements", "[list][int]") {
    List<int> l;
    for (int i = 0; i < 5; ++i) l.push_back(i); // [0,1,2,3,4]
    l.erase(0); // remove front
    REQUIRE(l[0] == 1);
    REQUIRE(l.size() == 4);

    l.erase(2); // remove index 2 (was 3)
    REQUIRE(l[2] == 4);
    REQUIRE(l.size() == 3);

    l.erase(l.size()-1); // remove back
    REQUIRE(l.size() == 2);
    REQUIRE(*l.back() == 2);
}

TEST_CASE("List<int> out of bounds access throws", "[list][int]") {
    List<int> l;
    l.push_back(1);
    REQUIRE_THROWS_AS(l[1], std::out_of_range);
    REQUIRE_THROWS_AS(l[-1], std::out_of_range);
}

TEST_CASE("List<int> insert and erase out of bounds throws", "[list][int]") {
    List<int> l;
    REQUIRE_THROWS_AS(l.insert(1, 10), std::out_of_range);
    l.push_back(1);
    REQUIRE_THROWS_AS(l.erase(1), std::out_of_range);
    REQUIRE_THROWS_AS(l.erase(-1), std::out_of_range);
}

TEST_CASE("List<std::string> works", "[list][string]") {
    List<std::string> l;
    l.push_back("a");
    l.push_back("b");
    l.insert(1, "c");
    REQUIRE(l.size() == 3);
    REQUIRE(l[0] == "a");
    REQUIRE(l[1] == "c");
    REQUIRE(l[2] == "b");
    l.erase(1);
    REQUIRE(l[1] == "b");
}

TEST_CASE("List<int> resizes correctly on push_back", "[list][resize]") {
    List<int> l(2); // start with small capacity
    REQUIRE(l.size() == 0);
    l.push_back(1);
    l.push_back(2);
    REQUIRE(l.size() == 2);
    l.push_back(3); // should trigger resize
    REQUIRE(l.size() == 3);
    REQUIRE(l[0] == 1);
    REQUIRE(l[1] == 2);
    REQUIRE(l[2] == 3);
    for (int i = 4; i <= 100; ++i) {
        l.push_back(i);
    }
    REQUIRE(l.size() == 100);
    REQUIRE(l[99] == 100);
}

TEST_CASE("List<std::string> resizes and preserves data", "[list][resize][string]") {
    List<std::string> l(1);
    l.push_back("a");
    l.push_back("b"); // triggers resize
    l.push_back("c");
    REQUIRE(l.size() == 3);
    REQUIRE(l[0] == "a");
    REQUIRE(l[1] == "b");
    REQUIRE(l[2] == "c");
}