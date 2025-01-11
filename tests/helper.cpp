#include "helper.hpp"

#include <map>

TEST(CompareTypes, Test2) {
  ASSERT_SAME(int, int);
  ASSERT_SAME(CC(std::map<int, int>), CC(std::map<int, int>));
}
