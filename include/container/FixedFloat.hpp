#pragma once

#include <stdint.h>

namespace SMAF
{
  // limit [0.1,1.0) => valid digits : 10
  // limit [1,10) => valid digits : 9
  // limit [10,100) => valid digits : 8
  // limit [100,1000) => valid digits : 7
  // ...
  constexpr uint8_t getDigits(float limit)
  {
    limit = limit > 0.f ? limit : -limit;

    uint8_t res{ 10 };
    while (limit > 1.0f)
    {
      res--;
      limit /= 10.0f;

      if (res == 0)
        return 0;
    }

    while (limit < 0.1f)
    {
      res++;
      limit *= 10.0f;

      if (res == UINT8_MAX)
        return UINT8_MAX;
    }

    return res;
  }

  // inverse operation of getDigits
  constexpr float getLimits(uint8_t digits)
  {
    float res = 1.0f;
    int16_t remain = int16_t(10) - int16_t(digits);

    while (remain > 0)
    {
      res *= 10.0f;
      remain--;
    }

    while (remain < 0)
    {
      res *= 0.1f;
      remain++;
    }

    return res;
  }

  /**
   * @brief FixedFloat class used for numerically stable arithmetics operations
   *
   * Requires maximum / minimum range
   * internally, float changed to int32_t with
   * summation results int64_t
   *
   * @tparam digits a valid number of floating point to int32_t
   */
  template<uint8_t digits>
  class FixedFloat
  {
   public:
    /**
     * @brief An intermediate class results after summation of FixedFloat class
     */
    class FixedSum
    {
     public:
      FixedSum() = default;
      explicit FixedSum(int64_t sum) : _sum(sum)
      {
      }
      explicit FixedSum(int32_t sum) : _sum(sum)
      {
      }

      static float get(const FixedSum& fixedSum)
      {
        return float(double(fixedSum._sum) / double(nominator()));
      }

      float get() const
      {
        return float(double(_sum) / double(nominator()));
      }

      template<typename T>
      FixedSum operator/(const T& data) const
      {
        FixedSum{ _sum / data };
      }
      template<typename T>
      FixedSum operator*(const T& data) const
      {
        FixedSum{ _sum * data };
      }

      template<typename T>
      void operator/=(const T& data)
      {
        _sum /= data;
      }
      template<typename T>
      void operator*=(const T& data)
      {
        _sum *= data;
      }

      FixedSum operator+(const float& data) const
      {
        return FixedSum{ FixedFloat{ data }.getFixed() + _sum };
      }
      FixedSum operator+(const FixedFloat& data) const
      {
        return FixedSum{ data.getFixed() + _sum };
      }
      FixedSum operator+(const FixedSum& data) const
      {
        return FixedSum{ data._sum + _sum };
      }

      void operator+=(const float& data)
      {
        _sum += FixedFloat{ data }.getFixed();
      }
      void operator+=(const FixedFloat& data)
      {
        _sum += data.getFixed();
      }
      void operator+=(const FixedSum& data)
      {
        _sum += data._sum;
      }

      FixedSum operator-(const float& data) const
      {
        return FixedSum{ _sum - FixedFloat{ data }.getFixed() };
      }
      FixedSum operator-(const FixedFloat& data) const
      {
        return FixedSum{ _sum - data.getFixed() };
      }
      FixedSum operator-(const FixedSum& data) const
      {
        return FixedSum{ _sum - data._sum };
      }

      void operator-=(const float& data)
      {
        _sum -= FixedFloat{ data }.getFixed();
      }
      void operator-=(const FixedFloat& data)
      {
        _sum -= data.getFixed();
      }
      void operator-=(const FixedSum& data)
      {
        _sum -= data._sum;
      }

     private:
      int64_t _sum{ 0 };
    };

   public:
    // class FixedSum;
    explicit FixedFloat() = default;
    explicit FixedFloat(const float& data)
    {
      const float _data = data > _limit ? _limit : (data < -_limit ? -_limit : data);
      _fixed_float = static_cast<int32_t>(_data * nominator());
    }
    explicit FixedFloat(const FixedFloat& copy)
    {
      _fixed_float = copy._fixed_float;
    }

    void operator=(const float& data)
    {
      const float _data = data > _limit ? _limit : (data < -_limit ? -_limit : data);
      _fixed_float = static_cast<int32_t>(_data * nominator());
    }
    void operator=(const FixedFloat& copy)
    {
      _fixed_float = copy._fixed_float;
    }

    FixedSum operator+(const float& data) const
    {
      return FixedSum{ FixedFloat{ data }.getFixed() + static_cast<int64_t>(_fixed_float) };
    }
    FixedSum operator+(const FixedFloat& data) const
    {
      return FixedSum{ data.getFixed() + static_cast<int64_t>(_fixed_float) };
    }
    FixedSum operator+(const FixedSum& data) const
    {
      return FixedSum{ data._sum + static_cast<int64_t>(_fixed_float) };
    }

    FixedSum operator-(const float& data) const
    {
      return FixedSum{ static_cast<int64_t>(_fixed_float) - FixedFloat{ data }.getFixed() };
    }
    FixedSum operator-(const FixedFloat& data) const
    {
      return FixedSum{ static_cast<int64_t>(_fixed_float) - data.getFixed() };
    }
    FixedSum operator-(const FixedSum& data) const
    {
      return FixedSum{ static_cast<int64_t>(_fixed_float) - data._sum };
    }

    int32_t getFixed() const
    {
      return _fixed_float;
    }
    float getFloat() const
    {
      return static_cast<float>(_fixed_float) / nominator();
    }

   private:
    static constexpr float _limit{ getLimits(digits) };

    constexpr static float nominator()
    {
      float res{ 1.0f };
      int _digit = digits;
      while (_digit > 0)
      {
        res *= 10.0f;
        _digit--;
      }
      return res;
    }

    int32_t _fixed_float{ 0 };
  };
};  // namespace SMAF