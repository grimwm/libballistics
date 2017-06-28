#include "gtest/gtest.h"
#include "ballistics.h"

TEST(PBR, PassMe) {
  struct PBRSolution* solution;
  EXPECT_EQ(1, pbr(&solution, G1, 0.48, 2800, 1.5, 4));
}