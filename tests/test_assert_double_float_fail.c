#include "config.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>
#include <cmocka_private.h>

static void test_assert_double_equal_fail(void **state)
{
    (void)state; /* unused */
    assert_double_equal(0.5f, 1.f, 0.000001f);
}

static void test_assert_double_not_equal_fail(void **state)
{
    (void)state; /* unused */
    assert_double_not_equal(1.f, 1.f, 0.000001f);
}

static void test_assert_float_equal_fail(void **state)
{
    (void)state; /* unused */
    assert_float_equal(0.5f, 1.f, 0.000001f);
}

static void test_assert_float_not_equal_fail(void **state)
{
    (void)state; /* unused */
    assert_float_not_equal(1.f, 1.f, 0.000001f);
}

int main(void) {
    const struct CMUnitTest float_tests_fail[] = {
        cmocka_unit_test(test_assert_double_equal_fail),
        cmocka_unit_test(test_assert_double_not_equal_fail),
        cmocka_unit_test(test_assert_float_equal_fail),
        cmocka_unit_test(test_assert_float_not_equal_fail),
    };

    int result = cmocka_run_group_tests(float_tests_fail, NULL, NULL);

    // For failing tests, we expect all tests to fail, so return 0 if that's the
    // case
    int expected_failures = sizeof(float_tests_fail) /
                            sizeof(struct CMUnitTest);
    return (result == expected_failures) ? 0 : 1;
}
