// g++ async_sub.cpp redisclient.cpp -o async_sub -g -w --std=c++17 -I/boost_1_70_0 -I../src -lpthread -L/boost_1_70_0/stage/lib -lboost_system && ./async_sub

#include <string>
#include <iostream>
#include <functional>
#include <thread>
#include <chrono>
#include <future>
#include <algorithm>
#include <boost/asio/ip/address.hpp>

//#include <redisclient/redisasyncclient.h>
#include "redisclient.h"
#include "/d/Projects/ACCS/server/Track.h"
#define trace(str)(std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << "(): " << str << std::endl)

static const std::string channelName = "channel-name";
static const std::string psc_accs_track = "accs_track";
static const std::string psc_accs_misc  = "accs_misc";


class PubHandler
{
public:
  PubHandler(boost::asio::io_service &ioService)
        : ioService(ioService)
  {}

  void onMessage(const std::vector<char> &buf, std::string& channel)
  {
		if(channel.compare(psc_accs_track) == 0)
		{
			trace("Track size=" << sizeof(Track));
			Track track;
			trace("size=" << buf.end() - buf.begin());
			//std::copy(buf.begin(), buf.end(), &track);
			//memcpy(&track, reinterpret_cast<const void*>(*(buf.begin())), buf.end() - buf.begin());
			memcpy(&track, (void*)buf.data(), buf.end() - buf.begin());
			trace("");
			trace(track.string());
			trace("");
		}
		else
		{		
      std::string msg(buf.begin(), buf.end());
      std::cerr << "Channel: " << channel << ", Message: " << msg << std::endl;
      if( msg == "stop" )
        ioService.stop();
		}
  }

private:
    boost::asio::io_service &ioService;
};

int main(int, char **)
{
	char* addr = "192.168.99.105";
  const unsigned short port = 6379;
  boost::asio::ip::address address = boost::asio::ip::address::from_string(addr);
  boost::asio::ip::tcp::endpoint endpoint(address, port);

  boost::asio::io_service ioServiceSub;
  redisclient::RedisAsyncClient subscriber(ioServiceSub);
  PubHandler pubHandler(ioServiceSub);
	trace("");


	// sub con thread
	std::thread sub_con_thread([&]{
  	subscriber.connect(endpoint, [&](boost::system::error_code ec){
			trace("");
  	  if(ec) { trace("subscriber: Can't connect to redis: " << ec.message());}
		});

    ioServiceSub.run();
	});
	sub_con_thread.detach();

	do{	std::this_thread::sleep_for(std::chrono::milliseconds(500));
		trace("subscriber still not connected");
	} while(!subscriber.isConnected());
	trace("subscriber connected!");
	
  subscriber.subscribe(psc_accs_misc,
    std::bind(&PubHandler::onMessage, &pubHandler, std::placeholders::_1, psc_accs_misc));
    //std::bind(&publishHandler, std::ref(publisher), std::placeholders::_1));
  subscriber.subscribe(psc_accs_track,
    std::bind(&PubHandler::onMessage, &pubHandler, std::placeholders::_1, psc_accs_track));
	trace("");

	while(true)
	{
		trace("waiting to receive....");
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

  return 0;
}
