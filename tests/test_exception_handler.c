#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>

#include <signal.h>

static void test_segfault_recovery(void **state)
{
    (void)state; /* unused */

    /* Raise segmentation fault */
    raise(SIGSEGV);
}

static void test_segfault_recovery1(void **state)
{
    test_segfault_recovery(state);
}

static void test_segfault_recovery2(void **state)
{
    test_segfault_recovery(state);
}

static void test_segfault_recovery3(void **state)
{
    test_segfault_recovery(state);
}

int main(void) {
    const struct CMUnitTest exception_tests[] = {
        cmocka_unit_test(test_segfault_recovery1),
        cmocka_unit_test(test_segfault_recovery2),
        cmocka_unit_test(test_segfault_recovery3),
    };

    int result = cmocka_run_group_tests(exception_tests, NULL, NULL);

    // For this test, we expect 1 failure out of 3 tests (testing exception
    // handling)
    int expected_failures = 1;
    return (result == expected_failures) ? 0 : 1;
}
