# classes

- for private fields, prefix with `m_` e.g `m_name`
- getters should return by value if inexpensive, otherwise const lvalue reference
  - when returning a reference, make sure not to keep a reference of an rvalue
  - `const std::string& ref { createEmployee("Garbo").getName() };` - this is a dangling reference
  - don't return a non const reference to a private instance
- generally, if a function doesn't need to access a classes internals, it should just be a non-member function

# constructors

- member initialisation from the constructor is in the order of declaration within the class

```cpp
class Foo
{
private:
    int m_x{};
    int m_y{};

public:
    Foo(int x, int y)
        : m_y { std::max(x, y) }, m_x { m_y } // undefined behaviour, m_x declared before m_y
    {
    }
}
```

- throwing an exception is generally the best thing to do if a constructor fails
- alternatively, create a public `friend` function that optionally returns the class

```cpp
class Fraction
{
private:
    int m_numerator { 0 };
    int m_denominator { 1 };
    Fraction(int numerator, int denominator):
        m_numerator { numerator }, m_denominator { denominator } {}

public:
    friend std::optional<Fraction> createFraction(int numerator, int denominator);
};

std::optional<Fraction> createFraction(int numerator, int denominator)
{
    if (denominator == 0)
        return {};
    return Fraction{numerator, denominator};
}
```

- prefer using a default or implicitly default constructor over a user defined empty constructor. this results in members being zero-initialised before default initialised
- calling a constructor within a function creates a temporary object

```cpp
Employee(std::string_view name, int id, bool isManager)
        : m_isManager { isManager } // this constructor initializes m_isManager
    {
        // Call Employee(std::string_view, int) to initialize m_name and m_id
        Employee(name, id); // temporary object that doesn't correlate to this initialisation
    }
```

# avoid direct initialisation

- we can also create objects with syntax like `Foo(1,2)` - creating a temporary Foo object
- but just don't do it
- `Foo * bar();` (with no additional parenthesis) groups the `*` with Foo by default. `Foo* bar();` is the declaration of a function named bar that has no parameters and returns a `Foo`.
- `Foo (*bar)();` explicitly groups the `*` with bar. This defines a function pointer named bar that holds the address of a function that takes no parameters and returns a Foo.
- `Foo (* bar());` is the same as `Foo * bar();`
- `(Foo *) bar();` might expect this to be the same as `Foo_ bar()`, but this is actually an expression statement that calls function `bar()`, C-style casts the return value to type Foo, and then discards it.

# copy constructor

```cpp
Fraction(const Fraction& fraction)
        // Initialize our members using the corresponding member of the parameter
        : m_numerator{ fraction.m_numerator }
        , m_denominator{ fraction.m_denominator }
    {}
```

- the copy constructor should have no side effects
- we should prefer the implicit behaviour
- if we're making our own copy instructor, the parameter should be an lvalue reference
- copy constructor is called whenever assigned to a variable, e.g `x = 5`
- when an object is passed by value into a parameter and they are the same class type, the copy constructor is called implicitly

```cpp
void printFraction(Fraction f) // f is pass by value
{ f.print(); } // calls copy constructor
```

- when an object is returned by value by a function, the copy constructor is again called implicitly

```cpp
Fraction generateFraction(int n, int d)
{
    Fraction f{ n, d };
    return f; // when returning this to a variable, will implicitly call copy constructor for the temporary variable
    // now if we're assigning this to something, the copy constructor will be called again
}
```

- copy elison can be enabled in the compiled to avoid unnecessary copies, e.g `A x { A{5} }` to `A x{5}`
