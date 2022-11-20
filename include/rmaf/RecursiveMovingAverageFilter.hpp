#pragma once

#include <container/BufferQueue.hpp>
#include <container/FixedFloat.hpp>

namespace RMAF
{
  template<uint8_t digits, uint32_t max_capacity>
  class RecursiveMovingAverageFilter
  {
   public:
    explicit RecursiveMovingAverageFilter() = delete;
    explicit RecursiveMovingAverageFilter(int32_t capacity, const char* name = "")
        : _queue(capacity, name)
    {
    }

    // If queue is full return true and return result.
    bool push(const float& in, float* result = nullptr)
    {
      FixedFloat<digits> fixedFloat{ in };
      _FixedSum += fixedFloat;
      FixedFloat<digits> out;
      if (_queue.enqueue(FixedFloat<digits>{ in }, &out))
      {
        _FixedSum -= out;
        if (result)
          *result = (_FixedSum / _queue.getCapacity()).get();
        return true;
      }
      return false;
    }

    void reset(int32_t capacity = 0) 
    {
      _queue.reset(capacity);
      _FixedSum._sum = 0;
    }

   private:
    typename FixedFloat<digits>::FixedSum _FixedSum;
    BufferQueue<FixedFloat<digits>, max_capacity> _queue;
  };
};  // namespace RMAF