#include <choreography/choreography.h>
#include <doctest/doctest.h>

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstdio>
#include <iostream>
#include <map>
#include <random>

TEST_CASE("Test 1 - naive") {
  choreography_naive::init(6, {5, 1, 4, 2, 0, 3});
  choreography_naive::move_left(2);
  CHECK(choreography_naive::get_position(0) == 2);
  choreography_naive::swap_places();
  choreography_naive::move_around();
  CHECK(choreography_naive::get_position(3) == 0);
}

TEST_CASE("Test 1 - choreography_steps_1_2_optimized") {
  using namespace choreography_steps_1_2_optimized;
  /*
|                | 0   | 1   | 2   | 3   | 4   | 5   |
| -------------- | --- | --- | --- | --- | --- | --- |
| position_array | 5   | 1   | 4   | 2   | 0   | 3   |
| dancer array   | 4   | 1   | 3   | 5   | 2   | 0   |
| left           | 2   |     |     |     |     |     |
| position_array | 4   | 2   | 0   | 3   | 5   | 1   |
| dancer array   | 2   | 5   | 1   | 3   | 0   | 4   |
| move_around    |     |     |     |     |     |     |
| position_array | 2   | 5   | 1   | 3   | 0   | 4   |
| dancer array   | 4   | 2   | 0   | 3   | 5   | 1   |
| right          | 1   |     |     |     |     |     |
| position_array | 4   | 2   | 5   | 1   | 3   | 0   |
| dancer array   | 5   | 3   | 1   | 4   | 0   | 2   |
| swap_places    |     |     |     |     |     |     |
| position_array | 2   | 4   | 1   | 5   | 0   | 3   |
| dancer array   | 4   | 2   | 0   | 5   | 1   | 3   |
  */
  init(6, {5, 1, 4, 2, 0, 3});
  // position array = [5, 1, 4, 2, 0, 3]
  // dancers_array  = [4, 1, 3, ]
  move_left(2);
  CHECK(get_position(0) == 2);
  CHECK(get_position(1) == 5);
  CHECK(get_position(2) == 1);
  CHECK(get_position(3) == 3);
  CHECK(get_position(4) == 0);
  CHECK(get_position(5) == 4);
  move_around();
  CHECK(get_position(0) == 4);
  CHECK(get_position(1) == 2);
  CHECK(get_position(2) == 0);
  CHECK(get_position(3) == 3);
  CHECK(get_position(4) == 5);
  CHECK(get_position(5) == 1);
  move_right(1);
  CHECK(get_position(0) == 5);
  CHECK(get_position(1) == 3);
  CHECK(get_position(2) == 1);
  CHECK(get_position(3) == 4);
  CHECK(get_position(4) == 0);
  CHECK(get_position(5) == 2);
  swap_places();
  CHECK(get_position(0) == 4);
  CHECK(get_position(1) == 2);
  CHECK(get_position(2) == 0);
  CHECK(get_position(3) == 5);
  CHECK(get_position(4) == 1);
  CHECK(get_position(5) == 3);
}