#include <gtest/gtest.h>

#include "helper.hpp"
#include "meta/meta.hpp"
#include "test_lists.hpp"
#include "test_operations.hpp"

#include <type_traits>

TEST(GTest, Smoke) {}

TEST(List, Empty) {
  ASSERT_TRUE(meta::op::is_empty_v<L0>);
  ASSERT_FALSE(meta::op::is_empty_v<L1>);
  ASSERT_FALSE(meta::op::is_empty_v<L2>);
  ASSERT_FALSE(meta::op::is_empty_v<L3>);
  ASSERT_FALSE(meta::op::is_empty_v<L4>);
  ASSERT_FALSE(meta::op::is_empty_v<L5>);
}

TEST(List, Front) {
  ASSERT_SAME(bool, meta::op::front_t<L1>);
  ASSERT_SAME(float, meta::op::front_t<L2>);
  ASSERT_SAME(int, meta::op::front_t<L3>);
  ASSERT_SAME(bool, meta::op::front_t<L4>);
  ASSERT_SAME(L0, meta::op::front_t<L5>);
}

TEST(List, Back) {
  EXPECT_SAME(bool, meta::op::back_t<L1>);
  EXPECT_SAME(double, meta::op::back_t<L2>);
  EXPECT_SAME(void, meta::op::back_t<L3>);
  EXPECT_SAME(long, meta::op::back_t<L4>);
  EXPECT_SAME(L4, meta::op::back_t<L5>);
}

TEST(List, Size) {
  ASSERT_EQ(0, meta::op::size_v<L0>);
  ASSERT_EQ(1, meta::op::size_v<L1>);
  ASSERT_EQ(2, meta::op::size_v<L2>);
  ASSERT_EQ(3, meta::op::size_v<L3>);
  ASSERT_EQ(4, meta::op::size_v<L4>);
  ASSERT_EQ(5, meta::op::size_v<L5>);
}

TEST(List, At) {
  EXPECT_SAME(bool, CC(meta::op::at_t<L1, 0>));
  EXPECT_SAME(float, CC(meta::op::at_t<L2, 0>));
  EXPECT_SAME(int, CC(meta::op::at_t<L3, 0>));
  EXPECT_SAME(bool, CC(meta::op::at_t<L4, 0>));
  EXPECT_SAME(L0, CC(meta::op::at_t<L5, 0>));

  EXPECT_SAME(double, CC(meta::op::at_t<L2, 1>));
  EXPECT_SAME(CC(std::tuple<char, short>), CC(meta::op::at_t<L3, 1>));
  EXPECT_SAME(char, CC(meta::op::at_t<L4, 1>));
  EXPECT_SAME(L1, CC(meta::op::at_t<L5, 1>));

  EXPECT_SAME(void, CC(meta::op::at_t<L3, 2>));
  EXPECT_SAME(int, CC(meta::op::at_t<L4, 2>));
  EXPECT_SAME(L2, CC(meta::op::at_t<L5, 2>));

  EXPECT_SAME(long, CC(meta::op::at_t<L4, 3>));
  EXPECT_SAME(L3, CC(meta::op::at_t<L5, 3>));

  EXPECT_SAME(L4, CC(meta::op::at_t<L5, 4>));
}

TEST(List, Concat) {
  EXPECT_SAME(CC(meta::op::concat_t<L0, L0>), L0);
  EXPECT_SAME(CC(meta::op::concat_t<L0, L1>), L1);
  EXPECT_SAME(CC(meta::op::concat_t<L0, L2>), L2);
  EXPECT_SAME(CC(meta::op::concat_t<L0, L3>), L3);
  EXPECT_SAME(CC(meta::op::concat_t<L0, L4>), L4);
  EXPECT_SAME(CC(meta::op::concat_t<L0, L5>), L5);
  EXPECT_SAME(CC(meta::op::concat_t<L1, L0>), L1);
  EXPECT_SAME(CC(meta::op::concat_t<L2, L0>), L2);
  EXPECT_SAME(CC(meta::op::concat_t<L3, L0>), L3);
  EXPECT_SAME(CC(meta::op::concat_t<L4, L0>), L4);
  EXPECT_SAME(CC(meta::op::concat_t<L5, L0>), L5);
  EXPECT_SAME(CC(meta::op::concat_t<L1, L2>),
              CC(meta::data::list<bool, float, double>));
  EXPECT_SAME(CC(meta::op::concat_t<L2, L1>),
              CC(meta::data::list<float, double, bool>));
  EXPECT_SAME(
      CC(meta::op::concat_t<L2, L3>),
      CC(meta::data::list<float, double, int, std::tuple<char, short>, void>));
  EXPECT_SAME(
      CC(meta::op::concat_t<L3, L2>),
      CC(meta::data::list<int, std::tuple<char, short>, void, float, double>));
  EXPECT_SAME(CC(meta::op::concat_t<L5, L2>),
              CC(meta::data::list<L0, L1, L2, L3, L4, float, double>));
  EXPECT_SAME(CC(meta::op::concat_t<L2, L5>),
              CC(meta::data::list<float, double, L0, L1, L2, L3, L4>));
}

TEST(List, Reverse) {
  EXPECT_SAME(meta::op::reverse_t<L0>, L0);
  EXPECT_SAME(meta::op::reverse_t<L1>, L1);
  EXPECT_SAME(meta::op::reverse_t<L2>, CC(meta::data::list<double, float>));
  EXPECT_SAME(meta::op::reverse_t<L3>,
              CC(meta::data::list<void, std::tuple<char, short>, int>));
  EXPECT_SAME(meta::op::reverse_t<L4>,
              CC(meta::data::list<long, int, char, bool>));
  EXPECT_SAME(meta::op::reverse_t<L5>,
              CC(meta::data::list<L4, L3, L2, L1, L0>));
}

TEST(List, DoubleReverse) {
  EXPECT_SAME(meta::op::reverse_t<meta::op::reverse_t<L0>>, L0);
  EXPECT_SAME(meta::op::reverse_t<meta::op::reverse_t<L1>>, L1);
  EXPECT_SAME(meta::op::reverse_t<meta::op::reverse_t<L2>>, L2);
  EXPECT_SAME(meta::op::reverse_t<meta::op::reverse_t<L3>>, L3);
  EXPECT_SAME(meta::op::reverse_t<meta::op::reverse_t<L4>>, L4);
  EXPECT_SAME(meta::op::reverse_t<meta::op::reverse_t<L5>>, L5);
}

TEST(List, Foreach) {
  EXPECT_SAME(CC(meta::op::foreach_t<std::type_identity, L0>), L0);
  EXPECT_SAME(CC(meta::op::foreach_t<std::type_identity, L1>), L1);
  EXPECT_SAME(CC(meta::op::foreach_t<std::type_identity, L2>), L2);
  EXPECT_SAME(CC(meta::op::foreach_t<std::type_identity, L3>), L3);
  EXPECT_SAME(CC(meta::op::foreach_t<std::type_identity, L4>), L4);
  EXPECT_SAME(CC(meta::op::foreach_t<std::type_identity, L5>), L5);

  EXPECT_SAME(CC(meta::op::foreach_t<std::add_const, L0>), L0);
  EXPECT_SAME(CC(meta::op::foreach_t<std::add_const, L1>),
              meta::data::list<const bool>);
  EXPECT_SAME(CC(meta::op::foreach_t<std::add_const, L2>),
              CC(meta::data::list<const float, const double>));
  EXPECT_SAME(CC(meta::op::foreach_t<std::add_const, L3>),
              CC(meta::data::list<const int, const std::tuple<char, short>,
                                  const void>));
  EXPECT_SAME(
      CC(meta::op::foreach_t<std::add_const, L4>),
      CC(meta::data::list<const bool, const char, const int, const long>));

  EXPECT_SAME(
      CC(meta::op::foreach_t<std::add_const, L5>),
      CC(meta::data::list<const L0, const L1, const L2, const L3, const L4>));

  EXPECT_SAME(CC(meta::op::foreach_t<std::add_pointer, L0>), L0);
  EXPECT_SAME(CC(meta::op::foreach_t<std::add_pointer, L1>),
              meta::data::list<bool *>);
  EXPECT_SAME(CC(meta::op::foreach_t<std::add_pointer, L2>),
              CC(meta::data::list<float *, double *>));
  EXPECT_SAME(CC(meta::op::foreach_t<std::add_pointer, L3>),
              CC(meta::data::list<int *, std::tuple<char, short> *, void *>));
  EXPECT_SAME(CC(meta::op::foreach_t<std::add_pointer, L4>),
              CC(meta::data::list<bool *, char *, int *, long *>));
  EXPECT_SAME(CC(meta::op::foreach_t<std::add_pointer, L5>),
              CC(meta::data::list<L0 *, L1 *, L2 *, L3 *, L4 *>));

  EXPECT_SAME(CC(meta::op::foreach_t<test::add_ptr_to_const, L0>), L0);
  EXPECT_SAME(CC(meta::op::foreach_t<test::add_ptr_to_const, L1>),
              meta::data::list<bool const *>);
  EXPECT_SAME(CC(meta::op::foreach_t<test::add_ptr_to_const, L2>),
              CC(meta::data::list<float const *, double const *>));
  EXPECT_SAME(CC(meta::op::foreach_t<test::add_ptr_to_const, L3>),
              CC(meta::data::list<int const *, std::tuple<char, short> const *,
                                  void const *>));
  EXPECT_SAME(CC(meta::op::foreach_t<test::add_ptr_to_const, L4>),
              CC(meta::data::list<bool const *, char const *, int const *,
                                  long const *>));
  EXPECT_SAME(CC(meta::op::foreach_t<test::add_ptr_to_const, L5>),
              CC(meta::data::list<L0 const *, L1 const *, L2 const *,
                                  L3 const *, L4 const *>));

  EXPECT_SAME(CC(meta::op::foreach_t<test::make_const_ptr, L0>), L0);
  EXPECT_SAME(CC(meta::op::foreach_t<test::make_const_ptr, L1>),
              meta::data::list<bool *const>);
  EXPECT_SAME(CC(meta::op::foreach_t<test::make_const_ptr, L2>),
              CC(meta::data::list<float *const, double *const>));
  EXPECT_SAME(CC(meta::op::foreach_t<test::make_const_ptr, L3>),
              CC(meta::data::list<int *const, std::tuple<char, short> *const,
                                  void *const>));
  EXPECT_SAME(
      CC(meta::op::foreach_t<test::make_const_ptr, L4>),
      CC(meta::data::list<bool *const, char *const, int *const, long *const>));
  EXPECT_SAME(CC(meta::op::foreach_t<test::make_const_ptr, L5>),
              CC(meta::data::list<L0 *const, L1 *const, L2 *const, L3 *const,
                                  L4 *const>));

  EXPECT_SAME(CC(meta::op::foreach_t<test::make_double_ptr_to_const, L0>), L0);
  EXPECT_SAME(CC(meta::op::foreach_t<test::make_double_ptr_to_const, L1>),
              meta::data::list<bool const **>);
  EXPECT_SAME(CC(meta::op::foreach_t<test::make_double_ptr_to_const, L2>),
              CC(meta::data::list<float const **, double const **>));
  EXPECT_SAME(
      CC(meta::op::foreach_t<test::make_double_ptr_to_const, L3>),
      CC(meta::data::list<int const **, std::tuple<char, short> const **,
                          void const **>));
  EXPECT_SAME(CC(meta::op::foreach_t<test::make_double_ptr_to_const, L4>),
              CC(meta::data::list<bool const **, char const **, int const **,
                                  long const **>));
  EXPECT_SAME(CC(meta::op::foreach_t<test::make_double_ptr_to_const, L5>),
              CC(meta::data::list<L0 const **, L1 const **, L2 const **,
                                  L3 const **, L4 const **>));

  EXPECT_SAME(CC(meta::op::foreach_t<test::make_ref_to_ptr_to_const, L0>), L0);
  EXPECT_SAME(CC(meta::op::foreach_t<test::make_ref_to_ptr_to_const, L1>),
              meta::data::list<bool const *&>);
  EXPECT_SAME(CC(meta::op::foreach_t<test::make_ref_to_ptr_to_const, L2>),
              CC(meta::data::list<float const *&, double const *&>));
  EXPECT_SAME(
      CC(meta::op::foreach_t<test::make_ref_to_ptr_to_const, L3>),
      CC(meta::data::list<int const *&, std::tuple<char, short> const *&,
                          void const *&>));
  EXPECT_SAME(CC(meta::op::foreach_t<test::make_ref_to_ptr_to_const, L4>),
              CC(meta::data::list<bool const *&, char const *&, int const *&,
                                  long const *&>));
  EXPECT_SAME(CC(meta::op::foreach_t<test::make_ref_to_ptr_to_const, L5>),
              CC(meta::data::list<L0 const *&, L1 const *&, L2 const *&,
                                  L3 const *&, L4 const *&>));
}

TEST(List, Flatten) {
  EXPECT_SAME(meta::op::flatten_t<L0>, L0);
  EXPECT_SAME(meta::op::flatten_t<L1>, L1);
  EXPECT_SAME(meta::op::flatten_t<L2>, L2);
  EXPECT_SAME(meta::op::flatten_t<L3>, L3);
  EXPECT_SAME(meta::op::flatten_t<L4>, L4);
  EXPECT_SAME(
      meta::op::flatten_t<L5>,
      CC(meta::data::list<bool, float, double, int, std::tuple<char, short>,
                          void, bool, char, int, long>));

  EXPECT_SAME(meta::op::flatten_t<meta::data::list<L0>>, L0);
  EXPECT_SAME(meta::op::flatten_t<meta::data::list<L1>>, L1);
  EXPECT_SAME(meta::op::flatten_t<meta::data::list<L2>>, L2);
  EXPECT_SAME(meta::op::flatten_t<meta::data::list<L3>>, L3);
  EXPECT_SAME(meta::op::flatten_t<meta::data::list<L4>>, L4);
  EXPECT_SAME(meta::op::flatten_t<meta::data::list<L5>>, L5);

  EXPECT_SAME(CC(meta::op::flatten_t<meta::data::list<int, L0, float>>),
              CC(meta::data::list<int, float>));
  EXPECT_SAME(CC(meta::op::flatten_t<meta::data::list<int, L1, float>>),
              CC(meta::data::list<int, bool, float>));
  EXPECT_SAME(CC(meta::op::flatten_t<meta::data::list<int, L2, float>>),
              CC(meta::data::list<int, float, double, float>));
  EXPECT_SAME(
      CC(meta::op::flatten_t<meta::data::list<int, L3, float>>),
      CC(meta::data::list<int, int, std::tuple<char, short>, void, float>));
  EXPECT_SAME(CC(meta::op::flatten_t<meta::data::list<int, L4, float>>),
              CC(meta::data::list<int, bool, char, int, long, float>));
  EXPECT_SAME(CC(meta::op::flatten_t<meta::data::list<int, L5, float>>),
              CC(meta::data::list<int, L0, L1, L2, L3, L4, float>));

  EXPECT_SAME(CC(meta::op::flatten_t<meta::data::list<L0, float>>),
              CC(meta::data::list<float>));
  EXPECT_SAME(CC(meta::op::flatten_t<meta::data::list<L1, float>>),
              CC(meta::data::list<bool, float>));
  EXPECT_SAME(CC(meta::op::flatten_t<meta::data::list<L2, float>>),
              CC(meta::data::list<float, double, float>));
  EXPECT_SAME(CC(meta::op::flatten_t<meta::data::list<L3, float>>),
              CC(meta::data::list<int, std::tuple<char, short>, void, float>));
  EXPECT_SAME(CC(meta::op::flatten_t<meta::data::list<L4, float>>),
              CC(meta::data::list<bool, char, int, long, float>));
  EXPECT_SAME(CC(meta::op::flatten_t<meta::data::list<L5, float>>),
              CC(meta::data::list<L0, L1, L2, L3, L4, float>));

  EXPECT_SAME(CC(meta::op::flatten_t<meta::data::list<int, L0>>),
              CC(meta::data::list<int>));
  EXPECT_SAME(CC(meta::op::flatten_t<meta::data::list<int, L1>>),
              CC(meta::data::list<int, bool>));
  EXPECT_SAME(CC(meta::op::flatten_t<meta::data::list<int, L2>>),
              CC(meta::data::list<int, float, double>));
  EXPECT_SAME(CC(meta::op::flatten_t<meta::data::list<int, L3>>),
              CC(meta::data::list<int, int, std::tuple<char, short>, void>));
  EXPECT_SAME(CC(meta::op::flatten_t<meta::data::list<int, L4>>),
              CC(meta::data::list<int, bool, char, int, long>));
  EXPECT_SAME(CC(meta::op::flatten_t<meta::data::list<int, L5>>),
              CC(meta::data::list<int, L0, L1, L2, L3, L4>));
}
