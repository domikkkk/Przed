#include <gtest/gtest.h>
#include <stdexcept>
#include "../include/Scorched/Tank/Tank.hpp"
#include "../include/Scorched/Map/Map.hpp"
#include "../include/Scorched/Terrain/TerrainTypes.hpp"

struct TankSetHpFixture : public testing::TestWithParam<std::tuple<int, int>> {};
struct TankSetHpFixtureInvalid : public testing::TestWithParam<std::tuple<int>> {};
struct TankSetArmorFixture: public testing::TestWithParam<std::tuple<int, int>> {};
struct TankSetArmorFixtureInvalid : public testing::TestWithParam<std::tuple<int>> {};
struct TankSetPosXFixture: public testing::TestWithParam<std::tuple<int, int>> {};
struct TankSetPosXFixtureInvalid : public testing::TestWithParam<std::tuple<int>> {};
struct TankSetPosYFixture: public testing::TestWithParam<std::tuple<int, int>> {};
struct TankSetPosYFixtureInvalid : public testing::TestWithParam<std::tuple<int>> {};
struct TankSetAmmoSlotFixture: public testing::TestWithParam<std::tuple<int, int>> {};
struct TankHitFixture: public testing::TestWithParam<std::tuple<int, int>> {};
struct TankHitFixtureNoArmor: public testing::TestWithParam<std::tuple<int, int>> {};

TEST_P(TankSetHpFixture, Set) {
  int input = std::get<0>(GetParam());
  int expect = std::get<1>(GetParam());
  Map dummyMap(1000, 1000);
  Tank testTank(dummyMap, "test", 10, 10, 1.0, 1.0, 0);
  testTank.setHp(input);
  EXPECT_EQ(testTank.getHp(), expect);
}

INSTANTIATE_TEST_SUITE_P(
    TankHp,
    TankSetHpFixture,
    testing::Values(
      std::make_tuple(10, 10),
      std::make_tuple(300, 300),
      std::make_tuple(500, 500))
);

TEST_P(TankSetHpFixtureInvalid, Set) {
  int input = std::get<0>(GetParam());
  Map dummyMap(1000, 1000);
  Tank testTank(dummyMap, "test", 10, 10, 1.0, 1.0, 0);
  EXPECT_THROW(testTank.setHp(input), std::invalid_argument);
}

INSTANTIATE_TEST_SUITE_P(
    TankHp,
    TankSetHpFixtureInvalid,
    testing::Values(
      std::make_tuple(0),
      std::make_tuple(-10),
      std::make_tuple(-500))
);

TEST_P(TankSetArmorFixture, Set) {
  int input = std::get<0>(GetParam());
  int expect = std::get<1>(GetParam());
  Map dummyMap(1000, 1000);
  Tank testTank(dummyMap, "test", 10, 10, 1.0, 1.0, 0);
  testTank.setArmor(input);
  EXPECT_EQ(testTank.getArmor(), expect);
}

INSTANTIATE_TEST_SUITE_P(
    TankArmor,
    TankSetArmorFixture,
    testing::Values(
      std::make_tuple(10, 10),
      std::make_tuple(100, 100),
      std::make_tuple(300, 300))
);

TEST_P(TankSetArmorFixtureInvalid, Set) {
  int input = std::get<0>(GetParam());
  Map dummyMap(1000, 1000);
  Tank testTank(dummyMap, "test", 10, 10, 1.0, 1.0, 0);
  EXPECT_THROW(testTank.setHp(input), std::invalid_argument);
}

INSTANTIATE_TEST_SUITE_P(
    TankArmor,
    TankSetArmorFixtureInvalid,
    testing::Values(
      std::make_tuple(0),
      std::make_tuple(-10),
      std::make_tuple(-500))
);

TEST_P(TankSetPosXFixture, Set) {
  int input = std::get<0>(GetParam());
  int expect = std::get<1>(GetParam());
  Map dummyMap(1000, 1000);
  Tank testTank(dummyMap, "test", 10, 10, 1.0, 1.0, 0);
  testTank.setPos(input, 10);
  EXPECT_EQ(testTank.getX(), expect);
}

INSTANTIATE_TEST_SUITE_P(
    TankPos,
    TankSetPosXFixture,
    testing::Values(
      std::make_tuple(10, 10),
      std::make_tuple(100, 100),
      std::make_tuple(300, 300))
);

TEST_P(TankSetPosXFixtureInvalid, Set) {
  int input = std::get<0>(GetParam());
  Map dummyMap(1000, 1000);
  Tank testTank(dummyMap, "test", 10, 10, 1.0, 1.0, 0);
  EXPECT_THROW(testTank.setPos(input, 10), std::invalid_argument);
}

INSTANTIATE_TEST_SUITE_P(
    TankPos,
    TankSetPosXFixtureInvalid,
    testing::Values(
      std::make_tuple(-1),
      std::make_tuple(-10),
      std::make_tuple(-500))
);

TEST_P(TankSetPosYFixture, Set) {
  int input = std::get<0>(GetParam());
  int expect = std::get<1>(GetParam());
  Map dummyMap(1000, 1000);
  Tank testTank(dummyMap, "test", 10, 10, 1.0, 1.0, 0);
  testTank.setPos(10, input);
  EXPECT_EQ(testTank.getY(), expect);
}

INSTANTIATE_TEST_SUITE_P(
    TankPos,
    TankSetPosYFixture,
    testing::Values(
      std::make_tuple(10, 10),
      std::make_tuple(100, 100),
      std::make_tuple(300, 300))
);

TEST_P(TankSetPosYFixtureInvalid, Set) {
  int input = std::get<0>(GetParam());
  Map dummyMap(1000, 1000);
  Tank testTank(dummyMap, "test", 10, 10, 1.0, 1.0, 0);
  EXPECT_THROW(testTank.setPos(10, input), std::invalid_argument);
}

INSTANTIATE_TEST_SUITE_P(
    TankPos,
    TankSetPosYFixtureInvalid,
    testing::Values(
      std::make_tuple(-1),
      std::make_tuple(-10),
      std::make_tuple(-500))
);

TEST_P(TankSetAmmoSlotFixture, Set) {
  int input = std::get<0>(GetParam());
  int expect = std::get<1>(GetParam());
  Map dummyMap(1000, 1000);
  Tank testTank(dummyMap, "test", 10, 10, 1.0, 1.0, 0);
  testTank.setAmmoSlot(input);
  EXPECT_EQ(testTank.getAmmoSlot(), expect);
}

INSTANTIATE_TEST_SUITE_P(
    TankAmmo,
    TankSetAmmoSlotFixture,
    testing::Values(
      std::make_tuple(1, 1),
      std::make_tuple(2, 2),
      std::make_tuple(100, 100))
);

TEST_P(TankHitFixture, Set) {
  int input = std::get<0>(GetParam());
  int expect = std::get<1>(GetParam());
  Map dummyMap(1000, 1000);
  Tank testTank(dummyMap, "test", 100, 10, 1.0, 1.0, 0);
  testTank.hit(input);
  EXPECT_EQ(testTank.getHp(), expect);
}

INSTANTIATE_TEST_SUITE_P(
    TankHit,
    TankHitFixture,
    testing::Values(
        // Tank has 10 armor
      std::make_tuple(0, 100),
      std::make_tuple(10, 100),
      std::make_tuple(100, 10),
      std::make_tuple(110, 0),
      std::make_tuple(-100, 100))
);

TEST_P(TankHitFixtureNoArmor, Set) {
  int input = std::get<0>(GetParam());
  int expect = std::get<1>(GetParam());
  Map dummyMap(1000, 1000);
  Tank testTank(dummyMap, "test", 100, 0, 1.0, 1.0, 0);
  testTank.hit(input);
  EXPECT_EQ(testTank.getHp(), expect);
}

INSTANTIATE_TEST_SUITE_P(
    TankHit,
    TankHitFixtureNoArmor,
    testing::Values(
        // Tank has 0 armor
      std::make_tuple(0, 100),
      std::make_tuple(10, 90),
      std::make_tuple(100, 0),
      std::make_tuple(-100, 100))
);

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
