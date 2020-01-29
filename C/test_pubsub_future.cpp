// g++ -g -Wall -o test test.cpp -lpthread
#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <chrono>
#define trace(str)(std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << "(): " << str << std::endl)

void pub(std::promise<int>* pPromise)
{
	trace("");
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	//for(int i=0; i<10; i++)	// cannot recyle future/promise
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		pPromise->set_value(444);
	}
}

void sub(std::future<int>* pFuture)
{
	trace("");
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	//for(int i=0; i<10; i++) // cannot recyle future/promise
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		int value = pFuture->get();
		std::cout << "Future value=" << value << std::endl;
	}
}
#include "Message.h"

int main(int argc, char** argv)
{
	std::cout << "Bismillah" << std::endl;

	std::promise<int> oPromise;
	std::future<int> oFuture = oPromise.get_future();
	std::thread thPub(pub, &oPromise);
	std::thread thSub(sub, &oFuture);
	thPub.join();
	thSub.join();

	std::cout << "__FLOAT_WORD_ORDER__="<< __FLOAT_WORD_ORDER__ << std::endl;
	std::cout << "__ORDER_LITTLE_ENDIAN__=" << __ORDER_LITTLE_ENDIAN__ << std::endl;
	std::cout << "__ORDER_BIG_ENDIAN__=" << __ORDER_BIG_ENDIAN__ << std::endl;

	TrackMsg track;
	std::cout << "size=" << sizeof(track) << std::endl;

	return true;
}

