// g++ test2.cpp -g -w --std=c++17 -lpthread
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>

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
#define MESSAGE_START 0xAAAA
#define INVALID_TRACK_FLOAT -99999.0
#define INVALID_TRACK_INTEGER -99999
#define PAYLOAD_SIZE_WIDTH 10


void func1(std::ostringstream str)
{
	std::cout << str.str() << std::endl;
}

int main(int argc, char** argv)
{
	std::cout << "Bismillah\n";
	
	char str[PAYLOAD_SIZE_WIDTH];
	int payload_size = 285;
	sprintf(str, "%10d", payload_size);
	std::cout << str << std::endl;
	//std::cout << std::setw(10) << std::setfill(' ') << str << std::endl;
}

