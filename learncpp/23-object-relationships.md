# composition

- to be a composition, an object / part must have the following relationship
  - the part (member) is part of the object (class)
  - the part (member) can only belong to one object (class) at once
  - the part (member) has its existence managed by the object (class)
  - the part (member) does not know about the existence of the object (class)

# aggregation

- to be an aggregation, an object / part must have the following relationship
  - the part (member) is part of the object (class)
  - the part (member) can belong to more than one object (class) at a time
  - the part (member) does not have its existence managed by the object (class)
  - the part (member) does not know about the existence of the object (class)

# association

- to be an association, an object / part must have the following relationship
  - the associated object (member) is otherwise unrelated to the object (class)
  - the associated object (member) can belong to more than one object (class)
  - the associated object (member) does not have its existence managed by the object (class)
  - the associated object (member) may or may not know about the existence of the object (Class)

# dependency

- a dependency occurs when an object invokes another objects functionality in order to accomplish some task
  - weaker than an association
  - typically not a member

# list initializer

- to allow for list initialisation, use `std::list_initializer`
  - see 23.6 cpp implem
- list initialization will now favour that defined list constructor

if you implement a constructor that takes a `std::initializer_list`, you should ensure you do at least one of the following:

- provide an overloaded list assignment operator
- provide a proper deep-copying copy assignment operator
- delete the copy assignment operator

if we don't have the assignment operator and use an assignment, e.g `array = { 1, 3, 5, 7, 9, 11 };`, now the compiler will resolve to the implicit provided copy assignment (shallow copy)

making both the data values point to the same thing, and then once the assignment occurs, the destructor is called on the temporary. now the data in `array` is a dangling pointer.
