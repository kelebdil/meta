#include "demangle.hpp"

#include <cstdlib>
#include <cxxabi.h>
#include <memory>

namespace test::utils {

std::string Demangle(const char *name) {
  int status{};

  std::unique_ptr<char, void (*)(void *)> res{
      abi::__cxa_demangle(name, NULL, NULL, &status), std::free};

  return (status == 0) ? res.get() : name;
}

} // namespace test::utils
