#ifndef _CPP_REDIS_HPP
#define _CPP_REDIS_HPP

#include <string>
#include "hiredis.h"

namespace Redis{

class HiRedisCommad{
public:
  explicit HiRedisCommad(redisContext* rc, const std::string& cmd);
  ~HiRedisCommad();

  std::string Get();
  void Set();
  void Execute();

private:
  redisReply* m_redis_reply;

};

class Client
{
public:
  Client();
  ~Client();
  //!
  //! Connect to redis server
  //!
  //! \param host host to be connected to
  //! \param port port to be connected to
  //! \param connect_callback connect handler to be called on connect events (may be null)
  //! \param timeout_msecs maximum time to connect
  //! \param max_reconnects maximum attempts of reconnection if connection dropped
  //! \param reconnect_interval_msecs time between two attempts of reconnection
  //!
  void Connect(
    const std::string& host                    = "127.0.0.1",
    const std::size_t port                           = 6379
    //const connect_callback_t& connect_callback = nullptr,
    //std::uint32_t timeout_msecs                = 0,
    //std::int32_t max_reconnects                = 0,
    //std::uint32_t reconnect_interval_msecs     = 0
    );

  void SetValue(const std::string& key, const std::string& value);
  std::string GetValue(const std::string& key);
  //void Execute(const std::string& cmd);

private:
  std::string m_redis_server;
  std::size_t m_redis_port;
  redisContext* m_redis_context;

};

};

#endif

