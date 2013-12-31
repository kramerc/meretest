# MereTest

MereTest is a header file that provides test and assertion macros for C/C++. It aims to provide dead simple unit testing.

## Installation

### System-wide

To install MereTest system-wide on Unix-based systems, simply run the following:

```
make install
```

Depending on your system you may need to be root before running that command. By default, it will install using `/usr/local` as the prefix. This can be changed easily inside `Makefile`.

### Project

Simply copy [meretest.h](include/meretest.h) somewhere in your project. If the file is placed in a separate directory outside of the location you will be placing your test source files, configure your build system to include it for your test source files.

## Usage

### Getting started

Create a new source file that will hold your tests and include the header file.

```c
#include <meretest.h>
```

Change the angular brackets to quotes if you simply placed meretest.h along with your test source files.

Then, start writing your tests using this format:

```c
TEST(my_first_meretest) {
  int i = 0;
  int j = 0;
  ASSERT_EQUAL(i, j)
}
```

Finally, create the entry point to your tests:

```c
TEST_MAIN(
  // List each test function here.
  my_first_meretest,
  another_test
)
```

#### Putting it together

The following is a functioning test and is all that it takes to get started with MereTest.

```c
#include <meretest.h>

TEST(my_first_meretest) {
  int i = 0;
  int j = 0;
  ASSERT_EQUAL(i, j)
}

TEST_MAIN(
  my_first_meretest
)
```

Compiling and running it will yield these results:

```
Test my_first_meretest passed!
Results: 1 out of 1 test passed.
```

#### Multiple test source files

It is possible to have multiple test source files with only one entry point. Simply create a header file and source file like you normally would and prototype the test function in the header file.

##### Example

* __second_test.h__

  ```c
  #ifndef SECOND_TEST_H
  #define SECOND_TEST_H

  #include <meretest.h>

  TEST(my_second_meretest);

  #endif
  ```

* __second_test.c__

  ```c
  #include "second_test.h"

  TEST(my_second_meretest) {
    // Test things here.
  }
  ```

* __first_test.c__

  ```c
  #include <meretest.h> // Optional now since second_test.h provides it
  #include "second_test.h"

  TEST(my_first_meretest) {
    int i = 0;
    int j = 0;
    ASSERT_EQUAL(i, j)
  }

  TEST_MAIN(
    my_first_meretest,
    my_second_meretest
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

It is possible to add the `test` make target with CMake and have it work with MereTest. It is best not to use CMake's testing commands as those are more geared towards CTest.

If you're creating an executable, an object library target can be used in order to avoid compiling your main source files twice.

To do so, consider this example:

```cmake
add_library(myproject_obj OBJECT
  # Do not include the source file containing the entry point.
  src/file1.c
  src/file2.c
)
add_executable(myproject $<TARGET_OBJECTS:myproject_obj> src/main.c)
```

The source file containing the entry point (`main`) is only provided to the executable. If it was compiled into the object library, it would result in a linking error regarding duplicate symbols when compiling the test source files as the tests have their own entry point. If you are unit testing functions that are inside the source file that contains the entry point, consider moving them outside of that source file.

Assuming that your test source files are in `test/`, you will want to tell CMake to add the `test/` subdirectory.

```cmake
add_subdirectory(test)
```

Then inside `test/`, create a `CMakeLists.txt` file that provides targets for your tests. If you're building an executable, the object library will be referenced here as well. The test executable name cannot be the same name as the custom `test` target.

#### Examples

* For executables:

  ```cmake
  add_executable(myproject_test $<TARGET_OBJECTS:myproject_obj>
    test_main.c
    test1.c
    test2.c
  )
  add_custom_target(test "${CMAKE_BINARY_DIR}/test/myproject_test" DEPENDS myproject_test)
  ```

* For libraries:

  ```cmake
  add_executable(myproject_test
    test_main.c
    test1.c
    test2.c
  )
  target_link_libraries(myproject_test myproject)
  add_custom_target(test "${CMAKE_BINARY_DIR}/test/project_test" DEPENDS myproject_test)
  ```
