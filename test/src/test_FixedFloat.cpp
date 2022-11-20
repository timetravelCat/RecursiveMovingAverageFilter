#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "container/FixedFloat.hpp"

using namespace RMAF;

TEST_CASE("FixedFloat Class")
{
  // limit [0.1,1.0) => valid digits : 10
  // limit [1,10) => valid digits : 9
  // limit [10,100) => valid digits : 8
  // limit [100,1000) => valid digits : 7
  // ...
  REQUIRE(getDigits(0.05f) == 10);
  REQUIRE(getDigits(0.5f) == 9);
  REQUIRE(getDigits(1.0f) == 9);
  REQUIRE(getDigits(1.5f) == 8);
  REQUIRE(getDigits(10.0f) == 8);
  REQUIRE(getDigits(10.5f) == 7);
  REQUIRE(getDigits(100.0f) == 7);
  REQUIRE(getDigits(100.5f) == 6);

  REQUIRE(getLimits(10) == 1.0f / 10.0f);
  REQUIRE(getLimits(9) == 1.0f);
  REQUIRE(getLimits(8) == 1.0f * 10.0f);
  REQUIRE(getLimits(7) == 1.0f * 10.0f * 10.0f);
  REQUIRE(getLimits(6) == 1.0f * 10.0f * 10.0f * 10.0f);

  FixedFloat<8> _float1{ 5.0f };
  REQUIRE(_float1.getFloat() == 5.0f);
  REQUIRE(_float1.getFixed() == static_cast<int32_t>(_float1.getFloat() * 1e8f));

  _float1 = -2.0f;
  REQUIRE(_float1.getFloat() == -2.0f);
  REQUIRE(_float1.getFixed() == static_cast<int32_t>(_float1.getFloat() * 1e8f));

  _float1 = FixedFloat<8>{ 7.0f };
  REQUIRE(_float1.getFloat() == 7.0f);
  REQUIRE(_float1.getFixed() == static_cast<int32_t>(_float1.getFloat() * 1e8f));

  FixedFloat<8>::FixedSum sum;
  sum += 1.0f;
  REQUIRE(sum.get() == 1.0f);
  sum += 2.0f;
  REQUIRE(sum.get() == 1.0f + 2.0f);
  sum -= 4.0f;
  REQUIRE(sum.get() == 1.0f + 2.0f - 4.0f);

  FixedFloat<8> _float2{ 5.0f };
  REQUIRE((_float1 + 7.0f).get() == 14.0f);
  REQUIRE((_float1 + _float2).get() == 12.0f);
}