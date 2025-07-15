# inheritance

- when we derive from a class, we get the two parts of a class. e.g the base class is constructed, then the derived class(es) are constructed. cpp always constructs from the first / most base class, then walks through the inheritance tree in order for constructing each then derived class

- when we initialise base class

  - memory for base is set aside
  - the base constructor is called
  - the member initialiser list initialises variables
  - the body of the constructor executes
  - control returned to caller

- when we initialise a derived class
  - memory for derived is set aside - enough for both base and derived portions
  - appropriate derived constructor is called
  - the base object is constructed first using base constructor. if no base constructor is specified, will use the default
  - the member initialiser list initialises variables
  - the body of the constructor executes
  - control returned to caller

```cpp
Derived(double cost = 0.0, int id = 0)
  : Base { id }
  , m_cost { cost }
```

- derived classes don't have access to the base classes `private` members (but do for `protected`)
- when a derived class is destroyed, destructor is called in the reverse order of construction
- if the base class has virtual functions, the destructor should also be virtual

# inheritance types

| Base Member        | Public Inheritance | Protected Inheritance | Private Inheritance |
| ------------------ | ------------------ | --------------------- | ------------------- |
| `public` member    | `public`           | `protected`           | `private`           |
| `protected` member | `protected`        | `protected`           | `private`           |
| `private` member   | never accessible   | never accessible      | never accessible    |

# extending functionality

```cpp
// basic functionality extension
void print() const
{
  std::cout << "Derived call\n";
  Base::print();
}

// calling friend functions - not part of base class
class Base {
  friend std::ostream& operator<<(std::ostream& out, const Base& b)
  {
    out << "Base\n";
    return out;
  }
}
class Derived : public Base
{
friend std::ostream& operator<<(std::ostream& out, const Derived& d)\
{
  out << "Derived\n";
  out << static_cast<const Base&>(d);
  return out;
}
}

// allowing for overload resolution
class Derived : public Base
{
public:
  using Base::print; // allow for all Base::print() functions eligible for overload
  // note: there's no way to change access specifiers for a single overload. only all of them
  void print(double) { std::cout << "Derived::print(double)\n"; } // otherwise overload would resolve to this
}

// hiding functionality in derived
class Derived : public Base
{
private:
  using Base::m_value // now the m_value (which is public in base) is not accessible from a Derived class
}
Derived derived{5}
std::cout << derived.m_value; // not ok
Base base{5}
std::cout << base.m_value; // ok

// delete inherited function
class Derived: public Base
{
public:
  int getValue() const = delete;
}
// can still access this through:
std::cout << derived.Base::getValue();
std::cout << static_cast<Base&>(derived).getValue();
```

- virtual function dispatch doesn't care about access specifiers at runtime
- the compiler enforces access control at compile time only
- so a private `b::fun()` that can't be called at compile time, can be called through `static_cast<A&>(b).fun()` - and this will dispatch and run `b::fun()`

# multiple inheritance

- generally avoided
  - can lead to lots of naming clashes from inherited functions
  - 'diamond' problem, diamond shaped inheritance pattern. lots of maintenance overhead + decisions

```cpp
class WirelessAdapter: public USBDevice, public NetworkDevice
{
public:
    WirelessAdapter(long usbId, long networkId)
        : USBDevice { usbId }, NetworkDevice { networkId }
    {
    }
};

WirelessAdapter adapter { 123, 12345 };
std::cout << adapter.USBDevice::getId();
std::cout << adapter.NetworkDevice::getId();
```
