
#define TESTS

// this is just to test if my macro trick works.
//
// if you use this header, you don't have to #define this,
// and #include "TEST_MA.h" again at the end of the file.
#define TEST_MA_SKIP_IMPLEMENTATION_FOR_NOW
#include "TEST_MA.h"

#include <stdio.h>


// predefining functions to make this file look cleaner.
void one_plus_one(void);
void size_of_works(void);
void my_strlen_behaves_as_expected(void);
void ints_are_64_bit_why_would_you_think_otherwise(void);
void dont_run_this_test_it_will_kill_you(void);
void i_will_run_until_the_heat_death_of_the_universe(void);
void i_will_also_run_forever_but_in_a_different_way(void);
void i_just_need_2_seconds(void);


int main(void) {
    printf("Whats TEST_MA you ask?\n");

    // basic tests
    ADD_TEST(one_plus_one, .custom_name = "basic test");
    ADD_TEST(size_of_works);

    // oh no! these ones will fail,
    // 
    // we run these without sandboxing, so that you can run
    // your debugger and break on these functions. to see 
    // where they went wrong!
    ADD_TEST(my_strlen_behaves_as_expected,                 .run_without_sandbox = true);
    ADD_TEST(ints_are_64_bit_why_would_you_think_otherwise, .run_without_sandbox = true);

    // this function will crash, and the test handler will handle it.
    ADD_TEST(dont_run_this_test_it_will_kill_you);
    // custom name, and showing you can stop some tests from running
    ADD_TEST(dont_run_this_test_it_will_kill_you, .dont_run = true, .custom_name = "wait, dont run this one.");

    // these test will inf loop,
    // the test runner will quit after 1 second
    ADD_TEST(i_will_run_until_the_heat_death_of_the_universe);
    ADD_TEST(i_will_also_run_forever_but_in_a_different_way);

    // giving this test just a little more time.
    ADD_TEST(i_just_need_2_seconds, .timeout_time = 2.0);
    // this will wait forever, so technically this program is never guaranteed to end!
    ADD_TEST(i_just_need_2_seconds, .timeout_time = -1, .custom_name = "inf wait time.");


    // run the tests, also showing (but not useing) a dangerous option.
    int num_tests_failed = RUN_TESTS(.disable_sandboxing_for_all_tests = false);

    printf("num_tests_failed = %d\n", num_tests_failed);
    if (num_tests_failed != 0)    printf("someone should fix those!\n");

    return 0;
}



int Add(int a, int b) {
    return a + b;
}
void one_plus_one(void) {
    TEST_EXPECT(Add(  1,   1) ==   2);
    TEST_EXPECT(Add( 34,  35) ==  69);
    TEST_EXPECT(Add(999, 999) == 999*2);
}

void size_of_works(void) {
    char buf[64];
    TEST_EXPECT(sizeof(buf) == 64);
}

int my_strlen(const char *s) {
    int n = 0;
    while (*s++) n++;
    return n;
}
void my_strlen_behaves_as_expected(void) {
    TEST_EXPECT(my_strlen("12345") == 5);
    int len = my_strlen("123456789012345678901234567890");
    TEST_EXPECT(len == 30);

    TEST_FAIL("everybody hates C strings, just define your own string.");
}

void ints_are_64_bit_why_would_you_think_otherwise(void) {
    TEST_EXPECT(sizeof(int)*8 == 64);
}

void dont_run_this_test_it_will_kill_you(void) {
    // oh god, oh no, somebody help me!
    int *ptr = 0;
    *ptr = 420;
}

void i_will_run_until_the_heat_death_of_the_universe(void) {
    int i = 0;
    TEST_PRINTF("I will live forever\n");
    while (true) { i += 1; }
    TEST_PRINTF("%d\n", i);
}

// we need 'sleep()'
#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
#else
    #include <unistd.h>
#endif

void i_will_also_run_forever_but_in_a_different_way(void) {
    sleep(999999999);
}

void i_just_need_2_seconds(void) {
    sleep(1);
}


#define TEST_MA_UNDEFINE_SKIP_IMPLEMENTATION
#include "TEST_MA.h"

