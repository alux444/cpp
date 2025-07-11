# allocation

## static and automatic

static memory allocation - happens for static / global variables. allocated on program run, persists throughout lifetime

automatic memory allocation - happens for function params and local variables. allocated when block entered, freed on block leave

static and automatic alloc / dalloc happen automatically, but the size of variables / array must be known at compile time

## dynamic

dynamic memory allocation - make a request for OS to reserve some memory for use from the heap

## pointer to pointers

```cpp
int** ptrptr { &ptr };
std::cout << **ptrptr << '\n';
```

```cpp
int** array { new int*[10] }; // array of pointers

int (*array)[5] { new int[x][5] }; // array is a pointer to 5 ints

// 2d array
int** array { new int*[10] }; // allocate an array of 10 int pointers — these are our rows
for (int count { 0 }; count < 10; ++count)
    array[count] = new int[5]; // these are our columns

// destroying 2d array
for (int count { 0 }; count < 10; ++count)
    delete[] array[count];
delete[] array;
```
