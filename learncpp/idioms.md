# resource acquisition is initialisation (raii)

- acquire resource in constructor
- release them in destructor
  = no need to manually release resources
  = released even if error occurs
  = encapsulate resource management inside objects
  = avoid leaks and dangling handles

# rule of 5

every class needs the following if it manages resources:
| Function | Purpose |
| ------------------------ | ------------------------------------------------------ |
| Destructor | Cleans up resources when object is destroyed |
| Copy constructor | Creates a new object as a copy of an existing one |
| Copy assignment operator | Replaces an existing object's contents with another's |
| Move constructor | Transfers ownership from a temporary (rvalue) object |
| Move assignment operator | Transfers ownership during assignment from a temporary |

the default copy constructor / assignment operators do shallow copies, which is fine for classes with no dynamically allocated variables. but if there is, we need to rather handle deep copies

# substitution failure is not an error (sfinae)

for selective template instantiations - selective templates for certain types

```cpp
#include <type_traits>
#include <iostream>

template <typename T>
auto func(T t) -> typename std::enable_if<std::is_integral<T>::value, void>::type {
    std::cout << "Integral version\n";
}

template <typename T>
auto func(T t) -> typename std::enable_if<!std::is_integral<T>::value, void>::type {
    std::cout << "Non-integral version\n";
}

int main() {
    func(42);       // prints: Integral version
    func(3.14);     // prints: Non-integral version
}
```

# copy on write / lazy copying

use shared references on an object, only copy on a modification

```cpp
class MyString {
public:
    MyString(const std::string &str) : data(std::make_shared<std::string>(str)) {}

    // Use the same shared data for copying.
    MyString(const MyString &other) : data(other.data) {
        std::cout << "Copied using the Copy-Write idiom.\n";
    }

    // Make a copy only if we want to modify the data.
    void write(const std::string &str) {
        // Check if there's more than one reference.
        if (data.use_count() > 1) {
            data = std::make_shared<std::string>(*data);
            std::cout << "Copy is actually made for writing.\n";
        }
        *data = str;
    }

private:
    std::shared_ptr<std::string> data;
};

int main() {
    MyString str1("Hello");
    MyString str2 = str1; // No copy operation, just shared references.

    str1.write("Hello, World!"); // This is where the actual duplication happens.
    return 0;
}
```

# copy and swap

efficient and safe copying by swapping values with other and then letting other go out of scope, so once it reaches the function scope, resources are freed

```cpp
class String {
    String(const String& other);

    friend void swap(String& first, String& second) { // friend function has access to private members of string
        using std::swap; // for arguments-dependent lookup (ADL)
        swap(first.size_, second.size_);
        swap(first.buffer_, second.buffer_);
    }

    String& operator=(String other) { // other is copied by value, therefore is a duplicate of the copied string
        swap(*this, other);
        return *this; // other goes out of scope. automatically deletes resources
    }
};
```

# non copyable / non movable

prevention of objects being copied or moved (usually for objects that manage a resource, e.g file handles, network sockets)

```cpp
class NonCopyable {
public:
  NonCopyable() = default;
  ~NonCopyable() = default;

  // Delete the copy constructor
  NonCopyable(const NonCopyable&) = delete;

  // Delete the copy assignment operator
  NonCopyable& operator=(const NonCopyable&) = delete;
};
```

# pointer to implementation idiom (pimpl)

hide implementation details of a class from its interface by just having a pointer to implementation class (improve encapsulation). pretty much just a basic wrapper for a class implementation

```cpp
// greeter.h
#pragma once
#include <memory>

class GreeterImpl; // forward declaration

class Greeter {
public:
    Greeter(const std::string& name);
    ~Greeter();
    void greet();

private:
    std::unique_ptr<GreeterImpl> pImpl;
};

#include "Greeter.h"
#include <iostream>

// greeter.cpp
class GreeterImpl {
public:
    GreeterImpl(const std::string& name) : name(name) {}
    void greet() {
        std::cout << "Hello, " << name << "!" << std::endl;
    }

private:
    std::string name;
};

// wrapper methods
Greeter::Greeter(const std::string& name)
    : pImpl(std::make_unique<GreeterImpl>(name)) {}

Greeter::~Greeter() = default;

void Greeter::greet() {
    pImpl->greet();
}

// main.cpp
#include "Greeter.h"

int main() {
    Greeter g("Alex");
    g.greet();  // prints: Hello, Alex!
    return 0;
}
```

# curiously returning template pattern (crtp)

class inherits from a template base class, taking derived class as parameter. allows for static compile time polymorphism (no runtime cost). no virtual functions, high performance.

```cpp
#include <iostream>

// Base class template
template <typename Derived>
class Printer {
public:
    void printType() {
        // calls Derived's getTypeName() method
        std::cout << static_cast<Derived*>(this)->getTypeName() << std::endl;
    }
};

// Derived class
class Apple : public Printer<Apple> {
public:
    std::string getTypeName() const { return "Apple"; }
};

class Banana : public Printer<Banana> {
public:
    std::string getTypeName() const { return "Banana"; }
};

int main() {
    Apple a;
    Banana b;
    a.printType();  // prints "Apple"
    b.printType();  // prints "Banana"
}
```
