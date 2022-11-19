#include <container/Buffer.hpp>

#define MAX_INSTANCE_NUM 100

namespace SMAF
{
  int32_t _buffer_bytes{ 0 };
  int32_t _num_instances{ 0 };

  namespace internal
  {
    static BufferInterface *_buffers[MAX_INSTANCE_NUM] = { nullptr };
    void _init_instance(int32_t buffer, BufferInterface *_ptr)
    {
      if (_num_instances < MAX_INSTANCE_NUM)
        _buffers[_num_instances] = _ptr;

      _num_instances++;
      _buffer_bytes += buffer;
    }
    void _deinit_instance(int32_t buffer)
    {
      _num_instances--;
      _buffer_bytes -= buffer;
    }
  };  // namespace internal

  void PrintBufferStatus()
  {
    // Todo Change to List
    printf("container instance : %d, total buffer %d \n", _num_instances, _buffer_bytes);
    if (_num_instances > MAX_INSTANCE_NUM)
      printf("Maximum instance log %d exceeded \n", MAX_INSTANCE_NUM);
    for (int i = 0; i < (_num_instances > MAX_INSTANCE_NUM ? MAX_INSTANCE_NUM : _num_instances); i++)
      if (internal::_buffers[i])
        internal::_buffers[i]->print();
  }
}  // namespace SMAF