#include "config.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>
#include <cmocka_private.h>

static void test_assert_int_in_range_fail_1(void **state)
{
    (void)state; /* unused */
    assert_int_in_range(0, 1, 2);
}

static void test_assert_int_in_range_fail_2(void **state)
{
    (void)state; /* unused */
    assert_int_in_range(2, -1, 1);
}

static void test_assert_int_in_range_fail_3(void **state)
{
    (void)state; /* unused */
    assert_int_in_range(0, 1, INTMAX_MAX);
}

static void test_assert_int_in_range_fail_4(void **state)
{
    (void)state; /* unused */
    assert_int_in_range(0, INTMAX_MIN, -1);
}

static void test_assert_int_not_in_range_fail_1(void **state)
{
    (void)state; /* unused */
    assert_int_not_in_range(0, INTMAX_MIN, INTMAX_MAX);
}

static void test_assert_uint_not_in_range_fail_1(void **state)
{
    (void)state; /* unused */
    assert_uint_not_in_range(1, 0, UINTMAX_MAX);
}

static void test_assert_float_in_range_fail_1(void **state)
{
    (void)state; /* unused */
    assert_float_in_range(0.001, 0.002, 2.0, 0.0001);
}

static void test_assert_float_in_range_fail_2(void **state)
{
    (void)state; /* unused */
    assert_float_in_range(2.001, 0.002, 2.0, 0.0001);
}

static void test_assert_float_in_range_fail_3(void **state)
{
    (void)state; /* unused */
    assert_float_in_range(-4.04, 0.0, -5.21, 0.1);
}

static void test_assert_float_not_in_range_fail_1(void **state)
{
    (void)state; /* unused */
    assert_float_not_in_range(0.0001, 0.00001, 0.1, 0.001);
}

static void test_assert_float_not_in_range_fail_2(void **state)
{
    (void)state; /* unused */
    assert_float_not_in_range(0.1, 0.00001, 0.1, 0.001);
}

static void test_assert_float_not_in_range_fail_3(void **state)
{
    (void)state; /* unused */
    assert_float_not_in_range(0.1, 0.0, 0.2, 0.01);
}

int main(void) {
    const struct CMUnitTest range_fail_tests[] = {
        cmocka_unit_test(test_assert_int_in_range_fail_1),
        cmocka_unit_test(test_assert_int_in_range_fail_2),
        cmocka_unit_test(test_assert_int_in_range_fail_3),
        cmocka_unit_test(test_assert_int_in_range_fail_4),
        cmocka_unit_test(test_assert_int_not_in_range_fail_1),
        cmocka_unit_test(test_assert_uint_not_in_range_fail_1),
        cmocka_unit_test(test_assert_float_in_range_fail_1),
        cmocka_unit_test(test_assert_float_in_range_fail_2),
        cmocka_unit_test(test_assert_float_in_range_fail_3),
        cmocka_unit_test(test_assert_float_not_in_range_fail_1),
        cmocka_unit_test(test_assert_float_not_in_range_fail_2),
        cmocka_unit_test(test_assert_float_not_in_range_fail_3),
    };

    int result = cmocka_run_group_tests(range_fail_tests, NULL, NULL);

    // For failing tests, we expect all tests to fail, so return 0 if that's the
    // case
    int expected_failures = sizeof(range_fail_tests) /
                            sizeof(struct CMUnitTest);
    return (result == expected_failures) ? 0 : 1;
}
