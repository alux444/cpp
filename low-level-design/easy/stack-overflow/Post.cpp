#include "src/Post.h"

int Post::nextId = 1;

Post::Post() : id(nextId++) {};