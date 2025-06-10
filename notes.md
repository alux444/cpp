# virtual functions

- abstract methods equivalent, for polymorphism - flexible, extensible code, use common interfaces etc.
- `override` for override, `final` to prevent further overrides
- support runtime polymorphism
- always make destructors virtual if class needs to be used polymorphically
- interfaces keyword doesn't exist - so to interface only make pure virtual functions
  `virtual void myFunc() = 0;`

# resource acquisition is initialisation (raii)

- acquire resource in constructor
- release them in destructor
  = no need to manually release resources
  = released even if error occurs
  = encapsulate resource management inside objects
  = avoid leaks and dangling handles

# new vs malloc

| Feature              | `new`                                | `malloc`                              |
| -------------------- | ------------------------------------ | ------------------------------------- |
| Type safety          | ✅ Type-safe                         | ❌ Returns `void*` (needs cast)       |
| Constructor called?  | ✅ Yes                               | ❌ No                                 |
| Destructor called?   | ✅ With `delete`                     | ❌ No (must use `free`)               |
| Overloadable?        | ✅ Yes (can overload `operator new`) | ❌ No                                 |
| Exception on failure | ✅ Throws `std::bad_alloc`           | ❌ Returns `nullptr`                  |
| Syntax               | `int* p = new int;`                  | `int* p = (int*)malloc(sizeof(int));` |
| Deallocate with      | `delete` / `delete[]`                | `free()`                              |

# inline func

where the compiler replaces function calls with actual function body and compile time. less overhead of calling functions.

# function overloading

multiple functions of the same name but different arguments, so compiler can choose which function to run off argument types

```cpp
void print(int x) {
    std::cout << "Integer: " << x << '\n';
}

void print(double x) {
    std::cout << "Double: " << x << '\n';
}
```

# templates

syntax for creating generic classes or functions (generic typing) - allows for type erasure (uniform interface for multiple types)

# mutable

allows for modification of a value even in a `const` object

# const_case

for modifying `const` or `volatile` attribute on an object

```cpp
void printConstString(const char* cstr) {
    // legacyPrint expects char*, but cstr is const char*
    legacyPrint(const_cast<char*>(cstr));  // Remove const to call legacyPrint
}

int x = 10;
const int& cx = const_cast<const int&>(x);       // Add const qualifier - but modifying x directly will still change this value
volatile int& vx = const_cast<volatile int&>(x); // Add volatile qualifier
```

# explicit

prevents implicit conversion bu the compiler

```cpp
class MyClass {
public:
    explicit MyClass(int x) { /*...*/ }
};

void func(MyClass obj) { /*...*/ }

int main() {
    func(42);       // Error: no implicit conversion allowed
    func(MyClass(42)); // OK: explicit construction
}
```

# decltype

query type of an expression at compile time without evaluating the expression - avoid runtime side effects

```cpp
int a = 10;
int& ra = a;
const int& cra = a;

decltype(ra) x = a;    // x is int& (reference)
decltype(cra) y = a;   // y is const int& (const reference)

int counter = 0;

int increment() {
    ++counter;
    std::cout << "increment called\n";
    return counter;
}

decltype(increment()) x;  // No "increment called" printed, function NOT called

std::cout << "counter = " << counter << "\n";  // counter still 0
```

# name hiding

allow for customising function behaviour without overriding

```cpp
class Base {
public:
    void func() { std::cout << "Base func()\n"; }
    void func(int x) { std::cout << "Base func(int)\n"; }
};

class Derived : public Base {
public:
    void func() { std::cout << "Derived func()\n"; }
};

int main() {
    Derived d;
    d.func();      // Calls Derived::func()
    // d.func(10); // Error: Base::func(int) is hidden by Derived::func()
    d.Base::func(10);  // OK: explicitly call base class function
}
```

# rule of 5

every class needs the following if it manages resources:
| Function | Purpose |
| ------------------------ | ------------------------------------------------------ |
| Destructor | Cleans up resources when object is destroyed |
| Copy constructor | Creates a new object as a copy of an existing one |
| Copy assignment operator | Replaces an existing object's contents with another's |
| Move constructor | Transfers ownership from a temporary (rvalue) object |
| Move assignment operator | Transfers ownership during assignment from a temporary |

# lambda syntax

```cpp
// capture is any variable in the surrounding scope that is accessible
[capture](parameters) -> return_type {
    // function body
};
```

# moving

move internal resources of an object that is about to be destroyed without needing to copy underlying data

```cpp
class MyClass {
public:
    std::vector<int> data;

    // && - rvalue reference (temp object that has no persistent memory address)
    MyClass(MyClass&& other) noexcept : data(std::move(other.data)) {
        std::cout << "Move constructor called\n";
    }
}
```

# copy constructor

by default, copy constructor is a shallow copy

```cpp
class MyClass {
public:
    int* data;

    // Copy constructor
    MyClass(const MyClass& other) {
        data = new int(*other.data);  // deep copy
    }
};
```

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

# using raw pointers

| Pros                                 | Cons                                        |
| ------------------------------------ | ------------------------------------------- |
| Low overhead and fast                | Risk of memory leaks                        |
| Full control over memory             | Dangling pointers and undefined behavior    |
| Compatible with C and low-level APIs | No automatic lifetime or ownership handling |
| Flexible (pointer arithmetic etc)    | Complex to use correctly and safely         |

# ref vs pointer

| Aspect        | Reference (`T&`)                                                   | Pointer (`T*`)                                                 |
| ------------- | ------------------------------------------------------------------ | -------------------------------------------------------------- |
| Syntax        | Uses `&` symbol                                                    | Uses `*` symbol                                                |
| Null value    | **Cannot be null** — must refer to an object                       | Can be `nullptr` (null pointer)                                |
| Reassignment  | Cannot be reseated to refer to another object after initialization | Can be reassigned to point to different objects                |
| Dereferencing | Automatically dereferenced; no need for `*`                        | Must explicitly dereference using `*`                          |
| Memory        | Usually implemented as an alias; no extra memory required          | Stored as an actual memory address                             |
| Use case      | Alias for another object, simpler syntax                           | More flexible for dynamic data structures and optional objects |
| Safety        | Safer, since it must always refer to valid object                  | Risk of dangling/null pointers if misused                      |

# smart pointers

pointers for managing lifetime of object automatically

| Smart Pointer     | Ownership Model     | Key Features                                                                                                      |
| ----------------- | ------------------- | ----------------------------------------------------------------------------------------------------------------- |
| `std::unique_ptr` | Exclusive ownership | Only one owner at a time; cannot be copied, only moved. Lightweight, no overhead beyond raw pointer.              |
| `std::shared_ptr` | Shared ownership    | Multiple owners share ownership; object deleted when last owner releases it. Has overhead for reference counting. |
| `std::weak_ptr`   | Non-owning observer | Observes an object managed by `shared_ptr` without affecting lifetime. Useful to break cyclic references.         |

| Feature         | `std::unique_ptr`                                       | `std::shared_ptr`                              |
| --------------- | ------------------------------------------------------- | ---------------------------------------------- |
| Ownership       | Sole (unique) owner                                     | Shared among multiple owners                   |
| Copyable        | No (only movable)                                       | Yes                                            |
| Memory overhead | Minimal (just a raw pointer)                            | Higher (reference counting data)               |
| Use case        | When only one object owner exists                       | When ownership is shared across parts          |
| Thread safety   | Not inherently thread-safe for ownership transfer       | Thread-safe reference counting                 |
| Example use     | Managing resources with strict ownership, e.g., in RAII | Shared resources, caches, or observer patterns |

```cpp
#include <memory>
#include <iostream>

void uniqueExample() {
    std::unique_ptr<int> p1 = std::make_unique<int>(42);
    // std::unique_ptr<int> p2 = p1; // Error! unique_ptr can't be copied
    std::unique_ptr<int> p2 = std::move(p1); // Ownership moved
    std::cout << *p2 << "\n";
}

void sharedExample() {
    std::shared_ptr<int> p1 = std::make_shared<int>(42);
    std::shared_ptr<int> p2 = p1;  // Shared ownership
    std::cout << *p1 << " and " << *p2 << "\n";
}
```

# std::thread

thread class representing single thread of execution
pass a function and immediately starts running on new thread
`join()` - block caller and wait for finish
`detach()` - thread runs independently in background
no built in return values

```cpp
#include <iostream>
#include <thread>

void worker() {
    std::cout << "Working in thread\n";
}

int main() {
    std::thread t(worker);
    t.join();  // Block caller and wait for thread to finish
}
```

# std::async

to run a function async, returns a `std::future`
call `std::async` with a callable, may run on new thread or defer execution (depends on launch policy)
`.get()` automatically waits for task to finish

```cpp
#include <iostream>
#include <future>

int compute() {
    return 444;
}

int main() {
    std::future<int> fut = std::async(std::launch::async, compute); // can use std::launch::deferred - waits until .get() or wait() on the future before running
    std::cout << "Result: " << fut.get() << "\n";  // Waits and retrieves result
}
```

# pointer to implementation idiom (pimpl)

hide implementation details of a class from its interface by just having a pointer to implementation class (improve encapsulation)
TODO

# curiously returning template pattern (crtp)

TODO
