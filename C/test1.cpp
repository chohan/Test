// g++ -g -w -o test1 test1.cpp --std=c++17 -lpthread && ./test1 algo
// g++ test1.cpp -g -w --std=c++17 -lpthread
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


// ./test macros
void macros(int argc, char** argv)
{
	std::cout << "__FLOAT_WORD_ORDER__="<< __FLOAT_WORD_ORDER__ << std::endl;
	std::cout << "__ORDER_LITTLE_ENDIAN__=" << __ORDER_LITTLE_ENDIAN__ << std::endl;
	std::cout << "__ORDER_BIG_ENDIAN__=" << __ORDER_BIG_ENDIAN__ << std::endl;
}

// ./test pilandrome 1234
void pilandrome(int argc, char** argv)
{
	//int num = atoi(argv[2]);
	int num = std::stoi(std::string(argv[2]));
	trace("num=" << num);
	assert(num>=0);
	int rev=0;
	while(num != 0){
		rev = rev*10 + num%10;
		num /= 10;
		//std::cout << "rev=" << rev << ", num=" << num << std::endl;
		//std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	std::cout << "num="<<argv[2] << ", rev="<<rev << std::endl;;
}

//this function returns prime number equal to or greater than N
// ./test PrimeNumber 101
unsigned long NextPrimeNumber(uint64_t N)
{
	switch(N)
	{
	case 0: return 1;
	case 1: return 1;
	case 2: return 2;
	case 3: return 3;
	case 4: return 5;
	case 5: return 5;
	}

	//convert into odd if even
	unsigned long NN = (N%2)? N:N+1;
	unsigned long D = 3;
	while(D<=sqrt((double)NN))
	{
		if(NN%D==0)
		{
			NN = ((NN+2)%5)? NN+2 : NN+4;
			D = 3;
			continue;
		}
		D += 2;
	}
	return NN;
}
unsigned long NextPrimeNumber(int args, char** argv)
{
	uint64_t N = std::stoi(std::string(argv[2]));
	uint64_t NN= NextPrimeNumber(N);
	std::cout << "Prime > " << N << " is " << NN << std::endl;
}


// ./test Factorize 24
void Factorize(int args, char** argv)
{
	uint64_t N = std::stoi(std::string(argv[2]));

	//for smaller number just give number
	if(N<4)
	{
		std::cout << N << "=" << N << std::endl;
		return;
	}

	std::list<unsigned long> factors;	//list containing factors
	unsigned long Q = N;	//Q will be sub number whose factor is needed
	unsigned long P = 2;	//prime numbers making factors
	unsigned long X = 1;
	//while(P<=(N/2.0))
	while(P<=sqrt(N))
	{
		//std::cout << "          Q=" << Q << ", P=" << P << std::endl;
		if((Q%P)==0)
		{
			factors.push_back(P);
			X *= P;

			if(X==N)break;	//if product of all factors is equal to initial number then break
			
			Q = Q/P;
			continue;
		}
		P = NextPrimeNumber(P+1);	//get next prime number
	}

	//if it is a prime number
	if(factors.size()==0)
	{
		std::cout << N << "=" << N << std::endl;
		return;
	}

	//printing the results
	std::list<unsigned long>::iterator itr = factors.begin();
	std::cout << N << "=" << *itr;
	++itr;
	while(itr!=factors.end())
	{
		std::cout << "x" << *itr;
		++itr;
	}
	std::cout << std::endl;
}

// ./test sizeOfArray
void sizeOfArray(int argc, char** argv)
{
	int a[10];
	std::cout << "size=" << std::size(a) << std::endl;	// only in C++17
	std::cout << "size=" << std::end(a) - std::begin(a) << std::endl;
	std::cout << "size=" << sizeof(a)/sizeof(a[0]) << std::endl;
}

// ./test bsearch 6 2 1 2 4 6 7 8 9
void bsearch(int argc, char** argv)
{
	int item = atoi(argv[2]);	// item to search 6
	int start= atoi(argv[3]); // starting index 2
	std::vector<int> arr;			// array containing sorted llst 1 2 4 6 7 8 9
	for(int i=4; i<argc; i++){arr.push_back(atoi(argv[i]));}
	
	int L=start; 
	int R=arr.size()-1;
	while(L<R){
		int M = (L+R)/2;
		if(arr[M] < item){ L=M+1; }
		else{ R=M; }
	}
	std::cout << "item index:" << ((L == R && arr[L] == item) ? L : -1) << std::endl;
}

// ./test mytuple
void mytuple(int argc, char** argv)
{
	std::tuple<int, char> foo (10, 'x');
	std::cout << "foo " << std::get<0>(foo) << " " << std::get<1>(foo) << std::endl;

	auto bar = std::make_tuple("test", 3.1, 14, 'y');
	std::get<2>(bar) = 100;
	std::apply([](auto&&... args){((std::cout << args << '\n'), ...);}, bar);
	std::cout << std::endl;
}


// ./test virtual
namespace virtu
{
class B
{//public:
	virtual void f1();
	int n=77;
};
void B::f1() {std::cout << "this is B::f1()\n";}

class Base
{public:
	Base(){std::cout << "Base ctor\n";}
	virtual ~Base(){std::cout << "Base dtor\n";}
	virtual void func(){std::cout << "Base func()\n";}
};
class Derived:public Base
{public:
	Derived(){std::cout << "Derived ctor\n";}
	~Derived(){std::cout << "Derived dtor\n";}
	void func(){std::cout << "Derived func()\n";}
};

void test(int argc, char** argv)
{
	B* pb = new B();
	//pb->n = 10;
	size_t* vptr = *(size_t**)pb;
	void (*pvf1)(void) = (void(*)(void))(pb->_vptr[0]);
	pvf1();
	void (*pvf2)(void) = (void(*)(void))(vptr[0]);
	pvf2();
	std::cout << "B::n=" << (*(vptr+16)) 
			<< ", pb->_vptr=" << pb->_vptr 
			<< ", pb=" << pb
			<< "\n pb+0="  << pb+0  << " " << *(int*)(pb+0)
			<< "\n pb+4="  << pb+4  << " " << *(int*)(pb+4)
			<< "\n pb+8="  << pb+8  << " " << *(int*)(pb+8)
			<< "\n pb+12=" << pb+12 << " " << *(int*)(pb+12)
			<< "\n pb+16=" << pb+16 << " " << *(int*)(pb+16)
			<< "\n pb+20=" << pb+20 << " " << *(int*)(pb+20)
//			<< "\n offset of n=" << offsetof(B,n)
			<<std::endl;
	delete pb;

	Base *pBase = new Derived;
	delete pBase;
}
}


namespace my_print
{
#include<stdio.h> 
#include<stdarg.h>						
int __printf (const char *format, ...)
{
   va_list arg;
   int done;

   va_start (arg, format);
   done = vfprintf (stdout, format, arg);
   va_end (arg);

   return done;
}

void test(int argc, char** argv)
{
	__printf("\nThis is my own printf=%s, Version=%f\n", "Bismillah", 1.0);
}
}


// ./test factorial
namespace factorial
{
	long fact(int n){ return ((n==2)? 2: n*fact(n-1)); }
	void factorial(int argc, char** argv){
		int n;
		std::cout << "\nPlease enter the number: ";
		while((std::cin >> n) && (n>1)){
			std::cout << "factorial of " << n << " is " << fact(n) << std::endl;
			std::cout << "\nPlease enter the number: ";
		}
	}
}


namespace test
{
void test(int argc, char** argv)
{
	trace("");

}
}

namespace n1{
class A{ public:
	virtual void g(){printf("A::g()\n");}
};
class B:public A{ public: 
	void g(){printf("B::g()\n");}
};
void test(){
	trace("n1::"<<__FUNCTION__);
	A* pA = new B();
	pA->g();
}
}

namespace n2{
class B{ public:
	B(){i=3;}
	int i;
};
class C: virtual public B{};
class D: virtual public B{};
class Z:public C, public D{};
void test(){
	trace("n2::"<<__FUNCTION__);
	Z z;
	C* pC = &z;
	D* pD = &z;
	pC->i=7;
	std::cout << z.i << std::endl;
}
}


namespace n3{
class A{public:
	A(){i =getValue();}
	virtual int getValue(){return 1;}
	int i;
};
class B: public A{public:
	B():A(){}
	int getValue(){return 2;}
};
void test(){
	trace("n3::"<<__FUNCTION__);
	B* pB = new B();
	std::cout << pB->i << std::endl;
}
}

namespace n4{
class A{public:
	A(){std::cout << "A ctor" << std::endl;}
	~A(){std::cout << "A dtor" << std::endl;}
};
class B: public A{public:
	B(){std::cout << "B ctor" << std::endl;}
	~B(){std::cout << "B dtor" << std::endl;}
};
void test(){
	trace("n4::"<<__FUNCTION__);
	A* pA = new B();
	delete pA;
}
}

namespace n5{
class A{public:
	A() {std::cout << "A ctor\n";}
	~A(){std::cout << "A dtor\n";}
};
class B{public:
	B() {std::cout << "B ctor\n";}
	~B(){std::cout << "B dtor\n";}
};
class C{public:
	C() {std::cout << "C ctor\n";}
	~C(){std::cout << "C dtor\n";}
};
class D{public:
	D():a(), b(), c() {}
	B b;
	A a;
	C c;
};
class E{public:
	E() {std::cout << "E ctor\n"; delete this; }//this->~E();}
	~E(){std::cout << "E dtor\n";}
	int ID;
	char state[3];
	int salary;
};
void test(){
	trace("n5::"<<__FUNCTION__);
	D* pD = new D();
	delete pD;
//	E e;
	std::cout << "size of E=" << sizeof(E) << std::endl;
}
}

namespace t1
{
class A
{public:
	//int a{0};
	//static void m1(){std::cout << __FUNCTION__ << std::endl;}
	void m2(){std::cout << __FUNCTION__ << std::endl;}
};

void test()
{
	int arr[3] = {10,34,12};
	std::cout << "0[arr]="<< 0[arr] 
						<< ", 1[arr]="<<1[arr] << ", 2[arr]="<< 2[arr] << std::endl;

	A *a = 0;//nullptr;
	//a->m1();
	a->m2();		// how is is possible??????????????????????????
}

int fib(int x)
{
	if(x==0) return 0;
	if(x==1) return 1;
	return (fib(x-1) + fib(x-2));
}

 void bit_count()
 {
	 uint64_t N;
	 std::cout << "\nPlease enter the number: ";
	 while((std::cin >> N) && (N>0)){

		std::bitset<64> bs(N);
		std::cout << "No of bits: " << bs.count() << std::endl;

		int count = 0;
		while(N){
			count += N & 1;
			N >>= 1;
		}
		std::cout << "\nbits=" << count;
	 	std::cout << "\nPlease enter the number: ";
	}
}

}	// namespace t1

namespace varg
{

void logg(const char* type, const char* fmt...)
{
    va_list args;
    va_start(args, fmt);
std::cout << "No of args: " << args.size() << std::endl;

	std::ostringstream oss;
	oss << type;
 
    while (*fmt != '\0') {
        if (*fmt == 'd') {
            int i = va_arg(args, int);
            std::cout << i << '\n';
						oss << ", " << i;
        } else if (*fmt == 'c') {
            // note automatic conversion to integral type
            int c = va_arg(args, int);
            std::cout << static_cast<char>(c) << '\n';
						oss << ", " << static_cast<char>(c);
        } else if (*fmt == 'f') {
            double d = va_arg(args, double);
            std::cout << d << '\n';
						oss << ", " << d;
        }
        ++fmt;
    }
 
    va_end(args);
		std::cout << "\n" << oss.str() << std::endl;
}

int test(int argc, char* argv[])
{
	logg("INFO", "dcff", 3, 'a', 1.999, 42.5);
	logg("INFO", "dcff");
}

}	// varg

#define showlist(...) puts(#__VA_ARGS__)
int main(int argc, char** argv)
{
	std::cout << "Bismillah" << std::endl;
	int data_size = 0;
	char* data=0;
	data = (char*)malloc(data_size);
	//std::cout << "found " << (unsigned int)data << std::endl;
	char sSize[6];
	std::string str("afasdf adsfas dfsadfasdfas ");
	sprintf(sSize, "%05d", str.size());
	trace(sSize);
	int size = std::strlen(sSize);
	n1::test();
	n2::test();
	n3::test();
	n4::test();
	n5::test();
	t1::test();
	std::cout << "No of bits: " << __builtin_popcountll(0xaa) << std::endl;
//	for(int i=0; i<45; i++){ printf("i=%d  %d\n", i, t1::fib(i)); }
//	return 0;


	//return true;
	if(argc < 2) { trace("insufficient No of parameters."); return false;}
	else if(memcmp(argv[1], "macros", strlen("macros")) == 0)						macros(argc, argv);
	else if(memcmp(argv[1], "pilandrome", strlen("pilandrome")) == 0)		pilandrome(argc, argv);
	else if(memcmp(argv[1], "Prime", strlen("Prime")) == 0)	NextPrimeNumber(argc, argv);
	else if(memcmp(argv[1], "Factorize", strlen("Factorize")) == 0)	Factorize(argc, argv);
	else if(memcmp(argv[1], "sizeOfArray", strlen("sizeOfArray")) == 0)	sizeOfArray(argc, argv);
	else if(memcmp(argv[1], "bsearch", strlen("bsearch")) == 0)	bsearch(argc, argv);
	else if(memcmp(argv[1], "mytuple", strlen("mytuple")) == 0)	mytuple(argc, argv);
	else if(memcmp(argv[1], "virtual", strlen("virtual")) == 0)	virtu::test(argc, argv);
	else if(memcmp(argv[1], "factorial", strlen("factorial")) == 0)	factorial::factorial(argc, argv);
	else if(memcmp(argv[1], "test", strlen("test")) == 0)	test::test(argc, argv);
	else if(memcmp(argv[1], "print", strlen("print")) == 0)	my_print::test(argc, argv);
	else if(memcmp(argv[1], "bitcount", strlen("bitcount")) == 0)	t1::bit_count();
	else if(memcmp(argv[1], "varg", strlen("varg")) == 0)	varg::test(argc, argv);


	return true;

}

