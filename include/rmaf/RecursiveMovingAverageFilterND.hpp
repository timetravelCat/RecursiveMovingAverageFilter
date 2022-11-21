#pragma once

#include <stdarg.h>

#include "RecursiveMovingAverageFilter.hpp"

namespace RMAF
{
  template<uint8_t digits, uint32_t... max_capacity>
  class RecursiveMovingAverageFilterND
  {
   public:
    static constexpr uint32_t SIZE = sizeof...(max_capacity);
    static constexpr uint32_t BUFFERS[] = { max_capacity... };

    explicit RecursiveMovingAverageFilterND() = delete;
    explicit RecursiveMovingAverageFilterND(const char *name)
    {
      int32_t _capacities[SIZE];
      for (uint32_t i = 0; i < SIZE; i++)
        _capacities[i] = static_cast<int32_t>(BUFFERS[i]);

      initialize<SIZE, max_capacity...>(_capacities, name);
    }
    explicit RecursiveMovingAverageFilterND(const char *name, int32_t capacities...)
    {
      int32_t _capacities[SIZE];
      _capacities[0] = capacities;

      va_list args;
      va_start(args, capacities);

      for (uint32_t i = 1; i < SIZE; i++)
        _capacities[i] = va_arg(args, int32_t);

      va_end(args);

      initialize<SIZE, max_capacity...>(_capacities, name);
    }

    void reset(int32_t capacities...)
    {
      _queue[0]->reset(capacities);

      va_list args;
      va_start(args, capacities);

      for (uint32_t i = 1; i < SIZE; i++)
        _queue[i]->reset(va_arg(args, int32_t));

      va_end(args);

      for (uint32_t i = 0; i < SIZE; i++)
        _FixedSum[i]._sum = 0;
    }

    bool push(const float &in, float *result = nullptr)
    {
      return push(in, result, 0);
    }

    ~RecursiveMovingAverageFilterND()
    {
      for (uint32_t i = 0; i < SIZE; i++)
        delete _queue[i];
    }

   private:
    template<uint32_t F, uint32_t First, uint32_t... Rest>
    void initialize(int32_t *capacities, const char *name)
    {
      _queue[SIZE - F] = new BufferQueue<FixedFloat<digits>, First>(capacities[SIZE - F], name);
      initialize<F - 1, Rest...>(capacities, name);
    }

    template<uint32_t F>
    static void initialize(int32_t *capacities, const char *name)
    {
      (void)capacities;
      (void)name;
    }

    bool push(const float &in, float *result, uint32_t depth)
    {
      bool res = false;
      FixedFloat<digits> fixedFloat{ in };
      _FixedSum[depth] += fixedFloat;

      FixedFloat<digits> out;

      if (_queue[depth]->enqueue(FixedFloat<digits>{ in }, &out))
      {
        _FixedSum[depth] -= out;
        const float _in = (_FixedSum[depth] / _queue[depth]->getCapacity()).get();

        depth++;

        if (depth < SIZE)
        {
          return push(_in, result, depth);
        }
        else
        {  // depth == DEPTH
          if (result)
            *result = _in;

          res = true;
        }
      }

      return res;
    }

    internal::QueueInterface<FixedFloat<digits>> *_queue[SIZE] = { nullptr };
    typename FixedFloat<digits>::FixedSum _FixedSum[SIZE];
  };

};  // namespace RMAF