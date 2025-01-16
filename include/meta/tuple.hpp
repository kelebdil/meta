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

namespace detail {
template <std::size_t at, typename... Args1, typename... Args2,
          std::size_t... Is>
constexpr void write_subtuple_impl(std::tuple<Args1...> &result,
                                   std::tuple<Args2...> const &subtuple,
                                   std::integer_sequence<std::size_t, Is...>) {
  ((std::get<at + Is>(result) = std::get<Is>(subtuple)), ...);
}

template <std::size_t at, typename... Args1, typename... Args2>
constexpr void write_subtuple(std::tuple<Args1...> &result,
                              std::tuple<Args2...> const &subtuple) {
  write_subtuple_impl<at>(
      result, subtuple,
      std::make_integer_sequence<std::size_t, sizeof...(Args2)>{});
}

template <std::size_t index, typename Input>
constexpr std::size_t subseq_length = meta::op::size_v<
    meta::op::accumulate_n_t<index, std::tuple<>, meta::op::concat, Input>>;

template <typename... Args, std::size_t... Is>
constexpr auto concat_tuples_impl(Args &&...args,
                                  std::integer_sequence<std::size_t, Is...>)
    -> meta::op::flatten_t<std::tuple<std::remove_reference_t<Args>...>> {
  using input_ref_t = std::tuple<Args...>;
  using input_t = std::tuple<std::remove_reference_t<Args>...>;
  input_ref_t input{std::forward<Args>(args)...};
  using result_t =
      meta::op::flatten_t<std::tuple<std::remove_reference_t<Args>...>>;
  result_t result{};
  (write_subtuple<subseq_length<Is, input_t>>(result, std::get<Is>(input)),
   ...);
  return result;
}
} // namespace detail

template <typename... Args> constexpr auto concat_tuples(Args &&...args) {
  return detail::concat_tuples_impl<Args...>(
      std::forward<Args>(args)...,
      std::make_integer_sequence<std::size_t, sizeof...(Args)>());
}

} // namespace meta::op
