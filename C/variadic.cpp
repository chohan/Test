// g++ -w -o variadic variadic.cpp --std=c++17 -fpermissive

#include <iostream>
#include <sstream>
#include <cstdarg>
#define trace(str)(std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << "(): " << str << std::endl)

template<class... Args>
void logg(char* cat, Args... args)
{
	//(std::cout << ... << args) << std::endl;
	std::ostringstream oss;
	(oss << ... << args) << std::endl;
	std::cout << cat << "###" << oss.str();
}

void log2(char* type, const char* format, ...)
{
  char buffer[256];
  va_list args;
  va_start (args, format);
  int size = vsnprintf (buffer,256,format, args);
  perror (buffer);
  va_end (args);

	std::cout << "size="<< size << std::endl;
	char* buf = new char[size+1];
	//char buf[123];
  va_start (args, format);
	vsprintf(buf, format, args);
  va_end (args);

	std::cout << buf << std::endl;
	delete[] buf;
}
int main(int argc, char* argv[])
{
	logg("INFO", 1, ":", " Hello", ',', " ", "World!", 4.56788);
	log2("INFO", "%s, float=%f, int=%d", "Bismillah", 45.67, 8888);
	
	return 0;
}

