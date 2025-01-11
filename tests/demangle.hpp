#pragma once

#include <string>
#include <typeinfo>

namespace test::utils {
std::string Demangle(const char *name);

template <typename T> std::string TypeName() {
  return Demangle(typeid(T).name());
}

} // namespace test::utils
