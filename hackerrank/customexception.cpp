#include <stdexcept> 
#include <string> 

class BadLengthException : public std::runtime_error {
    public:
        BadLengthException(const int& message) : std::runtime_error(std::to_string(message)) {}
};