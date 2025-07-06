#include "config.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

#include <cmocka.h>
#include <cmocka_private.h>

static void test_assert_false_fail(void **state)
{
    int x = 10;

    (void)state; /* unused */
    assert_false(x == 10);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_assert_false_fail),
    };

    int result = cmocka_run_group_tests(tests, NULL, NULL);

    // For failing tests, we expect all tests to fail, so return 0 if that's the
    // case
    int expected_failures = sizeof(tests) / sizeof(struct CMUnitTest);
    return (result == expected_failures) ? 0 : 1;
}
