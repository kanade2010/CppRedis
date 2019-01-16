#include "CppRedis.hpp"
#include <iostream>

int main()
{
  Redis::Client client;
  client.Connect();

  client.SetValue("sola", "ailumiyana");
  //client.Execute("subscribe bad_channel");

  getchar();

  std::cout << client.GetValue("sola") << '\n';

  getchar();
  return 0;
}