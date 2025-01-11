#pragma once

#include <cstddef>
#include <type_traits>

namespace meta {

namespace op {

template <typename T> struct is_empty;

template <typename T> constexpr bool is_empty_v = is_empty<T>::value;

template <typename T> struct front;

template <typename T> using front_t = typename front<T>::type;

template <typename T> struct back;

template <typename T> using back_t = typename back<T>::type;

template <typename T> struct size;

template <typename T> constexpr std::size_t size_v = size<T>::value;

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

} // namespace op
} // namespace meta
