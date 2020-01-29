// g++ test_struct_in_out.cpp -g -w --std=c++17 -lpthread && ./a.out
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#define trace(str)(std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << "(): " << str << std::endl)


struct A
{
	int a;
	std::string s;
	float f = 3.14;
};

void f1(A aa)
{
	std::cout << "A.a="<<aa.a << ", A.s="<<aa.s << ", A.f="<<aa.f << std::endl;
}

int main(int argc, char* argv[])
{
	trace("786");
	A aa = {11, "Salah Chohan", 34.4555};
	f1(aa);
	f1({22, "Shamim", 34.6789});

	return 0;
}
