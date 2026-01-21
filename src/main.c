
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


int main(void) {
    printf("Whats TEST_MA you ask?\n");

    ADD_TEST(one_plus_one, .custom_name = "basic test");
    ADD_TEST(size_of_works);
    ADD_TEST(my_strlen_behaves_as_expected);
    ADD_TEST(ints_are_64_bit_why_would_you_think_otherwise);
    // this function will crash, and the test handler will handle it.
    ADD_TEST(dont_run_this_test_it_will_kill_you);

    ADD_TEST(dont_run_this_test_it_will_kill_you, .custom_name = "wait, dont run this one.", .dont_run = true);


    int num_tests_failed = RUN_TESTS();
    return num_tests_failed;
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



#define TEST_MA_UNDEFINE_SKIP_IMPLEMENTATION
#include "TEST_MA.h"

