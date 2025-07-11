# vectors

- use `emplace_back` when constructing new objects
- use `push_back` for existing objects

# c style array

- usually when a c style array gets used in an expression, it gets implicitly converted to a pointer to the first element (aka array decay)
- it wont decay if
  - used as args for `sizeof()` and `typeid()`
  - when taking the address of the array using `operator&`
  - when passed to a member of a class type
  - when passed by reference
- decayed array pointer doesn't know the length
- therefore, c style arrays are passed by address, even when it seems like they're passed by value
- this was to ensure that c style arrays of different lengths can be passed as params without making expensive copies

- so in conclusion fuck c style arrays unless u rly need to

# pointer arithmetic

- `p[3]` is equivalent to `*(p+3)`
- we prefer using pointer arithmetic when we want to use relative position from a given element
