// g++ -w -o test test.cpp --std=c++17 -lpthread && ./test n1
// g++ test.cpp -g -w --std=c++17 -lpthread && ./a.out n1
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

#define trace(str)(std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << "(): " << str << std::endl)
template<typename T> void print(T coll){for(auto x:coll)std::cout<<x<<" "; std::cout<<std::endl;}

namespace n1
{
void test()
{
	trace("");
}

}	// n1


namespace n2
{
void test()
{
	trace("");
}

}	// n2


namespace n3
{
void test()
{
	trace("");
}

}	// n3


int main(int argc, char** argv)
{
	std::cout << "Bismillah" << std::endl;

	if(argc < 2) { trace("insufficient No of parameters."); return false;}
	else if(memcmp(argv[1], "n1", strlen("n1")) ==0) n1::test();
	else if(memcmp(argv[1], "n2", strlen("n2")) ==0) n2::test();
	else if(memcmp(argv[1], "n3", strlen("n3")) ==0) n3::test();

	return 0;
}

