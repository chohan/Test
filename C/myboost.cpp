#include "stdafx.h"
#include <iostream>
using namespace std;


//############ thread ###############################
//http://www.ddj.com/cpp/184401518?pgno=1
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include <boost/bind.hpp>


float val = 555;

//thread safety
void Thread1(void* pVoid)
{
	while(true)
	{
		val = (val + 2)/3;// = val + 5;
		cout << "Th1 " << val << endl;
	}
}

void Thread2(void* pVoid)
{
	while(true)
	{
		val = (val + 3)/2;
		cout << "Th2 " << val << endl;
	}
}
//#include <windows.h>
namespace q125
{
//  void q125()
//  {
//	  DWORD dwThreadID1;
//	  DWORD dwThreadID2;
//	  void* pVoid1=0;
//	  void* pVoid2=0;
//	  HANDLE h1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread1, pVoid1, 0, &dwThreadID1);
//	  HANDLE h2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread2, pVoid2, 0, &dwThreadID2);
//
//	  while(true)
//	  { Sleep(100);
//	  }
//	  
//  }

  void hello()
  {
    for(int i=0; i<10; i++)
    {
      std::cout << "Hello World, I am a thread from boost" << endl;
      boost::xtime xt;
      boost::xtime_get(&xt,boost::TIME_UTC_);
      xt.nsec += 1;
      boost::thread::sleep(xt);
    }
  }
  
  void q125()
  {
    boost::thread thrd(&hello);
    thrd.join();
	//thrd.detach();
  }
  
}

namespace Q1
{
  void hello()
  {
    cout << "786 Hello World" << endl;
  }
  
  void q1()
  {
    boost::thread thrd(&hello);
    thrd.join();
  }
}

namespace Q2
{
boost::mutex io_mutex;

  struct count
  {
    count(int id):id(id){}
    
    void operator()()
    {
      for(int i=0; i<10; i++)
      {
	boost::mutex::scoped_lock lock(io_mutex);
	cout << "id=" << id << " : " << i << endl;
	_sleep(100);
      }
    }
    int id;
  };
  
  void q2()
  {
    boost::thread thrd1(count(1));
    boost::thread thrd2(count(2));
    thrd1.join();
    thrd2.join();
  }

}

namespace Q3
{
  boost::mutex io_mutex;
  
  void count(int id)
  {
    for(int i=0; i<10; i++)
    {
      boost::mutex::scoped_lock lock(io_mutex);
      cout << "id=" << id << " : " << i << endl;
    }
  }
  
  void q3()
  {
    boost::thread thrd1(boost::bind(&count, 1));
    //boost::thread thrd1(&count, 1);
    boost::thread thrd2(boost::bind(&count, 2));
    thrd1.join();
    thrd2.join();
  }
}

namespace Q4
{
  typedef boost::mutex::scoped_lock scoped_lock;
  const int BUF_SIZE = 10;
  const int ITERS = 100;
  boost::mutex io_mutex;

  class buffer
  {
    private:
      boost::mutex mutex;
      boost::condition cond;
      unsigned int p, g, full;
      int buf[BUF_SIZE];
      
    public:
      
      buffer():p(0), g(0), full(0){}
      
	void put(int m)
    {
		{
			scoped_lock lock(io_mutex);
			cout << __FUNCTION__ << " entering.." << endl;
		}
		scoped_lock lock(mutex);
		if(full == BUF_SIZE)
		{
			{
				scoped_lock lock(io_mutex);
				cout << "Buffer is full. Waiting.." << endl;
			}
			while(full == BUF_SIZE)
			cond.wait(lock);
		}
		buf[p] = m;
		p = (p+1)%BUF_SIZE;
		++full;
		cond.notify_one();
		{
			scoped_lock lock(io_mutex);
			cout << __FUNCTION__ << " exiting.." << endl;
		}
	}
      
	int get()
	{
		{
			scoped_lock lock(io_mutex);
			cout << __FUNCTION__ << " entering.." << endl;
		}
		scoped_lock lock(mutex);
		if(full == 0)
		{
		  {
		    scoped_lock lock(io_mutex);
		    cout << "Buffer is empty. Waiting..." << endl;
		  }
		  while(full == 0)
		    cond.wait(lock);
		}
		int n = buf[g];
		g = (g+1)%BUF_SIZE;
		--full;
		cond.notify_one();
		{
			scoped_lock lock(io_mutex);
			cout << __FUNCTION__ << " exiting.." << endl;
		}
		return n;
	}
};
  
  buffer buf;
  
  void writer()
  {
    for(int i=0; i<ITERS; ++i)
    {
      {
		// below lock is to avoid writing in between each other messages
		boost::mutex::scoped_lock lock(io_mutex);
		cout << "sending:" << i << endl;
      }
      buf.put(i);
    }
  }
  
  void reader()
  {
    for(int j=0; j<ITERS; ++j)
    {
      int n = buf.get();
      {
		// below lock is to avoid writing in between each other messages
		boost::mutex::scoped_lock lock(io_mutex);
		cout << "received:" << n << endl;
      }
    }
  }
  
  void q4()
  {
    boost::thread thrd1(&reader);
    boost::thread thrd2(&writer);
    thrd1.join();
    thrd2.join();
  }
      
}
//############ thread ###############################



//############ filesystem ###############################
#include <boost/filesystem.hpp>
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include <boost/filesystem/fstream.hpp>
#include "boost/progress.hpp"
namespace fs = boost::filesystem;
namespace FS1
{
  void fs1()
  {
    fs::path mypath("./");
    if(fs::is_directory(mypath))
    {
		cout << "Current directory=" << mypath.native().c_str() << endl;	//mypath.native_directory_string() << endl;
      fs::directory_iterator end_itr;
      for(fs::directory_iterator itr(mypath); itr!=end_itr; ++itr)
      {
	if(fs::is_directory(itr->status()))
	{
	  cout << "Folder=" << itr->path().filename() << endl;	//itr->filename()
	}
	else if(fs::is_regular_file(itr->status()))
	{
	  cout << "File=" << itr->path().filename() << endl;
	}
	else
	{
	  cout << "Other=" << itr->path().filename() << endl;
	}
      }
    }
    ofstream file("./mytext.txt");
    file << "\n786 Hello World" << endl;
    //cout << file;
    file.close();
  }
}
//############ filesystem ###############################




//############ serialization ###############################
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace SR1
{
  class position
  {
    private:
      float latitude, longitude, altitude;
    public:
    position():latitude(0), longitude(0), altitude(0) {}
    position(float lat, float lng, float alt):latitude(lat), longitude(lng), altitude(alt){}
    void print(){cout << "lat=" << latitude << " lng=" << longitude << " alt=" << altitude << endl;}
    
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & latitude;
      ar & longitude;
      ar & altitude;
    }
  };
  
  class location : public position
  {
    private:
      float speed, direction;
    public:
    location(float lat, float lng, float alt, float spd, float dir)
    : speed(spd), direction(dir), position(lat, lng, alt){}
    
    void print()
    {
      position::print();
      cout << "spead=" << speed << " direction=" << direction << endl;
    }
    
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<position>(*this);
      ar & speed;
      ar & direction;
    }
    
  };
  
  void sr1()
  {
    //serialize
    location loc1(25.25F, 67.67F, 1000, 200, 300);
    ofstream ofs("./sr");
    boost::archive::text_oarchive ar1(ofs);
    ar1 << loc1;
    ofs.close();
    
    //deserialize
    location loc2(0,0,0,0,0);
    loc2.print();
    ifstream ifs("./sr");
    boost::archive::text_iarchive ar2(ifs);
    ar2 >> loc2;
    loc2.print();
    ifs.close();    
  }
}
//############ serialization ###############################


//############ smart pointers ###############################
#include "boost/smart_ptr/shared_ptr.hpp"
namespace t1
{
  class A
  {
  public:
	  A(){cout << "A ctor" << endl; this->f();}
	  ~A(){cout << "A dtor" << endl;}
	  void DoSomething(){cout << "DoSomething is called" << endl;}
	  A& operator=(const A&)
	  { cout << "assignment operator is called." << endl;
	  return *this;
	  }
	  int a;
	  virtual void f(){}
	  //const double sq2 = 5*5;
  };
  
  void t1()
  {//int t[15] = new int*;
	  A a;
	  A b(a);
	  A c;
	  c = a;

	  boost::shared_ptr<A> p1(new A());
	  cout << "Ref count=" << p1.use_count() << endl;

	  boost::shared_ptr<A> p2 = p1;
	  cout << "Ref count p1=" << p1.use_count() << endl;
	  cout << "Ref count p2=" << p2.use_count() << endl;

	  p1.reset();
	  cout << "Ref count p1=" << p1.use_count() << endl;
	  cout << "Ref count p2=" << p2.use_count() << endl;
	  
	  p2->DoSomething();

  }
}
//############ smart pointers ###############################



//############ asio ###############################

//synchronous operation
//boost::asio::io_service io_service;
//boost::asio::ip::tcp::socket socket(io_service);
//boost::system::error_code ec;
//socket.connect(server_endpoint, ec);



//Asynchronous operation
//void your_completion_handler(const boost::system::error_code& ec);
//socket.async_connect(server_endpoint, your_completion_handler);

//############ asio ###############################


void main_myboost()
{
  cout << "main_myboost" << endl;

  //Multi-threading
  //q125::q125();
  //Q1::q1();
  //Q2::q2();
  //Q3::q3();
  Q4::q4();
  
  //File system
  //FS1::fs1();
  
  //Serialization
  //SR1::sr1();
}
