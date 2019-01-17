#include <iostream>
#include <cpp_redis/cpp_redis>
#include <string>
#include <tacopie/tacopie>

int main()
{
  cpp_redis::active_logger = std::unique_ptr<cpp_redis::logger>(new cpp_redis::logger);

  cpp_redis::subscriber sub;

  sub.connect("127.0.0.1", 6379);

  sub.subscribe("test_chan", [](const std::string& chan, const std::string& msg){
    std::cout << "message " << chan << ": " << msg << std::endl;
  });
 
  sub.commit();

  getchar();
  return 0;
}