include(FetchContent)

# Fetch Catch2 (no download needed by user)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.5.3 # Use a recent version
)

FetchContent_MakeAvailable(Catch2)

# Create test executable
add_executable(my_tests test_main.cpp test_queue.cpp test_linkedlist.cpp test_list.cpp test_hashmap.cpp test_hashset.cpp)

# Link your code and Catch2
target_link_libraries(my_tests PRIVATE my_code Catch2::Catch2WithMain)

# Automatically register tests with CTest
include(Catch)
catch_discover_tests(my_tests)
