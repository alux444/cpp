# function pointers

```cpp
// fcnPtr is a pointer to a function that takes no arguments and returns an integer
int (*fcnPtr)();
int (*const fcnPtr)();

int foo() { return 2; }

int (*fcnPtr)(){ &foo };
// using std::function
std::function<int()> fcnPtr{ &foo };

using ValidateFunctionRaw = bool(*)(int, int); // type alias to raw function pointer
using ValidateFunction = std::function<bool(int, int)>; // type alias to std::function
```

- mainly used for passing functions as args to other functions
- prefer using `std::function`

# program memory

- code segment, where compiled program sits in memory (readonly)
- bss segment (uninitialised data segment), where zero-initialised global / static vars are stored
- data segment (initialised data segment), where initialised global / static vars are stored
- heap, where dynamically allocated variables are stored
- call stack, where function params, local vars and other function related info is stored

## call stack

keeps track of all active functions from the start of the program to current execution. handles allocation of all function params / local variables.

call stack segment holds memory for the call stack. on program start, `main()` is pushed to the call stack. on function end, pop off the stack (unwinding the stack)

# cli arguments

```cpp
int main(int argc, char* argv[])
```

argc - count of arguments passed to program

argv - char pointer (c style string) array of arguments. `argv[0]` is the path and name of the current program

# lambda

## example usage

```cpp
auto isEven{
  [](int i)
  { return (i%2) == 0; }
};
std::remove(v.begin(), v.end(), isEven);
```

## accepting lambdas as params

```cpp
// Case 1: use a `std::function` parameter
void repeat1(int repetitions, const std::function<void(int)>& fn)
{
    for (int i{ 0 }; i < repetitions; ++i)
        fn(i);
}

// Case 2: use a function template with a type template parameter
template <typename T>
void repeat2(int repetitions, const T& fn)
{
    for (int i{ 0 }; i < repetitions; ++i)
        fn(i);
}

// Case 3: use the abbreviated function template syntax (C++20)
void repeat3(int repetitions, const auto& fn)
{
    for (int i{ 0 }; i < repetitions; ++i)
        fn(i);
}

// Case 4: use function pointer (only for lambda with no captures)
void repeat4(int repetitions, void (*fn)(int))
{
    for (int i{ 0 }; i < repetitions; ++i)
        fn(i);
}
```

## unique lambdas are generated for each resolved type

```cpp
auto print{
  [](auto value) {
    static int callCount{ 0 };
    std::cout << callCount++ << ": " << value << '\n';
  }
};

print("hello"); // 0: hello
print("world"); // 1: world

print(1); // 0: 1
print(2); // 1: 2

print("ding dong"); // 2: ding dong
```

## lambda captures

```cpp
int ammo{ 10 };

auto shoot{
  [ammo]() mutable { // now mutable. default is const
    --ammo;
    std::cout << "Pew! " << ammo << " shot(s) left.\n";
  }
};
shoot(); // 9
shoot(); // 8
std::cout << ammo << " shot(s) left\n";
// 10 - lambdas have their own copy of the capture that is persisted across calls
```

```cpp
int ammo{ 10 };

auto shoot{
  [&ammo]() {  // capture by ref
    --ammo;
    std::cout << "Pew! " << ammo << " shot(s) left.\n";
  }
};
shoot(); // 9
std::cout << ammo << " shot(s) left\n"; // 8
```

## default capture

```cpp
auto found{ std::find_if(areas.begin(), areas.end(),
                           [=](int knownArea) { // will default capture width and height by value. use [&] for capture by ref
                             return width * height == knownArea; // because they're mentioned here
                           }) };
```
