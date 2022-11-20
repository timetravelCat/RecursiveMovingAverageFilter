#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <rmaf/RecursiveMovingAverageFilter.hpp>

using namespace RMAF;

TEST_CASE("RMAF")
{
  RecursiveMovingAverageFilter<getDigits(10.0f), 200> _rmaf{ 5, "rmaf 1" };
  REQUIRE(_rmaf.push(0.0f) == false);
  REQUIRE(_rmaf.push(1.0f) == false);
  REQUIRE(_rmaf.push(2.0f) == false);
  REQUIRE(_rmaf.push(3.0f) == false);
  REQUIRE(_rmaf.push(4.0f) == false);
  float result;
  REQUIRE(_rmaf.push(5.0f, &result) == true);

  _rmaf.reset(3);
  REQUIRE(_rmaf.push(0.0f) == false);
  REQUIRE(_rmaf.push(1.0f) == false);
  REQUIRE(_rmaf.push(2.0f) == false);
  REQUIRE(_rmaf.push(3.0f, &result) == true);



  PrintBufferStatus();
}