# libraries

## static library (archive)

- consists of routines that are compiled and linked directly into program
- .lib (windows) .a (linux)
- all the functionality of the library becomes a part of the executable
- ensures right version of library is always used with program
- can use them just like functionality used for the program
- but lots of wasted space
- difficult to upgrade library, to update, need to replace entire executable

## dynamic library (shared library)

- routines loaded into application at runtime
- library doesn't become part of executable, is a separate unit
- .dll (windows) .so (linux)
- many programs can share one copy, saving space
- easy to upgrade without replacing all executables
- must explicitly load and interface, can be awkward
  - can use import libraries to automate process of loading and using dynamic library

## installing libraries

- download library - usually precompiled package for the library
- install library - package manager (linux) unzipping library to directory (windows)
- make sure compiler knows where to look for header file(s)
- tell linker where to look for library file(s)
- if using static / import libraries, tell linker which library files to link
- `#include` library header file(s) in program
- if using dynamic libraries, make sure program knows where to find them
