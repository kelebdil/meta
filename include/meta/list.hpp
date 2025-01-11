#pragma once

#include "operations.hpp"

#include <cstddef>
#include <type_traits>

namespace meta {
namespace data {

template <typename... Args> struct list;

template <> struct list<> {};

template <typename T, typename... Args> struct list<T, Args...> {
  using type = T;
  using tail = list<Args...>;
};
} // namespace data

namespace op {

template <typename... Args>
struct is_empty<data::list<Args...>> : std::false_type {};

template <> struct is_empty<data::list<>> : std::true_type {};

template <typename... Args> struct front<data::list<Args...>> {
  using type = typename data::list<Args...>::type;
};

template <typename T> struct back<data::list<T>> {
  using type = T;
};

template <typename T, typename... Args> struct back<data::list<T, Args...>> {
  using type = back_t<data::list<Args...>>;
};

template <typename... Args>
struct size<data::list<Args...>>
    : std::integral_constant<std::size_t, sizeof...(Args)> {};

template <typename... Args1, typename... Args2>
struct concat<data::list<Args1...>, data::list<Args2...>> {
  using type = data::list<Args1..., Args2...>;
};

template <> struct reverse<data::list<>> {
  using type = data::list<>;
};

template <typename T, typename... Args> struct reverse<data::list<T, Args...>> {
  using type = concat_t<reverse_t<data::list<Args...>>, data::list<T>>;
};

template <template <typename X> class F> struct foreach<F, data::list<>> {
  using type = meta::data::list<>;
};

template <template <typename X> class F, typename T>
struct foreach<F, data::list<T>> {
  using type = meta::data::list<apply_t<F, T>>;
};

template <template <typename X> class F, typename... Args>
struct foreach<F, data::list<Args...>> {
  using type =
      concat_t<meta::data::list<apply_t<F, front_t<data::list<Args...>>>>,
               foreach_t<F, typename data::list<Args...>::tail>>;
};

} // namespace op
} // namespace meta
