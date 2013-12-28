# SimpleTest

SimpleTest is a header file that provides test and assertion macros for C/C++. It aims to provide dead simple unit testing.

## Installation

### System-wide

To install SimpleTest system-wide on Unix-based systems, simply run the following:

```
make install
```

Depending on your system you may need to be root before running that command. By default, it will install using `/usr/local` as the prefix. This can be changed easily inside `Makefile`.

### Project

Simply copy [simpletest.h](include/simpletest.h) somewhere in your project. If the file is placed in a separate directory outside of the location you will be placing your test source files, configure your build system to include it for your test source files.

## Usage

### Getting started

Create a new source file that will hold your tests and include the header file.

```c
#include <simpletest.h>
```

Change the angular brackets to quotes if you simply placed simpletest.h along with your test source files.

Then, start writing your tests using this format:

```c
TEST(my_first_simpletest) {
  int i = 0;
  int j = 0;
  ASSERT_EQUAL(i, j)
}
```

Finally, create the entry point to your tests:

```c
TEST_MAIN(
  // List each test function here.
  my_first_simpletest,
  another_test
)
```

#### Putting it together

The following is a functioning test and is all that it takes to get started with SimpleTest.

```c
#include <simpletest.h>

TEST(my_first_simpletest) {
  int i = 0;
  int j = 0;
  ASSERT_EQUAL(i, j)
}

TEST_MAIN(
  my_first_simpletest
)
```

Compiling and running it will yield these results:

```
Test my_first_simpletest passed!
Results: 1 out of 1 test passed.
```

#### Multiple test source files

It is possible to have multiple test source files with only one entry point. Simply create a header file and source file like you normally would and prototype the test function in the header file.

##### Example

* __second_test.h__

  ```c
  #ifndef SECOND_TEST_H
  #define SECOND_TEST_H

  #include <simpletest.h>

  TEST(my_second_simpletest);

  #endif
  ```

* __second_test.c__

  ```c
  #include "second_test.h"

  TEST(my_second_simpletest) {
    // Test things here.
  }
  ```

* __first_test.c__

  ```c
  #include <simpletest.h> // Optional now since second_test.h provides it
  #include "second_test.h"

  TEST(my_first_simpletest) {
    int i = 0;
    int j = 0;
    ASSERT_EQUAL(i, j)
  }

  TEST_MAIN(
    my_first_simpletest,
    my_second_simpletest
  )
  ```

### Assertions

Currently, there are only a few assertions available. These assertions are similar to [MiniTest's](http://docs.seattlerb.org/minitest/Minitest/Assertions.html).

* __ASSERT(test)__

  Asserts if `test` is true.

* __ASSERT_EQUAL(exp, act)__

  Asserts if `exp` is equal to `act`.

* __ASSERT_NULL(test)__

  Asserts if `test` is `NULL`.

## Build systems

### CMake

To add the `test` make target with CMake, follow these instructions. The instructions given here assume your tests are in `test/` and is directly under the root of your project. These instructions don't make use of CMake's testing commands as those are more geared towards CTest.

Add to `CMakeLists.txt` in your project root:

```cmake
add_subdirectory(test)
```

Create `CMakeLists.txt` in `test/` with the following:

```cmake
# Grab every source file in this directory.
file(GLOB_RECURSE test_SOURCES "*.c")

# Compile to an executable target named 'project_test'
add_executable(project_test ${test_SOURCES})

# Create a custom target named 'test' that runs the executable target 'project_test'
add_custom_target(test "${CMAKE_BINARY_DIR}/test/project_test")
```
