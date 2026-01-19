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

// TODO Comments / Explanation
// TODO Comments / Explanation
// TODO Comments / Explanation
// TODO Comments / Explanation
// TODO Comments / Explanation
// TODO Comments / Explanation
// TODO Comments / Explanation
// TODO Comments / Explanation
// TODO Comments / Explanation
// TODO Comments / Explanation
// TODO Comments / Explanation
// TODO Comments / Explanation
// TODO Comments / Explanation
// TODO Comments / Explanation
// TODO Comments / Explanation
// TODO Comments / Explanation
// TODO Comments / Explanation
// TODO Comments / Explanation
// TODO Comments / Explanation
// TODO Comments / Explanation

#ifndef TEST_MA_H
#define TEST_MA_H


// TODO comment the shit out of this.


#include <stdbool.h> // for 'bool'
#include <stdint.h>  // for 'size_t'
#include <string.h>  // for 'strlen()'
#include <stdio.h>   // for 'printf()'
#include <stdarg.h>  // for 'temp_sprintf()' reasons

#include <assert.h>  // for 'assert()'


// what static means in a local variable context
#define TEST_MA_local_persist       static
// what static means in a function context, (its marked private)
#define TEST_MA_internal            static
// what static means in a global variable context, (i have no idea)
#define TEST_MA_global_variable     static




// the type of function you pass into ADD_TEST
typedef void (Test_Function)(void);

typedef struct {
    // if you dont want to run this test right now.
    bool dont_run;
    // display a custom name in test logs.
    const char *custom_name;

} Add_Test_Opt;

void Add_Test_with_opt(Test_Function func, const char *real_function_name, Add_Test_Opt opt);

#define TEST_MA_ADD_TEST(test_function, ...)        \
    Add_Test_with_opt(test_function, #test_function, (Add_Test_Opt){ __VA_ARGS__ })



// returns number of failures
int TEST_MA_Run_Tests(void);

// returns number of failures
#define TEST_MA_RUN_TESTS() TEST_MA_Run_Tests()











TEST_MA_internal const char *TEST_MA_temp_sprintf(const char *format, ...) __attribute__ ((format (printf, 1, 2)));









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







// tools to help you create tests, and help test state management



// TODO maybe this could be a helper macro.
// // predefine the tests
// #define X(test, ...)   void test(void);
//     TESTS
// #undef X





// when calling TEST_EXPECT or otherwise failing a test, one of these is set to true


// // TODO use __FILE__ and __LINE__ for better messages.
// #define SET_CURRENT_TEST_FAILED(reason_text_fmt, ...)                               \
//     do {                                                                            \
//         if (!(0 <= TEST_MA_context.current_test_index && TEST_MA_context.current_test_index < (int)TEST_MA_context.tests_count)) {      \
//             assert(false && "You called some test function in an improper way, use TEST_MA_RUN_TESTS to run your tests, you cannot run tests individually for now");        \
//         } else {                                                                    \
//             TEST_MA_context.tests[TEST_MA_context.current_test_index].test_failed = true;       \
//             TEST_MA_context.tests[TEST_MA_context.current_test_index].reason_for_test_failure = TEST_MA_temp_sprintf(reason_text_fmt, ##__VA_ARGS__);       \
//         }                                                                           \
//     } while (0)




// can be used to swap out printf for something else later
//
// new line is required for now... might remove it later...
#define TEST_MA_TEST_PRINTF(fmt, ...)       printf("    " fmt, ##__VA_ARGS__)

// TODO TEST_MA_STRIP_PREFIXES
#define TEST_PRINTF     TEST_MA_TEST_PRINTF



bool TEST_MA_test_expect(bool result, const char *expression_string,
                         const char *file, int line,
                         const char *reason);

// were doing a poor mans longjmp here.
// 
// maybe we should ge the real long jmp in here...
#define TEST_EXPECT(expr)                               \
        do { if (TEST_MA_test_expect((expr), #expr, __FILE__, __LINE__, NULL))                  return; } while (0)

#define TEST_EXPECT_WITH_REASON(expr, reason, ...)      \
        do { if (TEST_MA_test_expect((expr), #expr, __FILE__, __LINE__, TEST_MA_temp_sprintf(reason, ##__VA_ARGS__))) return; } while (0)



void TEST_MA_test_fail(const char *reason, const char *file, int line);

#define TEST_FAIL(reason, ...)                          \
        do { TEST_MA_test_fail(TEST_MA_temp_sprintf(reason, ##__VA_ARGS__), __FILE__, __LINE__); return; } while (0)



// TODO do something like this.
// #ifndef TEST_MA_DONT_STRIP_PREFIXES
//     // #define TEST_PRINTF TEST_MA_PRINTF
// #endif // TEST_MA_DONT_STRIP_PREFIXES




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

const char *TEST_MA_temp_sprintf(const char *format, ...) {
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
    printf("    " WC(TEST_MA_COLOR_GREEN, "SUCCESS: %s)") "\n", expr);
}

bool TEST_MA_test_expect(bool result, const char *expression_string,
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
        set_failed_text = TEST_MA_temp_sprintf("TEST_EXPECT: failed on '%s'", expression_string);
    } else {
        set_failed_text = TEST_MA_temp_sprintf("TEST_EXPECT: failed on '%s', with reason '%s'", expression_string, reason);
    }

    TEST_MA_internal_set_current_test_failed(set_failed_text);

    return true;
}


void TEST_MA_test_fail(const char *reason, const char *file, int line) {
    (void) file;
    (void) line;

    const char *set_failed_text = TEST_MA_temp_sprintf("TEST_FAIL: %s", reason);
    TEST_MA_internal_set_current_test_failed(set_failed_text);
}




void Add_Test_with_opt(Test_Function func, const char *real_function_name, Add_Test_Opt opt) {
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




int TEST_MA_Run_Tests(void) {
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



    for (size_t i = 0; i < TEST_MA_context.tests_count; i++) {
        TEST_MA_One_Test *to_test = &TEST_MA_context.tests[i];

        const char *test_name = to_test->real_function_name;
        if (to_test->opt.custom_name) test_name = to_test->opt.custom_name;

        if (to_test->opt.dont_run) {
            printf(WC(TEST_MA_COLOR_GRAY,  "Passing Test %ld: %-*s") "\n\n", i, max_text_len, test_name);
            continue;
        }

        printf("Running Test %ld: " WC(TEST_MA_COLOR_YELLOW, "%-*s") "\n", i, max_text_len, test_name);

        TEST_MA_context.current_test_index =  i;
        to_test->func();
        TEST_MA_context.current_test_index = -1;

        if (!to_test->test_failed) {
            printf("Test " WC(TEST_MA_COLOR_GREEN, "Passed") " %ld: " WC(TEST_MA_COLOR_YELLOW, "%s") "\n", i, test_name);
        } else {
            printf(WC(TEST_MA_COLOR_RED,   "Test Failed %ld: ") WC(TEST_MA_COLOR_YELLOW, "%s") "\n", i, test_name);
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
                status_text = TEST_MA_temp_sprintf(WC(TEST_MA_COLOR_RED, "FAILED") "  - %s", to_test->reason_for_test_failure);
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


