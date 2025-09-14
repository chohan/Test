#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <deque>

namespace MultiThreading_Event
{
	const int THREADCOUNTPUB = 1;
	HANDLE hThreadPub[THREADCOUNTPUB];
	const int THREADCOUNTSUB = 1;
	HANDLE hThreadSub[THREADCOUNTSUB];

	DWORD dwThIdPublisher;
	DWORD dwThIdSubscriber;
	HANDLE	hEventPublisher;
	HANDLE	hEventSubscriber;
	std::deque<int> v;
	int val;


	DWORD ThPublisher(LPVOID lpParam)
	{
		std::cout << "Publisher thread is called" << std::endl;
		while(true)
		{
			//WaitForSingleObject(hEventSubscriber, INFINITE);
			WaitForMultipleObjects(THREADCOUNTSUB, hThreadSub, TRUE, INFINITE);
			ResetEvent(hEventPublisher);
			{
				v.push_back(++val);
				std::cout << "Publisher  i=" << val << " ThId=" << GetCurrentThreadId() << std::endl;
			}
			SetEvent(hEventPublisher);
		}
		return 0;
	}

	DWORD ThSubscriber(LPVOID lpParam)
	{
		int* pv = reinterpret_cast<int*>(lpParam);
		int iThCount = *pv;
		std::cout << "Subscriber thread is called" << std::endl;
		while(true)
		{
			Sleep(100);
			WaitForSingleObject(hEventPublisher, INFINITE);
			//HANDLE handle = GetCurrentThread();
			//ResetEvent(hEventSubscriber);
			ResetEvent(hThreadSub[iThCount]);
			{
				while(v.size()>0)
				{
					int i = v.front();
					v.pop_front();
					std::cout << "Subscriber i=" << i << " ThId=" << GetCurrentThreadId() << " Thread Count=" << iThCount << std::endl;
				}
			}
			//SetEvent(hEventSubscriber);
			SetEvent(hThreadSub[iThCount]);
		}
		return 0;
	}

	void f1()
	{
		std::cout << __FUNCTION__ << std::endl;
		val = 0;
		hEventPublisher = CreateEvent(NULL, TRUE, FALSE, L"Publisher");
		hEventSubscriber= CreateEvent(NULL, TRUE, TRUE, L"Subscriber");

		//publisher thread
		for(int i=0; i<THREADCOUNTPUB; i++)
		{
			hThreadSub[i] = CreateEvent(NULL, TRUE, TRUE, L"Subscriber");
			HANDLE h = CreateThread(NULL, //Choose default security
							0, //Default stack size
							(LPTHREAD_START_ROUTINE)&ThPublisher,//Routine to execute
							(LPVOID) &i, //Thread parameter
							0, //Immediately run the thread
							&dwThIdPublisher //Thread Id
				);
			if(h == NULL)
			{ std::cout << "Error Creating Publisher Thread" << std::endl; }
			else { std::cout << "Success creating Publisher thread, count=" << i << std::endl; }
		}

		//subscriber thread
		for(int i=0; i<THREADCOUNTSUB; i++)
		{
			hThreadSub[i] = CreateThread(NULL, //Choose default security
							0, //Default stack size
							(LPTHREAD_START_ROUTINE)&ThSubscriber,//Routine to execute
							(LPVOID) &i, //Thread parameter
							0, //Immediately run the thread
							&dwThIdPublisher //Thread Id
				);
			if(hThreadSub[i] == NULL)
			{ std::cout << "Error Creating Subscriber Thread" << std::endl; }
			else { std::cout << "Success creating Subscriber thread, count=" << i << std::endl; }
		}

		// Close thread and semaphore handles
		Sleep(5000);
		for(int i=0; i < THREADCOUNTPUB; i++ )
			CloseHandle(hThreadPub[i]);
		for(int i=0; i < THREADCOUNTSUB; i++ )
			CloseHandle(hThreadSub[i]);
	}
}

namespace MultiThreading_CriticalSection
{
	DWORD dwThIdPublisher;
	DWORD dwThIdSubscriber;
	const int THREADCOUNTPUB = 10;
	HANDLE hThPub[THREADCOUNTPUB];
	const int THREADCOUNTSUB = 10;
	HANDLE hThSub[THREADCOUNTSUB];
	DWORD dwWaitResult;
	std::deque<int> v;
	int val;
	CRITICAL_SECTION crs;

	HANDLE	hEvent;

	DWORD ThPublisher(LPVOID lpParam)
	{
		int* pi = reinterpret_cast<int*>(lpParam);
		int iThId = *pi;
		std::cout << "Publisher thread, ThId=" << iThId << std::endl;
		while(true)
		{
			//add an element to array
			//WaitForSingleObject(hEvent, INFINITE);
			//ResetEvent(hEvent);
			EnterCriticalSection(&crs);
			{
				//std::cout << "inside PCS" << std::endl;
				v.push_back(++val);
				std::cout << "Publisher  i=" << val << " ThId=" << iThId << std::endl;
			}
			LeaveCriticalSection(&crs);
			Sleep(50);
		}
		//set event to notify subscriber thread
		return 0;
	}

	DWORD ThSubscriber(LPVOID lpParam)
	{
		int* pi = reinterpret_cast<int*>(lpParam);
		int iThId = *pi;
		std::cout << "Subscriber thread, ThId=" << iThId << std::endl;
		while(true)
		{
			//remove elements from array
			//set event to notify publisher thread
			EnterCriticalSection(&crs);
			{
				//std::cout << "inside SCS" << std::endl;
				while(v.size()>0)
				{
					int i = v.front();
					v.pop_front();
					std::cout << "Subscriber i=" << i << " ThId=" << iThId << std::endl;
				}
			}
			LeaveCriticalSection(&crs);
			Sleep(50);
			//SetEvent(hEvent);
		}
		return 0;
	}

	void f1()
	{
		val=0;
		std::cout << __FUNCTION__ << std::endl;
		InitializeCriticalSection(&crs);
		hEvent = CreateEvent(NULL, TRUE, FALSE, L"TickReceived");

		//publisher thread
		for(int i=0; i<THREADCOUNTPUB; i++)
		{
			if (CreateThread(NULL, //Choose default security
				0, //Default stack size
				(LPTHREAD_START_ROUTINE)&ThPublisher,//Routine to execute
				(LPVOID) &i, //Thread parameter
				0, //Immediately run the thread
				&dwThIdPublisher //Thread Id
				) == NULL)
			{ std::cout << "Error Creating Publisher Thread" << std::endl; }
			else { std::cout << "Success creating Publisher thread" << std::endl; }
		}

		//subscriber thread
		for(int i=0; i<THREADCOUNTSUB; i++)
		{
			if (CreateThread(NULL, //Choose default security
				0, //Default stack size
				(LPTHREAD_START_ROUTINE)&ThSubscriber,//Routine to execute
				(LPVOID) &i, //Thread parameter
				0, //Immediately run the thread
				&dwThIdSubscriber //Thread Id
				) == NULL)
			{ std::cout << "Error Creating Subscriber Thread" << std::endl; }
			else { std::cout << "Success creating Subscriber thread" << std::endl; }
		}

		Sleep(3000);
		DeleteCriticalSection(&crs);
		CloseHandle(hEvent);
	}
}

namespace MultiThreading_Mutex
{
	DWORD dwThIdPublisher;
	DWORD dwThIdSubscriber;
	const int THREADCOUNTPUB = 10;
	HANDLE hThPub[THREADCOUNTPUB];
	const int THREADCOUNTSUB = 10;
	HANDLE hThSub[THREADCOUNTSUB];
	DWORD dwWaitResult;
	std::deque<int> v;
	int val;
	HANDLE	g_hMutex;

	DWORD ThPublisher(LPVOID lpParam)
	{
		int* pi = reinterpret_cast<int*>(lpParam);
		int iThId = *pi;
		std::cout << "Publisher thread, ThId=" << iThId << std::endl;
		while(true)
		{
			dwWaitResult = WaitForSingleObject(g_hMutex, INFINITE);
			{
				v.push_back(++val);
				std::cout << "Publisher  i=" << val << " ThId=" << iThId << std::endl;
			}
			ReleaseMutex(g_hMutex);
		}
		return 0;
	}

	DWORD ThSubscriber(LPVOID lpParam)
	{
		int* pi = reinterpret_cast<int*>(lpParam);
		int iThId = *pi;
		std::cout << "Subscriber thread, ThId=" << iThId << std::endl;

		while(true)
		{
			//Sleep(100);
			dwWaitResult = WaitForSingleObject(g_hMutex, INFINITE);
			{
				while(v.size()>0)
				{
					int i = v.front();
					v.pop_front();
					std::cout << "Subscriber i=" << i << " ThId=" << iThId << std::endl;
				}
			}
			ReleaseMutex(g_hMutex);
		}
		return 0;
	}

	void f1()
	{
		val=0;
		std::cout << __FUNCTION__ << std::endl;
		g_hMutex = CreateMutex(NULL, FALSE, L"MyMutex");
		if(g_hMutex == NULL) { std::cout << "failed to create mutex: " << GetLastError() << std::endl;  return; }

		//publisher thread
		for(int i=0; i<THREADCOUNTPUB; i++)
		{
			if (CreateThread(NULL, //Choose default security
				0, //Default stack size
				(LPTHREAD_START_ROUTINE)&ThPublisher,//Routine to execute
				(LPVOID) &i, //Thread parameter
				0, //Immediately run the thread
				&dwThIdPublisher //Thread Id
				) == NULL)
			{ std::cout << "Error Creating Publisher Thread" << std::endl; }
			else { std::cout << "Success creating Publisher thread" << std::endl; }
		}

		//subscriber thread
		for(int i=0; i<THREADCOUNTSUB; i++)
		{
			if (CreateThread(NULL, //Choose default security
				0, //Default stack size
				(LPTHREAD_START_ROUTINE)&ThSubscriber,//Routine to execute
				(LPVOID) &i, //Thread parameter
				0, //Immediately run the thread
				&dwThIdSubscriber //Thread Id
				) == NULL)
			{ std::cout << "Error Creating Subscriber Thread" << std::endl; }
			else { std::cout << "Success creating Subscriber thread" << std::endl; }
		}

		Sleep(3000);
	}
}

namespace MultiThreading_Semaphore
{
	HANDLE	g_hSemPub;
	HANDLE	g_hSemSub;
	HANDLE	g_hEventPub;
	HANDLE	g_hEventSub;
	DWORD dwThIdPublisher;
	DWORD dwThIdSubscriber;

	const int THREADCOUNTPUB = 1;
	HANDLE hThPub[THREADCOUNTPUB];
	const int THREADCOUNTSUB = 10;
	HANDLE hThSub[THREADCOUNTSUB];
	std::deque<int> v;
	int val;


	DWORD ThPublisher(LPVOID lpParam)
	{
		int* pi = reinterpret_cast<int*>(lpParam);
		int iThId = *pi;
		std::cout << "Publisher  thread. ThId=" << iThId << std::endl;
		DWORD dwRes;
		//dwRes = WaitForSingleObject(g_hSemSub, INFINITE);
		//while(dwRes == WAIT_OBJECT_0)
		while((dwRes =  WaitForSingleObject(g_hSemSub, INFINITE)) == WAIT_OBJECT_0)
		{
			//WaitForSingleObject(g_hEventPub, INFINITE);
			{
				v.push_back(++val);
				std::cout << "Publisher  i=" << val << " ThId=" << iThId << std::endl;
			}

			LONG pOldVal;
			ReleaseSemaphore(g_hSemPub, 1, &pOldVal);
			//dwRes = WaitForSingleObject(g_hSemSub, INFINITE);
			Sleep(50);
		}
		return 0;
	}

	DWORD ThSubscriber(LPVOID lpParam)
	{
		int* pi = reinterpret_cast<int*>(lpParam);
		int iThId = *pi;
		std::cout << "Subscriber thread, ThId=" << iThId << std::endl;
		DWORD dwRes;
		//dwRes = WaitForSingleObject(g_hSemPub, INFINITE);
		//while(dwRes == WAIT_OBJECT_0)
		while((dwRes = WaitForSingleObject(g_hSemPub, INFINITE)) == WAIT_OBJECT_0)
		{
			//WaitForSingleObject(g_hEventSub, INFINITE);
			{
				while(v.size()>0)
				{
					int i = v.front();
					v.pop_front();
					std::cout << "Subscriber i=" << i << " ThId=" << iThId << std::endl;
				}
			}
			ReleaseSemaphore(g_hSemSub, 1, 0);
			//dwRes = WaitForSingleObject(g_hSemPub, INFINITE);
			Sleep(50);
		}
		return 0;
	}

	void f1()
	{
		val=0;
		std::cout << __FUNCTION__ << std::endl;
		g_hSemPub = CreateSemaphore(NULL, 0, THREADCOUNTPUB, L"SemPub");
		if(g_hSemPub == NULL) { std::cout << "failed to create SemPub: " << GetLastError() << std::endl;  return; }
		g_hSemSub = CreateSemaphore(NULL, THREADCOUNTSUB, THREADCOUNTSUB, L"SemSub");
		if(g_hSemSub == NULL) { std::cout << "failed to create SemSub: " << GetLastError() << std::endl;  return; }

		g_hEventPub = CreateEvent(NULL, TRUE, FALSE, L"Pub");
		g_hEventSub = CreateEvent(NULL, TRUE, FALSE, L"Sub");

		//publisher thread
		for(int i=0; i<THREADCOUNTPUB; i++)
		{
			hThPub[i] = CreateThread(NULL, //Choose default security
							0, //Default stack size
							(LPTHREAD_START_ROUTINE)&ThPublisher,//Routine to execute
							(LPVOID) &i, //Thread parameter
							0, //Immediately run the thread
							&dwThIdPublisher //Thread Id
				);
			if(hThPub[i] == NULL)
			{ std::cout << "Error Creating Publisher Thread" << std::endl; }
			else { std::cout << "Success creating Publisher thread" << std::endl; }
		}

		//subscriber thread
		for(int i=0; i<THREADCOUNTSUB; i++)
		{
			hThSub[i] = CreateThread(NULL, //Choose default security
							0, //Default stack size
							(LPTHREAD_START_ROUTINE)&ThSubscriber,//Routine to execute
							(LPVOID) &i, //Thread parameter
							0, //Immediately run the thread
							&dwThIdSubscriber //Thread Id
				);
			if(hThSub[i] == NULL)
			{ std::cout << "Error Creating Subscriber Thread" << std::endl; }
			else { std::cout << "Success creating Subscriber thread" << std::endl; }
		}
		SetEvent(g_hEventPub);
		SetEvent(g_hEventSub);

		// Close thread and semaphore handles
		Sleep(1000);
		for(int i=0; i<THREADCOUNTPUB; i++)
			CloseHandle(hThPub[i]);
		for(int i=0; i<THREADCOUNTSUB; i++)
			CloseHandle(hThSub[i]);
	}
}

namespace MultiThreading_NoSynch
{
	DWORD dwThIdPublisher;
	DWORD dwThIdSubscriber;

	const int THREADCOUNTPUB = 10;
	HANDLE hThPub[THREADCOUNTPUB];
	const int THREADCOUNTSUB = 10;
	HANDLE hThSub[THREADCOUNTSUB];
	int val;


	DWORD ThPublisher(LPVOID lpParam)
	{
		int* pi = reinterpret_cast<int*>(lpParam);
		int iThId = *pi;
		std::cout << "Publisher  thread. ThId=" << iThId << std::endl;
		while(true)
		{
			++val;
			std::cout << "Publisher  i=" << val << " ThId=" << iThId << std::endl;
			Sleep(50);
		}
		return 0;
	}

	DWORD ThSubscriber(LPVOID lpParam)
	{
		int* pi = reinterpret_cast<int*>(lpParam);
		int iThId = *pi;
		std::cout << "Subscriber thread, ThId=" << iThId << std::endl;
		while(true)
		{
			std::cout << "Subscriber i=" << val << " ThId=" << iThId << std::endl;
			Sleep(50);
		}
		return 0;
	}

	void f1()
	{
		std::cout << __FUNCTION__ << std::endl;
		val=0;

		//publisher thread
		for(int i=0; i<THREADCOUNTPUB; i++)
		{
			hThPub[i] = CreateThread(NULL, //Choose default security
							0, //Default stack size
							(LPTHREAD_START_ROUTINE)&ThPublisher,//Routine to execute
							(LPVOID) &i, //Thread parameter
							0, //Immediately run the thread
							&dwThIdPublisher //Thread Id
				);
			if(hThPub[i] == NULL)
			{ std::cout << "Error Creating Publisher Thread" << std::endl; }
			else { std::cout << "Success creating Publisher thread" << std::endl; }
		}

		//subscriber thread
		for(int i=0; i<THREADCOUNTSUB; i++)
		{
			hThSub[i] = CreateThread(NULL, //Choose default security
							0, //Default stack size
							(LPTHREAD_START_ROUTINE)&ThSubscriber,//Routine to execute
							(LPVOID) &i, //Thread parameter
							0, //Immediately run the thread
							&dwThIdSubscriber //Thread Id
				);
			if(hThSub[i] == NULL)
			{ std::cout << "Error Creating Subscriber Thread" << std::endl; }
			else { std::cout << "Success creating Subscriber thread" << std::endl; }
		}

		// Close thread and semaphore handles
		Sleep(10000);
		for(int i=0; i<THREADCOUNTPUB; i++)
			CloseHandle(hThPub[i]);
		for(int i=0; i<THREADCOUNTSUB; i++)
			CloseHandle(hThSub[i]);
	}
}

namespace MultiThreading_
{
	void f1()
	{
		std::cout << __FUNCTION__ << std::endl;
	}
}

#include <boost/thread.hpp> 
namespace MultiThreading_Boost
{
 
	void task1() { std::cout << "Thread1 " << std::endl; } 
	void task2() { std::cout << "Thread2 " << std::endl; }
 
	void f1()
	{
		std::cout << __FUNCTION__ << std::endl;
		using namespace boost;  
		thread thread_1 = thread(task1); 
		thread thread_2 = thread(task2); 
 
		// do other stuff 
		thread_2.join(); 
		thread_1.join(); 
	}
}

#include <thread>
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
namespace MT_STL
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
					_sleep(100);
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
					_sleep(100);
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
					_sleep(100);
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
				_sleep(100);
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

	void main1()
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
}	//MT_STL


//////////////////////////////////////////////////////////////////
void main_MultiThreading()
{
	std::cout << "main_MultiThreading" << std::endl;
	//MultiThreading_Event::f1();		//dead locking
	//MultiThreading_CriticalSection::f1();	//working
	//MultiThreading_Mutex::f1();			//working
	//MultiThreading_Semaphore::f1();	//working
	//MultiThreading_Boost::f1();
	//MultiThreading_NoSynch::f1();	//
	MT_STL::main1();
}
