# returning self

```cpp
class Calc
{
private:
    int m_value{};

public:
    Calc& add(int value) { m_value += value; return *this; }
    Calc& sub(int value) { m_value -= value; return *this; }
    Calc& mult(int value) { m_value *= value; return *this; }

    int getValue() const { return m_value; }
};

// to allow for chaining
calc.add(5).sub(3).mult(4);
```

# convention

- prefer having a header file for a class with the signatures and the function declarations is a separate `.cpp` file
- this is because any function defined within in a class is implicitly inline, thus doesn't follow the one declaration rule. by defining it outside, it is not inline and during linking an error will be thrown
- also, if any change in the .h file occurs, we have to recompile every file that includes the header

# destructors

- function that is run anytime an object is destroyed

```cpp
~NetworkData()
	{ sendData(); } // make sure all data is sent before object is destroyed
```

- if `std::exit` is used to terminate a program, it will just end. local variables won't be destroyed, therefore destructors won't be run
- unhandled exceptions also might not unwind the stack, resulting in destructors not being called

# static members

```cpp
class Something
{
private:
    static inline int s_value { 1 };

public:
    static int getValue() { return s_value; } // static member function
};

Something::getValue();
```

- static member functions aren't associated with an object, so don't have `this` pointer.

# friend

## friend function

```cpp
class Class; // forward declaration

class Accumulator
{
private:
    int m_value { 0 };
public:
    void add(int value) { m_value += value; }

    // Here is the friend declaration that makes non-member function void print(const Accumulator& accumulator) a friend of Accumulator
    friend void print(const Accumulator& accumulator);
    // can also make the function of a class too, but will need to forward declare the class.
    friend void Class::print(const Accumulator& accumulator);
};

void print(const Accumulator& accumulator)
{
    // Because print() is a friend of Accumulator
    // it can access the private members of Accumulator
    std::cout << accumulator.m_value;
}
```

- prefer to not have functions implemented as friend function where possible

## friend class

```cpp
class Storage
{
private:
    int m_nValue {};
    double m_dValue {};
public:
    Storage(int nValue, double dValue)
       : m_nValue { nValue }, m_dValue { dValue }
    { }

    // Make the Display class a friend of Storage
    friend class Display;
};
```

- display is a friend of storage, this doesn't mean storage is a friend of display unless added
- it is not transitive, so if A and B are friends and B and C are friends, A and C are not friends
- it is not inherited, so if class A makes B a friend, classes derived of B are not friends

