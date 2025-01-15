#pragma once

namespace meta::op {

namespace detail {

template <template <typename...> typename T> struct template_tag_impl {
  template <typename... Args> struct rebind {
    using type = T<Args...>;
  };
};

} // namespace detail

template <typename Container> struct template_tag;

template <typename Container>
using template_tag_t = typename template_tag<Container>::type;

template <template <typename...> typename T, typename... Args>
struct template_tag<T<Args...>> {
  using type = detail::template_tag_impl<T>;
};

} // namespace meta::op
