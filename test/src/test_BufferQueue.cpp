#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "container/BufferQueue.hpp"

TEST_CASE("Queue Class")
{
  SMAF::BufferQueue<float, 200> BufferQueue1(100, "queue1");
  SMAF::BufferQueue<float, 300> BufferQueue2(100, "queue2");
  SMAF::PrintBufferStatus();

  BufferQueue1.enqueue(10.0f);
  BufferQueue1.enqueue(20.0f);
  BufferQueue1.enqueue(30.0f);
  BufferQueue1.enqueue(40.0f);
  REQUIRE(BufferQueue1.recent() == 40.0f);
  REQUIRE(BufferQueue1.recent(1) == 30.0f);
  REQUIRE(BufferQueue1.recent(2) == 20.0f);
  REQUIRE(BufferQueue1.recent(3) == 10.0f);

  REQUIRE(BufferQueue1.old() == 10.0f);
  REQUIRE(BufferQueue1.old(1) == 20.0f);
  REQUIRE(BufferQueue1.old(2) == 30.0f);
  REQUIRE(BufferQueue1.old(3) == 40.0f);

  float result;
  BufferQueue1.dequeue(&result);
  REQUIRE(result == 10.0f);
  BufferQueue1.dequeue(&result);
  REQUIRE(result == 20.0f);
  BufferQueue1.dequeue(&result);
  REQUIRE(result == 30.0f);
  BufferQueue1.dequeue(&result);
  REQUIRE(result == 40.0f);
  REQUIRE(BufferQueue1.dequeue(&result) == false);
  for (int i = 0; i < 100; i++)
    REQUIRE(BufferQueue2.enqueue(20.0f) == false);
  REQUIRE(BufferQueue2.enqueue(10.0f, &result) == true);
  REQUIRE(result == 20.0f);

  BufferQueue1.reset(1);
  BufferQueue1.enqueue(0.0f);
  BufferQueue1.enqueue(10.0f);
  REQUIRE(BufferQueue1.recent() == 10.0f);
  REQUIRE(BufferQueue1.old() == 10.0f);
}