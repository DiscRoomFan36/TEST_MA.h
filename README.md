
# TEST_MA.h

Whats `TEST_MA` you ask? Great Question!

`TEST_MA.h` is a C testing (single header) library, it is designed for ease of use.

*and has some weird quirks compared to other single header files, but we'll talk about them later.*

The `TEST_MA.h` file itself explains most of whats in this readme (and more it doesn't explain), if you would prefer to read that.



## How Do I Use TEST_MA.h? (The Quick Version)

The src/example.c file is a good demonstration, (And the TEST_MA.h file itself is a good resource),

But heres a quick example file, with a step by step breakdown below.

```c
// You don't need to  #define TEST_MA_IMPLEMENTATION
// I will explain this later
#include "TEST_MA.H"


// classic fib function
int fib(int n) {
    if (n <= 1) return 1;
    return fib(n-2) + fib(n-1);
}


// This is a test function
void test_my_fibonacci(void) {
    TEST_EXPECT_WITH_REASON(fib(0) == 1, "*my* fib function starts from 1 not zero.");

    TEST_EXPECT(fib(24) == 75025);

    if (1 == 3) TEST_FAIL("Just making sure. you can never be too careful, what if we were on a 1-bit int system?");
}


int main(void) {
    // add the test
    ADD_TEST(test_my_fibonacci);

    // this function also has optional arguments,
    // (implemented as a macro), see 'TEST_MA_Add_Test_Opt' struct
    // definition to see all options
    ADD_TEST(test_my_fibonacci, .custom_name = "my fibonacci test", .dont_run = true);


    // run all the tests, and return how many failed.
    int num_tests_failed = RUN_TESTS();

    // exit abnormally if there were any failed tests.
    return (num_tests_failed == 0) ? 0 : 1;
}
```

## How Do I Use TEST_MA.h? (The Slow Version)

A Step By Step Breakdown

### Write The Behavior You Want To Test

```c
// classic fib function,
//
// I want to test that this is correct!
int fib(int n) {
    if (n <= 1) return 1;
    return fib(n-2) + fib(n-1);
}
```

### Include The File In Your Project

```c
// You don't need to  #define TEST_MA_IMPLEMENTATION
// I will explain this later
#include "TEST_MA.h"
```

### Make A Test

Test functions are just regular c functions, but they must:
  - Take no arguments, and,
  - Return no arguments.

Here is the typedef:
```c
typedef void (Test_Function)(void);
```

But what makes test functions special is that they can call the TEST_*-ing functions.

All testing is done though the TEST_* functions. Heres an Example:

```c
void test_my_fibonacci(void) {
    TEST_EXPECT_WITH_REASON(fib(0) == 1, "*my* fib function starts from 1 not zero.");

    TEST_EXPECT(fib(24) == 75025);

    if (1 == 3) TEST_FAIL("Just making sure, you can never be too careful, what if we were on a 1-bit int system?");
}
```

### Running The Tests

This testing framework is not built into your compiler, so you can't just run `clang test` or whatever.

To run tests you have to actually run them, (from inside your main function.)

All it takes is 2 easy steps.
1. Add The Test
2. Run all tests

Heres an example main:

```c
int main(void) {
    // add the test
    ADD_TEST(test_my_fibonacci);

    // this function also has optional arguments,
    // (implemented as a macro), see 'TEST_MA_Add_Test_Opt' struct
    // definition to see all options
    ADD_TEST(test_my_fibonacci, .custom_name = "my fibonacci test", .dont_run = true);


    // run all the tests, and return how many failed.
    int num_tests_failed = RUN_TESTS();

    // exit abnormally if there were any failed tests.
    return (num_tests_failed == 0) ? 0 : 1;
}
```



## Quick Start / Running The Example

heres how you run

* **NOTE FOR WINDOWS USERS**
  - I haven't tested this at all on widows, good luck!
  - Also one of the tests is gonna segfault you. have fun.

```bash
# compile the build script once.
$ cc -o nob nob.c

# compile and run
$ ./nob debug && ./build/example_debug
```



## Wait, What Single-File-Header Quirks Where You Talking About?

Normal Single Header Libraries would use thing like **Implementation Guards** And **Macros To Enable Striping Prefixes**, however ,this library inverts those principles.


Here is what a Normal Library Would Do:
```c
// for example, instead of doing this too:
#define TEST_MA_STRIP_PREFIXES   // strip prefixes off of common functions
#include "TEST_MA.h"

// < Your C File >

#define TEST_MA_IMPLEMENTATION   // add the implementation
#include "TEST_MA.h"
```

Here is what we do instead:
```c
#define TEST_MA_DONT_STRIP_PREFIXES         // to not strip prefixes
#define TEST_MA_SKIP_IMPLEMENTATION_FOR_NOW // skip the implementation for now.
#include "TEST_MA.h"

// < Your C File >

// later, when you want to add the implementation again:
#define TEST_MA_UNDEFINE_SKIP_IMPLEMENTATION
#include "TEST_MA.h"
```

```c
// Or in the highly unlikely case where you
// want to strip prefixes AND/OR also are only
// using a single file so you don't need to
// worry about implementation guards
//
// Just include the file
#include "TEST_MA.h"
```

### Why is it done this way?
- So that the most common use case, (actually testing something), is made to be the easiest.



## Questions

### What If My Program Crashes?

TODO
