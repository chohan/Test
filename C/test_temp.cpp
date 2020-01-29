// g++ test_temp -o test -g -w --std=c++17 -I/boost_1_70_0 -L/boost_1_70_0/stage/lib -L/usr/local/lib -lboost_thread -lpthread
// -I/d/ThirdParty/C++/zeromq/cppzmq -lzmq
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
#include <bitset>

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
#include <cstdarg>

#define trace(str)(std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << "(): " << str << std::endl)
template<typename T> void print(T coll){for(auto x:coll)std::cout<<x<<" "; std::cout<<std::endl;}



namespace n1{
void test(int argc, char** argv){
	trace("n1::"<<__FUNCTION__);
}
}


namespace n2{
void test(int argc, char** argv){
	trace("n2::"<<__FUNCTION__);
}
}


namespace n3{
void test(int argc, char** argv){
	trace("n3::"<<__FUNCTION__);
	trace("");
}
}


int test(int argc, char* argv[])
{
	trace("");
}


int main(int argc, char** argv)
{
	std::cout << "Bismillah" << std::endl;
	n1::test(argc, argv);
	n2::test(argc, argv);
	n3::test(argc, argv);
	test(argc, argv);

	return true;
}

