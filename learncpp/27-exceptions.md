# exceptions

when an exception is thrown:

- the program first looks to se if the exception can be handled immediately inside the current function (try catch block). if it can handle the exception, it does
- if not, the program next checks whether the function's caller (next up on call stack) can handle the exception
- if not, continues up the call stack, until either handler is found or all functions on stack have been checked, and no handler is found
- if a handler is found, execution jumps from the point where exception is thrown to the top of the matching catch block, which requires unwinding the stack until the function handling the exception is at the top of the call stack
- if no handler is found, the stack may or may not be unwound
- when the current function is removed from the call stack, all local variables are destroyed (as usual) but no value is returned

# uncaught exception

- if no exception is caught, `std::terminate()` is called. the call stack may or may not be unwound - so if it is not , local variables will not be destroyed, cleanup expected upon destruction will not happen
- this would be in the case of ensuring information about the state of the stack is preserved, making it easier to debug

# catch all

```cpp
try {
  throw 5;
}
catch (double x)
{
  std::cout << "Caught exception type of double: " << x << '\n';
}
catch (...) // catch all
{
  std::cout << "Caught exception undetermined type\n";
}
```

# std::exception

- exceptions thrown by standard library

```cpp
try {
  std::string s;
  s.resize(std::numeric_limits<std::size_t>::max());
}
catch (const std::exception& exception)
{
  std::cerr << exception.what() << '\n';
}
```

# std::runtime_error

- popular exception to throw in custom code

```cpp
try {
  throw std::runtime_error("Some error message");
}
```

# exception lifetime

- when an exception is thrown, compiler makes a copy of the exception object to some unspecified memory outside of the call stack, reserved for handling exceptions
- this ensures the exception persists no matter how the stack is unwound
- so this means objects being thrown generally need to be copyable

# rethrowing exceptions

```cpp
try
{
  try
  {
    throw Derived {}
  }
  catch (Base& b)
  {
    throw; // rethrow the exact same object
    // otherwise we would throw a sliced base
  }
}
```

# function try blocks

- to establish an exception handler around the body of an entire function, rather than a block of code

```cpp
class A
{
private:
  int m_x;
public:
  A(int x): m_x{x}
  {
    if (x <= 0)
      throw 1;
  }
}

class B : public A
{
public:
  B(int x) try : A{x}
  {
  }
  catch (...)
  {
    std::cerr << "Exception\n";
    throw; //rethrow
  }
}
```

- function level catch block for a constructor must either throw a new exception or rethrow. they cannot resolve or return values. implicitly rethrows
- function level catch block for a destructor can throw, rethrow or resolve the current exception via a return statement. implicitly rethrows
  - but NEVER actually use exceptions in a destructor, because the compiler doesn't know whether to continue stack unwinding / handle the exception, resulting in immediate termination.
  - just don't use exceptions, write to a log file instead
- function level catch block for other functions can throw, rethrow or resolve the current exception via return statement. reaching the end of the catch block will implicitly resolve the exception for non-value (void) returning functions, and undefined behaviour for value returning functions

# resource cleanup

- when constructors fail, the destructor isn't called
- don't try to call it, instead, create a RAII compliant class, e.g use smart pointers, so it cleans up after itself if the constructor fails

- similarly, with try catch blocks, we can use unique ptrs

```cpp
try
{
    auto* john { new Person("John", 18, PERSON_MALE) };
    std::unique_ptr<Person> upJohn { john }; // upJohn now owns john
    ProcessPerson(john);
    // when upJohn goes out of scope, it will delete john
}
catch (const PersonException& exception)
{
    std::cerr << "Failed to process person: " << exception.what() << '\n';
}
```

# when to use exceptions

- when the error being handled is likely infrequent
- error is serious and execution can't continue otherwise
- error cannot be handled at the place it occurs
- there's no good alternative way to return an error code back to the caller

# noexcept

- `noexcept` functions promise not to throw exceptions that are visible to the caller
- it doesn't actually prevent the function from throwing exceptions or calling other functions that are potentially throwing
  - this is fine as long as the `noexcept` function catches and handles exceptions internally and the exceptions don't exit the function
  - if an unhandled exception exits a `noexcept` function, `std::terminate` will be called, even if there is a handler somewhere in the stack

```cpp
void myFunction() noexcept
```

- `noexcept` as an operator can also be used to check if the compiler thinks it wil throw an exception or not
- this is evaluated at compile time. it doesn't actually evaluate the input expression

```cpp
void a() {throw -1;};
void b() {};
void c() noexcept {};
struct D{};

constexpr bool b1{ noexcept(5 + 3) }; // true; ints are non-throwing
constexpr bool b2{ noexcept(a()) }; // false; a() throws an exception
constexpr bool b3{ noexcept(b()) }; // false; b() is implicitly noexcept(false)
constexpr bool b4{ noexcept(c()) }; // true; c() is explicitly noexcept(true)
constexpr bool b5{ noexcept(D{}) };   // true; a struct's default constructor is noexcept by default
```

# exception safety guarantee

- no guarantee - no guarantee what will happen if an exception is thrown (e.g class may be left in unusable state)
- basic guarantee - if exception is thrown, no memory leaks and the object is still usable, but program may be left in modified state
- strong guarantee - if exception is thrown, no memory leaks and program state is not changed, so the function must either completely succeed or have no side effects if it fails
  - can be easy if the failure happens before any modification, but can also be achieved by rollbacks
- no throw / no fail guarantee - the function will always succeed (no fail) or fail without throwing an exception to the caller (no throw) (`noexcept`)

## no throw guarantee

- if a function fails, then it won't throw an exception. instead, return an error code or ignore the problem.
- required during stack unwinding when an exception is already being handled (e.g destructors / functions called by destructor)
- destructors and memory deallocation / cleanups
- functions that higher level no throw functions need to call

## no fail guarantee

- a function will always succeed in what it tries to do, and so never needs to throw an exception
- move constructors and move assignment
- swap functions
- clear / erase / reset on containers
- operators on `std::unique_ptr`
- functions that higher level no fail functions need to call

- always make move constructor / move assignment / swap functions `noexcept`
- make copy constructors / copy assignments `noexcept` when you can

# move constructor exceptions

- if we are moving an object, and the operation is interrupted after transfer of ownership, source object is left in a modified state
- to ensure strong exception guarantee, we need to move the resource back, but if the move failed the first time, there is no guarantee the move back will succeed either

## std::move_if_noexcept

```cpp
std::pair moved_pair{ std::move_if_noexcept(my_pair) };
```

- `std::move_if_noexcept` returns `my_pair` as an l-value reference
  - this causes `moved_pair` to be created by the copy constructor (rather than move constructor)
  - this can throw safely because the source object isn't modified
  - pretty much just uses copying if the move constructor of an object can throw
