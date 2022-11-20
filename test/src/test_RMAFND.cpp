#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <rmaf/RecursiveMovingAverageFilterND.hpp>

using namespace RMAF;

TEST_CASE("RMAFND")
{
  RecursiveMovingAverageFilterND<getDigits(10.0f), 10, 5, 3> _RecursiveMovingAverageFilterND{ "test_RMAFND", 4, 3, 2 };

  REQUIRE(_RecursiveMovingAverageFilterND.push(1.0f) == false);
  REQUIRE(_RecursiveMovingAverageFilterND.push(1.0f) == false);
  REQUIRE(_RecursiveMovingAverageFilterND.push(1.0f) == false);
  REQUIRE(_RecursiveMovingAverageFilterND.push(1.0f) == false);
  REQUIRE(_RecursiveMovingAverageFilterND.push(1.0f) == false);
  REQUIRE(_RecursiveMovingAverageFilterND.push(1.0f) == false);
  REQUIRE(_RecursiveMovingAverageFilterND.push(1.0f) == false);
  REQUIRE(_RecursiveMovingAverageFilterND.push(1.0f) == false);
  REQUIRE(_RecursiveMovingAverageFilterND.push(1.0f) == false);
  REQUIRE(_RecursiveMovingAverageFilterND.push(1.0f) == true);
  REQUIRE(_RecursiveMovingAverageFilterND.push(1.0f) == true);
  REQUIRE(_RecursiveMovingAverageFilterND.push(1.0f) == true);

  _RecursiveMovingAverageFilterND.reset(3, 4, 2);
  REQUIRE(_RecursiveMovingAverageFilterND.push(1.0f) == false);
  REQUIRE(_RecursiveMovingAverageFilterND.push(1.0f) == false);
  REQUIRE(_RecursiveMovingAverageFilterND.push(1.0f) == false);
  REQUIRE(_RecursiveMovingAverageFilterND.push(1.0f) == false);
  REQUIRE(_RecursiveMovingAverageFilterND.push(1.0f) == false);
  REQUIRE(_RecursiveMovingAverageFilterND.push(1.0f) == false);
  REQUIRE(_RecursiveMovingAverageFilterND.push(1.0f) == false);
  REQUIRE(_RecursiveMovingAverageFilterND.push(1.0f) == false);
  REQUIRE(_RecursiveMovingAverageFilterND.push(1.0f) == false);
  REQUIRE(_RecursiveMovingAverageFilterND.push(1.0f) == true);
  REQUIRE(_RecursiveMovingAverageFilterND.push(1.0f) == true);
  REQUIRE(_RecursiveMovingAverageFilterND.push(1.0f) == true);

  // Value Check?
  _RecursiveMovingAverageFilterND.reset(2, 2, 2);
  REQUIRE(_RecursiveMovingAverageFilterND.push(0.0f) == false);
  REQUIRE(_RecursiveMovingAverageFilterND.push(1.0f) == false);
  REQUIRE(_RecursiveMovingAverageFilterND.push(2.0f) == false);
  REQUIRE(_RecursiveMovingAverageFilterND.push(3.0f) == false);
  REQUIRE(_RecursiveMovingAverageFilterND.push(4.0f) == false);
  REQUIRE(_RecursiveMovingAverageFilterND.push(5.0f) == false);
  float res;
  REQUIRE(_RecursiveMovingAverageFilterND.push(6.0f, &res) == true);
  REQUIRE(res == 4.5f);

  PrintBufferStatus();
}