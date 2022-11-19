#include <stdint.h>
#include <stdio.h>
#include <string.h>

namespace SMAF
{
  namespace internal
  {
    class BufferInterface
    {
     public:
      virtual void print() = 0;

     protected:
      char* getName()
      {
        return _name;
      };
      BufferInterface() = default;
      virtual ~BufferInterface() = default;

      char _name[16];
    };

    void _init_instance(int32_t buffer, BufferInterface*);
    void _deinit_instance(int32_t buffer);

    /**
     * @brief A memory
     *
     */
    template<class T>
    class BufferImpl : internal::BufferInterface
    {
     public:
      void print() override
      {
        printf("container : %s, \t buffer = %dbytes \n", _name, static_cast<T*>(this)->buffer());
      }

     protected:
      BufferImpl() = delete;

      explicit BufferImpl(const char* name)
      {
        strcpy(_name, name);
        internal::_init_instance(static_cast<T*>(this)->buffer(), static_cast<BufferInterface*>(this));
      }
      virtual ~BufferImpl()
      {
        internal::_deinit_instance(static_cast<T*>(this)->buffer());
      }
    };
  }  // namespace internal

  void PrintBufferStatus();

}  // namespace SMAF