// g++ -w -o nyse nyse.cpp --std=c++17 -lpthread && ./nyse n1
// g++ nyse.cpp -g -w --std=c++17 -lpthread && ./a.out n1
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

/**
1.       Write a program that does the following:
Read a double precision number (from stdin) and print the smallest number that is larger than 95% of numbers encountered so far.
Run program on input size = 128,000,000 and provide the time taken. Provide the time taken for this random input along with the solution.
**/

// sort it (use priority Q for example)
// using Nearest Rank method: n = 0.95*N
#include <random>
namespace n1
{
void test()
{
	trace("");
	unsigned int SIZE = 10;
	std::vector<double> vrn(SIZE);
	for(int i=0; i<SIZE; i++){
		std::default_random_engine re;
		double drnd = double(rand())/ (double(RAND_MAX) + 1.0);
		//vrn.push_back(drnd);
		vrn[i] = drnd;
		printf("\ni(%d) = %f", i, drnd);
	}
	trace("");
	//print(vrn);
	int i =0;
	auto itr = vrn.begin();
	while(itr != vrn.end()){
		printf("\ni(%d) = %f", i++, *itr);
		++itr;
	}
}

}	// n1


/**
2.       You have a set of parquet tiles of size 3x1 and 2x1 length units.
Parquet tiles are always laid out in strips, for instance 3223 is a strip of length 10.
When two strips are adjacent, no two tiles can share an inner edge. 
For instance, strips 3223 and 3322 both start with a 3 so they cannot be neighbors.
But strips 3223 and 22222 of length 10 can be neighbors because they don't share inner edges.
Write a program in C/C++, that does the following:
Find the total number of floor designs which have 11 strips of length 30.  Provide the answer with the solution.
**/
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

