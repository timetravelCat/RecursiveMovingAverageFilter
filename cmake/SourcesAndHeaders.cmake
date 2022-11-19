set(sources
    src/Buffer.cpp
    # src/FixedFloat.cpp
)

# set(exe_sources
# 		src/main.cpp
# 		${sources}
# )

set(headers
    include/container/BufferQueue.hpp
    include/container/Buffer.hpp
)

set(test_sources
  src/test_BufferQueue.cpp
  src/test_FixedFloat.cpp
)
