# input (istream)

## width manipulator

```cpp
char buf[10] {};
std::cin >> std::setw(10) >> buf;
```

## whitespace

```cpp
char ch {};
while (std::cin >> ch) // skips whitespace
  std::cout << ch;

char ch{};
while (std::cin.get(ch)) // gets character from input stream
  std::cout << ch;

std::cin.get(stringBuffer, 11); // maximum characters to read (string ver)
// note: get() does not read in a newline character
// so once it reaches a newline, it stops reading
```

## some other input functions

```cpp
std::cin.getline(buffer, 11); // will extract and discard delimiter
std::cin.gcount(); // returns the amount of characters read by previous getline()
std::cin.ignore(); // discard first character in stream
std::cin.ignore(int nCount) // discard first nCount chars in stream
std::cin.peek(); // read without removing from stream
std::cin.unget(); // returns last character read to stream
std::cin.putback(char ch) // puts a char of choice into front of stream
```

# output (ostream)

## flags

```cpp
std::cout.setf(std::ios::showpos); // turn on showpos flag
std::cout.setf(std::ios::showpos | std::ios::uppercase); // turn on showpos flaga and uppercase flag
std::cout.unsetf(std::ios::showpos); // turn off showpos flag

// setf doesn't turn mutually exclusive flas off
std::cout.unsetf(std::ios::dec); // turn off decimal output
std::cout.setf(std::ios::hex); // turn on hexadecimal output
std::cout << 27 << '\n';

std::cout.setf(std::ios::hex, std::ios::basefield); // turns off all other flags in the group

std::cout << std::hex << 27 << '\n'; // alternative to flags
```

## justify

```cpp
std::cout << -12345 << '\n';
std::cout << std::setw(10) << -12345 << '\n';
std::cout << std::setw(10) << std::left << -12345 << '\n';
std::cout << std::setw(10) << std::right << -12345 << '\n';
std::cout << std::setw(10) << std::internal << -12345 << '\n';
std::cout.fill('*');
std::cout << std::setw(10) << -12345 << '\n';

-12345
    -12345
-12345
    -12345
-    12345
****-12345
```

# stream states

goodbit - everything is ok
badbit - some kind of fatal error (e.g read past EOF)
eofbit - stream reached an EOF
failbit - non fatal error (e.g entered chars when expected int)

```cpp
good() // returns true if goodbit set
bad() // returns true if badbit set
eof() // returns true if eofbit set
fail() // returns true if failbit set
clear() // clear all flags
clear(state) // clear and set flag passed in
rdstate() // return all currently set flags
setstate(state) // set the state
```

```cpp
std::isalnum(int) // return non zero if param is letter / digit
std::isalpha(int) // if is letter
std::iscntrl(int) // if is control char
std::isdigit(int) // if is digit
std::isgraph(int) // if printable non whitespace char
std::isprint(int) // if printable, including whitespace
std::ispunct(int) // if not alphanumeric or whitespace
std::isspace(int) // if is space
std::isxdigit(int) // if hexadecimal digit (0-9, a-f, A-F)
```

# file io

```cpp
std::ofstream outf { "file.txt", std::ios::app }; // append mode
if (!outf)
  std::cerr << "Couldn't open file for writing\n";
outf << "Added a line\n";

std::ifstream inf { "file.txt" };
if (!inf)
  std::cerr << "Couldn't open file for reading\n";
std::string str{};
while (inf >> str) // line seperated
  std::cout << str << '\n';
while (std::getline(inf, str)) // newline seperated
  std::cout << str << '\n';
```
