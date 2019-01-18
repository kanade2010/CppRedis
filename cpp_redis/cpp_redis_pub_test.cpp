#include <iostream>
#include <cpp_redis/cpp_redis>
#include <thread>
#include <chrono>

int main()
{
  cpp_redis::active_logger = std::unique_ptr<cpp_redis::logger>(new cpp_redis::logger);

  cpp_redis::client client;

  client.connect("127.0.0.1", 6379);

  while(true)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    client.publish("test_chan", "hello redis subscriber");
    client.commit();
  }

  return 0;
}