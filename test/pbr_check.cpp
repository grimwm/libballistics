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
#include "ballistics/pbr.h"

namespace {
  class PBRTest : public ::testing::Test {
  protected:
    struct PBR* pbr;

    virtual void SetUp() {
      ASSERT_EQ(0, PBR_solve(&pbr, G1, 0.48, 2800, 1.5, 4));
    }

    virtual void TearDown() {
      PBR_free(pbr);
    }
  };

  TEST_F(PBRTest, PassMe) {
    EXPECT_EQ(29, PBR_get_near_zero_yards(pbr));
    EXPECT_EQ(203, PBR_get_far_zero_yards(pbr));
    EXPECT_EQ(0, PBR_get_min_PBR_yards(pbr));
    EXPECT_EQ(238, PBR_get_max_PBR_yards(pbr));
    EXPECT_DOUBLE_EQ(1.89, PBR_get_sight_in_at_100yards(pbr) / 100.0);
  }
} // namespace