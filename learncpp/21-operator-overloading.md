# operator overloading

- an overloaded operator should operate on at least one program-defined type
- if the overload isn't clear or intuitive, should be using a named function instead
- operators that don't modify operands (e.g arithmetic) should return by value
- operators that modify leftmost operand should return by left value reference

# friend operator overload

```cpp
Cents(int cents) : m_cents{ cents } { }
friend Cents operator+(const Cents& c1, const Cents& c2);
...
Cents operator+(const Cents& c1, const Cents& c2)
{
	return Cents { c1.m_cents + c2.m_cents };
}
```

# without friend

```cpp
Cents operator+(const Cents& c1, const Cents& c2)
{
  return Cents{ c1.getCents() + c2.getCents() };
}
```

preferred if we don't need to make it a friend function + don't need to add more functions

# member operator overload

```cpp
Cents operator+(int value) const;
...
Cents Cents::operator+ (int value) const
{ return Cents { m_cents + value }; } // implicit *this pointer
```

# overloading io

```cpp
// ostream
friend std::ostream& operator<< (std::ostream& out, const Point& point);
// istream
friend std::istream& operator>> (std::istream& in, Point& point);
```

# unary overload

unary = takes one parameter

```cpp
Cents operator-() const;
...
Cents Cents::operator-() const
{ return -m_cents; } // implicit Cents(-m_cents) call
```

# prefix and postfix differentiation

```cpp
Digit& operator++(); // prefix has no parameter
Digit& operator--(); // prefix has no parameter
Digit operator++(int); // postfix has an int parameter
Digit operator--(int); // postfix has an int parameter

Digit& Digit::operator++()
{
    if (m_digit == 9)
        m_digit = 0;
    else
        ++m_digit;
    return *this;
}

Digit Digit::operator++(int)
{
    Digit temp{*this};
    ++(*this);
    return temp;
}
```

# subscript overload

```cpp
int& operator[] (int index)
{ return m_list[index]; }

const int& operator[] (int index) const
{ return m_list[index]; }

// code is reused, can instead do something like
int& operator[] (int index)
{ return const_cast<int&>(std::as_const(*this)[index]); }
```

# parentheses overload

```cpp
class Matrix
{
private:
    double m_data[4][4]{};
public:
    double& operator()(int row, int col);
}

double& Matrix::operator()(int row, int col)
{
    assert(row >= 0 && row < 4);
    assert(col >= 0 && col < 4);
    return m_data[row][col];
}

Matrix matrix;
matrix(1, 2) = 4.5;
std::cout << matrix(1, 2) << '\n';
```

# overload typecasting

```cpp
explicit operator int() const { return m_cents; }
// explicit to prevent implicit conversion
int cent { Cents };
```

generally, we should prefer a converting constructor over this

# function templates

```cpp
template <typename T>
const T& max(const T& x, const T& y)
{ return (x < y) ? y : x; }
// this template won't be able to handle being called with our specific class unless there is an overload
friend bool operator< (const Cents& c1, const Cents& c2)
{ return (c1.m_cents < c2.m_cents); }
```

