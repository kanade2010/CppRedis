#include <iostream>
#include <cpp_redis/cpp_redis>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <memory>

/*
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
}*/


/*void PublishThread()
{
  cpp_redis::client pub;

  pub.connect();

  pub.commit();

  while(1)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    pub.publish("test_chan", "hello redis subscriber");
    pub.commit();
  }

}*/

std::condition_variable g_exit_cond;

void ConnectCallBack(const std::string& host, std::size_t port, cpp_redis::subscriber::connect_state status)
{
  if (status == cpp_redis::subscriber::connect_state::dropped) {
    std::cout << "client disconnected from " << host << ":" << port << std::endl;
    g_exit_cond.notify_all();
  }
}

int main()
{
  cpp_redis::active_logger = std::unique_ptr<cpp_redis::logger>(new cpp_redis::logger);

  cpp_redis::subscriber sub;

  sub.connect("127.0.0.1", 6379, ConnectCallBack);

  sub.subscribe("test_chan", [](const std::string& chan, const std::string& msg){
    std::cout << "message " << chan << ": " << msg << std::endl;
  });
 
  sub.commit();

  std::mutex mutex;
  std::unique_lock<std::mutex> lock(mutex);
  g_exit_cond.wait(lock);

  return 0;
}