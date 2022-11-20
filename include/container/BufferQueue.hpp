#pragma once

#include <stdint.h>

#include "Buffer.hpp"

namespace RMAF
{
  namespace internal
  {
    template<typename T>
    class QueueInterface
    {
     public:
      virtual ~QueueInterface() = default;
      virtual void reset(int32_t capacity = 0) = 0;
      virtual bool isEmpty() const = 0;
      virtual bool isFull() const = 0;
      virtual bool enqueue(const T& in, T* out = nullptr) = 0;
      virtual bool dequeue(T* result) = 0;
      virtual T recent(int32_t idx = 0) const = 0;
      virtual T old(int32_t idx = 0) const = 0;
      virtual int32_t getCapacity() const = 0;
    };
  }  // namespace internal

  /**
   * @brief A simple template Queue class
   *
   * @tparam T type of data
   * @tparam Buffer
   */
  template<typename T, uint32_t Buffer>
  class BufferQueue : public internal::BufferImpl<BufferQueue<T, Buffer>>, public internal::QueueInterface<T>
  {
   public:
    using Parent = internal::BufferImpl<BufferQueue<T, Buffer>>;
    explicit BufferQueue(int32_t capacity, const char* name = "") : Parent(name), _capacity(capacity)
    {
      assert(_capacity >= 0);
      if(_capacity == 0)
        _capacity = Buffer;

      assert(strlen(name) <= 16);
      assert(capacity <= static_cast<int32_t>(Buffer));
    };
    explicit BufferQueue(const BufferQueue&) = delete;

    static constexpr int32_t buffer()
    {
      return sizeof(T) * Buffer;
    }

    void reset(int32_t capacity = 0) override
    {
      _rear = -1;
      _front = 0;
      _size = 0;
      if (_capacity > 0)
      {
        assert(capacity <= static_cast<int32_t>(Buffer));
        _capacity = capacity;
      }
    }

    bool isEmpty() const override
    {
      return (_size == 0);
    }

    bool isFull() const override
    {
      return (_capacity == _size);
    }

    // if true, queue is full and return rear data
    bool enqueue(const T& in, T* out = nullptr) override
    {
      bool res{ false };
      if (isFull())
      {
        dequeue(out);
        res = true;
      }

      _rear = (_rear + 1) % _capacity;
      _data[_rear] = in;
      _size++;
      return res;
    }

    // if false, queue size is already zero
    bool dequeue(T* result) override
    {
      if (_size == 0)
        return false;

      if (result)
        *result = _data[_front];
      _front = (_front + 1) % _capacity;
      _size--;

      return true;
    }

    // Get recent data
    T recent(int32_t idx = 0) const override
    {
      assert(idx < _capacity);
      const int32_t _idx = (_rear - idx) % _capacity;
      return _data[_idx < 0 ? _idx + _capacity : _idx];
    }

    // Get old data
    T old(int32_t idx = 0) const override
    {
      return _data[(_front + idx) % _capacity];
    }

    int32_t getCapacity() const override
    {
      return _capacity;
    }

   private:
    int32_t _rear{ -1 };
    int32_t _front{ 0 };
    int32_t _size{ 0 };
    int32_t _capacity{ 0 };
    T _data[Buffer];
  };
}  // namespace RMAF