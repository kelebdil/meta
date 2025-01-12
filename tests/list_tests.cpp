#include <gtest/gtest.h>

#include "helper.hpp"
#include "meta/meta.hpp"

#include <type_traits>

TEST(GTest, Smoke) {}

using L0 = meta::data::list<>;
using L1 = meta::data::list<bool>;
using L2 = meta::data::list<float, double>;
using L3 = meta::data::list<int, char, void>;
using L4 = meta::data::list<bool, char, int, long>;

TEST(List, Empty) {
  ASSERT_TRUE(meta::op::is_empty_v<L0>);
  ASSERT_FALSE(meta::op::is_empty_v<L1>);
  ASSERT_FALSE(meta::op::is_empty_v<L2>);
  ASSERT_FALSE(meta::op::is_empty_v<L3>);
  ASSERT_FALSE(meta::op::is_empty_v<L4>);
}

TEST(List, Front) {
  ASSERT_SAME(bool, meta::op::front_t<L1>);
  ASSERT_SAME(float, meta::op::front_t<L2>);
  ASSERT_SAME(int, meta::op::front_t<L3>);
  ASSERT_SAME(bool, meta::op::front_t<L4>);
}

TEST(List, Back) {
  EXPECT_SAME(bool, meta::op::back_t<L1>);
  EXPECT_SAME(double, meta::op::back_t<L2>);
  EXPECT_SAME(void, meta::op::back_t<L3>);
  EXPECT_SAME(long, meta::op::back_t<L4>);
}

TEST(List, Size) {
  ASSERT_EQ(0, meta::op::size_v<L0>);
  ASSERT_EQ(1, meta::op::size_v<L1>);
  ASSERT_EQ(2, meta::op::size_v<L2>);
  ASSERT_EQ(3, meta::op::size_v<L3>);
  ASSERT_EQ(4, meta::op::size_v<L4>);
}

TEST(List, At) {
  EXPECT_SAME(bool, CC(meta::op::at_t<L1, 0>));
  EXPECT_SAME(float, CC(meta::op::at_t<L2, 0>));
  EXPECT_SAME(int, CC(meta::op::at_t<L3, 0>));
  EXPECT_SAME(bool, CC(meta::op::at_t<L4, 0>));

  EXPECT_SAME(double, CC(meta::op::at_t<L2, 1>));
  EXPECT_SAME(char, CC(meta::op::at_t<L3, 1>));
  EXPECT_SAME(char, CC(meta::op::at_t<L4, 1>));

  EXPECT_SAME(void, CC(meta::op::at_t<L3, 2>));
  EXPECT_SAME(int, CC(meta::op::at_t<L4, 2>));

  EXPECT_SAME(long, CC(meta::op::at_t<L4, 3>));
}

TEST(List, Concat) {
  EXPECT_SAME(CC(meta::op::concat_t<L0, L0>), L0);
  EXPECT_SAME(CC(meta::op::concat_t<L0, L1>), L1);
  EXPECT_SAME(CC(meta::op::concat_t<L0, L2>), L2);
  EXPECT_SAME(CC(meta::op::concat_t<L0, L3>), L3);
  EXPECT_SAME(CC(meta::op::concat_t<L1, L0>), L1);
  EXPECT_SAME(CC(meta::op::concat_t<L2, L0>), L2);
  EXPECT_SAME(CC(meta::op::concat_t<L3, L0>), L3);
  EXPECT_SAME(CC(meta::op::concat_t<L1, L2>),
              CC(meta::data::list<bool, float, double>));
  EXPECT_SAME(CC(meta::op::concat_t<L2, L1>),
              CC(meta::data::list<float, double, bool>));
  EXPECT_SAME(CC(meta::op::concat_t<L2, L3>),
              CC(meta::data::list<float, double, int, char, void>));
  EXPECT_SAME(CC(meta::op::concat_t<L3, L2>),
              CC(meta::data::list<int, char, void, float, double>));
}

TEST(List, Reverse) {
  EXPECT_SAME(meta::op::reverse_t<L0>, L0);
  EXPECT_SAME(meta::op::reverse_t<L1>, L1);
  EXPECT_SAME(meta::op::reverse_t<L2>, CC(meta::data::list<double, float>));
  EXPECT_SAME(meta::op::reverse_t<L3>, CC(meta::data::list<void, char, int>));
  EXPECT_SAME(meta::op::reverse_t<L4>,
              CC(meta::data::list<long, int, char, bool>));
}

TEST(List, DoubleReverse) {
  EXPECT_SAME(meta::op::reverse_t<meta::op::reverse_t<L0>>, L0);
  EXPECT_SAME(meta::op::reverse_t<meta::op::reverse_t<L1>>, L1);
  EXPECT_SAME(meta::op::reverse_t<meta::op::reverse_t<L2>>, L2);
  EXPECT_SAME(meta::op::reverse_t<meta::op::reverse_t<L3>>, L3);
  EXPECT_SAME(meta::op::reverse_t<meta::op::reverse_t<L4>>, L4);
}

TEST(Apply, Test) {
  EXPECT_SAME(CC(meta::op::apply_t<std::type_identity, int>), int);
  EXPECT_SAME(CC(meta::op::apply_t<std::add_const, int>), const int);
}

namespace test {

template <typename T>
using add_ptr_to_const =
    meta::op::compose<std::add_pointer, std::add_const>::op<T>;

template <typename T>
using make_const_ptr =
    meta::op::compose<std::add_const, std::add_pointer>::op<T>;

template <typename T>
using make_double_ptr_to_const =
    meta::op::compose<std::add_pointer, std::add_pointer,
                      std::add_const>::op<T>;

template <typename T>
using make_ref_to_ptr_to_const =
    meta::op::compose<std::add_lvalue_reference, std::add_pointer,
                      std::add_const>::op<T>;

} // namespace test

TEST(Meta, ListForeach) {
  EXPECT_SAME(CC(meta::op::foreach_t<std::type_identity, L0>), L0);
  EXPECT_SAME(CC(meta::op::foreach_t<std::type_identity, L1>), L1);
  EXPECT_SAME(CC(meta::op::foreach_t<std::type_identity, L2>), L2);
  EXPECT_SAME(CC(meta::op::foreach_t<std::type_identity, L3>), L3);
  EXPECT_SAME(CC(meta::op::foreach_t<std::type_identity, L4>), L4);

  EXPECT_SAME(CC(meta::op::foreach_t<std::add_const, L0>), L0);
  EXPECT_SAME(CC(meta::op::foreach_t<std::add_const, L1>),
              meta::data::list<const bool>);
  EXPECT_SAME(CC(meta::op::foreach_t<std::add_const, L2>),
              CC(meta::data::list<const float, const double>));
  EXPECT_SAME(CC(meta::op::foreach_t<std::add_const, L3>),
              CC(meta::data::list<const int, const char, const void>));
  EXPECT_SAME(
      CC(meta::op::foreach_t<std::add_const, L4>),
      CC(meta::data::list<const bool, const char, const int, const long>));

  EXPECT_SAME(CC(meta::op::foreach_t<std::add_pointer, L0>), L0);
  EXPECT_SAME(CC(meta::op::foreach_t<std::add_pointer, L1>),
              meta::data::list<bool *>);
  EXPECT_SAME(CC(meta::op::foreach_t<std::add_pointer, L2>),
              CC(meta::data::list<float *, double *>));
  EXPECT_SAME(CC(meta::op::foreach_t<std::add_pointer, L3>),
              CC(meta::data::list<int *, char *, void *>));
  EXPECT_SAME(CC(meta::op::foreach_t<std::add_pointer, L4>),
              CC(meta::data::list<bool *, char *, int *, long *>));

  EXPECT_SAME(CC(meta::op::foreach_t<test::add_ptr_to_const, L0>), L0);
  EXPECT_SAME(CC(meta::op::foreach_t<test::add_ptr_to_const, L1>),
              meta::data::list<bool const *>);
  EXPECT_SAME(CC(meta::op::foreach_t<test::add_ptr_to_const, L2>),
              CC(meta::data::list<float const *, double const *>));
  EXPECT_SAME(CC(meta::op::foreach_t<test::add_ptr_to_const, L3>),
              CC(meta::data::list<int const *, char const *, void const *>));
  EXPECT_SAME(CC(meta::op::foreach_t<test::add_ptr_to_const, L4>),
              CC(meta::data::list<bool const *, char const *, int const *,
                                  long const *>));

  EXPECT_SAME(CC(meta::op::foreach_t<test::make_const_ptr, L0>), L0);
  EXPECT_SAME(CC(meta::op::foreach_t<test::make_const_ptr, L1>),
              meta::data::list<bool *const>);
  EXPECT_SAME(CC(meta::op::foreach_t<test::make_const_ptr, L2>),
              CC(meta::data::list<float *const, double *const>));
  EXPECT_SAME(CC(meta::op::foreach_t<test::make_const_ptr, L3>),
              CC(meta::data::list<int *const, char *const, void *const>));
  EXPECT_SAME(
      CC(meta::op::foreach_t<test::make_const_ptr, L4>),
      CC(meta::data::list<bool *const, char *const, int *const, long *const>));

  EXPECT_SAME(CC(meta::op::foreach_t<test::make_double_ptr_to_const, L0>), L0);
  EXPECT_SAME(CC(meta::op::foreach_t<test::make_double_ptr_to_const, L1>),
              meta::data::list<bool const **>);
  EXPECT_SAME(CC(meta::op::foreach_t<test::make_double_ptr_to_const, L2>),
              CC(meta::data::list<float const **, double const **>));
  EXPECT_SAME(CC(meta::op::foreach_t<test::make_double_ptr_to_const, L3>),
              CC(meta::data::list<int const **, char const **, void const **>));
  EXPECT_SAME(CC(meta::op::foreach_t<test::make_double_ptr_to_const, L4>),
              CC(meta::data::list<bool const **, char const **, int const **,
                                  long const **>));

  EXPECT_SAME(CC(meta::op::foreach_t<test::make_ref_to_ptr_to_const, L0>), L0);
  EXPECT_SAME(CC(meta::op::foreach_t<test::make_ref_to_ptr_to_const, L1>),
              meta::data::list<bool const *&>);
  EXPECT_SAME(CC(meta::op::foreach_t<test::make_ref_to_ptr_to_const, L2>),
              CC(meta::data::list<float const *&, double const *&>));
  EXPECT_SAME(CC(meta::op::foreach_t<test::make_ref_to_ptr_to_const, L3>),
              CC(meta::data::list<int const *&, char const *&, void const *&>));
  EXPECT_SAME(CC(meta::op::foreach_t<test::make_ref_to_ptr_to_const, L4>),
              CC(meta::data::list<bool const *&, char const *&, int const *&,
                                  long const *&>));
}
