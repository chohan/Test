// g++ async_pub.cpp redisclient.cpp -o async_sub -g -w --std=c++17 -I/boost_1_70_0 -I../src -lpthread -L/boost_1_70_0/stage/lib -lboost_system && ./async_pub

#include <string>
#include <iostream>
#include <functional>
#include <thread>
#include <chrono>
#include <future>
#include <boost/asio/ip/address.hpp>

#include "redisclient.h"
#include "/d/Projects/ACCS/server/Track.h"
#define trace(str)(std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << "(): " << str << std::endl)

class RedisPublisher
{
public:
	RedisPublisher(const std::string& host, uint16_t port);
	~RedisPublisher();
	bool connect();
	void disconnect();
	bool isConnected();
	void publish(const std::string& channel, const std::string& message);
	void publish(const std::string& channel, const char* buffer, const int size);
	void publish(const std::string& channel, const Track* pTrack);
	void publish();

protected:
	std::string _host;
	uint16_t		_port;
  boost::asio::io_service _ioService;
  redisclient::RedisAsyncClient* _publisher;
};

RedisPublisher::RedisPublisher(const std::string& host, uint16_t port):_host(host), _port(port)
{
}

RedisPublisher::~RedisPublisher()
{
	disconnect();
}

bool RedisPublisher::connect()
{
  boost::asio::ip::address address = boost::asio::ip::address::from_string(_host);
  boost::asio::ip::tcp::endpoint endpoint(address, _port);
	_publisher = new redisclient::RedisAsyncClient(_ioService);

	// conn thread
	std::thread conn_thread([&]{
		_publisher->connect(endpoint, [&](boost::system::error_code ec){
  	  if(ec) { trace("publisher: Can't connect to redis: " << ec.message()); return false; }
		});

    _ioService.run();
	});
	conn_thread.detach();

	while(!isConnected())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		trace("publisher still not connected");
	}
	trace("publisher connected!");
	return true;
}

void RedisPublisher::disconnect()
{
	_publisher->disconnect();
	delete _publisher;
}

bool RedisPublisher::isConnected()
{
	return _publisher->isConnected();
}

void RedisPublisher::publish(const std::string& channel, const std::string& message)
{
	_publisher->publish(channel, message);
}

void RedisPublisher::publish(const std::string& channel, const char* buffer, const int size)
{
	redisclient::RedisBuffer rb(buffer, size);
	_publisher->publish(channel, rb);
}

void RedisPublisher::publish(const std::string& channel, const Track* pTrack)
{
	publish(channel, reinterpret_cast<const char*>(pTrack), sizeof(Track));
}

void RedisPublisher::publish()
{
	trace("Publisheing...");
	while(isConnected())
	{
		trace("message#1 => accs_misc"); publish("accs_misc", "message#1");
		trace("message#2 => accs_misc"); publish("accs_misc", "message#2");
		trace("message#3 => accs_misc"); publish("accs_misc", "message#3");

		Track track;
		track.nSysTN = 100;
		track.nSenTN = 200;
		track.nSensorId = 786;
		strcpy(track.sCallsign, "Pak1");
		track.fLatitude = 43.567;
		track.fLongitude = -79.045;
		publish("accs_track", &track);
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	}
	publish("accs_misc", "stop");
}


int main(int, char **)
{
	RedisPublisher rp("192.168.99.105", 6379);
	rp.connect();
	rp.publish();


  return 0;
}
