#include <stdint.h>

#include "Buffer.hpp"

namespace SMAF
{
  /**
   * @brief A simple template Queue class
   * https://github.com/sougatadafader/Circular-Queue/blob/master/queue_array.c
   *
   * @tparam T type of data
   * @tparam Buffer
   */
  template<typename T, uint32_t Buffer>
  class BufferQueue : public internal::BufferImpl<BufferQueue<T, Buffer>>
  {
   public:
    using Parent = internal::BufferImpl<BufferQueue<T, Buffer>>;
    explicit BufferQueue(int32_t capacity, const char* name = "") : Parent(name), _capacity(capacity)
    {
      assert(_capacity >= 1);
      assert(strlen(name) <= 16);
      assert(capacity <= static_cast<int32_t>(Buffer));
    };
    explicit BufferQueue(const BufferQueue&) = delete;

    static constexpr int32_t buffer()
    {
      return sizeof(T) * Buffer;
    }

    void reset(int32_t capacity = 0)
    {
      _rear = -1;
      _front = 0;
      _size = 0;
      if (_capacity > 0)
        _capacity = capacity;
    }

    bool isEmpty()
    {
      return (_size == 0);
    }

    bool isFull()
    {
      return (_capacity == _size);
    }

    // if true, queue is full and return rear data
    bool enqueue(const T& in, T* out = nullptr)
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
    bool dequeue(T* result)
    {
      if (_size == 0)
        return false;

      *result = _data[_front];
      _front = (_front + 1) % _capacity;
      _size--;

      return true;
    }

    // Get recent data
    T recent()
    {
      return _data[_rear];
    }

    // Get old data
    T old()
    {
      return _data[_front];
    }

   private:
    int32_t _rear{ -1 };
    int32_t _front{ 0 };
    int32_t _size{ 0 };
    int32_t _capacity{ 0 };
    T _data[Buffer] = {};
  };
}  // namespace SMAF