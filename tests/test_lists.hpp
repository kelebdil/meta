#pragma once

#include "meta/list.hpp"

#include <tuple>

using L0 = meta::data::list<>;
using L1 = meta::data::list<bool>;
using L2 = meta::data::list<float, double>;
using L3 = meta::data::list<int, std::tuple<char, short>, void>;
using L4 = meta::data::list<bool, char, int, long>;
using L5 = meta::data::list<L0, L1, L2, L3, L4>;
