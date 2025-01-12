#pragma once

#include "meta/operations.hpp"

#include <type_traits>

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
