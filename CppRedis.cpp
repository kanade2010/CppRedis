#include <string>
#include <memory>
#include <algorithm>
#include "CppRedis.hpp"

namespace sola{

redisContext* connect(const std::string& host, const std::size_t port)
{
  redisContext* c = redisConnect("127.0.0.1", 6379);  

  if ( c->err)
  {  
    redisFree(c);
    printf("Connect to redisServer faile %s\n", c->errstr);
    return nullptr;
  }

  return c;
}


redisReply* command(redisContext* context, const std::string& cmd)
{
  int i = 0;
  redisReply *r;

  if(cmd.empty())
    return nullptr;

  printf("%s\n", cmd.c_str());

  r = (redisReply *)redisCommand(context, cmd.c_str());
  if (nullptr == r) {
      printf("%s, Error[%d:%s]", context->err, context->errstr);
      return nullptr;
  }

  return r; 
}

/*
std::string getString(redisContext* context, const std::string& cmd)
{
  std::unique_ptr<redisReply> r = command(context, cmd);

  if(!r) return "";

  printf("error type: %d\n", r->type);

  if(r->type != REDIS_REPLY_STRING)
  {
    printf("error type: %d\n", r->type); 
    return "";
  }

  std::string ret(r->str);
  freeReplyObject(r); 
  return ret;

  switch(r->type) {
  case REDIS_REPLY_STATUS:
      printf("type:%s, reply->len:%d reply->str:%s\n", "REDIS_REPLY_STATUS", r->len, r->str);
      break;
  case REDIS_REPLY_ERROR:
      printf("type:%s, reply->len:%d reply->str:%s\n", "REDIS_REPLY_ERROR", r->len, r->str);
      break;
  case REDIS_REPLY_INTEGER:
      printf("type:%s, reply->integer:%lld\n", "REDIS_REPLY_INTEGER", r->integer);
      break;
  case REDIS_REPLY_NIL:
      printf("type:%s, no data\n", "REDIS_REPLY_NIL");
      break;
  case REDIS_REPLY_STRING:
      printf("type:%s, reply->len:%d reply->str:%s\n", "REDIS_REPLY_STRING", r->len, r->str);
      break;
  case REDIS_REPLY_ARRAY:
      printf("type:%s, reply->elements:%d\n", "REDIS_REPLY_ARRAY", r->elements);
      for (i = 0; i < r->elements; i++) {
          printf("%d: %s\n", i, r->element[i]->str);
      }
      break;
  default:
      printf("unkonwn type:%s\n", r->type);
      break;
  }

  //release reply and context 
  freeReplyObject(r); 
}
*/
};
 

namespace Redis{

HiRedisCommad::HiRedisCommad(redisContext* rc, const std::string& cmd)
  : m_redis_reply(sola::command(rc, cmd))
{

}

HiRedisCommad::~HiRedisCommad()
{
  freeReplyObject(m_redis_reply);
}

std::string HiRedisCommad::Get()
{
  if(!m_redis_reply) {
    return "";
  }

  switch(m_redis_reply->type) {
    case REDIS_REPLY_INTEGER:
        return std::to_string(m_redis_reply->integer);
        printf("type:%s, reply->integer:%lld\n", "REDIS_REPLY_INTEGER", m_redis_reply->integer);
        break;
    case REDIS_REPLY_STRING:
        return m_redis_reply->str;
        printf("type:%s, reply->len:%d reply->str:%s\n", "REDIS_REPLY_STRING", m_redis_reply->len, m_redis_reply->str);
        break;
    default:
        printf("unkonwn type:%s\n", m_redis_reply->type);
        break;
  }
}

void HiRedisCommad::Set()
{
  if(!m_redis_reply) {
    return ;
  }

  if(m_redis_reply->type != REDIS_REPLY_STATUS)
  {
    return ;
  }

  std::transform(m_redis_reply->str, m_redis_reply->str + m_redis_reply->len, m_redis_reply->str, ::toupper);
  printf("type:%s, reply->len:%d reply->str:%s\n", "REDIS_REPLY_STATUS", m_redis_reply->len, m_redis_reply->str);

  if(std::string(m_redis_reply->str) != "OK")
  {
    return ;
  }

}

/*void HiRedisCommad::Execute()
{
  if(!m_redis_reply) {
    printf("error exec\n");
    return ;
  }

  switch(m_redis_reply->type) {
    case REDIS_REPLY_STATUS:
        printf("type:%s, reply->len:%d reply->str:%s\n", "REDIS_REPLY_STATUS", m_redis_reply->len, m_redis_reply->str);
        break;
    case REDIS_REPLY_ERROR:
        printf("type:%s, reply->len:%d reply->str:%s\n", "REDIS_REPLY_ERROR", m_redis_reply->len, m_redis_reply->str);
        break;
    case REDIS_REPLY_INTEGER:
        printf("type:%s, reply->integer:%lld\n", "REDIS_REPLY_INTEGER", m_redis_reply->integer);
        break;
    case REDIS_REPLY_NIL:
        printf("type:%s, no data\n", "REDIS_REPLY_NIL");
        break;
    case REDIS_REPLY_STRING:
        printf("type:%s, reply->len:%d reply->str:%s\n", "REDIS_REPLY_STRING", m_redis_reply->len, m_redis_reply->str);
        break;
    case REDIS_REPLY_ARRAY:
        printf("type:%s, reply->elements:%d\n", "REDIS_REPLY_ARRAY", m_redis_reply->elements);
        for (int i = 0; i < m_redis_reply->elements; i++) {
            printf("%d: %s\n", i, m_redis_reply->element[i]->str);
        }
        break;
    default:
        printf("unkonwn type:%s\n", m_redis_reply->type);
        break;
  }

}*/

Client::Client()
{
}

Client::~Client()
{
  redisFree(m_redis_context);
}

void Client::Connect(
  const std::string& host, const std::size_t port
  //const connect_callback_t& connect_callback,
  //std::uint32_t timeout_msecs,
  //std::int32_t max_reconnects,
  //std::uint32_t reconnect_interval_msecs
  ) {
  
  //! Save for auto reconnects
  m_redis_server             = host;
  m_redis_port               = port;
  //m_connect_callback         = connect_callback;
  //m_max_reconnects           = max_reconnects;
  //m_reconnect_interval_msecs = reconnect_interval_msecs;

  //! notify start
  /*if (m_connect_callback) {
    m_connect_callback(host, port, connect_state::start);
  }*/

  m_redis_context = sola::connect(m_redis_server.c_str(), port);

  //! notify end
  //if (m_connect_callback) {
  //  m_connect_callback(m_redis_server, m_redis_port, connect_state::ok);
  //}
}

void Client::SetValue(const std::string& key, const std::string& value)
{
  std::string cmd = "set " + key + " " + value;
  HiRedisCommad(m_redis_context, cmd).Set();
}

std::string Client::GetValue(const std::string& key)
{
  std::string cmd = "get " + key;
  return HiRedisCommad(m_redis_context, cmd).Get();
}

/*void Client::Execute(const std::string& cmd)
{
  HiRedisCommad(m_redis_context, cmd);
}*/

};
