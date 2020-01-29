// g++ async_pub.cpp redisclient.cpp -o async_sub -g -w --std=c++17 -I/boost_1_70_0 -I../src -lpthread -L/boost_1_70_0/stage/lib -lboost_system && ./async_pub

#include <string>
#include <iostream>
#include <functional>
#include <thread>
#include <chrono>
#include <future>
#include <boost/asio/ip/address.hpp>

//#include <redisclient/redisasyncclient.h>
#include "redisclient.h"
#include "/d/Projects/ACCS/server/Track.h"
#define trace(str)(std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << "(): " << str << std::endl)

static const std::string channelName = "channel-name";
static const std::string psc_accs_track = "accs_track";
static const std::string psc_accs_misc  = "accs_misc";

void publishHandler(redisclient::RedisAsyncClient &publisher, const redisclient::RedisValue &)
{
    publisher.publish(channelName, "First hello", [&](const redisclient::RedisValue &) {
        publisher.publish(channelName, "Last hello", [&](const redisclient::RedisValue &) {
            publisher.publish(channelName, "stop");
        });
    });
	publisher.publish(psc_accs_misc, "first message on accs_misc");
	
	Track track;
	std::cout << track.string() << std::endl;
}

int main(int, char **)
{
	char* addr = "192.168.99.105";
  const unsigned short port = 6379;
  boost::asio::ip::address address = boost::asio::ip::address::from_string(addr);
  boost::asio::ip::tcp::endpoint endpoint(address, port);

  boost::asio::io_service ioServicePub;
  redisclient::RedisAsyncClient publisher(ioServicePub);

	// pub con thread
	std::thread pub_con_thread([&]{
		publisher.connect(endpoint, [&](boost::system::error_code ec){
			trace("");
  	  if(ec) { trace("publisher: Can't connect to redis: " << ec.message());}
		});

    ioServicePub.run();
	});
	pub_con_thread.detach();

	do{	std::this_thread::sleep_for(std::chrono::milliseconds(500));
		trace("publisher still not connected");
	} while(!publisher.isConnected());
	trace("publisher connected!");


	while(true)
	{
		trace("publishing on " << psc_accs_misc);
		publisher.publish(psc_accs_misc, "message#1 on accs_misc");
		publisher.publish(psc_accs_misc, "message#2 on accs_misc");
		Track track;
		track.nSysTN = 100;
		track.nSenTN = 200;
		track.nSensorId = 786;
		strcpy(track.sCallsign, "Pak1");
		track.fLatitude = 43.567;
		track.fLongitude = -79.045;
		redisclient::RedisBuffer rb(reinterpret_cast<const char*>(&track), sizeof(track));
		publisher.publish(psc_accs_track, rb);
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	}
	publisher.publish(psc_accs_misc, "stop");


  return 0;
}
