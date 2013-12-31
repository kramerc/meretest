#include <meretest.h>

/*
 * In order to test for intended assertion failures, wrapper functions are
 * needed as the macros add a return statement that are intended to halt the
 * test function from continuing.
 */

#define fprintf(...) // Silence the error messages caused by these failures
static void assert_fail_wrapper(test_assertion_error_t *assertion_error) {
  ASSERT(0)
}

static void assert_equal_fail_wrapper(test_assertion_error_t *assertion_error) {
  ASSERT_EQUAL(1, 0)
}

static void assert_null_fail_wrapper(test_assertion_error_t *assertion_error) {
  char test = 't';
  ASSERT_NULL(&test)
}
#undef fprintf // Unsilence error messages

TEST(truthy_assertion) {
  ASSERT(1 == 1)
}

TEST(truthy_assertion_fail) {
  test_assertion_error_t assertion_error_test = NONE;
  assert_fail_wrapper(&assertion_error_test);
  ASSERT(assertion_error_test == ASSERT_FAIL)
}

TEST(equal_assertion) {
  ASSERT_EQUAL(1, 1)
}

TEST(equal_assertion_fail) {
  test_assertion_error_t assertion_error_test = NONE;
  assert_equal_fail_wrapper(&assertion_error_test);
  ASSERT(assertion_error_test == ASSERT_EQUAL_FAIL)
}

TEST(null_assertion) {
  ASSERT_NULL(NULL)
}

TEST(null_assertion_fail) {
  test_assertion_error_t assertion_error_test = NONE;
  assert_null_fail_wrapper(&assertion_error_test);
  ASSERT(assertion_error_test == ASSERT_NULL_FAIL)
}

TEST_MAIN(
  truthy_assertion,
  truthy_assertion_fail,
  equal_assertion,
  equal_assertion_fail,
  null_assertion,
  null_assertion_fail
)
