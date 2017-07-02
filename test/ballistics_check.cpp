/**
 * Copyright 2017 William Grim
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "gtest/gtest.h"
#include "ballistics/ballistics.h"

TEST(BallisticsCheck, PassMe) {
  Ballistics* solution;
  double bc = 0.5;
  double fps = 1200;
  double seightHeight = 1.6;
  double angle = 0;
  double zero = 100;
  double windSpeed = 0;
  double windAngle = 0;
  double zeroAngle = zero_angle(G1, bc, fps, 1.6, zero, 0);
  int nsoln = Ballistics_solve(&solution, G1, bc, fps, seightHeight, angle, zeroAngle, windSpeed, windAngle);
  EXPECT_EQ(5090, nsoln);
  EXPECT_DOUBLE_EQ(-1.60, Ballistics_get_path(solution, 0));
  EXPECT_DOUBLE_EQ(0.021086942030323762, Ballistics_get_path(solution, 100));
  EXPECT_DOUBLE_EQ(-25.871778035601729, Ballistics_get_path(solution, 200));
  EXPECT_DOUBLE_EQ(-82.458422497938699, Ballistics_get_path(solution, 300));
  EXPECT_DOUBLE_EQ(-172.74938891261581, Ballistics_get_path(solution, 400));
  EXPECT_DOUBLE_EQ(-299.58523278666632, Ballistics_get_path(solution, 500));
  EXPECT_DOUBLE_EQ(-465.99531684228566, Ballistics_get_path(solution, 600));
  EXPECT_DOUBLE_EQ(-674.45631229315825, Ballistics_get_path(solution, 700));
  EXPECT_DOUBLE_EQ(-927.58052626524727, Ballistics_get_path(solution, 800));
  EXPECT_DOUBLE_EQ(-1229.0334190298465, Ballistics_get_path(solution, 900));
  EXPECT_DOUBLE_EQ(-1580.0152706594765, Ballistics_get_path(solution, 1000));
}
