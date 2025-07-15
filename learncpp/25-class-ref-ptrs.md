# object pointers

- it's fine to set a pointer to a base class from the derived class
- however, a base reference / pointer can only see members of base (or any classes inherited by base)
  - therefore it's impossible to call any functions declared within the scope of the derived class

```cpp
Derived derived{ 5 };
Base& rBase{ derived };
Base* pBase{ &derived };
```

# virtual functions

- to make sure we can resolve to the most derived version of a function on call
- virtual dispatch only works when a member function is called through a pointer or reference to a class type object
- use `virtual` keyword for base class declaration, use `override` for derived
- use the `final` keyword for a virtual function that can't be overridden. `final` can also be used to prevent further inheritance from the `final` class
- derived class virtual functions can only have a different return type if it is a pointer or reference to a derived class - this is a covariant return type

```cpp
class Base
{
public:
    virtual std::string_view getName() const { return "Base"; }
    virtual std::string_view getName2() const { return "Base"; }
};

class Derived final : public Base
{
public:
    std::string_view getName() const override { return "Derived"; }
    std::string_view getName2() const override final { return "Derived2"; }
};
```

## do not call virtual functions from constructors / destructors

- when a derived class is created, the base portion is constructed first. if you call a virtual function from the base constructor and the derived portion of the class hasn't been created, it will be unable to call the derived version and call the base version
- similarly for a destructor

## why not make everything virtual?

- resolving a virtual function call takes longer than a resolving a regular one
- compiler has to allocate an extra pointer for each object of a class that has virtual functions

# virtual destructors

- always make a virtual destructor when dealing with inheritance
  - avoid memory leaks, e.g if derived class has memory allocation

```cpp
virtual ~Base() = default
```

- if the class is intended to be inherited, make a virtual and public destructor
- if not, make sure the class is final

# binding and dispatch

- binding is the process of associating names with properties
- function binding / method binding is the process that determines what function definition is associated with a function call. the process of invoking a bound function is called dispatching

## early binding

- when a direct call is made to a non-member function / non-virtual member function, the compiler can determine which function definition should be matched to the call
- this type of binding is early / static binding, where it occurs at compile time. the compiler / linker can generate machine language instructions that tell the CPU to jump directly to the address of the function

## late binding

- if a function call can't be resolved until runtime, this is late binding (in the case of virtual function resolution, dynamic dispatch)
- any indirect function call (through a function pointer) will result in the call being made to whatever function exists at that address held by the function pointer
- late binding is slightly less efficient as the program reads the address held in the pointer, then jumps to that address

# virtual table

C++ implementations typically implement virtual functions using a form of late binding known as the virtual table

- lookup table of functions used to resolve function calls in a dynamic / late binding manner
- aka vtable, virtual function table, virtual method table, dispatch table

early binding / static dispatch = direct function call overload resolution
late binding = indirect function call resolution
dynamic dispatch = virtual function override resolution

## virtual table implementation

- every class that uses virtual functions (or is derived from a class that uses virtual functions) has a corresponding virtual table
- the table is a static array the compiler creates at compile time
- contains 1 entry for each virtual function that can be called by objects of the class
- each entry in the table is a function pointer that points to the most derived function accessible by the class

- the compiler also adds a hidden pointer that is a member of the base class, `*__vptr`

  - this is set automatically when the class object is created to point to the virtual table
  - unlike `this`, which is a function parameter used by the compiler to resolve self references, `*__vptr` is a real pointer
  - this makes every class object allocated bigger by the size of 1 pointer
  - `*__vptr` is inherited by derived classes

- even when we make a derived pointer a base pointer, the `*__vptr` still points to the derived virtual table, so will call the derived version of the virtual function

therefore, calling a virtual function involves:

- using `*__vptr` to get the appropriate virtual table
- index the virtual table to find the correct function to call
- call the function

this is 3 operations compared to 2 for an indirect function call, and 1 for a direct function call

# pure virtual functions (abstract base classes)

- a pure virtual (abstract) function means that the derived classes must implement the function
- any class with one or more pure virtual functions becomes an abstract base class, so they cannot be instantiated

```cpp
class Animal
{
public:
  virtual std::string_view speak() const = 0;
}
```

## interface

- a class that has no member variables
- where all the functions are pure virtual
- standard to denote through `I` prefix, e.g `IErrorLog`

# virtual base classes

- to share a base class, use `virtual` keyword in the inheritance list
- the most derived class is now responsible for constructing the virtual base class
  - this means constructor calls in the `Scanner` or `Printer` classes to the base class will be ignored
- all classes inheriting a virtual base class will have a vtable, even if they would not normally have one otherwise (1 pointer larger size)

```cpp
class PoweredDevice {};

class Scanner: virtual public PoweredDevice {};

class Printer: virtual public PoweredDevice {};

class Copier: public Scanner, public Printer {};
```

# object slicing

the slicing of the portions of an inheriting object

```cpp
Derived derived{ 5 };
Base base{ derived }; // slices derived

void printName(const Base base) // will call the sliced version
void printName(const Base &base) // will call the correct derived version

// slicing in a vector
std::vector<Base> v{};
v.push_back(Base{ 5 });
v.push_back(Derived{ 6 });
// change to a pointer or reference to avoid slicing
std::vector<Base*> v{};
std::vector<std::reference_wrapper<Base>> v{};
```

- if the base is not designed to be instantiated by itself, avoid slicing through making the base class non-copyable

# dynamic casting

```cpp
Base* getObject(bool returnDerived)
{
	if (returnDerived)
		return new Derived{1, "Apple"};
	else
		return new Base{2};
}

int main()
{
	Base* b{ getObject(true) };
  // can also do the same with references, but since there is no null reference, if a dynamic cast fails, a std::bad_cast gets thrown
  Derived* d{ dynamic_cast<Derived*>(b) };
  if (d)
    ...
}
```

downcasting with dynamic cast will not work

- with `protected` or `private` inheritance
- for classes that do not declare or inherit any virtual functions (so have no vtable)
- some specific virtual vase class cases

can still cast with `static_cast`, but there is no runtime type checking. so its faster, but more dangerous

# ostream with virtual classes

```cpp
class Base
{
public:
  friend std::ostream& operator<<(std::ostream& out, const Base& b)
  { return b.print(out); }

  virtual std::ostream& print(std::ostream& out) const
  {
    out << "Base";
    return out;
  }
}

class Derived : public Base
{
public:
  std::ostream& print(std::ostream& out) const
  {
    out << "Derived";
    out << "Derived";
    return out;
  }
}
```
