// g++ async_sub.cpp redisclient.cpp -o async_sub -g -w --std=c++17 -I/boost_1_70_0 -I../src -lpthread -L/boost_1_70_0/stage/lib -lboost_system && ./async_sub

#include <string>
#include <iostream>
#include <functional>
#include <thread>
#include <chrono>
#include <future>
#include <algorithm>
#include <boost/asio/ip/address.hpp>

#include "redisclient.h"
#include "/d/Projects/ACCS/server/Track.h"
#define trace(str)(std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << "(): " << str << std::endl)

class RedisSubscriber
{
public:
	RedisSubscriber(const std::string& host, uint16_t port);
	~RedisSubscriber();
  bool connect();
  void disconnect();
  bool isConnected();
	void subscribe(const std::string& channel);
	void subscribe();
	void onSubscription(const std::vector<char> &buf, const std::string& channel);


protected:
  std::string _host;
  uint16_t    _port;
  boost::asio::io_service _ioService;
  redisclient::RedisAsyncClient* _subscriber;
};

RedisSubscriber::RedisSubscriber(const std::string& host, uint16_t port):_host(host),
    _port(port)
{
}

RedisSubscriber::~RedisSubscriber()
{
	disconnect();
}

bool RedisSubscriber::connect()
{
  boost::asio::ip::address address = boost::asio::ip::address::from_string(_host);
  boost::asio::ip::tcp::endpoint endpoint(address, _port);
  _subscriber = new redisclient::RedisAsyncClient(_ioService);

  // conn thread
  std::thread conn_thread([&]{
    _subscriber->connect(endpoint, [&](boost::system::error_code ec){
      if(ec) { trace("subscriber: Can't connect to redis: " << ec.message()); return false; }
		});

    _ioService.run();
  });
  conn_thread.detach();

  while(!isConnected())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
    trace("subscriber still not connected");
  }
  trace("subscriber connected!");
  return true;
}

void RedisSubscriber::disconnect()
{
  _subscriber->disconnect();
  delete _subscriber;
}

bool RedisSubscriber::isConnected()
{
  return _subscriber->isConnected();
}
 
void RedisSubscriber::subscribe(const std::string& channel)
{
  _subscriber->subscribe(channel,
			std::bind(&RedisSubscriber::onSubscription, this, std::placeholders::_1, channel));
}

void RedisSubscriber::subscribe()
{
	subscribe("accs_track");
	subscribe("accs_misc");
}

void RedisSubscriber::onSubscription(const std::vector<char> &buf, const std::string& channel)
{
	if(channel.compare("accs_track") == 0)
	{
		trace("Track size=" << sizeof(Track));
		Track track;
		trace("size=" << buf.end() - buf.begin());
		memcpy(&track, (void*)buf.data(), buf.end() - buf.begin());
		trace("");
		trace(track.string());
		trace("");
	}
	else if(channel.compare("accs_misc") == 0)
	{		
    std::string msg(buf.begin(), buf.end());
    std::cerr << "Channel: " << channel << ", Message: " << msg << std::endl;
    if( msg == "stop" )
      _ioService.stop();
	}
	else
	{
		trace("unknown channel: " << channel);
	}
}


int main(int, char **)
{
	RedisSubscriber rs("192.168.99.105", 6379);
	rs.connect();
	rs.subscribe();


	while(true)
	{
		trace("waiting to receive....");
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

  return 0;
}
