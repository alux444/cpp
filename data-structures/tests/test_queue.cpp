#include <catch2/catch_all.hpp>
#include "../src/queue.cpp"

#include <string>
#include <stdexcept>

TEST_CASE("Queue<int> basic operations", "[queue][int]") {
    Queue<int> q;

    REQUIRE(q.empty());
    q.enqueue(10);
    REQUIRE_FALSE(q.empty());
    q.enqueue(20);
    q.enqueue(30);

    REQUIRE(q.deque() == 10);
    REQUIRE(q.deque() == 20);
    REQUIRE(q.deque() == 30);
    REQUIRE(q.empty());
}

TEST_CASE("Queue<std::string> basic operations", "[queue][string]") {
    Queue<std::string> q;

    REQUIRE(q.empty());
    q.enqueue("hello");
    q.enqueue("world");

    REQUIRE(q.deque() == "hello");
    REQUIRE(q.deque() == "world");
    REQUIRE(q.empty());
}

TEST_CASE("Queue handles overflow", "[queue][overflow]") {
    Queue<int> q;
    for (int i = 0; i < MAX_SIZE; ++i) {
        q.enqueue(i);
    }
    // Next enqueue should not add a new element
    q.enqueue(999);
    // Dequeue all and check values
    for (int i = 0; i < MAX_SIZE; ++i) {
        REQUIRE(q.deque() == i);
    }
    REQUIRE(q.empty());
}

TEST_CASE("Queue handles underflow", "[queue][underflow]") {
    Queue<int> q;
    REQUIRE_THROWS_AS(q.deque(), std::out_of_range);
}

TEST_CASE("Queue<int> size and empty checks", "[queue][int]") {
    Queue<int> q;

    REQUIRE(q.empty());
    REQUIRE(q.size() == 0);

    q.enqueue(1);
    REQUIRE_FALSE(q.empty());
    REQUIRE(q.size() == 1);

    q.enqueue(2);
    q.enqueue(3);
    REQUIRE(q.size() == 3);

    q.deque();
    REQUIRE(q.size() == 2);

    q.deque();
    q.deque();
    REQUIRE(q.empty());
    REQUIRE(q.size() == 0);
}

