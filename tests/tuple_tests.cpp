#include <gtest/gtest.h>

#include "helper.hpp"
#include "meta/tuple.hpp"
#include "test_lists.hpp"

using T0 = std::tuple<>;
using T1 = std::tuple<bool>;
using T2 = std::tuple<float, double>;
using T3 = std::tuple<int, std::tuple<char, short>, void *>;
using T4 = std::tuple<bool, char, int, long>;
using T5 = std::tuple<T0, T1, T2, T3, T4>;
using TupleOfLists = std::tuple<L0, L1, L2, L3, L4>;

TEST(Tuple, ListFromTuple) {
  EXPECT_SAME(meta::op::list_from_tuple_t<T0>, L0);
  EXPECT_SAME(meta::op::list_from_tuple_t<T1>, L1);
  EXPECT_SAME(meta::op::list_from_tuple_t<T2>, L2);
  EXPECT_SAME(meta::op::list_from_tuple_t<T3>,
              CC(meta::data::list<int, std::tuple<char, short>, void *>));
  EXPECT_SAME(meta::op::list_from_tuple_t<T4>, L4);
  EXPECT_SAME(meta::op::list_from_tuple_t<TupleOfLists>, L5);
}

TEST(Tuple, TupleFromList) {
  EXPECT_SAME(meta::op::tuple_from_list_t<L0>, T0);
  EXPECT_SAME(meta::op::tuple_from_list_t<L1>, T1);
  EXPECT_SAME(meta::op::tuple_from_list_t<L2>, T2);
  EXPECT_SAME(meta::op::tuple_from_list_t<L4>, T4);
  EXPECT_SAME(meta::op::tuple_from_list_t<L5>, TupleOfLists);
}

TEST(Tuple, Size) {
  ASSERT_EQ(0, meta::op::size_v<T0>);
  ASSERT_EQ(1, meta::op::size_v<T1>);
  ASSERT_EQ(2, meta::op::size_v<T2>);
  ASSERT_EQ(3, meta::op::size_v<T3>);
  ASSERT_EQ(4, meta::op::size_v<T4>);
  ASSERT_EQ(5, meta::op::size_v<T5>);
}

TEST(Operations, ConcatTuplesType) {
  EXPECT_SAME(CC(meta::op::concat_t<T0, T0>), T0);
  EXPECT_SAME(CC(meta::op::concat_t<T0, T1>), T1);
  EXPECT_SAME(CC(meta::op::concat_t<T0, T2>), T2);
  EXPECT_SAME(CC(meta::op::concat_t<T0, T3>), T3);
  EXPECT_SAME(CC(meta::op::concat_t<T0, T4>), T4);
  EXPECT_SAME(CC(meta::op::concat_t<T0, T5>), T5);

  EXPECT_SAME(CC(meta::op::concat_t<T1, T0>), T1);
  EXPECT_SAME(CC(meta::op::concat_t<T2, T0>), T2);
  EXPECT_SAME(CC(meta::op::concat_t<T3, T0>), T3);
  EXPECT_SAME(CC(meta::op::concat_t<T4, T0>), T4);
  EXPECT_SAME(CC(meta::op::concat_t<T5, T0>), T5);

  EXPECT_SAME(CC(meta::op::concat_t<T1, T1>), CC(std::tuple<bool, bool>));
  EXPECT_SAME(CC(meta::op::concat_t<T1, T2>),
              CC(std::tuple<bool, float, double>));
  EXPECT_SAME(CC(meta::op::concat_t<T1, T3>),
              CC(std::tuple<bool, int, std::tuple<char, short>, void *>));
  EXPECT_SAME(CC(meta::op::concat_t<T1, T4>),
              CC(std::tuple<bool, bool, char, int, long>));
  EXPECT_SAME(CC(meta::op::concat_t<T1, T5>),
              CC(std::tuple<bool, T0, T1, T2, T3, T4>));

  EXPECT_SAME(CC(meta::op::concat_t<T2, T1>),
              CC(std::tuple<float, double, bool>));
  EXPECT_SAME(CC(meta::op::concat_t<T3, T1>),
              CC(std::tuple<int, std::tuple<char, short>, void *, bool>));
  EXPECT_SAME(CC(meta::op::concat_t<T4, T1>),
              CC(std::tuple<bool, char, int, long, bool>));
  EXPECT_SAME(CC(meta::op::concat_t<T5, T1>),
              CC(std::tuple<T0, T1, T2, T3, T4, bool>));

  EXPECT_SAME(CC(meta::op::concat_t<T2, T2>),
              CC(std::tuple<float, double, float, double>));
  EXPECT_SAME(
      CC(meta::op::concat_t<T2, T3>),
      CC(std::tuple<float, double, int, std::tuple<char, short>, void *>));
  EXPECT_SAME(CC(meta::op::concat_t<T2, T4>),
              CC(std::tuple<float, double, bool, char, int, long>));
  EXPECT_SAME(CC(meta::op::concat_t<T2, T5>),
              CC(std::tuple<float, double, T0, T1, T2, T3, T4>));

  EXPECT_SAME(
      CC(meta::op::concat_t<T3, T2>),
      CC(std::tuple<int, std::tuple<char, short>, void *, float, double>));
  EXPECT_SAME(CC(meta::op::concat_t<T4, T2>),
              CC(std::tuple<bool, char, int, long, float, double>));
  EXPECT_SAME(CC(meta::op::concat_t<T5, T2>),
              CC(std::tuple<T0, T1, T2, T3, T4, float, double>));

  EXPECT_SAME(CC(meta::op::concat_t<T3, T3>),
              CC(std::tuple<int, std::tuple<char, short>, void *, int,
                            std::tuple<char, short>, void *>));
  EXPECT_SAME(CC(meta::op::concat_t<T3, T4>),
              CC(std::tuple<int, std::tuple<char, short>, void *, bool, char,
                            int, long>));
  EXPECT_SAME(
      CC(meta::op::concat_t<T3, T5>),
      CC(std::tuple<int, std::tuple<char, short>, void *, T0, T1, T2, T3, T4>));

  EXPECT_SAME(CC(meta::op::concat_t<T4, T3>),
              CC(std::tuple<bool, char, int, long, int, std::tuple<char, short>,
                            void *>));
  EXPECT_SAME(
      CC(meta::op::concat_t<T5, T3>),
      CC(std::tuple<T0, T1, T2, T3, T4, int, std::tuple<char, short>, void *>));

  EXPECT_SAME(CC(meta::op::concat_t<T4, T4>),
              CC(std::tuple<bool, char, int, long, bool, char, int, long>));
  EXPECT_SAME(CC(meta::op::concat_t<T4, T5>),
              CC(std::tuple<bool, char, int, long, T0, T1, T2, T3, T4>));

  EXPECT_SAME(CC(meta::op::concat_t<T5, T4>),
              CC(std::tuple<T0, T1, T2, T3, T4, bool, char, int, long>));

  EXPECT_SAME(CC(meta::op::concat_t<T5, T5>),
              CC(std::tuple<T0, T1, T2, T3, T4, T0, T1, T2, T3, T4>));
}

TEST(Tuple, Flatten) {
  EXPECT_SAME(meta::op::flatten_t<T0>, T0);
  EXPECT_SAME(meta::op::flatten_t<T1>, T1);
  EXPECT_SAME(meta::op::flatten_t<T2>, T2);
  EXPECT_SAME(meta::op::flatten_t<T4>, T4);
  EXPECT_SAME(meta::op::flatten_t<T5>,
              CC(std::tuple<bool, float, double, int, std::tuple<char, short>,
                            void *, bool, char, int, long>));

  EXPECT_SAME(meta::op::flatten_t<std::tuple<T0>>, T0);
  EXPECT_SAME(meta::op::flatten_t<std::tuple<T1>>, T1);
  EXPECT_SAME(meta::op::flatten_t<std::tuple<T2>>, T2);
  EXPECT_SAME(meta::op::flatten_t<std::tuple<T3>>, T3);
  EXPECT_SAME(meta::op::flatten_t<std::tuple<T4>>, T4);
  EXPECT_SAME(meta::op::flatten_t<std::tuple<T5>>, T5);

  EXPECT_SAME(CC(meta::op::flatten_t<std::tuple<int, T0, float>>),
              CC(std::tuple<int, float>));
  EXPECT_SAME(CC(meta::op::flatten_t<std::tuple<int, T1, float>>),
              CC(std::tuple<int, bool, float>));
  EXPECT_SAME(CC(meta::op::flatten_t<std::tuple<int, T2, float>>),
              CC(std::tuple<int, float, double, float>));
  EXPECT_SAME(CC(meta::op::flatten_t<std::tuple<int, T3, float>>),
              CC(std::tuple<int, int, std::tuple<char, short>, void *, float>));
  EXPECT_SAME(CC(meta::op::flatten_t<std::tuple<int, T4, float>>),
              CC(std::tuple<int, bool, char, int, long, float>));
  EXPECT_SAME(CC(meta::op::flatten_t<std::tuple<int, T5, float>>),
              CC(std::tuple<int, T0, T1, T2, T3, T4, float>));

  EXPECT_SAME(CC(meta::op::flatten_t<std::tuple<T0, float>>),
              CC(std::tuple<float>));
  EXPECT_SAME(CC(meta::op::flatten_t<std::tuple<T1, float>>),
              CC(std::tuple<bool, float>));
  EXPECT_SAME(CC(meta::op::flatten_t<std::tuple<T2, float>>),
              CC(std::tuple<float, double, float>));
  EXPECT_SAME(CC(meta::op::flatten_t<std::tuple<T3, float>>),
              CC(std::tuple<int, std::tuple<char, short>, void *, float>));
  EXPECT_SAME(CC(meta::op::flatten_t<std::tuple<T4, float>>),
              CC(std::tuple<bool, char, int, long, float>));
  EXPECT_SAME(CC(meta::op::flatten_t<std::tuple<T5, float>>),
              CC(std::tuple<T0, T1, T2, T3, T4, float>));

  EXPECT_SAME(CC(meta::op::flatten_t<std::tuple<int, T0>>),
              CC(std::tuple<int>));
  EXPECT_SAME(CC(meta::op::flatten_t<std::tuple<int, T1>>),
              CC(std::tuple<int, bool>));
  EXPECT_SAME(CC(meta::op::flatten_t<std::tuple<int, T2>>),
              CC(std::tuple<int, float, double>));
  EXPECT_SAME(CC(meta::op::flatten_t<std::tuple<int, T3>>),
              CC(std::tuple<int, int, std::tuple<char, short>, void *>));
  EXPECT_SAME(CC(meta::op::flatten_t<std::tuple<int, T4>>),
              CC(std::tuple<int, bool, char, int, long>));
  EXPECT_SAME(CC(meta::op::flatten_t<std::tuple<int, T5>>),
              CC(std::tuple<int, T0, T1, T2, T3, T4>));
  EXPECT_SAME(meta::op::flatten_t<TupleOfLists>, TupleOfLists);
}

TEST(Tuple, ConcatTuples) {
  std::tuple<int, char> t1{1, 'a'};
  std::tuple<float, double, void *> t2{3.0f, 3.14, nullptr};
  std::tuple<long, short> t3{long{1}, short{2}};
  std::tuple<int, char, float, double, void *, long, short> ct =
      std::make_tuple(1, 'a', 3.0f, 3.14, (void *)nullptr, long{1}, short{2});

  ASSERT_SAME(decltype(meta::op::concat_tuples(t1, t2, t3)),
              CC(std::tuple<int, char, float, double, void *, long, short>));
  ASSERT_EQ(meta::op::concat_tuples(t1, t2, t3), ct);
  ASSERT_EQ(meta::op::concat_tuples(t1, t2),
            std::make_tuple(1, 'a', 3.0f, 3.14, nullptr));
  ASSERT_EQ(std::tuple_cat(t1, t2, t3), ct);
}
