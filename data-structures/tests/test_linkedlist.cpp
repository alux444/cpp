#include <catch2/catch_all.hpp>
#include "../src/linkedlist.cpp"
#include <string>

TEST_CASE("LinkedList<int> initially empty", "[linkedlist]") {
  LinkedList<int> list;
  REQUIRE(list.empty());  
}

TEST_CASE("LinkedList<int> push_front and peek_front", "[linkedlist][int]") {
  LinkedList<int> list;
  REQUIRE(list.empty());  
}

TEST_CASE("LinkedList<int> push_front and push_back", "[linkedlist][int]") {
    LinkedList<int> list;
    REQUIRE(list.empty());
    list.push_front(2);
    list.push_front(1);
    list.push_back(3);
    list.push_back(4);

    REQUIRE(list.peek_front()->value == 1);
    REQUIRE(list.peek_back()->value == 4);
    REQUIRE(list.size == 4);
}

TEST_CASE("LinkedList<int> erase by index", "[linkedlist][int]") {
    LinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    REQUIRE(list.erase(1)); // remove 20
    REQUIRE(list.size == 2);
    REQUIRE(list.peek_front()->value == 10);
    REQUIRE(list.peek_back()->value == 30);
}

TEST_CASE("LinkedList<std::string> find and erase by node", "[linkedlist][string]") {
    LinkedList<std::string> list;
    list.push_back("a");
    list.push_back("b");
    list.push_back("c");

    Node<std::string>* node = list.find("b");
    REQUIRE(node != nullptr);
    REQUIRE(node->value == "b");
    REQUIRE(list.erase(node));
    REQUIRE(list.size == 2);
    REQUIRE(list.find("b") == nullptr);
}

TEST_CASE("LinkedList<int> empty and peek", "[linkedlist][int]") {
    LinkedList<int> list;
    REQUIRE(list.empty());
    REQUIRE(list.peek_front() == nullptr);
    REQUIRE(list.peek_back() == nullptr);
}