#include <string>
#include "src/User.h"

int User::nextId = 1;

User::User(std::string username)
    : id(nextId++), username(username), reputation(0) {};