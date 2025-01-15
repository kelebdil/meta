#pragma once

#include "meta/list.hpp"

#include <tuple>

namespace meta::op {

template <typename... Args> struct tuple_from_list;

template <typename... Args>
using tuple_from_list_t = typename tuple_from_list<Args...>::type;

template <typename... Args> struct tuple_from_list<data::list<Args...>> {
  using type = std::tuple<Args...>;
};

template <typename... Args> struct list_from_tuple;

template <typename... Args>
using list_from_tuple_t = typename list_from_tuple<Args...>::type;

template <typename... Args> struct list_from_tuple<std::tuple<Args...>> {
  using type = data::list<Args...>;
};

template <typename... Args>
struct size<std::tuple<Args...>>
    : std::integral_constant<std::size_t, sizeof...(Args)> {};

template <typename... Args1, typename... Args2>
struct concat<std::tuple<Args1...>, std::tuple<Args2...>> {
  using type =
      tuple_from_list_t<concat_t<list_from_tuple_t<std::tuple<Args1...>>,
                                 list_from_tuple_t<std::tuple<Args2...>>>>;
};

} // namespace meta::op
