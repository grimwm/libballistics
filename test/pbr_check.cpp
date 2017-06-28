#include "gtest/gtest.h"
#include "ballistics.h"

namespace {
  class PBRTest : public ::testing::Test {
  protected:
    struct PBR* pbr;

    virtual void SetUp() {
      ASSERT_EQ(0, pbr_solve(&pbr, G1, 0.48, 2800, 1.5, 4));
    }

    virtual void TearDown() {
      pbr_free(pbr);
    }
  };

  TEST_F(PBRTest, PassMe) {
    EXPECT_EQ(29, pbr_get_near_zero_yards(pbr));
    EXPECT_EQ(203, pbr_get_far_zero_yards(pbr));
    EXPECT_EQ(0, pbr_get_min_pbr_yards(pbr));
    EXPECT_EQ(238, pbr_get_max_pbr_yards(pbr));
    EXPECT_DOUBLE_EQ(1.89, pbr_get_sight_in_at_100yards(pbr) / 100.0);
  }
} // namespace