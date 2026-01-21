//
// TEST_MA.h - Whats TEST_MA you ask?
//
// Author   - Fletcher M
//
// Created  - 19/01/26
// Modified - 19/01/26
//
//
// TEST_MA.h is a C testing library, Simply create some test,
// ADD_TEST your tests, (with optional arguments for setting
// timeouts, and custom names), then RUN_TESTS() and watch
// your terminal fill with pretty colors.
//


//
//             THE API / TUTORIAL
//
// Lets Go thought the API of this library together,
//
// TODO something about skipping to a quick overview
//
// lets just jump over this include guard and function
// definition, and hop right in!
//

// ignore this
#ifndef TEST_MA_H
#define TEST_MA_H

// ignore this
static const char *TEST_MA_internal_temp_sprintf(const char *format, ...) __attribute__ ((format (printf, 1, 2)));

// ignore this
#include <stdbool.h> // for 'bool'

//
//
// lets say you have a function you want to test,
//
//     int fib(int n) { /* Your implementation here */ }
//
// but you dont know if you got it correct, or have have an off buy one error!
//
// - is fib(0) -> 0 or 1?
//   - are you producing the nth fibonacci number?
//   - or the index n in an array if fibonacci numbers?
//
// you should probably test that. but how????????????????????????????????????????
//
// TEST_MA.h revolves around test functions, that have the signature:
//

typedef void (Test_Function)(void);

//
// AKA they take no arguments, and return no arguments.
//
// lets write an quick example function:
//
/*

// Testing functions are just regular functions.
void test_my_fibonacci(void) {
    //
    // TEST_EXPECT(expr) will fail, and immediately return
    // from the function, if expr is not == true
    //
    // TEST_EXPECT_WITH_REASON(expr, fmt, ...) allows you
    // to add a printf'd message to the test.
    //
    TEST_EXPECT_WITH_REASON(fib(1) == 1, "First Fib is 1");
    TEST_EXPECT(fib(2) == 1);
    TEST_EXPECT(fib(3) == 2);
    TEST_EXPECT(fib(4) == 3);

    TEST_MA_TEST_PRINTF("I sure hope this doesn't take forever.\n");
    TEST_EXPECT(fib(25) == 75025);

    // TEST_FAIL works exactly how you expect.
    if (fib(0) != 0) {
        TEST_FAIL("The 0th fib number should be 0");
    }

    // no need to return or anything. you can 'return;' at any
    // point to stop the test early, will be detected as correctly
    // passing the test
    //
    // return;
}

*/
//
// this codes tests pretty much everything you want about you fib function.
// (excludeing performance tests, but we'll talk about that later)
// (TODO talk about that later)
//
//
// Here are there relevent function headers. (they are actually
// implemented as macros, for developer ease of use)
//
//
// note the prefixes here, at the end of this #ifdef block,
// we strip the prefixes of of the macros for user friendly-ness
//
// Search for    #ifndef TEST_MA_DONT_STRIP_PREFIXES    for more info on prefixes
//


//
// expect some expression to evaluate to true, exits the test if false.
//
// were doing a poor mans longjmp here.
//
// TODO maybe we should ge the real long jmp in here...
//
#define TEST_MA_TEST_EXPECT(expr)                               \
        do { if (TEST_MA_internal_test_expect((expr), #expr, __FILE__, __LINE__, NULL))                  return; } while (0)

//
// just TEST_EXPECT, but you can add extra text
//
// TODO maybe we can combine these somehow?
// dose something like 'TEST_MA_internal_temp_sprintf( ##__VA_ARGS__## )' work?
//
#define TEST_MA_TEST_EXPECT_WITH_REASON(expr, reason, ...)      \
        do { if (TEST_MA_internal_test_expect((expr), #expr, __FILE__, __LINE__, TEST_MA_internal_temp_sprintf(reason, ##__VA_ARGS__))) return; } while (0)


//
// exits the test, failing it in the process. must provide some message
//
#define TEST_MA_TEST_FAIL(reason, ...)                          \
        do { TEST_MA_internal_test_fail(TEST_MA_internal_temp_sprintf(reason, ##__VA_ARGS__), __FILE__, __LINE__); return; } while (0)

//
//
//
//
//
// But how do we run the tests? (and our function from before.)
// all it takes is 2 easy steps.
//
//     1. Adding the test / tests:
//

typedef struct Add_Test_Opt {
    // display a custom name in test logs.
    const char *custom_name;
    // if you dont want to run this test right now.
    bool dont_run;
} Add_Test_Opt;

//
// Add a test, with optional arguments, just pass
// the function you want straight in
//
#define TEST_MA_ADD_TEST(test_function, ...)        \
    TEST_MA_internal_Add_Test_with_opt(test_function, #test_function, (Add_Test_Opt){ __VA_ARGS__ })


//
//     2. running all added tests:
//

// returns number of failures.
//
// yes, even this is a macro. gotta stay consistent.
#define TEST_MA_RUN_TESTS() TEST_MA_internal_Run_Tests()


//
//
// this is an example main function:
//
/*

int main(void) {
    // add the test
    ADD_TEST(test_my_fibonacci);

    // this function also has optional arguments,
    // (implemented as a macro), see 'Add_Test_Opt' struct
    // definition to see all options
    ADD_TEST(test_my_fibonacci, .custom_name = "my fibonacci test", .dont_run = true);


    // run all the tests, and return how many failed.
    int num_tests_failed = RUN_TESTS();

    // exit abnormally if there were any failed tests.
    return num_tests_failed == 0 ? 0 : 1;
}

*/
//
//
// And thats it. Thats the entire API, (for now.)
//
// TODO explain what happens if you crash
// TODO explain TEST_MA_TEST_PRINTF
//
//


// can be used to swap out printf for something else later
//
// new line is required for now... might remove it later...
#define TEST_MA_TEST_PRINTF(fmt, ...)       printf("    " fmt, ##__VA_ARGS__)




// TODO crash example
/*

void test_negative_numbers_in_fib(void) {
    // i sure hope this is correctly handled,
    // and dont crash or something.
    fib(-1);
    fib(-9999);
}

*/




//
// Internal Functions:
//
// Needed here because of macros.
//

void TEST_MA_internal_Add_Test_with_opt(Test_Function func, const char *real_function_name, Add_Test_Opt opt);

// returns number of failures
int TEST_MA_internal_Run_Tests(void);

bool TEST_MA_internal_test_expect(bool result, const char *expression_string,
                                  const char *file, int line,
                                  const char *reason);

void TEST_MA_internal_test_fail(const char *reason, const char *file, int line);





//
// Inspired by (but an inversion of) "nob.h"'s NOB_STRIP_PREFIX macro.
//
// If You    #define TEST_MA_DONT_STRIP_PREFIXES    the macros will not be stripped.
//
// I might change it to the way nob.h dose it.
// but this library is suppost to be stupid easy to use.
//

#ifdef TEST_MA_STRIP_PREFIX
    #warning "TEST_MA_STRIP_PREFIX isn't being used right now. This fact might change later."
#endif

#ifndef TEST_MA_DONT_STRIP_PREFIXES

    #define TEST_EXPECT                     TEST_MA_TEST_EXPECT
    #define TEST_EXPECT_WITH_REASON         TEST_MA_TEST_EXPECT_WITH_REASON
    #define TEST_FAIL                       TEST_MA_TEST_FAIL

    #define TEST_PRINTF                     TEST_MA_TEST_PRINTF

    #define ADD_TEST                        TEST_MA_ADD_TEST
    #define RUN_TESTS                       TEST_MA_RUN_TESTS

#endif // TEST_MA_DONT_STRIP_PREFIXES




#endif // TEST_MA_H










// see below comment. (the one before #ifndef TEST_MA_SKIP_IMPLEMENTATION_FOR_NOW)
#ifdef TEST_MA_UNDEFINE_SKIP_IMPLEMENTATION
    // test to see if its there, might stop some annoying errors.
    #ifdef TEST_MA_SKIP_IMPLEMENTATION_FOR_NOW
        #undef TEST_MA_SKIP_IMPLEMENTATION_FOR_NOW
    #endif
#endif // TEST_MA_UNDEFINE_SKIP_IMPLEMENTATION


//
// unlike other Header only libraries, if you want to want to
// include this testing framework in multiple files, and only
//      #define TEST_MA_IMPLEMENTATION
// in one file, you will have to stick this before your includes,
// and undef it later.
//
// (or just
//      #define TEST_MA_UNDEFINE_SKIP_IMPLEMENTATION
// for convenience)
//
//
// REASONING:
//      this is suppost to be convenient. if somebody doesn't know
//      about the header #define trick, they might get confused and
//      have a bad experience with my libary.
//
#ifndef TEST_MA_SKIP_IMPLEMENTATION_FOR_NOW

#ifndef __TEST_MA_IMPLEMENTATION_GUARD
#define __TEST_MA_IMPLEMENTATION_GUARD



// what static means in a local variable context
#define TEST_MA_local_persist       static
// what static means in a function context, (its marked private)
#define TEST_MA_internal            static
// what static means in a global variable context, (i have no idea)
#define TEST_MA_global_variable     static





#include <string.h>  // for 'strlen()'
#include <stdint.h>  // for 'size_t'
#include <stddef.h>  // for 'NULL'

#include <stdio.h>   // for 'printf()'
#include <stdarg.h>  // for 'temp_sprintf()' reasons

#include <assert.h>  // for 'assert()'

#include <stdlib.h>  // for 'exit()'


#ifdef _WIN32

    #warning "Windows support has not been tested. good luck."

#else

    #include <unistd.h>     // for 'fork()' and other functions for test sandboxing
    #include <sys/wait.h>   // for 'waitpid()'

#endif




// terminal color codes.
#define TEST_MA_COLOR_RESET     "\033[1;0m"
#define TEST_MA_COLOR_GREEN     "\033[1;32m"
#define TEST_MA_COLOR_RED       "\033[1;31m"
#define TEST_MA_COLOR_YELLOW    "\033[1;33m"
#define TEST_MA_COLOR_GRAY      "\033[1;90m"

// 'with color'
#define WC(COLOR, text)   COLOR text TEST_MA_COLOR_RESET


#define TEST_MA_ARRAY_LEN(arr) (sizeof(arr) / sizeof(arr[0]))




// TODO how big should we make this number?
//
// how many tests can the user possibly have?
#define TEST_MA_TEMP_SPRINTF_NUM_BUFFERS        256
#define TEST_MA_TEMP_SPRINTF_BUFFER_SIZE        512

const char *TEST_MA_internal_temp_sprintf(const char *format, ...) {
    TEST_MA_local_persist char          buffers[TEST_MA_TEMP_SPRINTF_NUM_BUFFERS][TEST_MA_TEMP_SPRINTF_BUFFER_SIZE];
    // TODO make atomic
    TEST_MA_local_persist unsigned int  current_buffer_index = 0;

    char *buf = buffers[(current_buffer_index++) % TEST_MA_ARRAY_LEN(buffers)];

    va_list args;
    va_start(args, format);
        vsnprintf(buf, sizeof(buffers[0]), format, args);
    va_end(args);

    return buf;
}







typedef struct TEST_MA_One_Test {
    Test_Function *func;
    const char *real_function_name;
    Add_Test_Opt opt;

    // will be set to true inside one of the tests, when you call TEST_FAIL() or something
    bool test_failed;
    // text to be set if a test fails for some reason.
    const char *reason_for_test_failure;
} TEST_MA_One_Test;



// this number has a relation to TEST_MA_TEMP_SPRINTF_BUFFER_COUNT
#define TEST_MA_MAX_TESTS   256

typedef struct TEST_MA_Context {
    // will set this before calling a test.
    int current_test_index;

    TEST_MA_One_Test tests[TEST_MA_MAX_TESTS];
    size_t tests_count;
} TEST_MA_Context;

// global variable for now. this just makes it easier to do things
TEST_MA_global_variable TEST_MA_Context TEST_MA_context = {
    .current_test_index = -1,
};






// TODO use __FILE__ and __LINE__ for better messages.
TEST_MA_internal void TEST_MA_internal_set_current_test_failed(const char *text) {
    bool current_index_in_bounds = (0 <= TEST_MA_context.current_test_index && TEST_MA_context.current_test_index < (int)TEST_MA_context.tests_count);

    if (!current_index_in_bounds) {
        assert(false && "You called some test function in an improper way, use TEST_MA_RUN_TESTS to run your tests, you cannot run tests individually for now");
    } else {
        TEST_MA_context.tests[TEST_MA_context.current_test_index].test_failed = true;
        TEST_MA_context.tests[TEST_MA_context.current_test_index].reason_for_test_failure = text;
    }
}



TEST_MA_internal void TEST_MA_internal_test_expect_success(const char *expr) {
    printf("    " WC(TEST_MA_COLOR_GREEN, "SUCCESS - %s") "\n", expr);
}

bool TEST_MA_internal_test_expect(bool result, const char *expression_string,
                         const char *file, int line,
                         const char *reason) {

    (void) file; // TODO for better errors
    (void) line; // TODO for better errors

    if (result) {
        TEST_MA_internal_test_expect_success(expression_string);
        return false;
    }

    const char *set_failed_text;
    if (!reason) {
        set_failed_text = TEST_MA_internal_temp_sprintf("TEST_EXPECT: failed on '%s'", expression_string);
    } else {
        set_failed_text = TEST_MA_internal_temp_sprintf("TEST_EXPECT: failed on '%s', with reason '%s'", expression_string, reason);
    }

    TEST_MA_internal_set_current_test_failed(set_failed_text);

    return true;
}


void TEST_MA_internal_test_fail(const char *reason, const char *file, int line) {
    (void) file;
    (void) line;

    const char *set_failed_text = TEST_MA_internal_temp_sprintf("TEST_FAIL: %s", reason);
    TEST_MA_internal_set_current_test_failed(set_failed_text);
}




void TEST_MA_internal_Add_Test_with_opt(Test_Function func, const char *real_function_name, Add_Test_Opt opt) {
    assert(TEST_MA_context.tests_count < TEST_MA_ARRAY_LEN(TEST_MA_context.tests));

    TEST_MA_One_Test new_test = {
        .func = func,
        .real_function_name = real_function_name,
        .opt = opt,

        .test_failed = false,
        .reason_for_test_failure = NULL,
    };

    TEST_MA_context.tests[TEST_MA_context.tests_count++] = new_test;
}



TEST_MA_internal void TEST_MA_internal_run_one_test(size_t test_index) {
    TEST_MA_One_Test *to_test = &TEST_MA_context.tests[test_index];

#ifdef _WIN32

    // Windows dose not support for, we use fork for sandboxing
    // against testing functions crashing, and for automatic
    // memory management, you can't leek memory from the os.
    // it sees all.
    TEST_MA_context.current_test_index = test_index;
    to_test->func();
    TEST_MA_context.current_test_index = -1;

#else

    TEST_MA_context.current_test_index = test_index;

    bool run_on_main_thread = false;

    union Pipe_File_Descriptors {
        struct { int read, write; };
        int as_pair[2];
    } pipefd;

    bool close_pipefd = false;


    if (pipe2(pipefd.as_pair, 0) != 0) {
        perror("Could not create pipes");
        run_on_main_thread = true;
        goto just_do_the_test_on_the_main_thread;
    } else {
        close_pipefd = true;
    }

    // assumes you provide a L-value
    #define CLOSE_PIPE(pipe) do { if (pipe) { close(pipe); pipe = 0; } } while (0)
    // fork the process so we dont die if someone divides by zero.
    pid_t pid = fork();
    if (pid == -1) {
        perror("error when trying to fork");
        run_on_main_thread = true;
        goto just_do_the_test_on_the_main_thread;
    }

    if (pid == 0) { // child process
        // child dose not read
        CLOSE_PIPE(pipefd.read);

        to_test->func();

        if (to_test->test_failed) {
            // send some info back to the parent
            //
            // we know we did not crash, but we did fail a test.
            //
            // +1 because were also sending the null terminator
            write(pipefd.write, to_test->reason_for_test_failure, strlen(to_test->reason_for_test_failure)+1);
            CLOSE_PIPE(pipefd.write);
            exit(1);
        }

        CLOSE_PIPE(pipefd.write);
        exit(0);

    }

    // we are the parent

    // parent dose not write
    CLOSE_PIPE(pipefd.write);


    // TODO WNOHANG for quitting after some time, to stop inf loops.
    //
    // TODO we need to get more info out of this 

    // wait for child to quit.
    int status;
    pid_t result = waitpid(pid, &status, 0);

    if (result == -1) {
        perror("Could not wait for child to end. Quitting");
        exit(1);
    }
    assert(result == pid);

    if (status != 0) {
        to_test->test_failed = true;

        // try to get a message from the dead child.
        char buf[512] = {0};
        // make sure there will still be a null terminator.
        ssize_t count = read(pipefd.read, buf, sizeof(buf)-1);
        if (count == -1) {
            perror("Could not read from pipe");
            to_test->reason_for_test_failure = "UNKNOWN: Failed To Read From Pipe";
        } else {

            size_t n = strlen(buf);

            if (n != 0) {
                // @Leak we could keep track of things like this, but meh.
                to_test->reason_for_test_failure = strdup(buf);
            } else {
                to_test->reason_for_test_failure = "UNKNOWN: Test did not communicate with test handler, it probably crashed.";
            }
        }
    }



just_do_the_test_on_the_main_thread:
    if (close_pipefd) {
        // TODO use to communicate
        CLOSE_PIPE(pipefd.read);
        CLOSE_PIPE(pipefd.write);
    }

    #undef CLOSE_PIPE // take out the trash


    if (run_on_main_thread) {
        printf("Running test on main thread. If this crashes we all go down.\n");
        to_test->func();
    }


    TEST_MA_context.current_test_index = -1;

#endif
}



int TEST_MA_internal_Run_Tests(void) {
    if (TEST_MA_context.tests_count == 0) {
        // TODO better message.
        printf("No tests to run.\n");
        return 0;
    }


    int max_text_len = 0;
    for (size_t i = 0; i < TEST_MA_context.tests_count; i++) {
        TEST_MA_One_Test *to_test = &TEST_MA_context.tests[i];

        const char *test_name = to_test->real_function_name;
        if (to_test->opt.custom_name) test_name = to_test->opt.custom_name;

        int text_len = strlen(test_name);
        if (max_text_len < text_len) max_text_len = text_len;
    }



    for (size_t test_index = 0; test_index < TEST_MA_context.tests_count; test_index++) {
        TEST_MA_One_Test *to_test = &TEST_MA_context.tests[test_index];

        const char *test_name = to_test->real_function_name;
        if (to_test->opt.custom_name) test_name = to_test->opt.custom_name;

        if (to_test->opt.dont_run) {
            printf(WC(TEST_MA_COLOR_GRAY,  "Passing Test %ld: %-*s") "\n\n", test_index, max_text_len, test_name);
            continue;;
        }

        printf("Running Test %ld: " WC(TEST_MA_COLOR_YELLOW, "%-*s") "\n", test_index, max_text_len, test_name);


        // actually run the test here.
        TEST_MA_internal_run_one_test(test_index);


        if (!to_test->test_failed) {
            printf("Test " WC(TEST_MA_COLOR_GREEN, "Passed") " %ld: " WC(TEST_MA_COLOR_YELLOW, "%s") "\n", test_index, test_name);
        } else {
            printf(WC(TEST_MA_COLOR_RED,   "Test Failed %ld: ") WC(TEST_MA_COLOR_YELLOW, "%s") "\n", test_index, test_name);
            printf("    " WC(TEST_MA_COLOR_RED, "%s") "\n", to_test->reason_for_test_failure);
        }
        printf("\n");
    }

    int number_of_fails = 0;
    for (size_t i = 0; i < TEST_MA_context.tests_count; i++) {
        TEST_MA_One_Test *to_test = &TEST_MA_context.tests[i];

        const char *test_name = to_test->real_function_name;
        if (to_test->opt.custom_name) test_name = to_test->opt.custom_name;

        const char *status_text = WC(TEST_MA_COLOR_GRAY, "PASS");
        if (!to_test->opt.dont_run) {
            if (to_test->test_failed) {
                status_text = TEST_MA_internal_temp_sprintf(WC(TEST_MA_COLOR_RED, "FAILED") "  - %s", to_test->reason_for_test_failure);
                number_of_fails += 1;
            } else {
                status_text = WC(TEST_MA_COLOR_GREEN, "SUCCESS");
            }
        }

        printf(
            "TEST %ld: " WC(TEST_MA_COLOR_YELLOW, "%-*s") " - STATUS: %s\n",
            i, max_text_len, test_name, status_text
        );
    }


    //
    // maybe reset this?
    //
    // we dont want users to call this in a loop, only garbage collected
    // languages can do that free()'ly...
    //
    // maybe we can use forks? just call the function from inside there?
    // when the process dies, the memory will be gone...
    //
    // TEST_MA_context.tests_count = 0;

    return number_of_fails;
}







#endif // __TEST_MA_IMPLEMENTATION_GUARD

#endif //  TEST_MA_SKIP_IMPLEMENTATION_FOR_NOW


