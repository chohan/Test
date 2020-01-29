#include "stdafx.h"
#include <iostream>
#include <iterator>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <functional>
#include <algorithm>
#include <iomanip>
#include <string>
#include <string.h>
using namespace std;



void q3()
{
	class Foo{
	public:
		virtual ~Foo(){}
	};

	class Bar : public Foo {
	};

	class Bar2 : public Foo {
	};

	class FooBar : public Bar {
	};

	class FooBar2 : public Bar2 {
	};

	//Foo &foo1 = static_cast<Foo&>(FooBar2 f);
	Foo &foo2 = dynamic_cast<Foo&>(*(new FooBar2));
	//Foo &foo3 = new FooBar;
	//FooBar2 *fb3 = new Foo;
	//FooBar2 &fb2 = dynamic_cast<Foo&>(new FooBar2);
}












void Previsor3()
{
	std::vector<int> vi(100);

	for(unsigned int i=0; i<100; i++)
		vi[i] = i*i;

	int x = 100;
	std::vector<int>::iterator ix = std::find(vi.begin(), vi.end(), x);

	int y = 7;
	std::vector<int>::iterator iy = std::find(vi.begin(), vi.end(), y);

	if(ix == vi.begin()+10)
		cout << "vi.begin()+10" << endl;
	if(iy == vi.end())
		cout << "vi.end()" << endl;


	cout << "ix=" << *ix ;//<< "  iy=" << *iy << endl;
}

void print(int val)
{
	cout << val << endl;
}
bool IsOdd (int i) { return ((i%2)==1); }

void Previsor4()
{
	std::vector<int> items;
	for(int i=45; i<55; i++)
		items.push_back(i);

	std::copy(items.begin(), items.end(), std::ostream_iterator<int>(cout, " "));

	std::vector<int>::iterator bitr = items.begin();
	std::vector<int>::iterator newend = std::remove_if(items.begin(), items.end(), std::bind2nd(std::greater<int>(), 50));
	cout << "\nwith new end iterator" << endl;
	for_each(bitr, newend, print);
	
	//items.erase(std::remove_if(items.begin(), items.end(), std::bind2nd(std::greater<int>(), 50)), items.end()); //works only when itesm or sorted
	//items.erase(items.begin()+2);
	//std::copy(items.begin(), items.end(), std::ostream_iterator<int>(cout, " "));

	//cout << "\nwith items iterators" << endl;
	//std::copy(items.begin(), items.end(), std::ostream_iterator<int>(cout, " "));
}

void Previsor5()
{
	class String{
	public:
		explicit String(char ch, int n=1){} //line 1
		String(const char* p){}
	private:
		void operator=(const char*){}	//line 2
	};

	//String s1 = 'a';	//line 3 (there is a problem on this line)
	String s2 = "abc";	//line 4
}

void Previsor6()
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
}

void Previsor10()
{
	int v[1000];
	std::sort(v, v+1000);
}

void Previsor11()
{
	int n = 12;
	std::cin >> std::hex >> n;
	std::cout << std::setprecision(2) << n;
	//18
}

namespace Previsor12
{
	//b
	//template<class T> void foo(T op1, T op2)
	//{}
	//template<int> void foo(int op1, int op2)
	//{
	//	std::cout << "op1 + op2 = " << op1 + op2 << endl;
	//}

	//c
	template<class T> void foo(T op1, T op2)
	{}
	template<> void foo<int>(int op1, int op2)
	{
		std::cout << "op1 + op2 = " << op1 + op2 << endl;
	}

	//d
	//void foo<int>(int op1, int op2)
	//{
	//	std::cout << "op1 + op2 = " << op1 + op2 << endl;
	//}
}

void Previsor13()
{
	class SomeClass
	{
		int x;
	public:
		SomeClass(int xx) : x(xx){}
	};

	SomeClass a(10);
	SomeClass b(a);
}

namespace Previsor14
{
	class Base {
	public:
		Base(){}
		~Base(){}
		int getBaseNum(){return 0;}
	private:
		int baseNum;
	};

	class A : public Base {
	public:
		A(){}
		~A(){}
		float getBaseNum(){return 0;}
	private:
		float baseNum;
	};

	//Base class function getBaseNum() and variable are hidden/overridden
	//by derived class function and variable

}

namespace Previsor15
{
	template<typename T> class DynArray
	{
		T *contents;
		int size;
	public:
		explicit DynArray(int initial_size){};
	};
	void pq9()
	{
		DynArray<std::string> a(7);		// 1
		DynArray<std::string> b('7');	// 2
		//DynArray<std::string> c = 7;	// 3
		DynArray<std::string> d(a);		// 4
		DynArray<std::string> e = b;	// 5
	}
}

void Previsor16()
{
	class Foo{
	public:
		Foo(int i){}
	};

	class Bar : virtual Foo{
	public:
		Bar() : Foo(0) {}
	};

	Bar b;
}

void Previsor17()
{
	int n = 18;
	std::cout << std::hex << std::showbase << n;
}

void Previsor18()
{
	class A
	{
	public:
		A() {cout << "A::A()\n";}
		virtual void Foo() {cout << "A::Foo()\n";}
	};

	class B : public A
	{
	public:
		B() { cout << "B::B()\n";}
		virtual void Foo() {cout << "B::Foo()\n";}
	};

	try{
		throw B();
	}
	catch(A ex) {ex.Foo();}	//since it is not a reference so it will call A::Foo() 
	catch(B& ex) {ex.Foo();}

	//d is the answer
}

void Previsor19()
{
	struct Foo {
		Foo() {cout << "d";}
		Foo(int i) {cout << "i";}
		Foo(char c) {cout << "c";}
		Foo(long l) {cout << "l";}
		Foo(float f) {cout << "f";}
	};

	Foo f1('a');
	Foo f2('a' + 1);
	Foo f3(1);
	Foo f4(0x01);
	Foo f5(0x0001L);
	Foo f6(1.0f);
	
	cout << endl;

	//ciiilf
}

namespace Previsor20
{
	extern void print(int *ia, int sz);
	void print(int *array, int size);
}

namespace Previsor21
{
	//typedef basic_streambuf< char > 	std::streambuf;//redefinition
	//http://www.aoc.nrao.edu/~tjuerges/ALMA/STL/html/group__s27__2__iosfwd.html
}

namespace Previsor22
{
	//constant pointer to non-constant data
	void q1(){	char* const pc=0; }
}

namespace Previsor28
{
	class Foo
	{
		char *buf;
	public:
		Foo(const char *b = "default")
		{
			if(b)
			{
				buf = new char[strlen(b) + 1];
				//std::strcpy(buf, b);
			}
			else
				buf = 0;
		}
		~Foo() {
			delete[] buf;
		}
	};

	//Foo& func(Foo f)
	//{
	//	return f;
	//}

	//when func(f) is called, it calls the default copy constructor
	//which shallow copies.
	//When func(f) returns it calls the destructor of Foo as local copy of Foo (f) 
	//goes out of scope. In destructor its tries to delete buf.
	//When foo goes out of scope, it also calls the Foo's destructor.
	//As a result it then tries to delete buf. Since it was shallow copied,
	//therefore, it results in crashing the program

	//so the correct answer is a
}

void Previsor30()
{
	std::string str;
	//cin.getline(str);
	//getline(str);
	//cout.read(str);
	//cin.read(str);
	getline(cin, str);
}

void Previsor32()
{
	std::vector<int> v;
	for(int i=0; i<5; ++i) v.push_back(i);

	v.erase(std::find(v.rbegin(), v.rend(), 2).base());
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));//0 1 2 4
	
	cout << endl;
	v.insert(std::find(v.rbegin(), v.rend(), 1).base(), 10);
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));//0 1 10 2 4
}

void Previsor33()
{
	char s[] = "string";
	const int c = 2;
	//char *p;
	char *const cp = s;
	const char *const cpc = s;

	//cp = p;
	//cpc[3] = 'a';
	cp[3] = 'b';
	//cpc = p;
	//int *p2 = &c;

	const int *p2 = &c;
}

void Previsor34()
{
	class Person {
	public:
		~Person(){delete[] m_szName;}
		Person(const char* szName)
		{
			int size = strlen(szName) + 1;
			m_szName = new char[size];
			strcpy_s(m_szName, size, szName);
		}
		const char* GetName() const { return m_szName;}

		//std::string operator() {return GetName();}
		//char* operator char*() const {return GetName(); }
		operator const char*() const {return GetName();}	//operator conversion
		//const char* Convert() const {return GetName();}
		//std::string ToString() {return GetName();}

		//operator int(){return 10;}	//another example of operator conversion

	private:
		char* m_szName;
	};

	Person person("John");
	std::cout << person;
}

namespace Previsor35
{
	void f() //throw(std::runtime_error)
	{
		if(2<3)
		{
			//throw std::bad_alloc();
			//throw std::range_error();
			//throw std::invalid_argument();
			//throw std::logic_error();
			throw std::exception();
		}
	}
}

namespace Previsor36
{
	int function(){return 0;}

	int x;
	//function() = x;

}

void Previsor37()
{
	class someclass{
	public:
		someclass(){cout << "hello" << endl;}
		//void (*someclass::Pointer)(int);
		void myfunc(){cout << "myfunc" << endl;}
	};
	someclass *a = new someclass();
	someclass *b = new someclass;

//	someclass aa();	//aa is a function which returns someclass by value
	someclass bb;

	//someclass xx;
	//someclass yy();
	//yy.myfunc();
}

namespace Previsor38
{
	//template <typename T>
	//bool is_int<T>() {return false;};
	//template<int>
	//bool is_int() {return true;};

	template <typename T>
	bool is_int() {return false;};
	template<>
	bool is_int<int>() {return true;};
}

void Previsor39()
{
	std::string s("Hello World");
	const char *c = s.c_str();
	//char *c = s.c_str();
	//float f = strlen(c);
}

namespace Previsor40
{
	class Foo {
	public:
		void virtual abc() throw(int, double, long){}
	};

	class Bar : public Foo {
	public:
//		void abc() throw(double, int, long){}
//		void abc(){throw "sdfsadf";}
	};
}

void Previsor41()
{
	int* p = new int[100];
	if(!p)
	{
		Previsor39();
	}
}

void Previsor46()
{
	class A
	{
	public:
		int i;
		A(int ii){i=ii;}
		A(const A& a){i=a.i; i++;}
		const A& operator=(const A& a){i=a.i; i--; return a;}
	};

	A a(4);
	A b = a;

	cout << b.i << endl;	//5
}

void Previsor47(void)
{
	char ary1[] = {'a', 'b', 'c', 'A', 'B', 'C', 'D'};
	char ary2[] = {'A', 'B', 'C'};
	std::vector<char> v1(ary1, ary1+7);
	std::vector<char> v2(ary2, ary2+7);
	std::vector<char>::iterator itr = std::find_first_of(v1.begin(), v1.end(), v2.begin(), v2.end());
	cout << ((itr==v1.end())? "No common elements" : "some common elements") << endl;
}

void Previsor49(void)
{
	class X {
	public:
		X& operator=(const X& rhs){return *this;}
		const X& operator+(const X& rhs) const {return *this;}
		const X& operator+(int m){return *this;}
		//X(int a){}
		//X(){}
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

namespace Previsor51
{
	//using cout;
	using std::cout;
	using namespace std;	//right answer
	//using iostream::cout;
	//using namespace iostream;
}
	class Foo{
	public:
		Foo(){std::cout << "Foo ";}
		static const  int a = 10;
	};

void Previsor52()
{//Same as q30
	class Foo{
	public:
		Foo(){std::cout << "Foo ";}
	};

	class Bar:Foo{
	public:
		Bar(){std::cout << "Bar ";}
	};

	class FooToo:virtual Foo{
	public:
		FooToo(){std::cout << "FooToo ";}
	};

	class FooTooBar: virtual FooToo, virtual Bar{
	public:
		FooTooBar(){std::cout << "FooTooBar ";}
	};
//	FooTooBar ftb;//Foo FooToo Foo Bar FooTooBar
}

namespace Previsor53
{
	void f()
	{
		int n = std::rand()%3;
		if(n == 0)
			throw "0";
		if(n == 1)
			throw 1;
		if(n == 2)
			throw 2.5;
	}

	int main_Previsor53()
	{
		try{
			f();
		}
		//catch(int i){return 2;}
		//catch(const char* cp){return 3;}
		catch(...){return 1;}
		return 0;
	}
}

namespace Previsor54
{
	template<class T> void foo(T op1, T op2)
	{
		std::cout << "op1 = " << op1 << std::endl;
		std::cout << "op2 = " << op2 << std::endl;
	}

	template<class T>
	struct sum
	{
		static void foo(T op1, T op2)
		{
			std::cout << "sum = " << op2 << std::endl;
		}
	};

	int main_Previsor54()
	{
		foo(1, 3);			//Line 1
		foo<int>(1, '3');	//Line 2
		sum<int>::foo(1, 2);//Line 3

		return 0;
	}
}

void Previsor55()
{
}

void Previsor56()
{
	class Parent{};
	class Child : public Parent{};
	Child* c = new Child;
	Parent *p = c;
}

namespace Previsor
{
	class Base {
	public:	int a;
	protected:	int b;
	private:	int c;
	};

	class Derived : Base {
		friend class Friend;
		int d;
	};

	class Friend {
		Derived derived;
		void func(){
		derived.a = 10;
		derived.b = 20;
		//derived.c = 30;
		derived.d = 40;
		}
	};

	class A{
	public:
		void f(int a);
	};
	void (A::*p)(int);
}

namespace Previsor59
{
	class Base {
	public:
		virtual void Method()=0;
	private:
		int n;
	};

	void Base::Method(){ n=1; }

	class D1 : Base{};
	class D2 : public D1 {
		int l;
		void Method(){l = 2;}
	};

	//compiles with no error
}


namespace Previsor60
{
	void log(std::string message){};

	class Account
	{
	public:
		Account(int id){};
		virtual ~Account();
		virtual std::string get_name() = 0;
		int get_id(){return 0;}
	};

	Account::~Account()
	{
		//log("Destroying: " + get_name());
	}

	class Cash : public Account
	{
	public:
		std::string get_name(){return "Hello";}
	};
}

namespace Previsor61
{
	class String
	{
		char* s;
		int length;
	public:
		String(const char *){};
		String(){};
		operator const char*() const { return s; }
		//char* const operator() const { return s; }
		//operator char* const() const { return s; }
		//char* operator() { return s; }
		//char* const operator() { return s; }
	};

	int q1()
	{
		String s1 = "abc";
		String s2 = "def";
		return strcmp(s1, s2);
	}
}

namespace Previsor62
{
	void q()
	{
		std::list<std::string> cars;
		cars.push_back("Ford");
		cars.push_back("Dawoo");
		cars.push_back("BMW");
		cars.push_back("Toyota");
		//cars.sort(std::greater<std::string>);
		//cars.sort_descending();
		cars.sort(std::greater<std::string>());
		//std::sort(cars.rbegin(), cars.rend(), std::less<std::string>);
		//std::sort(cars.begin(), cars.end(), std::less<std::string>);
		std::copy(cars.begin(), cars.end(), std::ostream_iterator<std::string>(cout, " "));
		
		//std::set<std::string> col;
		//std::sort(col.begin(), col.end());
	}
}


//######################### main_IKM ############################
void main_Previsor()
{
	cout << "main_Previsor" << endl;
	Previsor3();
	Previsor4();
	Previsor5();
	Previsor6();
	//Previsor7();
	//Previsor8();
	Previsor10();
	//Previsor14();
	//Previsor15();
	Previsor16();
	Previsor18();
	Previsor19();
	//Previsor28::q28();
	Previsor32();
	Previsor34();
	Previsor37();
	Previsor46();
	Previsor47();
	Previsor49();
	//Previsor52();
	//Previsor62::q();






}
