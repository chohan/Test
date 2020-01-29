// Brainbench.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include <iostream>
#include <string>
#include <typeinfo>
#include <memory>
#include <vector>
#include <iterator>
#include <map>
//#include <hash_map>
#include <functional>   // std::bind2nd
using namespace std;


void q4()
{
	struct A{
		A(int value):m_value(value){}
		int m_value;
	};
	struct B : A{
		B(int value):A(value){}
	};

	try{
		try{
			throw B(5);
		}
		catch(A a){
			a.m_value *= 2;
			throw a;
		}
		//catch(B b){
		//	b.m_value -= 2;
		//	throw b;
		//}
	}
	catch(A a){
		std::cout << a.m_value;	//10
	}
}

void q5()
{
	struct A{
		int i, j;
	public:
		A(int ii, int jj):i(ii),j(jj){}
		A(const A& a)
		{
			std::cout << "(" << a.i << "," << a.j << ")";
		}
		A& operator=(const A& a)
		{
			std::cout << "[" << i << "," << j << "]";
			return *this;
		}
	};

		A x(1,2);
		A y(3,4);
		A z = (x=y);

		//[1,2](1,2)
}

void q6()
{
	typedef basic_streambuf<char> streambuf;
}

void q9()
{
	class ABC
	{
	public:
		void* operator new(size_t size)
		{
			void* ptr = malloc(size);
			if (ptr == NULL)
				throw "bad memory allocation";
			return ptr;
		}

		void operator delete(void* ptr)
		{
			//free ptr;
			std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << std::endl;
		}
	};
}

void q10()
{
	class X{
	public:
		X& operator=(const X& rhs) {return *this;};
		const X& operator+(const X& rhs) const {return *this;};
		const X& operator+(int m) {return *this;};
	private:
		int n;
	};

	X a, b, c;
	//a = b + c + 5;
	a = b + 5;
	a = a = b + c;
	(c = a + a) = b + c;
	a = a + 5 + c;
}

#include <algorithm>
void q11()
{
	int v[1000];
	//std::sort(v);
	std::sort(v, v+1000);
	//std::sort(v.begin(), v.end());
	//std::sort((void*)v, (void*)&v+1000, sizeof(int));
}

void q12()
{
	class X {
		int a;
	public:
		X() { cout << "X() is called" << endl; }
		X(int x) { cout << "X(int x) is called" << endl; }
		~X() { cout << "~X() is called" << endl; }
	};

	X x(3);
}


namespace q13
{
	namespace { static int n; }
	namespace A { 
		namespace {static int n; }
	}
	using namespace A;

	int main2()
	{
		//n = 5;	// n is ambiguous
		return 0;
	}
}

void q14()
{
	class screen;
	//screen sc;//in order to instantiate, you got to have a body of class at least set of curly brackets {}
}

void q14a()
{
	int a;
	std::cout << "cout";
	std::cerr << "cerr";
	std::cin >> a;
	std::clog << "clog";
}

void q15()
{
	class A{public: A(int a){}};
	class B
	{
	public:
		B(A aa): a(aa){}
		//B(A aa, int i) { a(aa); }

		A &a;
	};
}

namespace q16
{
	struct ABC
	{
		virtual void func(){}
	};

	//inline virtual void myfunc(){}

	template<typename T> class ABCD
	{
	public:
		virtual ~ABCD(){}
	};
}

void q16a()
{
	char s[] = "string";
	const int c = 2;
	//char *p;
	char *const cp = s;
	const char *const cpc = s;

	//cpc[3] = 'a';
	cp[3] = 'b';
	//int *p2 = &c;
	//cpc = p;
	//cp = p;
}


namespace q18
{
	class RangeErr{};
	extern void done(int, int) throw(const char*, RangeErr);
}

namespace q18a
{
	class Base 
	{
	public: int a;
	protected: int b;
	private: int c;
	};

	class Derived : public Base
	{
		friend class Friend;
		int d;
	};

	class Friend
	{
		Derived derived;
		void func()
		{
			derived.a = 1;
			derived.b = 2;
			//derived.c = 3;
			derived.d = 4;
		}
	};
}

void q19()
{
	class A{
	public:
		virtual void f() throw(int, char){throw 5;};
	};

	class B : public A {
	public:
		void f() throw(int){};
	};

	class C : public A {
	public:
		void f() throw(int, char, float){};
	};
}

namespace q19b
{
	template<typename T>
	class Foo
	{
		T tVar;
	public:
		Foo(){}	//default constructor is required OR call is non-default constructor in derived class constructor initialization list
		Foo(T t) : tVar(t){}
	};
	class FooDrived : public Foo<std::string>{};
	FooDrived fd;
}

void q20()
{
	extern void print(int *la, int sz);
	void print(int *array,  int size);
}

void q20a()
{
	typedef std::map<int, std::string> MapType;
	MapType theMap;

	MapType::iterator it = theMap.begin();
	while(it != theMap.end())
	{
		std::cout << (*it++).second;	
	}
}

void q21()
{
	class Foo{
	public:
		Foo(){cout << "Foo" << endl;}
	};

	class Bar :  Foo {
	public:
		Bar(){cout << "Bar" << endl;}
	};

	class FooToo : virtual Foo {
	public:
		FooToo(){cout << "FooToo" << endl;}
	};

	class FooTooBar : virtual FooToo, virtual Bar {
	public:
		FooTooBar(){cout << "FooTooBar" << endl;}
	};

//	FooTooBar ftb;	//Foo FooToo Foo Bar FooTooBar
}

namespace Brainbech_q21
{
	class ABC{};
	struct BCD{};
	void func(int a) throw(ABC, BCD, int, char, char*, float){ABC abc; throw abc;}
}

int q22()
{
	int i =12;
	int &r = i;
	r += r/4;
	int *p = &r;
	*p += r;
	return i;	//30
}

void q22b()
{
	class Foo{
public:
	Foo(int i){}
	};

	class Bar : virtual Foo {
	public:
		Bar():Foo(0){}
	};

	Bar b;
}

void q23()
{
	std::string s("Hello World");
	const char *c = s.c_str();
	float f = strlen(c);
}

namespace q24
{
class Airplane{};

std::ostream& operator<<(std::ostream& os, Airplane const& a)
{
	os << "Hello World";
	return os;
}

void do_stuff_and_output(Airplane& a)
{
	std::cout << a << '\n';
}

void mymain()
{
	Airplane a;
	do_stuff_and_output(a);
}

}

namespace q25
{
	namespace N1
	{
		int f(int n){return n*2;}
	}
	namespace N2
	{
		int f(double n){return n*3;}
	}

	void q25()
	{
		using N1::f;
		int i1 = f(1.0);

		using N2::f;
		int i2 = f(1.0);

		std::cout << "i1=" << i1 << ", i2=" << i2 << std::endl;
	}
}

void q25a()
{
	struct B {
		void Go() {std::cout << "B::Go ";}
		void Back() { std::cout << "B::Back ";}
	};

	struct C : public B {
		void Go() {std::cout << "C::Go ";}
	};

	struct D : public B {
		void Back() {std::cout << "D::Back ";}
	};

	B *bd = new D;
	B *bc = new C;
	D d;
	bd->Go();
	bd->Back();
	bc->Go();
	bc->Back();
	d.Go();
}

#include <iostream>
#include <fstream>
void Brainbench_q28()
{
	//write to a file
	std::ofstream fout("test.txt");
	//std::ofstream fout;
	//fout.open("test.txt");
	//fout.open("test.txt", ios::out | ios::app);
	if(fout.is_open())
	{
		fout << "hello world 1" << std::endl;
		fout << "hello world 2" << std::endl;
		fout << "hello world 3" << std::endl;
		fout.close();
	}
	else std::cout << "unable to open the file to write\n";

	//read from a file
	std::ifstream fin("test.txt");
	//std::ifstream fin;
	//fin.open("test.txt");
	//fin.open("test.txt", ios::in);
	std::string line;
	if(fin.is_open())
	{
		while(getline(fin, line))
		{
			std::cout << line << std::endl;
		}
		fin.close();
	}
	else std::cout << "unable to open the file to read\n";
}

namespace q29
{
	void log(std::string message){};

	class Account
	{
	public:
		Account(int id){};
		virtual ~Account();//{log("Destroying: " + get_name());};
		virtual std::string get_name()=0;
		int get_id(){};
	};
	Account::~Account()
	{
		//pure virtual function cannot be called from a destructor	
		//log("Destroying: " + get_name());
	}
}

void q30()
{
	//if inheritance of sub1 to Base and sub2 to Base are both virtual then Base constructor will be called once.
	//if inheritance of multi to sub1 and multi to sub2 are both virtual then Base constructor will be called once
	class Base{public:Base(){cout << "\nBase is called"; };};
	class Sub1:public virtual Base{public:Sub1(){};};
	class Sub2:public Base{public:Sub2(){};};
	class Multi:public Sub1, public Sub2{public:Multi(){};};

	Multi m;	//2
}

namespace Brainbench_q30
{
	class A
	{public: int a; protected: int b; private: int c;
		void func()
		{
//			C c;
			//std::cout << c.c;//this shows friendship is NOT transitive i.e. if A is friend of B and B is fried of C then A is NOT friend of C
		}
	};
	class B{public: int a; protected: int b; private: int c;	friend A; };
	class C{public: int a; protected: int b; private: int c;	friend B; };
}

void q31()
{
	std::vector<int> v;
	for(int i=0; i<25; i++)
		v.push_back(i);
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(cout, " "));
	std::replace_if(v.begin(), v.end(), std::bind2nd(std::less<int>(), 10), 10);
	cout << endl;
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(cout, " "));
}

namespace  q31a
{
	void HandleNoMemory(){std::cout << "HandleNoMemory called" << std::endl;}

	int main0()
	{
		int* p = new int[100];
		if(!p)
		{
			HandleNoMemory();
		}
		std::cout << "sizeof(p)=" << sizeof(p) << std::endl;	//4
		return 0;
	}
//	std::failed_alloc fa;
	//ans: HandleMemory is never called.
}

void q31b()
{
	//repalces all entries less than 10 with 8
	class myclass{public: void operator()(int i){std::cout << i << std::endl;}};
	myclass myobject;

	vector<int> seq;
	seq.push_back(1);
	seq.push_back(3);
	seq.push_back(4);
	seq.push_back(10);
	seq.push_back(14);
	seq.push_back(7);
	seq.push_back(30);
	seq.push_back(15);
	seq.push_back(38);
	seq.push_back(6);

	std::cout << "before replace" << std::endl;
	for_each(seq.begin(), seq.end(), myobject);
	std::replace_if(seq.begin(), seq.end(), std::bind2nd(std::less<int>(), 10), 8);
	std::cout << "after replace" << std::endl;
	for_each(seq.begin(), seq.end(), myobject);
}

#include <iomanip>
void q32()
{
	int n = 18;

	//cout << std::setbase(16) << std::showbase() << n;
	//cout << std::sethex(true) << std::setshowbase(true) << n;
	cout << std::hex << std::showbase << n;
	//cout << std::setbase(16) << n;
	//cout << std::hex() << std::showbase() << n;
}

void q32a()
{
	std::vector<std::string> vs;
	//std::generate_n(std::back_inserter(vs), 5, "hello");
	std::fill_n(std::back_inserter(vs), 5, "hello");

	std::copy(vs.begin(), vs.end(), std::ostream_iterator<std::string>(cout, " "));
}

#include <iomanip>
void q33()
{
	int n = 21;
	std::cout << n << ' '
		<< std::hex << n << ' '
		<< std::dec << n << ' '
		<< std::oct << n << ' '
		<< std::setbase(10) << n << std::endl;	//21 15 21 25 21
}

void q33a()
{
	class A{};
	class B : public A{};

	try{
		throw new B;
	}
	catch(B*){ cout << "b* is caught" << endl;}		//b* is caught
	catch(A*){ cout << "a* is caught" << endl;}		//a* is caught
	catch(B){ cout << "b is caught" << endl;}
	catch(A){ cout << "a is caught" << endl;}
}

void q34()
{
	try{
		throw std::string("4");
	}catch(std::string &s)
	{
		try{
			std::cout << s;
			throw 2;
		}catch(int i)
		{
			std::cout << i;
		}catch(...)
		{
			throw;
		}
		std::cout << "s" + s;
	}catch(...)
	{
		std::cout << "all";
	}
//answer: 42s4
}

void q34a()		//could not replicate
{
	class ABC { int a[0x7ffffff];};
	try
	{
//		ABC *pA = new ABC[100];
//		int *p = new int[0x7ffffff];
	}catch(std::bad_alloc b){std::cout << "std::bad_alloc is caught" << std::endl;}
}

void q35()
{
	class A{
		int i;
	public:
		A(int ii){i=ii;}
		A(const A& a){i=a.i; i++;}
		A& operator=(const A& a){i=a.i; i--; return *this;}
	};

	A a(4);
	A b = a;	//5
}

namespace q36
{
	template<typename T> class DynArray
	{
		T *contents;
		int size;
	public:
		explicit DynArray(int initial_size){};
	};

	void mymain()
	{
		DynArray<std::string> a(7);		//1
		DynArray<std::string> b('7');	//2
	//	DynArray<std::string> c = 7;	//3
		DynArray<std::string> d(a);		//4
		DynArray<std::string> e = b;	//5
	}
}

namespace q37
{
	template<class T1, class T2, class T3>
	int Product(T1 a, T2 b, T3 c)
	{
		return a*b*c;
	}
}

void q37a()
{
	char c = 'c';
	char* str = "abc";
	int i = 10;
	int* p = &i;
	const int* cip;			//non-constant pointer to constannt data
	int* const icp = &i;	//constant pointer to non-constant data

	char const* pc1;		//non-constant pointer to constant data
	const char* pc10;		//non-constant pointer to constant data
// tip: see is 'const' is apearing before or after '*'

	char* const pc2 = &c;	//constant pointer to non-constant data

	pc10 = str;
	pc2[1] = 'c';


	//*icp = 20;
}

void q38(void)
{
	typedef const char *monthTable[3];
	monthTable winter, spring={"March","April","May"};
//	std::copy(winter, winter+2, std::ostream_iterator<std::string>(std::cout, " "));
	std::copy(spring, spring+3, std::ostream_iterator<std::string>(std::cout, " "));
}

void q38a()
{
	class SomeClass{
	public:
		SomeClass(){cout << "SomeClass ctor" << endl;}
	};
	SomeClass *psc = new SomeClass();
	SomeClass *psc2= new SomeClass;
}

void q39(void)
{
	for(int ii=0; ii<3; ++ii)
		switch(ii)
		{
			case 0:std::cout << "ZERO";
			case 1:std::cout << "ONE";continue;
			case 2:std::cout << "TWO"; break;
		}
	std::cout << std::endl;

	//What is the output? (0112)
}





//////////////////////////////////////////////////////////////////
int main_Brainbench()
{
	std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << std::endl;
	//q3();
	//q4();
	//q5();
	//q11();
	//q12();
	//q15();
	//q20();
	//q21();
	//q22();
	//q24::mymain();
	//q25::q25();
	//q25a();
	//Brainbench_q28();
	//q30();
	//q31();
	//q31a::main0();
	//q31b();
	//q32();
	//q32a();
	//q33();
	//q33a();
	//q34();
	//q34a();
	//q35();
	//q38();
	//q38a();

	return 0;
}
