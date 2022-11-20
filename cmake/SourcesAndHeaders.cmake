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
    include/rmaf/RecursiveMovingAverageFilter.hpp
)

set(test_sources
  src/test_BufferQueue.cpp
  src/test_FixedFloat.cpp
  src/test_RMAF.cpp
  src/test_RMAFND.cpp
)
