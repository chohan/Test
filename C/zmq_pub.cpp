// g++ zmq_pub.cpp -o zmq_pub -g -w --std=c++17 -I/boost_1_70_0 -I/d/ThirdParty/C++/zeromq/cppzmq -L/boost_1_70_0/stage/lib -L/usr/local/lib -lboost_thread -lpthread -lzmq

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include <boost/format.hpp>
#include <zmq.hpp>
#include <string>
#include <iostream>
#define trace(str)(std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << "(): " << str << std::endl)


class ZmqPub
{
public:
	ZmqPub();
	~ZmqPub() = default;
	void connect();
	void disconnect();
	bool isConnected();
	void publish(const std::string& topic, const std::string& msg);
	void publish(const std::string& topic, const char* buffer, int size);
	void run();

protected:
	std::string _host;
	int _port;
	zmq::context_t  z_context;
	zmq::socket_t		z_socket;
};

ZmqPub::ZmqPub():z_context(1), z_socket(z_context, ZMQ_PUSH), _host("127.0.0.1"), _port(5555)
{
}

void ZmqPub::connect()
{
	char uri[100];
	sprintf(uri, "tcp://%s:%d", _host.c_str(), _port);
	trace(uri);
  z_socket.bind(uri);//"tcp://127.0.0.1:5555");
}

void ZmqPub::disconnect()
{
	z_socket.disconnect("");
}

bool ZmqPub::isConnected()
{
	return z_socket.connected();
}

void ZmqPub::publish(const std::string& topic, const std::string& msg)
{
	publish(topic, msg.data(), msg.size());
}

void ZmqPub::publish(const std::string& topic, const char* buffer, int size)
{
  zmq::message_t env(topic.size());
  memcpy(env.data(), topic.c_str(), topic.size());
  //std::string msg1_str = (boost::format("Hello-%i") % (n + 1)).str();
  zmq::message_t msg(size);
  memcpy(msg.data(), buffer, size);
  trace("Sending topic: " << topic << ", Msg: " << msg);
  z_socket.send(env, ZMQ_SNDMORE);
  z_socket.send(msg);
}

void ZmqPub::run()
{
  boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
	publish("A", "test");
	publish("A", "hello 1");
  boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
	publish("B", "hello 1");
  boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
	publish("A", "hello 2");
  boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
	publish("B", "hello 2");
  boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
	publish("A", "hello 3");
  boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
	publish("B", "hello 3");
  boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
	publish("A", "hello 4");
  boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
	publish("B", "hello 4");
}

int main(int argc, char* argv[])
{
	ZmqPub pub;
	pub.connect();
	pub.run();

  return 0;
}

/*
int main()
{
    zmq::context_t context(1);
    //zmq::socket_t publisher(context, ZMQ_PUB);
    //publisher.bind("tcp://*:5555");
    publisher(context, ZMQ_PUB);
		char uri[100];
		sprintf(uri, "tcp://%s:%d", host, port);
    publisher.bind(uri);

    for(int n = 0; n < 3; n++) {
				std::string msg1 = (boost::format("Hello-%i") % (n + 1)).str();
				publish("A", msg1);
        std::string msg2 = (boost::format("World-%i") % (n + 1)).str();
				publish("B", msg2);

        //zmq::message_t env1(1);
        //memcpy(env1.data(), "A", 1);
        //std::string msg1_str = (boost::format("Hello-%i") % (n + 1)).str();
        //zmq::message_t msg1(msg1_str.size());
        //memcpy(msg1.data(), msg1_str.c_str(), msg1_str.size());
        //std::cout << "Sending '" << msg1_str << "' on topic A" << std::endl;
        //publisher.send(env1, ZMQ_SNDMORE);
        //publisher.send(msg1);

        //zmq::message_t env2(1);
        //memcpy(env2.data(), "B", 1);
        //std::string msg2_str = (boost::format("World-%i") % (n + 1)).str();
        //zmq::message_t msg2(msg2_str.size());
        //memcpy(msg2.data(), msg2_str.c_str(), msg2_str.size());
        //std::cout << "Sending '" << msg2_str << "' on topic B" << std::endl;
        //publisher.send(env2, ZMQ_SNDMORE);
        //publisher.send(msg2);

        boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
    }
    return 0;
}
*/
//
//  Pubsub envelope publisher
//  Note that the zhelpers.h file also provides s_sendmore
//
// Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>

//#include "zhelpers.hpp"
//
//int main () {
//    //  Prepare our context and publisher
//    zmq::context_t context(1);
//    zmq::socket_t publisher(context, ZMQ_PUB);
//    publisher.bind("tcp://*:5563");
//
//    while (1) {
//        //  Write two messages, each with an envelope and content
//        s_sendmore (publisher, "A");
//        s_send (publisher, "We don't want to see this");
//        s_sendmore (publisher, "B");
//        s_send (publisher, "We would like to see this");
//        sleep (1);
//    }
//    return 0;
//}

