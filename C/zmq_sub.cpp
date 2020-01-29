// g++ zmq_sub.cpp -o zmq_sub -g -w --std=c++17 -I/boost_1_70_0 -I/d/ThirdParty/C++/zeromq/cppzmq -L/boost_1_70_0/stage/lib -L/usr/local/lib -lboost_thread -lpthread -lzmq

#include <zmq.hpp>
#include <string>
#include <iostream>
#include <functional>
#define trace(str)(std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << "(): " << str << std::endl)


class ZmqSub
{
public:
	ZmqSub();
	~ZmqSub() = default;
	void connect();
	void disconnect();
	bool isConnected();
	void subscribe(std::function<void(const std::string&, const char* buffer, int size)>callback);
	void receiver(const std::string& topic, const char* buffer, int size);
	void run();

protected:
  std::string _host;
  int _port;
	std::vector<std::string> _topics;
  zmq::context_t	z_context;
  zmq::socket_t		z_socket;
};

ZmqSub::ZmqSub():z_context(1), z_socket(z_context, ZMQ_PULL), _host("127.0.0.1"), _port(5555), _topics({"A", "B", "C"})
{
}

void ZmqSub::connect()
{
	char uri[100];
	sprintf(uri, "tcp://%s:%d", _host.c_str(), _port);
	trace("Connecting to: " << uri);
	z_socket.connect(uri);
	for(auto it=_topics.begin(); it!=_topics.end(); it++)
	{
		//std::string topic = *it;
		//trace("Subscribing to topic: " << topic);
		//z_socket.setsockopt(ZMQ_SUBSCRIBE, topic.c_str(), topic.size());
	}
}

void ZmqSub::disconnect()
{
	z_socket.disconnect("");
}

bool ZmqSub::isConnected()
{
	return z_socket.connected();
}

void ZmqSub::subscribe(std::function<void(const std::string&, const char* buffer, int size)>callback)
{
	trace("");
  while(true)
  {
    zmq::message_t env;
    z_socket.recv(&env);
    std::string env_str = std::string(static_cast<char*>(env.data()), env.size());
    trace("Received envelope " << env_str);

    zmq::message_t msg;
    z_socket.recv(&msg);
    std::string msg_str = std::string(static_cast<char*>(msg.data()), msg.size());
    trace("Received " << msg_str);
		callback(env_str, (const char*)msg.data(), msg.size());
  }
}

void ZmqSub::receiver(const std::string& topic, const char* buffer, int size)
{
	std::string msg = std::string(static_cast<const char*>(buffer), size);
	trace("Received;  Topics: " << topic << ", Msg: " << msg);
}

void ZmqSub::run()
{
	subscribe(std::bind(&ZmqSub::receiver, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

int main(int argc, char* argv[])
{
	ZmqSub sub;
	sub.connect();
	sub.run();

	return 0;
}
//int main()
//{
//    zmq::context_t context(1);
//    zmq::socket_t subscriber(context, ZMQ_SUB);
//    subscriber.connect("tcp://localhost:5555");
//    subscriber.setsockopt(ZMQ_SUBSCRIBE, "B", 1);
//
//    while(true)
//    {
//        zmq::message_t env;
//        subscriber.recv(&env);
//        std::string env_str = std::string(static_cast<char*>(env.data()), env.size());
//        std::cout << "Received envelope '" << env_str << "'" << std::endl;
//
//        zmq::message_t msg;
//        subscriber.recv(&msg);
//        std::string msg_str = std::string(static_cast<char*>(msg.data()), msg.size());
//        std::cout << "Received '" << msg_str << "'" << std::endl;
//    }
//    return 0;
//}

//
//  Pubsub envelope subscriber
//
// Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>

//#include "zhelpers.hpp"
//
//int main () {
//    //  Prepare our context and subscriber
//    zmq::context_t context(1);
//    zmq::socket_t subscriber (context, ZMQ_SUB);
//    subscriber.connect("tcp://localhost:5563");
//    subscriber.setsockopt( ZMQ_SUBSCRIBE, "B", 1);
//
//    while (1) {
//
//        //  Read envelope with address
//        std::string address = s_recv (subscriber);
//        //  Read message contents
//        std::string contents = s_recv (subscriber);
//        
//        std::cout << "[" << address << "] " << contents << std::endl;
//    }
//    return 0;
//}

