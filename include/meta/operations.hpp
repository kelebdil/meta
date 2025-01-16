#pragma once

#include <cstddef>
#include <type_traits>

#include "meta/traits.hpp"

namespace meta::op {

template <typename T> struct is_empty;

template <typename T> constexpr bool is_empty_v = is_empty<T>::value;

template <typename T> struct front;

template <typename T> using front_t = typename front<T>::type;

template <typename T> struct back;

template <typename T> using back_t = typename back<T>::type;

template <typename T> struct size;

template <typename T> constexpr std::size_t size_v = size<T>::value;

template <typename C, std::size_t index> struct at;

template <typename C, std::size_t index>
using at_t = typename at<C, index>::type;

template <typename T1, typename T2> struct concat;

template <typename T1, typename T2>
using concat_t = typename concat<T1, T2>::type;

template <typename T> struct reverse;

template <typename T> using reverse_t = typename reverse<T>::type;

template <template <typename...> class F, typename... Args> struct apply {
  using type = typename F<Args...>::type;
};

template <template <typename...> class F, typename... Args>
using apply_t = typename apply<F, Args...>::type;

template <template <typename X> class F, typename C> struct foreach;

template <template <typename X> class F, typename C>
using foreach_t = typename foreach<F, C>::type;

template <template <typename...> class... Args> struct compose;

template <template <typename> class F, template <typename...> class G>
struct compose<F, G> {
  template <typename... Args> struct op {
    using type = typename F<typename G<Args...>::type>::type;
  };
};

template <template <typename X> class F, template <typename...> class... Others>
struct compose<F, Others...> {
private:
  template <typename... Args>
  using last = typename compose<Others...>::template op<Args...>;

public:
  template <typename... Args> struct op {
    using type = typename compose<F, last>::template op<Args...>::type;
  };
};

namespace detail {

template <typename ContainerTag, typename Container> struct flatten_impl;

}

namespace detail {
template <typename template_tag, typename C> struct flatten_op_impl;

template <typename template_tag, template <typename...> typename C>
struct flatten_op_impl<template_tag, C<>> {
  using type = C<>;
};

template <typename template_tag, template <typename...> typename C,
          typename... Args>
struct flatten_op_impl<template_tag, C<C<Args...>>> {
  using type = C<Args...>;
};

template <typename template_tag, template <typename...> typename C,
          typename... Args1, typename... Args2>
struct flatten_op_impl<template_tag, C<C<Args1...>, Args2...>> {
  using type =
      concat_t<C<Args1...>,
               typename flatten_op_impl<template_tag, C<Args2...>>::type>;
};

template <typename template_tag, template <typename...> typename C, typename T,
          typename... Args>
struct flatten_op_impl<template_tag, C<T, Args...>> {
  using type =
      concat_t<C<T>, typename flatten_op_impl<template_tag, C<Args...>>::type>;
};

} // namespace detail

template <typename C>
using flatten = detail::flatten_op_impl<template_tag_t<C>, C>;

template <typename C> using flatten_t = typename flatten<C>::type;

template <typename Init, template <typename X, typename Y> typename Acc,
          typename C>
struct accumulate;

template <typename Init, template <typename X, typename Y> typename Acc,
          typename C>
using accumulate_t = typename accumulate<Init, Acc, C>::type;

template <typename Init, template <typename X, typename Y> typename Acc,
          template <typename...> typename C>
struct accumulate<Init, Acc, C<>> {
  using type = Init;
};

template <typename Init, template <typename X, typename Y> typename Acc,
          template <typename...> typename C, typename T>
struct accumulate<Init, Acc, C<T>> {
  using type = typename Acc<Init, T>::type;
};

template <typename Init, template <typename X, typename Y> typename Acc,
          template <typename...> typename C, typename T, typename... Args>
struct accumulate<Init, Acc, C<T, Args...>> {
  using type = accumulate_t<accumulate_t<Init, Acc, C<T>>, Acc, C<Args...>>;
};

} // namespace meta::op
