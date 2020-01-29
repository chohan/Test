// g++ C_Questionnaire.cpp -g -w --std=c++17 -lpthread
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
#include <queue>
#include <stack>
#include <functional>   // std::greater
#include <initializer_list>	//C++11 feature

#include <numeric>
#include <regex>

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
using namespace std;

#define trace(str)(std::cout << "\n" << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << "(): " << str << std::endl)
template<typename T> void print(T coll){for(auto x:coll)std::cout<<x<<" "; std::cout<<std::endl;}

namespace C_Q_placement_new
{
	// shows any object created using placement new, will have same memory address as that of original buffer
	void f1()
	{
		char* buf = new char[1000];
		std::string * ps = new (buf) std::string("hello world");
		std::cout << "buf address:" << *((int*)buf) << ", placement new add:" << *((int*)ps) << std::endl;
	}
}

//initialization list
namespace C_Q31
{
	class foo
	{
	public:
		foo(int i) {}
	};

	class bar : public foo
	{
	public:
		bar(int a) : foo(a), strA("hello world"), L(10) {}
	private:
		std::string strA;
		const long L;
	};

	void f1()
	{
		bar b(10);
	};
}

// initialization order
namespace C_Q35
{
	class A {public: A(int i){std::cout << __FUNCTION__ << i << std::endl;}};
	class B {public: B(int i){std::cout << __FUNCTION__ << i << std::endl;}};
	class C {public: C(int i){std::cout << __FUNCTION__ << i << std::endl;}};
	class ABC
	{	public:
	ABC():c(3), b(2), a(1){std::cout << __FUNCTION__ << std::endl;};// objects are initialized in the order they are defined in class and NOT in the order they are in initialization list
	A a;
	C c;
	B b;
	};

	void f1()
	{
		trace("initialization order");
		ABC abc;
	}
}

namespace C_Q43
{
	void f1()
	{
		trace("placement new");
		char* buf = new char[1000];
		std::string* pStr = new (buf) std::string("hello world");
		//delete pStr;
		delete buf;
	};
}

namespace C_Q52
{
	void f1()
	{
		trace("printf(\"%d\")");
		printf("%d");
	}
}

namespace C_Q63
{
	class A
	{public:
		A(){std::cout << __FUNCTION__ << std::endl;}
		~A(){std::cout << __FUNCTION__ << std::endl;}
	};

	void f1()
	{
		trace("is dtor called, when memory is freed?");
		A* pa = new A();
		char * pc = (char*)malloc(1000);
		free(pc);
		free(pa);
	}
}

namespace C_Q70
{
	//how to bar an object to be copied
	class foo {};

	class bar
	{
	public:
		bar(){}

	private:
		bar(const bar& b){}
	};

	void f1()
	{
		trace("private copy constructor");
		//can be copied easily
		foo foo1;
		foo foo2(foo1);

		const foo foo3;
		foo foo4(foo3);

		//cannot be copied as copy constructor is private
		bar bar1;
		//bar bar2(bar1);
	}
}

namespace C_Q73
{
	//size of a class
	class foo{};
	class bar : public foo{public: int a; void func(){int a=10; printf("a=%d", a);}};

	void f1()
	{
		trace("size of empty class");
		std::cout << "sizeof(foo empty class)=" << sizeof(foo) << std::endl;
		std::cout << "sizeof(bar, with one int)=" << sizeof(bar) << std::endl;
	}
}

namespace C_Q74
{
	//Singleton
	class Singleton
	{
	public:
		static Singleton* getInstance()
		{
			if(pSingleton==NULL)
				pSingleton = new Singleton();
			return pSingleton;
		}

	private:
		static Singleton* pSingleton;
		Singleton(){pSingleton=NULL;std::cout << "Singleton::ctor";}
	};
	Singleton* Singleton::pSingleton = NULL;

	void f1()
	{
		trace("singleton");
		Singleton* p1 = Singleton::getInstance();
		Singleton* p2 = Singleton::getInstance();
	}
}

namespace C_Q75
{
	//casting
	void f1()
	{
		trace("casting");
		class A{public: int i;};
		class B{virtual void f1(){}};
		class D : public B {};


		int i = 10;

		//reinterpret_cast
		//only for pointers and int to/from pointer
		long* l = reinterpret_cast<long*>(i);
		A* pa = new A;
		B* pb = reinterpret_cast<B*>(pa);
		delete pb;

		//static_cast
		D* pd = static_cast<D*>(new B);
		B* pbb = static_cast<B*>(pd);

		//dynamic_cast
		B* pb1 = new B;
		B* pb2 = new D;
		D* pd1 = dynamic_cast<D*>(pb1);	//should fail, returns null
		D* pd2 = dynamic_cast<D*>(pb2);	//should succeed
		std::cout << "pd1=" << pd1 << std::endl;
		std::cout << "pd2=" << pd2 << std::endl;

		pd1 = static_cast<D*>(new B);	//without static_cast, it will not work
		pd2 = new D;
		pb1 = dynamic_cast<B*>(pd1);	//should succeed
		pb2 = dynamic_cast<B*>(pd2);	//should also succeed
		std::cout << "pd1=" << pd1 << std::endl;
		std::cout << "pd2=" << pd2 << std::endl;

		//const_cast
		A* pa1 = new A;
		const A* pa2 = new A;
		pa1->i = 1;		//allowed as pa1 is NOT a pointer to a constant object
		//pa2->i = 2;	//not allowed as pa2 is a pointer to a constant object
		//A* pa3 = pa2;	//not allowed as pa2 is a pointer to a constant object
		A* pa3 = const_cast<A*>(pa2);
		pa3->i = 3;
	}
}

// dynamic_cast does not work if there is no virtual function in base class
namespace C_Q77
{
	class Base{public: virtual void vfunc(){} };
	class Derived : public Base {};

	void f1()
	{	
		trace("dynamic_cast");
		Derived d;
		Base b;
	
		Base bb    = dynamic_cast<Base&>(d); 		std::cout << "\nBase bb    = dynamic_cast<Base&>(d) => success";
		try{
		Derived dd = dynamic_cast<Derived&>(b);	std::cout << "\nDerived dd = dynamic_cast<Derived&>(b) => fail";
		}catch(exception ex){std::cout << "\nException caught: " << ex.what() << std::endl;}

		Base* pb = new Derived();
		Derived* pd = dynamic_cast<Derived*>(pb);std::cout << "\nDerived* pd = dynamic_cast<Derived*>(pb) => success";
	}
}

namespace C_Q_templates
{
	template<typename T> T adder(T t1, T t2) { return t1+t2; };		//template declaration
	template<typename T> T adder2(T t1, int t2) { return t1+t2; };	//template partial specialization
	template<> int adder<int>(int t1, int t2) { return t1+t2; };	//template specialization
	template<typename T> class myclass
	{
	public:
		T subtractor(T t1, T t2) { return t1-t2; }
	};


//nested templates
template<typename T>
struct first { typedef T * pointer; };

template<typename T>
class second { typename first<T>::pointer p; };//you cannot use class instead of typename here

	void f1()
	{
		trace("templates");
		int a = adder<int>(10, 20);	//template instantiation
		std::cout << "adder=" << a << std::endl;

		myclass<int> obj;	//template instantiation
		int b = obj.subtractor(20, 5);
		std::cout << "subtractor=" << b << std::endl;

		//template specialization
	}
}

namespace C_Q_operator_overloading
{
	//operator conversion (class conversion to an instrinsic type like int, float)
	class ABC
	{
	public:
		ABC():a(10), b(20.0){}
		operator int()   { return a; }
		operator float() { return b; }
		void *operator new(size_t size)
		{
			std::cout << __FUNCTION__ << ", size=" << size << std::endl;
			return malloc(size);
		}
		void operator delete(void* p)
		{
			std::cout << __FUNCTION__ << std::endl;
			free(p);
		}
			

	private:
		int a;
		float b;
	};

	void f1()
	{
		trace("new/delete operator_overloading");
		ABC abc;
		int a = abc;
		float b = abc;
		std::cout << "ABC::int()=" << a << " ABC::float()=" << b << std::endl;
		ABC* p = new ABC();
		delete p;
	}

	//overloading operator + for a complex number
	class Complex
	{
	public:
		Complex():m_real(0), m_imag(0){}
		Complex(float real, float img=0): m_real(real), m_imag(img){}
		void print(){std::cout << "real=" << m_real << " imag=" << m_imag << std::endl;}
		Complex operator=(const Complex& rhs)
		{
			m_real = rhs.m_real;
			m_imag = rhs.m_imag;
			return *this;
		}

		Complex operator+(const Complex& rhs)
		{
			float real = m_real + rhs.m_real;
			float img  = m_imag + rhs.m_imag;
			return Complex(real, img);
		}


	private:
		float m_real, m_imag;

		//friend Complex operator+(const Complex& a, const Complex& b);
		//friend Complex operator=(Complex& a, const Complex& b);
		friend std::istream &operator>>(std::istream &in, Complex &c);
		friend std::ostream &operator<<(std::ostream &out, Complex &c);
};

	//Complex operator+(const Complex& a, const Complex& b)
	//{
	//	float real = a.m_real + b.m_real;
	//	float img  = a.m_imag  + b.m_imag;
	//	return Complex(real, img);
	//}

	//Complex operator=(Complex& a, const Complex& b)
	//{
	//	a.m_real = b.m_real;
	//	a.m_imag = b.m_imag;
	//	return a;
	//}

	std::istream &operator>>(std::istream &in, Complex &c)
	{
		std::cout << "enter real part:";
		in>>c.m_real;
		std::cout << "enter imag part:";
		in>>c.m_imag;
		return in;
	}

	std::ostream &operator<<(std::ostream &out, Complex &c)
	{
		out << "real=" << c.m_real << " imag=" << c.m_imag << std::endl;
		return out;
	}


	void f2()
	{
		Complex a = Complex(1,2);
		Complex b = Complex(3, 4);
		Complex c = a.operator+(b);	//OR Complex c = a + b;
		c.print();
		Complex d;
		std::cin>>d;
		//d.print();
		std::cout << "d: " << d;
		Complex e;
		e = d;
		std::cout << "d: " << d;
		std::cout << "e: " << e;
	}
}

namespace C_Q_Exceptions
{
	class B
	{
	public:
		B()
		{
			std::cout << "B::ctor before throw" << std::endl;
			//throw 10;	//if exception is thrown from constructor then destructor is not called
			//std::cout << "B::ctor after throw" << std::endl;
		}
		~B()
		{
			std::cout << "B::dtor before throw" << std::endl;
			//throw 20;
			//std::cout << "B::dtor after throw" << std::endl;
		}
	};

	class A
	{
	public:
		A()
		{
			std::cout << "A::ctor before throw" << std::endl;
			B b;
			B* pB = new B;
			throw 10;	//if exception is thrown from constructor then destructor is not called
			std::cout << "A::ctor after throw" << std::endl;
		}
		~A()
		{
			std::cout << "A::dtor before throw" << std::endl;
			throw 20;
			std::cout << "A::dtor after throw" << std::endl;
		}
	};

	void myunexpected () {
		std::cout << "unexpected called\n";
		throw 0;     // throws int (in exception-specification)
	}
	void f1()
	{
		trace("exception::f1, class A, B");
		try{A a;} catch(...){std::cout << "exception is caught" << std::endl;}
		//A* pa = new A();
		//try{delete pa;} catch(...){std::cout << "exception is caught" << std::endl;}
		//try{f2();} catch(...){std::cout << "exception is caught" << std::endl;}

		std::set_unexpected(&myunexpected);

		// try{
		// std::cout << "about to throw float exception" << std::endl;		throw(12.9);
		// }catch(int i){std::cout << "int exception is caught=" << i << std::endl;}
		// catch(char c){std::cout << "char exception is caught=" << c << std::endl;}
		// catch(...){std::cout << "other exception is caught=" << std::endl;}
	}

	class X
	{
	public:
		X(){std::cout << "\nX ctor"; throw 10;}
		~X(){std::cout << "\nX dtor";}
	};
	class Y
	{
	public:
		Y(){std::cout << "\nY ctor";}
		~Y(){std::cout << "\nY dtor"; throw 20;}
	};
	struct Z {X x; Y y;};// X will be contructed but Y will not. Desctructors of both will not be called.
	void f2() 
	{
		trace("exception::f2, class X, Y");
		std::cout << "\nX is throwing exception in ctor"
							<< "\nY is throwing exception in dtor\n";
		//try { Z z; } catch(...){std::cout << "\nexception in Z is caught";}
		X* px;
		try{ px = new X();}catch(...){std::cout << "\nexception caught " << std::endl;}
		//delete px;	// dtor will be called here but towards the end will generate Seg fault
		//try{ Y y;}catch(...){std::cout << "\nexception caught " << std::endl;}
		// above exception will not be caught and aborted will be caught.

		if(std::uncaught_exception())
			std::cout << "\nexception is thrown but uncaught.\n";
	}

}	// C_Q_Exceptions

namespace C_Q_memory_management
{
	class ABC {};

	int g_int;
	ABC* g_pABC;

	void f1()
	{
		trace("memory_management");
		static int static_int;
		static ABC* static_pABC;
		std::cout << "global uninitized variables will always be initialized to zero: g_int=" << g_int << ", static_int=" << static_int << std::endl;
		std::cout << "global uninitized variables will always be initialized to zero: g_pABC=" << g_pABC << ", static_pABC=" << static_pABC << std::endl;
	}
}

namespace C_Q_ctor_dtor
{
	//need of virtual destructor
	class Base
	{
	public:
		int base_i;
		Base():base_i(10) { std::cout << "Base ctor" << std::endl; }
		//~Base(){ std::cout << "Base dtor" << std::endl; }
		virtual ~Base(){ std::cout << "Base dtor" << std::endl; }
		void func(int a) { std::cout << "Base_func" << " a=" << a <<std::endl; }
		//virtual void vfunc(){std::cout << "Base virtual function" << std::endl;}
		void *operator new(size_t size)
		{
			std::cout << __FUNCTION__ << std::endl;
			return malloc(size);
		}
	};

	class Derived : public Base
	{
	public:
		int derived_i;
		Derived():derived_i(20){ std::cout << "Derived ctor" << std::endl; }
		~Derived(){ std::cout << "Derived dtor" << std::endl; }
		void func(int a, int b) { std::cout << "Derived_func" << " a+b=" << a+b <<std::endl; }
		//virtual void vfunc(){std::cout << "Base virtual function" << std::endl;}
	};

	class ABC : public std::vector<int>
	{
	public:
		int a;
	protected:
		int b;
	private:
		int c;
	};

	void f1()
	{
		trace("C_Q_ctor_dtor");
		//Base* pB = new Derived();
		//delete pB;

		//smart pointer
		std::auto_ptr<Base> sp1(new Derived());
		sp1->func(2);

		std::auto_ptr<Base> sp2 = sp1;
		//sp1->func(2);
		sp2->func(2);

		ABC abc;
		abc.a  = 10;
		//std::tuple<int,char, int, char> foo (10,'x', 4, 'c');
		//std::tuple<int, char> tp(1, 'a');
		auto bar = std::make_tuple ("test", 3.1, 14, 'y');
	}
}

namespace Inheritance1
{
	// diamond inheritance
	class Base
	{
	public:
		Base() { std::cout << "Base ctor" << std::endl; }
		~Base(){ std::cout << "Base dtor" << std::endl; }
	};

	class D1 : public virtual Base
	{
	public:
		D1() { std::cout << "D1 ctor" << std::endl; }
		~D1(){ std::cout << "D1 dtor" << std::endl; }
	};
	class D2 : public virtual Base
	{
	public:
		D2() { std::cout << "D2 ctor" << std::endl; }
		~D2(){ std::cout << "D2 dtor" << std::endl; }
	};
	class DD : public D1, D2
	{
	public:
		DD() { std::cout << "DD ctor" << std::endl; }
		~DD(){ std::cout << "DD dtor" << std::endl; }
	};

	void f1()
	{
		trace("Inheritance1: diamond");
		DD dd;
	}
}

namespace Inheritance2
{
	// how to avoid copyable
	class A
	{public:
		A(const A& a){std::cout << "A copy ctor" << std::endl;}
		A& operator=(const A& a){std::cout << "assignment operator\n";}
		int a;

	public:
		A():a(10){std::cout << "A normal ctor" << std::endl;}
	};

	class B : public A
	{
	};

	class C
	{
	public:
		A a;
	};

	void f1()
	{
		trace("Inheritance2");
		A a1;
		A a2(a1);		//not copyable/accessable due to private copy ctor
		A a3;
		a3 = a1;	//not copyable due to private assignment operator
		B b1;
//		B b2(b1);

		C c1;
		//C c2(c1);		//not copyable
	}
}

// same name in derived class hide function from base class
namespace Inheritance3
{
	class Base
	{
	public:
		void func1(int a){std::cout << a << std::endl;}
	};
	class Derived : public Base
	{
	public:
		void func1(int a, int b) { std::cout << a << ", " << b << std::endl;}
	};

	void f1()
	{
		trace("Inheritance3");
		Base* pb = new Derived();
		//pb->func1(10, 20);	// compile time error
		Derived* pd = static_cast<Derived*>(pb);
		pd->func1(10, 20);
	}
}

// pure virtual function implementation
namespace Polymorphism
{
	class ABC
	{
	public:
		virtual int func(int a) = 0;
	};

	int ABC::func(int a) { return a; }	// a class can have implementation of its own pure virtual function

	//need of virtual destructor
	class Base
	{
	public:
		Base():base_i(10) { std::cout << "Base ctor" << std::endl; }
		~Base(){ std::cout << "Base dtor" << std::endl; }
		//virtual ~Base(){ std::cout << "Base dtor" << std::endl; }
		void func() { std::cout << "Base_func" << std::endl; }
		virtual void vfunc(){std::cout << "Base virtual function" << std::endl;}
		int base_i;
	};

	class Derived : public Base
	{
	public:
		int derived_i;
		Derived():derived_i(20){ std::cout << "Derived ctor" << std::endl; }
		~Derived(){ std::cout << "Derived dtor" << std::endl; }
		void func() { std::cout << "Derived_func" <<std::endl; }
		virtual void vfunc() override {std::cout << "Derived virtual function" << std::endl;}
	};

	void f1()
	{
		trace("Polymorphism");
		Base* p = new Derived();
		p->func();				// base func
		p->vfunc();				// derived virtual func
		p->Base::vfunc();	// base virtual func
		delete p;

		Derived d;
		//d.func(10);	//non-virtual function in derived class, hides base class function with same "name"
		d.func();

		// shows first location of a derived class is _vptr and second location is base class member integer and third is derived class member integer
	//	std::cout << "1st location address/value=" << (int)&d << "/" << *((int*)&d) << std::endl;
		std::cout << "2nd location address/value=" << (((int*)&d)+1) << "/" << *(((int*)&d)+1) << std::endl;
		std::cout << "3rd location address/value=" << (((int*)&d)+2) << "/" << *(((int*)&d)+2) << std::endl;
		std::cout << "4th location address/value=" << (((int*)&d)+3) << "/" << *(((int*)&d)+3) << std::endl;
	}
}

namespace Multithreading
{
	void task1()
	{
		std::cout << __FUNCTION__ << " started" << std::endl;
		for(auto i=0; i<5; i++)
		{
			std::cout << "I am " << __FUNCTION__ << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		std::cout << __FUNCTION__ << " finished" << std::endl;
	}

	void task2(int a, const char* str)
	{
		std::cout << __FUNCTION__ << " started" << std::endl;
		for(auto i=0; i<5; i++)
		{
			std::cout << "I am " << __FUNCTION__ << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
		}
		//_sleep(5000);
		std::cout << __FUNCTION__ << " finished" << std::endl;
	}

	void func()
	{
		trace("Multithreading");
		std::thread th1(task1);
		std::thread th2(task2, 10, "hello");
		std::cout << "both threads started" << std::endl;

		//either you should detach these spawning thread or join them as below
		th1.detach();
		th2.detach();
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));

		//th1.join();
		//std::cout << "th1 thread finished" << std::endl;
		//th2.join();
		//std::cout << "th2 thread finished" << std::endl;
	}
}

namespace covarient
{
	class ABC{
	public:
	int func(int a){}
	//float func(int b){}	// cannot overload functions distinguished by return type alone
	};

}
//////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
	trace("Bismillah");
	C_Q_placement_new::f1();
	C_Q31::f1();
	C_Q35::f1();
	C_Q43::f1();
	C_Q52::f1();
	C_Q63::f1();
	C_Q70::f1();
	C_Q73::f1();
	C_Q74::f1();
	C_Q75::f1();
	C_Q77::f1();
	C_Q_templates::f1();
	C_Q_operator_overloading::f1();
	C_Q_operator_overloading::f2();
	C_Q_Exceptions::f1();
	C_Q_Exceptions::f2();
	C_Q_memory_management::f1();
	C_Q_ctor_dtor::f1();
	Inheritance1::f1();
	Inheritance2::f1();
	Inheritance3::f1();
	Polymorphism::f1();
	Multithreading::func();

	//int nStack[100000000]; //causes the program to crash due to stack overlow

}
