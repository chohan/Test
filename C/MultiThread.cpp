// g++ -g -w -o mt MultiThread.cpp --std=c++17 -lpthread && ./test algo
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include <algorithm>
#include <utility>
#include <limits>
#include <iterator>
#include <vector>
#include <list>
#include <tuple>
#include <map>
#include <set>

#include <thread>
#include <mutex>
#include <future>
#include <chrono>

#include <cstdlib>
#include <ctime>
#include <cassert>
#include <cstring>
#include <cmath>
#include <cstddef>

#define trace(str)(std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << "(): " << str << std::endl)
template<typename T> void print(T coll){for(auto x:coll)std::cout<<x<<" "; std::cout<<std::endl;}



// ./test timer
namespace timer
{
std::string asString (const std::chrono::system_clock::time_point& tp)
{
     // convert to system time:
     std::time_t t = std::chrono::system_clock::to_time_t(tp);
     std::string ts = std::ctime(&t);// convert to calendar time
     ts.resize(ts.size()-1);         // skip trailing newline
     return ts;
}

void timer(int args, char** argv)
{
	using time_stamp = std::chrono::time_point<std::chrono::system_clock, std::chrono::microseconds>;
	time_stamp ts = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now());

	std::chrono::system_clock::time_point tp;	
	std::chrono::time_point tpNow = std::chrono::system_clock::now();
	std::chrono::duration te = tpNow - tp;
	long micro = te.count();//tp.duration.count();
	std::cout << "Time=" << micro 
		<< "\nmin=" << asString(std::chrono::system_clock::time_point::min())
		<< "\nmax=" << asString(std::chrono::system_clock::time_point::max())
		<< std::endl;


	using Clock = std::chrono::high_resolution_clock;
	// time to number
	{
		uint64_t sec = std::chrono::duration_cast<std::chrono::seconds>(Clock::now().time_since_epoch()).count();
		uint64_t mls = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now().time_since_epoch()).count();
		uint64_t mcs = std::chrono::duration_cast<std::chrono::microseconds>(Clock::now().time_since_epoch()).count();
		uint64_t ns = std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now().time_since_epoch()).count();

		uint64_t mcs2 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

		std::cout << "\nTime to number"
			<< "\nepoch seconds  ="	<< sec
			<< "\nepoch milli sec=" << mls
			<< "\nepoch micro sec=" << mcs
			<< "\nepoch micro2sec=" << mcs2
			<< "\nepoch nano  sec=" << ns
			<< std::endl;

	}

	// number to time
	{
		uint64_t mls0 = 1553704734072;
		Clock::duration d = std::chrono::milliseconds(mls0);
		std::chrono::time_point<Clock> tp(d);
		uint64_t sec = std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch()).count();
		uint64_t mls = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch()).count();
		uint64_t mcs = std::chrono::duration_cast<std::chrono::microseconds>(tp.time_since_epoch()).count();
		uint64_t ns = std::chrono::duration_cast<std::chrono::nanoseconds>(tp.time_since_epoch()).count();
		std::cout << "\nNumber(" << mls0 << ") to time"
			<< "\nepoch seconds  ="	<< sec
			<< "\nepoch milli sec=" << mls
			<< "\nepoch micro sec=" << mcs
			<< "\nepoch nano  sec=" << ns
			<< std::endl;
	}

	// time elapsed
	{
		std::chrono::time_point start = std::chrono::high_resolution_clock::now();
		for(int i=0; i<1000000; i++);
		std::chrono::time_point finish = std::chrono::high_resolution_clock::now();
		uint64_t mls = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
		std::cout << "\n\nduration in milliseconds=" << mls << std::endl;
	}
}
}   // timer




namespace new_multithreading	// with mutex and atomic
{
class do_work
{
public:
	void operator()() { for (int i = 0; i < 10; i++)	std::cout << "Hello World!"; }
};

std::mutex accum_mutex;
int sum_no_sync = 0;
int sum_synched = 0;
std::atomic<int> atomic_sum(0);
void square(int x, int thrd, int& res) 
{ 
	std::cout << "\nlanuched by thread " << thrd << std::endl;
	int temp = x * x;

	sum_no_sync += temp;

	accum_mutex.lock();
	res += temp;
	accum_mutex.unlock();
	
	atomic_sum += temp;
}

void test_thread()
{
	trace("");
	do_work dw;
	//std::thread th(dw);
	std::thread th(std::ref(dw));	// instead of copying the object, it uses ref
	th.join();

	const int MT = 1250;
	std::vector<std::thread> ths;
	for (int i = 0; i < MT; i++) {
		ths.push_back(std::thread(square, i, i, std::ref(sum_synched)));
	}
	for (auto& th: ths) {th.join();}
	std::cout << "\nsum_no_sync=" << sum_no_sync << std::endl;
	std::cout << "\nsum_synched=" << sum_synched << std::endl;
	std::cout << "\natomic_sum=" << atomic_sum << std::endl;
}

////////////////////// async
int doubler(int x)
{
	return 2*x;
}
void test_async()
{
	trace("");
	const int MT = 5;//1250;
	std::vector<std::future<int>> vf;
	for (int i = 0; i < MT; i++) {
		vf.push_back(std::async(std::launch::async, doubler, i));		//launch::async to ensure separate thread, launch::deferred to defer till future::get is called 
	}
	int sum = 0;
	for (auto& th : vf) {sum += th.get();}
	std::cout << "\nsum=" << sum << std::endl;
}

void task2()
{
	//std::this_thread::sleep_for(std::chrono::seconds(5));
	//for(int j=0; j<1; j++)
	for(int i=0; i<1000000000; i++)
	{
		double x = i*i + 2*i*5/13 - 7*i*59-39/3434*343;
	}
	trace("inside async func");
}
void test_async2()
{
	trace("before async");
	std::async(std::launch::async, task2);
	trace("after func but before lambda");
	std::async([](){
		trace("inside async lambda");
		std::this_thread::sleep_for(std::chrono::seconds(5));
	});
	trace("after async");
	std::this_thread::sleep_for(std::chrono::seconds(10));
}

///////////////////// promise/future
void fp(std::promise<int> * promObj)
{
	std::cout << "Inside Thread" << std::endl;     promObj->set_value(35);
}

int test_future_promise()
{
	trace("");
	std::promise<int> promiseObj;
	std::future<int> futureObj = promiseObj.get_future();
	std::thread th(fp, &promiseObj);
	std::cout << futureObj.get() << std::endl;
	th.join();
	return 0;
}

void test()
{
//	test_thread();
//	test_async();
//	test_future_promise();
	test_async2();
}
}	// new_multithreading


namespace pubsub
{
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

// ./test pubsub
void pubsub(int argc, char** argv)
{
	std::promise<int> oPromise;
	std::future<int> oFuture = oPromise.get_future();
	std::thread thPub(pub, &oPromise);
	std::thread thSub(sub, &oFuture);
	thPub.join();
	thSub.join();
}
}   // pubsub


#include <thread>
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
namespace pubsub2
{
	std::mutex mutex_io;			// mutex for writing to console
	const int UPPER_LIMIT	= 20;	// when producer should stop producing and let consumer start consuming
	const int LOWER_LIMIT	= 10;	// whebn consumder should stop consuming and let producer start producing

	class Storage
	{
	mutable std::mutex mutex_prd_con;	// mutex for producer and consumer
	mutable std::condition_variable cond;

	public:
		Storage()
		{
		}
		void print_msg(const char pc, int threadId, const char* msg) const
		{
			std::unique_lock<std::mutex> lock_io(mutex_io);
			std::cout << pc << "_" << threadId << msg << std::endl;
		}

		void producer1(int threadId, int item) const
		{
			print_msg('P', threadId, " entering...");

			std::unique_lock<std::mutex> lck(mutex_prd_con);
			if(items >= UPPER_LIMIT)
			{
				{ std::unique_lock<std::mutex> lock_io(mutex_io); std::cout << "P_" << threadId << " Buffer is full. Waiting for items to be consumed..." << std::endl; }
				print_msg('P', threadId, " Buffer is full. Waiting for items to be consumed...");
				while(items >= UPPER_LIMIT)
					cond.wait(lck);
			}
			else 
			{
				while(items < UPPER_LIMIT)
				{
					{ std::unique_lock<std::mutex> lock_io(mutex_io); std::cout << "P_" << threadId << " producing..." << items+1 << std::endl; }
					buffer.push_back(items);
					++items;
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
				}
				cond.notify_one();
				{ std::unique_lock<std::mutex> lock_io(mutex_io); std::cout << "P_" << threadId << " exiting..." << std::endl; }
			}
		}

		int consumer1(int threadId)
		{
			{ std::unique_lock<std::mutex> lck(mutex_io); std::cout << "C_" << threadId << " entering..." << std::endl; }
			std::unique_lock<std::mutex> lck(mutex_prd_con);
			if(items < LOWER_LIMIT)
			{
				{ std::unique_lock<std::mutex> lck(mutex_io); std::cout << "C_" << threadId << " Buffer is at deplited level. Waiting replanishment..." << std::endl; }
				while(items <= LOWER_LIMIT)
					cond.wait(lck);
			}
			else
			{
				while(items > LOWER_LIMIT)
				{
					{ std::unique_lock<std::mutex> lck(mutex_io); std::cout << "C_" << threadId << " consuming..." << items << std::endl; }
					int item = buffer.back();
					buffer.pop_back();
					--items;
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
				}
				cond.notify_one();
				//cond.notify_all();
				{ std::unique_lock<std::mutex> lck(mutex_io); std::cout << "get_" << threadId << " exiting..." << std::endl; }
			}

			return 0;
		}

		// same as producer1 but without verbosity
		void porducer2(int threadId)
		{
			std::unique_lock<std::mutex> lck(mutex_prd_con);
			if(items >= UPPER_LIMIT)
			{
				while(items >= UPPER_LIMIT)
					cond.wait(lck);
			}
			else
			{
				while(items < UPPER_LIMIT)
				{
					//keep adding
					items++;
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
				}
				cond.notify_one();
			}
		}

		// same as consumer1 but without verbosity
		void consumer2(int threadId)
		{
			std::unique_lock<std::mutex> lck(mutex_prd_con);
			if(items < LOWER_LIMIT)
			{
				while(items < LOWER_LIMIT)
					cond.wait(lck);
			}
			else
			{
				// keep consuming
				--items;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
			cond.notify_one();
		}

	private:
		mutable std::list<int> buffer;
		mutable unsigned int items;

	};	// Storage

	Storage stg;

	void producer(int threadId, int n)
	{
		//for(auto i=0; i<n; i++)
		{
			stg.producer1(threadId, 0);
			//stg.porducer2(threadId);
		}
	}

	void consumer(int threadId, int n)
	{
		//for(auto i=0; i<n; i++)
		{
			stg.consumer1(threadId);
			//stg.consumer2(threadId);
		}
	}

	void pubsub2(int argc, char** argv)
	{
		const int PRODUCER_THREADS = 10;
		const int CONSUMER_THREADS = 10;
		std::thread producerThreads[PRODUCER_THREADS];
		std::thread consumerThreads[CONSUMER_THREADS];

		for(auto i=0; i<PRODUCER_THREADS; i++)
		{
			producerThreads[i] = std::thread(&producer, i, 3);
		}

		for(auto i=0; i<CONSUMER_THREADS; i++)
		{
			consumerThreads[i] = std::thread(&consumer, i, 3);
		}
		//producerThreads[0].join();
		//consumerThreads[0].join();
		for (auto& th : producerThreads)	th.join();
		for (auto& th : consumerThreads)	th.join();
	}
}	// pubsub2


namespace async
{
int worker(int id)
{
  std::cout << "Inside Worker, called by async\n";
	uint64_t s = 0;
	for(auto i=0;i<1000000; i++){
		s = i*i;
	}
	printf("\nInside Worker: id=%d, s=%d", id, s);
  return 999;
}

void test_worker()
{
  std::future<int> result(std::async(worker, 0));
  std::cout << "Outside worker: " << result.get() << std::endl;

  std::vector<std::future<int>> futures;
  for(int i=0; i<10; ++i){futures.push_back(std::async(std::launch::async, worker, i));}
	//std::this_thread::sleep_for(std::chrono::milliseconds(100));
  //for(int i=0; i<10; ++i){futures.push_back(std::async(std::launch::deferred, worker, i));}
	for(auto &f: futures) f.wait();
	for(auto &f : futures){std::cout << "Outside workder, result from worker: " << f.get() << std::endl;}
	std::cout << "Outside worker, end of test_worker\n\n\n";
}

void test(int argc, char** argv)
{
	test_worker();
  auto start = std::chrono::steady_clock::now();
  std::vector<std::future<int>> futures;
  for(int i=0; i<10; ++i){futures.push_back(std::async([](int a, int b){return a+b;}, i, i));}
  for(auto &f : futures){std::cout << f.get() << std::endl;}
  auto end = std::chrono::steady_clock::now();
  auto diff = end - start;
	std::cout << std::chrono::duration <double, std::milli> (diff).count() << " ms" << std::endl;

}
}   // async


namespace mt_except
{
	static std::exception_ptr globalExceptionPtr = nullptr;

void LaunchRocket()
{
	try{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		throw std::runtime_error("Catch me in call func");
	}catch(...){
		globalExceptionPtr = std::current_exception();
	}
}

void test()
{
	std::thread t1(LaunchRocket);
	t1.join();

	if(globalExceptionPtr){
		try{
			std::rethrow_exception(globalExceptionPtr);
		}catch(const std::exception &ex){
			std::cout << "Thread exited with exception: " << ex.what() << std::endl;
		}
	}
}
}	// mt_except

// ./test once
namespace once
{
std::once_flag flag;

void do_something(){
  std::call_once(flag, [](){std::cout << "Called once" << std::endl;});
  std::cout << "Called each time" << std::endl;
}

int main(){
    std::thread t1(do_something);
    std::thread t2(do_something);
    std::thread t3(do_something);
    std::thread t4(do_something);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}
}


// ./test performance
namespace performance
{

void f1(int id)
{
	uint64_t s = 0;
	for(auto i=0;i<1000000; i++){
		s = i*i;
	}
	printf("\nid=%d, s=%d", id, s);
}

// ./test performance
int test(int argc, char** argv)
{
  typedef std::chrono::high_resolution_clock Clock;
  typedef std::chrono::microseconds micro;
  auto start = Clock::now();

	std::thread t1(f1, 1);
	std::thread t2(f1, 2);
	std::thread t3(f1, 3);
	std::thread t4(f1, 4);
	std::thread t5(f1, 5);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	
  auto finish = Clock::now();
  micro diff = std::chrono::duration_cast<micro>(finish - start);
  std::cout << "\ntime diff (micro sec)=" << diff.count() << std::endl;

  start = Clock::now();
  for(int i=0; i<5; i++) f1(i);
  finish = Clock::now();
  diff = std::chrono::duration_cast<micro>(finish - start);
  std::cout << "\ntime diff (micro sec) No thread=" << diff.count() << std::endl;
}
}   // performance

//std::thread subs_thread([&subscriber, &p, &nrx, &nmsg]() {
//// do something
//});
// subs_thread.join();


int main(int argc, char** argv)
{
	std::cout << "Bismillah" << std::endl;

	if(argc < 2) { trace("insufficient No of parameters."); return false;}
	else if(memcmp(argv[1], "new_multithreading", strlen("new_multithreading")) == 0)		new_multithreading::test();
	else if(memcmp(argv[1], "pubsub2", std::strlen("pubsub2")) == 0)	pubsub2::pubsub2(argc, argv);
	else if(memcmp(argv[1], "pubsub", std::strlen("pubsub")) == 0)	pubsub::pubsub(argc, argv);
	else if(memcmp(argv[1], "timer", strlen("timer")) == 0)	timer::timer(argc, argv);
	else if(memcmp(argv[1], "once", strlen("once")) == 0)	once::main();
	else if(memcmp(argv[1], "performance", strlen("performance")) == 0)	performance::test(argc, argv);
	else if(memcmp(argv[1], "mt_except", strlen("mt_except")) == 0)	mt_except::test();
	else if(memcmp(argv[1], "async", strlen("async")) == 0)	async::test(argc, argv);

    return true;
}
