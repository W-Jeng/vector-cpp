# Standard Vector and Allocator Implementation

## Overview

This project provides a custom implementation of:

1. **Allocator**: A memory allocator (`ctm::allocator`) designed to handle memory allocation and deallocation for a specific type.
2. **Vector**: A dynamic array (`ctm::vector`) that utilises the custom allocator, offering functionalities similar to `std::vector`.

To ensure reliability and correctness, the implementation is rigorously tested with 38 test cases using **GoogleTest** and **CMake**.

---

## Features

### Custom Allocator (`ctm::allocator`)
- Implements the **Allocator concept** for use in standard and custom containers.
- Features:
  - Memory allocation with `allocate`.
  - Memory deallocation with `deallocate`.
  - Object construction and destruction.
  - Maximum size management.
  - Compatibility with rebind for other types.

### Custom Vector (`ctm::vector`)
- Implements a **dynamic array** similar to `std::vector`.
- Features:
  - Full range of element access methods (e.g., `at`, `front`, `back`, `data`).
  - Iterators for traversal (`begin`, `end`).
  - Capacity management (`size`, `capacity`, `reserve`, `resize`).
  - Modifiers (`push_back`, `pop_back`, `insert`, `erase`, `clear`, `swap`).
  - Supports **move semantics**, **copying**, and **initialisation from iterators** or **initializer lists**.
  - Automatic capacity resizing using a power-of-two growth strategy.

---

## Testing

### Framework
- **GoogleTest**: All tests are written using the GoogleTest framework to ensure correctness and robustness.
- **CMake**: The project is configured to use CMake for building and running tests.

### Coverage
The tests cover:
1. **Constructors**:
   - Default constructor, copy constructor, move constructor.
   - Initialisation with `size`, `value`, or iterators.
   - Initialisation from initializer lists.
2. **Element Access**:
   - `at()`, `operator[]`, `front()`, `back()`, `data()`.
   - Validating bounds and exception handling for `at()`.
3. **Iterators**:
   - Testing `begin()`, `end()`, `cbegin()`, `cend()` for both mutable and immutable contexts.
4. **Capacity**:
   - Verifying `size()`, `capacity()`, and `reserve()`.
   - Checking behaviour of `empty()`.
5. **Modifiers**:
   - Correctness of `push_back`, `pop_back`, `insert`, `erase`.
   - Proper resizing with `resize()` and destruction of elements during `clear()`.
   - Swap operation integrity with `swap()`.
6. **Performance**:
   - Growth strategy validation using `reserve` and insertion benchmarks.

### Example Test Case

```cpp
#include <gtest/gtest.h>
#include "custom_vector.h"

TEST(VectorTest, PushBackIncreasesSize) {
    ctm::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
}
```

### Example Usage
## Using the Custom Allocator
```cpp
#include "custom_allocator.h"

int main() {
    ctm::allocator<int> alloc;
    int* ptr = alloc.allocate(5);
    alloc.construct(ptr, 42);

    std::cout << "Value: " << *ptr << std::endl;

    alloc.destroy(ptr);
    alloc.deallocate(ptr, 5);

    return 0;
}
```

## Using the Custom Vector
```cpp
#include "custom_vector.h"

int main() {
    ctm::vector<int> vec;

    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    for (const auto& val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    return 0;
}
```

### Build and Run Instructions
## Prerequisites
- CMake: Version 3.20 and above.
- GoogleTest: Installed as a submodule.

## Build the Project
1. Clone the repo:
```bash
git clone https://github.com/W-Jeng/vector-cpp.git
cd vector-cpp
git submodule update --init --recursive
```

2. Create a build directory and configure the project
```bash
mkdir build
cd build
cmake ..
```

3. Build the project:
```bash
cmake --build .
```

## Run Tests
```bash
./bin/runtest
```

## Run main
```bash
./bin/main
```

### Lessons Learnt

Through this project, I gained a deeper understanding of memory allocation, the internal workings of allocators and dynamic arrays, and significantly improved my knowledge of templates and modern C++. I also enhanced my skills in implementing efficient data structures and optimising resource management. Writing comprehensive tests using GoogleTest not only improved my testing abilities but also helped me identify and fix unseen bugs, reinforcing the importance of rigorous validation and edge case handling in software development. Additionally, I developed a better appreciation for modular design, reusable code, and the significance of adhering to best practices in creating performant and maintainable libraries.
