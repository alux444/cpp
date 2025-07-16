# non-type parameters

non type parameters can be:

- an integral type
- an enumeration type
- a pointer or reference to a class object
- a pointer or reference to a function
- a pointer or reference to a class member function
- std::nullptr_t
- a floating point type (since C++20)

```cpp
template <typename T, int size> // size is an integral non-type parameter
class StaticArray
{
private:
    T m_array[size] {};
    ...
}
```

# function template specialization

- full specializations are not implicitly inline, so if defined in a header file, use `inline` to avoid ODR violations when imported in multiple files

```cpp
// primary template
template <typename T>
void print(const T& t) { std::cout << t << '\n'; }

// specialized template
template<>
void print<double>(const double& d)
{
  std::cout << std::scientific << d << '\n';
}
```

# class template specialization

```cpp
template <typename T>
class MyClass
{ ... }

// class specialization
template <>
class MyClass<bool>
{ ... }

// class member function specialization
template <>
void MyClass<bool>::print()
{ ... }
```

# partial template specialization

```cpp
// overload of print() for partially specialized Array<char, size>
template <int size>
void print(const Array<char, size>& array)
{ ... }
```

```cpp
// partial template specialization with inheritance
template <typename T, int size>
class Array_Base
{ ... }

template <typename T, int size>
class Array : public Array_Base<T, size> {};

template <int size>
class Array<double, size> : public Array_Base<double, size>
{ ... }
```

# partial template specialization with pointers

```cpp
template <typename T>
class MyClass
{
  static_assert(!std::is_pointer_v<T> && !std::is_null_pointer_v<T>, "MyClass<T*> and MyClass<nullptr> not allowed.")
  ...
}

template <typename T>
class MyClass
{
private:
  std::unique_ptr<T> m_value {};
public:
  MyClass(T* value): m_value { std::make_unique<T>(value ? *value : 0)} {} // or throw exception if !value
}
```
