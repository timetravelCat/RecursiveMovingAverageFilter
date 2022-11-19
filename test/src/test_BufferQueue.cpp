#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "container/BufferQueue.hpp"

TEST_CASE("Queue Class")
{
    SMAF::BufferQueue<int32_t, 200> BufferQueue1(100, "queue1");
    SMAF::BufferQueue<int32_t, 300> BufferQueue2(100, "queue2");
    
    SMAF::PrintBufferStatus();

    REQUIRE(true);
}