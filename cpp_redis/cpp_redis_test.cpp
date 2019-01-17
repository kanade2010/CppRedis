#include <iostream>
#include <cpp_redis/cpp_redis>
//#include <cpp_redis/core/reply.hpp>

int main()
{
  cpp_redis::active_logger = std::unique_ptr<cpp_redis::logger>(new cpp_redis::logger);

  cpp_redis::client client;

  client.connect("127.0.0.1", 6379);

  client.set("hello", "redis world", [](cpp_redis::reply& reply){
    std::cout << reply << "\n";
  });

  client.get("hello", [](cpp_redis::reply& reply){
    std::cout << reply << "\n";
  });

  client.sync_commit();


  getchar();
  return 0;
}