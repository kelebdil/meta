#include <gtest/gtest.h>

#include "helper.hpp"
#include "meta/meta.hpp"
#include "test_lists.hpp"
#include "test_operations.hpp"

#include <type_traits>

TEST(Operations, Apply) {
  EXPECT_SAME(CC(meta::op::apply_t<std::type_identity, int>), int);
  EXPECT_SAME(CC(meta::op::apply_t<std::add_const, int>), const int);
}

TEST(Operations, Compose) {
  EXPECT_SAME(CC(meta::op::apply_t<test::add_ptr_to_const, int>), int const *);
  EXPECT_SAME(CC(meta::op::apply_t<test::make_const_ptr, double>),
              double *const);
  EXPECT_SAME(CC(meta::op::apply_t<test::make_double_ptr_to_const, void>),
              void const **);
  EXPECT_SAME(CC(meta::op::apply_t<test::make_ref_to_ptr_to_const, bool>),
              bool const *&);

  EXPECT_SAME(CC(meta::op::apply_t<test::add_ptr_to_const, L1>), L1 const *);
  EXPECT_SAME(CC(meta::op::apply_t<test::make_const_ptr, L2>), L2 *const);
  EXPECT_SAME(CC(meta::op::apply_t<test::make_double_ptr_to_const, L3>),
              L3 const **);
  EXPECT_SAME(CC(meta::op::apply_t<test::make_ref_to_ptr_to_const, L4>),
              L4 const *&);
}

TEST(Operations, Accumulate) {
  EXPECT_SAME(
      CC(meta::op::accumulate_t<L0, meta::op::concat, L5>),
      CC(meta::data::list<bool, float, double, int, std::tuple<char, short>,
                          void, bool, char, int, long>));
  EXPECT_SAME(CC(meta::op::accumulate_t<L0, meta::op::concat, L5>),
              meta::op::flatten_t<L5>);
}

