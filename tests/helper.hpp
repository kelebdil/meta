#pragma once

#include <gtest/gtest.h>

#include "demangle.hpp"

#include <type_traits>

template <typename T1, typename T2>
testing::AssertionResult types_same(const char *l_expr, const char *r_expr) {
  using test::utils::TypeName;
  if (std::is_same_v<T1, T2>)
    return testing::AssertionSuccess();
  return testing::AssertionFailure()
         << "Types " << l_expr << " and " << r_expr << " does not match "
         << " (" << TypeName<T1>() << " != " << TypeName<T2>() << ")";
}

#define CONCAT2(...) __VA_ARGS__
#define CC(...) CONCAT2(__VA_ARGS__)
#define UNPACK(...) __VA_ARGS__
#define ASSERT_SAME(a, b)                                                      \
  GTEST_ASSERT_((types_same<UNPACK(a), UNPACK(b)>(#a, #b)),                    \
                GTEST_FATAL_FAILURE_)
#define EXPECT_SAME(a, b)                                                      \
  GTEST_ASSERT_((types_same<UNPACK(a), UNPACK(b)>(#a, #b)),                    \
                GTEST_NONFATAL_FAILURE_)
