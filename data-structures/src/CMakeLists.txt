add_library(my_code STATIC queue.cpp linkedlist.cpp list.cpp)
target_include_directories(my_code PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
