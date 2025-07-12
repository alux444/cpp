# smart pointer

- a composition class that is designed to manage dynamically allocated memory
- it will automatically allocate (construction) and deallocate (destruction) (RAII)

# move semantics

- simply transfer or move ownership of a pointer from source to destination, cheaper than copying

# lvalues and rvalues

```cpp
int x{ 5 };
int& lref{ x }; // l-value reference initialized with l-value x
int&& rref{ 5 }; // r-value reference initialized with r-value 5
```

# move constructors and assignments

```cpp
Auto_ptr4(Auto_ptr4&& a) noexcept
		: m_ptr { a.m_ptr }
{ a.m_ptr = nullptr; }

Auto_ptr4& operator=(Auto_ptr4&& a) noexcept
{
  if (&a == this)
    return *this;
  delete m_ptr;

  m_ptr = a.m_ptr;
  a.m_ptr = nullptr;

  return *this;
}
```

the implicit move constructor / assignment will copy pointers, not move them

# implicit move

sometimes we might want to implicitly move an lvalue. in this case use `std::move`

```cpp
template <typename T>
void mySwapCopy(T& a, T& b)
{
	T tmp { a }; // invokes copy constructor
	a = b; // invokes copy assignment
	b = tmp; // invokes copy assignment
}

template <typename T>
void mySwapMove(T& a, T& b)
{
	T tmp { std::move(a) }; // invokes move constructor
	a = std::move(b); // invokes move assignment
	b = std::move(tmp); // invokes move assignment
}
```

# unique ptr

- ensures only one `unique_ptr` owns an object at a time
- when `unique_ptr` goes out of scope, it will automatically delete the object it owns. handles arrays too
- uses one pointer internally

- cannot copy a `unique_ptr`, but can move

```cpp
auto ptr { std::make_unique<Fraction>(3, 5) };
const Fraction* pFraction = ptr.get();
```

# shared ptr

- for when we need multiple smart pointers co-owning a resource
- `std::shared_ptr` uses 2 pointers internally, one at the resource and another at a control block

```cpp
Resource* res { new Resource };
std::shared_ptr<Resource> ptr1 { res };
{
  std:shared_ptr<Resource> ptr2 { ptr1 }; // OK
  std:shared_ptr<Resource> ptr2 { res }; // don't do this - need the pointers to be aware of each other. so always make a copy of the existing shared ptr
}

auto ptr1 { std::make_shared<Resource>() };
{
  auto ptr2 { ptr1 };
}
```

# circular references

```cpp
class Person
{
	std::string m_name;
	std::shared_ptr<Person> m_partner;
public:
	Person(const std::string &name): m_name(name) {}

	friend bool partnerUp(std::shared_ptr<Person> &p1, std::shared_ptr<Person> &p2)
	{
		if (!p1 || !p2)
			return false;
		p1->m_partner = p2;
		p2->m_partner = p1;
		return true;
	}
};

auto lucy { std::make_shared<Person>("Lucy") };
auto ricky { std::make_shared<Person>("Ricky") };
partnerUp(lucy, ricky);
```

- after `partnerUp()` there are 2 shared pointers at ricky (`ricky` and `m_partner` in `lucy`) and vice versa
- at the end of main, `ricky` goes out of scope first. checks if any other shared ptrs own `ricky` - which is owned by `m_partner` in `lucy`
- now `lucy` goes out of scope, with the same thing happening
- now the program ends with neither `ricky` or `lucy` being deallocated

# weak ptr

- designed to solve cyclical ownership issues
- observer that can observe same object as a `std::shared_ptr`, but is not considered an owner

to solve the previous issue:

```cpp
class Person
{
	std::string m_name;
	std::weak_ptr<Person> m_partner;
private:
// but now to use a weak ptr, we have to convert it to a shared ptr, using `lock()`
  std::shared_ptr<Person> getPartner() const { return m_partner.lock(); }
}
```

- a weak ptr won't keep an owned resource alive, but it has access to the reference count for an object, so it knows if it's pointing to a valid object or not
- to check, we can use the `expired()` function. this returns `true` if the weak ptr is pointing to an invalid object
