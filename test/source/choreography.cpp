#include <choreography/choreography.h>
#include <doctest/doctest.h>

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstdio>
#include <iostream>
#include <map>
#include <random>

TEST_CASE("Test 1") {
  init(6, {5, 1, 4, 2, 0, 3});
  move_left(2);
  CHECK(get_position(0) == 2);
  swap_places();
  move_around();
  CHECK(get_position(3) == 0);
}