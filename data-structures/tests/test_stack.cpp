#include <catch2/catch_all.hpp>
#include "../src/stack.cpp"
#include <string>

TEST_CASE("Stack<int> basic push and pop", "[stack][int]") {
    Stack<int> s;
    REQUIRE(s.empty());
    s.push(1);
    s.push(2);
    s.push(3);
    REQUIRE(s.size() == 3);
    REQUIRE_FALSE(s.empty());

    REQUIRE(s.pop() == 3);
    REQUIRE(s.pop() == 2);
    REQUIRE(s.pop() == 1);
    REQUIRE(s.empty());
}

TEST_CASE("Stack<std::string> works", "[stack][string]") {
    Stack<std::string> s;
    s.push("a");
    s.push("b");
    REQUIRE(s.size() == 2);
    REQUIRE(s.pop() == "b");
    REQUIRE(s.pop() == "a");
    REQUIRE(s.empty());
}

TEST_CASE("Stack<int> underflow throws", "[stack][int][underflow]") {
    Stack<int> s;
    REQUIRE_THROWS_AS(s.pop(), std::out_of_range);
}

TEST_CASE("Stack<int> handles overflow", "[stack][int][overflow]") {
    Stack<int> s;
    for (int i = 0; i < MAX_SIZE; ++i) {
        s.push(i);
    }
    // Next push should not increase size
    s.push(999);
    REQUIRE(s.size() == MAX_SIZE);
}