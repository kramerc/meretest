/*
 * SimpleTest v0.0.0 - test and assertion macros
 *
 * Copyright (c) 2013 Kramer Campbell
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef SIMPLETEST_H
#define SIMPLETEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Assertions macros
 */

typedef enum {
  NONE,
  ASSERT_FAIL,
  ASSERT_EQUAL_FAIL,
  ASSERT_NULL_FAIL
} test_assertion_error_t;

#define ASSERT(test) \
  if (!(test)) { \
    *assertion_error = ASSERT_FAIL; \
    fprintf(stderr, "%s: Expected %s to be true (%s:%d)\n", \
      __func__, #test, __FILE__, __LINE__); \
    return; \
  }

#define ASSERT_EQUAL(exp, act) \
  if (exp != act) { \
    *assertion_error = ASSERT_EQUAL_FAIL; \
    fprintf(stderr, "%s: Expected %s to equal %s (%s:%d)\n", \
      __func__, #exp, #act, __FILE__, __LINE__); \
    return; \
  }

#define ASSERT_NULL(test) \
  if (variable != NULL) { \
    *assertion_error = ASSERT_NULL_FAIL; \
    fprintf(stderr, "%s: Expected %s to be null (%s:%d)\n", \
      __func__, #variable, __FILE__, __LINE__); \
    return; \
  }

/*
 * Test macros
 */

typedef void (*test_function_t)(test_assertion_error_t *);

#define TEST(name) \
  void name(test_assertion_error_t *assertion_error)

#define TEST_MAIN(...) \
  int main(int argc, char **argv) { \
    size_t i = 0; \
    int count = sizeof((test_function_t[]) {__VA_ARGS__}) / \
      sizeof(test_function_t); \
    \
    /* Parse __VA_ARGS__ string */ \
    char va_args_str[] = #__VA_ARGS__; \
    char *test_function_names[count]; \
    char *token = strtok(va_args_str, ", "); \
    while (token != NULL) { \
      test_function_names[i] = \
        (char *) malloc(sizeof(char) * (strlen(token) + 1)); \
      strcpy(test_function_names[i++], token); \
      token = strtok(NULL, ", "); \
    } \
    \
    test_function_t test_functions[] = {__VA_ARGS__}; \
    test_assertion_error_t assertion_error = NONE; \
    int failed_tests = 0; \
    for (i = 0; i < count; i++) { \
      test_functions[i](&assertion_error); \
      printf("Test %s ", test_function_names[i]); \
      if (assertion_error != NONE) { \
        printf("failed!\n"); \
        failed_tests++; \
        assertion_error = NONE; \
      } else { \
        printf("passed!\n"); \
      } \
      free(test_function_names[i]); \
    } \
    printf("Results: %d out of %d %s passed.\n", \
      count - failed_tests, count, ((count > 1) ? "tests" : "test")); \
    return failed_tests; \
  }

#endif
