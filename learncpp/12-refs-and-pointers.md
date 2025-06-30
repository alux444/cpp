# lvalue vs rvalue

lvalue: locator value - any value with an addressable object in memory
rvalue: read value - any temporary value or literal without a persistent address

# const lvalue

```cpp
int x {5};
const int& ref {x}; // non modifiable reference of x
```

otherwise we can do something like `ref = 6` - which would do the same as `x = 5`, modifying the original reference

# conversions

if any conversion occurs to the type of the bound object and the original reference gets modified, the changes won't be propagated because it's a different object

```cpp
short x {5};
const int& y {x};
--x; // only affects x. y will remain the same (5)
```

# constexpr references

can only be bound to objects with static duration (globals or static locals)

```cpp
int g_x { 5 };

int main()
{
    [[maybe_unused]] constexpr int& ref1 { g_x }; // ok, can bind to global

    static int s_x { 6 };
    [[maybe_unused]] constexpr int& ref2 { s_x }; // ok, can bind to static local

    int x { 6 };
    [[maybe_unused]] constexpr int& ref3 { x }; // compile error: can't bind to non-static object

    return 0;
}
```

# when to pass by ref

## pass by copy

- fundamental (primitive) / enum types, cheap to copy
- `std::string_view` / `std::span`
- types that mimic references or non owning pointers, e.g iterators, `std::reference_wrapper`
- cheap to copy class types, e.g `std::pair`

## pass by ref

- classes typically by const reference as they can be expensive to copy
- arguments that need to be modified by the function
- not copyable types e.g `std::ostream`
- types where copying has unwanted implications e.g `std::unique_ptr`, `std::shared_ptr`
- types that have virtual functions or are likely to be inherited from (object slicing)

# cost of references

- pass by value means making a copy. the cost of copying is proportionate to size of the object and any additional setup (e.g opening file)
- binding an object to a reference always takes about the time to copy a primitive

- whenever a value parameter is used by a function, the program can directly access the storage location (CPU register / RAM) of the copied arg.
- when using a reference, the program accesses the storage location of the reference to determine the object being referenced. then it is able to access that storage location of the actual referenced object.

- the compiler can sometimes optimise better with a pass by value because there is no chance of aliasing (2+ pointers accessing the same object)

- we can generally say an object is cheap to copy if it takes up less than 3 memory addresses in size, i.e `sizeof(T) <= 2 * sizeof(void*)`

# pointers

`const int* const pX` - a const pointer (address can't be changed) that points to a const value (so value can't be changed)

# pass by address / pointer

- address can be null (nullptr), reference can't, so use pointer if field is optional / can be skipped
- whenever C api needs to be used (only raw pointers can interface with)

# return by reference / address

- similar to pass by reference - if we return a reference, we avoid that copying of an object.
- need to make sure that the reference is not dangling when returned
- only really want to use this for exposing internal state and allow mutation of that state

```cpp
const std::string& getProgramName()
{
    const std::string programName { "Calculator" }; // not static. will be destroyed at end of scope. therefore undefined behaviour from returning dangling reference
    return programName;
}
```

- generally prefer return by reference unless explicitly need nullptr functionality from address

# type deduction

## with references

```cpp
const std::string& getConstRef(); // some function that returns a const reference

int main()
{
    auto ref1{ getConstRef() };        // std::string (reference and top-level const dropped)
    const auto ref2{ getConstRef() };  // const std::string (reference dropped, const dropped, const reapplied)
    auto& ref3{ getConstRef() };       // const std::string& (reference dropped and reapplied, low-level const not dropped)
    const auto& ref4{ getConstRef() }; // const std::string& (reference dropped and reapplied, low-level const not dropped)
    return 0;
}
```

## with pointers

pointer doesn't get dereferenced

```cpp
std::string* getPtr(); // some function that returns a pointer

int main()
{
    auto ptr1{ getPtr() };  // std::string*
    auto* ptr2{ getPtr() }; // std::string*

    return 0;
}
```

# std::optional

```cpp
std::optional<int> doIntDivision(int x, int y)
{
    if (y == 0)
        return {}; // or return std::nullopt
    return x / y;
}
```

```cpp
if (o1)
if (o1.has_value())

std::cout << *o1;             // dereference to get value stored in o1 (undefined behavior if o1 does not have a value)
std::cout << o2.value();      // call value() to get value stored in o2 (throws std::bad_optional_access exception if o2 does not have a value)
std::cout << o3.value_or(42); // call value_or() to get value stored in o3 (or value `42` if o3 doesn't have a value)
```

```cpp
void printIDNumber(std::optional<const int> id = std::nullopt)
{
    if (id)
        std::cout << "Your ID number is " << *id << ".\n";
    else
        std::cout << "Your ID number is not known.\n";
}
```

to make a reference optional `std::optional<std::reference_wrapper<Class>>`