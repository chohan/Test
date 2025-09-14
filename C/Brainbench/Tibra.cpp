//Tibra.cpp
#include "stdafx.h"
#include "boost/smart_ptr/shared_ptr.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <string>
using namespace std;

namespace Tibra2
{
	void Tibra2()
	{
		//how many bytes will be reserved
		char abc[] = "abc";
		int len = sizeof(abc);	//4
	}

	//Question
	class Foo
	{
	public:
		Foo(int x) : i(x) {};

	private:
		int i;
	};

	void Qb()
	{
		//int i = Foo::i;
		const Foo &af = Foo(10);
		//Foo *af = new Foo[10];
		//Foo &f = new Foo(1);
		//Foo *f = new Foo;
	}


}
void Tibra4()
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


	//order of local objects' desctruction
	class B{public:	~B(){cout << "B dtor" << endl;}	};
	class C{public:	~C(){cout << "C dtor" << endl;}	};
	class D{public:	~D(){cout << "D dtor" << endl;}	};

	B b;
	C c;
	D d;
}

namespace Tibra7
{
	class Foo
	{
	public:
		Foo(){cout << "default ctor" << endl;}
		Foo(const Foo& foo){cout << "copy ctor" << endl;}
		~Foo(){cout << "dtor" << endl;}
	};
	Foo ReturnByValue()
	{
		return Foo();
	}

	void UserCode()
	{
		//Foo y;
		//Foo z(y);
		Foo x = ReturnByValue();
	}
}

namespace Tibra10
{
	void f() //throw(float)
	{
		throw 10.0f;
	}

	int main1()
	{
		try
		{
			std::cout << 'A';
			f();
			std::cout << 'B';
		}
		catch(...){std::cout << 'C';}
		return 0;
	}
}

namespace Tibra13
{
	class Base
	{
	public:
		Base()
		{
			cout << "Base ctor" << endl;
			this->vf();
			//Base(1);
		}
		Base(int a){cout<<"this is Base(int a)"<<endl;};
		~Base(){}
		virtual void vf(){cout<<"Hi Base class vf"<<endl;}
	};

	class Derived : public Base
	{
	public:
		Derived()
		{
			cout << "Derived ctor" << endl;
			this->vf();			
		};
		virtual void vf(){cout<<"Hi Derived class vf"<<endl;}
	};
}

namespace Tibra14
{
	template<class T> class A
	{
	public:
		A(){}
	};

	template<class T> class B
	{
	public:
		B(){}
		friend class A<T>;
		//friend template class A<B>;
		//friend template<class B> class A;
		//template<> friend class A;
	};
}

namespace Tibra14b
{
	class SomeClass
	{
		int x;
	public:
		SomeClass(int xx) : x(xx) {}
	};

	int mymain()
	{
		SomeClass a(10);
		SomeClass b(a);
		return 0;
	}
}

void Tibra15()
{
	std::list<std::string> cars;
	cars.push_back("Mondeo");
	cars.push_back("Toyota");
	cars.push_back("Honda");
	cars.push_back("Mitsubishi");
	cars.push_back("BMW");
	//cars.sort(std::greater<std::string>);
	//std::sort(cars.begin(), cars.end(), std::less<std::string>);
	//std::sort(cars.begin(), cars.end(), std::less<std::string>);
	cars.sort(std::greater<std::string>());
	//cars.sort_descending();

	std::list<string>::iterator itr = cars.begin();
	while(itr != cars.end())
	{
		cout << *itr++ << endl;
	}
}

namespace Tibra16
{
	template<class T, class X>
	class Obj
	{
		T my_t;
		X my_x;
	public:
		Obj(T t, X x) : my_t(t), my_x(x){}
		//T operator(T) const {return my_t;}
		//T operator T (const Obj &obj){return ob.my_t;}
		//T operator T(){return my_t;}
		operator T() const{return my_t;}
		//operator (T) const{return my_t;}
	};

	void userCode()
	{
		int iT;
		Obj<int, float> obj(15, 10.375);

		iT = obj;
	}
}

namespace Tibra18
{
	namespace { static int n; }
	namespace A {
		namespace { static int n; }
	}
	using namespace A;

	int mymain()
	{
//		n = 5;
		return 0;
	}
}

namespace Tibra19
{
	int *t1[15];			//array of int pointers
	int *t2 = new int[15];	//pointer to array of int
	int t3[15];				//array of int
	int **t4 = new int*[15];//pointer to an array of pointers
	//int t5[15] = new int*;
}

namespace Tibra22
{
	class String
	{
		~String();
	};
	String::~String()
	{
		std::cout << "~String() " << std::endl;
	}
}

namespace Tibra22b
{
	class TestClass
	{
	public:
		void Test()	{	DoTest();	}
	private:
		virtual void DoTest() {	cout << 'a'; }
	};

	class DerivedClass : public TestClass
	{
	private:
		virtual void DoTest() {	cout << 'b'; }
	};
	
	void mymain()
	{
		DerivedClass dc;
		dc.Test();
	}
}

namespace Tibra23
{

	class Foo{};

	void UserCode()
	{
		Foo foo1;
		boost::shared_ptr<Foo> fooPtr = boost::shared_ptr<Foo>(&foo1);
	}
}

namespace Tibra24
{
	class X
	{
		int i;
	public:
		int f();// const;
	};
	int X::f()//const
	{ return i++; }
}

namespace Tibra25
{
	struct color { int r, g, b; };
}

namespace Tibra27
{
	class professor 
	{
	public:
		professor(){cout << "professor ctor" << endl;}
		~professor(){cout << "professor dtor" << endl;}
	};

	class researcher 
	{
	public:
		researcher(){cout << "researcher ctor" << endl;}
		~researcher(){cout << "researcher dtor" << endl;}
	};

	class teacher : public professor 
	{
	public:
		teacher(){cout << "teacher ctor" << endl;}
		~teacher(){cout << "teacher dtor" << endl;}
	};

	class guru : public teacher, public researcher
	{
	public:
		guru(){cout << "guru ctor" << endl;}
		~guru(){cout << "guru dtor" << endl;}
	};

	void mymain()
	{
		guru g;	//
	}
	//int multi inheritance situation,
	//constor of the first inheritance will be called first
	//conversely destructor of the last will be called first
}

namespace Tibra28
{
	int abs(int n){return n;}
	unsigned long abs(unsigned long n){return n;}
	double abs(double n){return n;}
	float abs(float n){return n;}

	int mymain()
	{
		cout << abs(-10);
		return 0;
	}
}

void Tibra31()
{
	std::vector<std::string> strVec;
	strVec.push_back("Foo");
	strVec.push_back("Bar");
	strVec.push_back("Baz");
	strVec.push_back("Bee");
	cout << count_if(strVec.begin(), strVec.end(), bind2nd(std::greater<std::string>(), "Baz"));
	//1
}

namespace Tibra32
{
	template<class T> void foo(T op1, T op2)
	{
		std::cout << "op1+op2=" << op1 + op2 << std::endl;
	}
	template<> void foo<int>(int op1, int op2)
	{
		std::cout << "op1+op2=" << op1 + op2 << std::endl;
	}

	//template<class T> void foo(T op1, T op2){}
	//template<int> void foo(int op1, int op2)
	//{
	//	std::cout << "op1+op2=" << op1 + op2 << std::endl;
	//}

	void mymain()
	{
		foo<int>(2, 5);
	}
}

namespace Tibra33
{
	void MyMethod()
	{
		cout << "MyMethod" << endl;
		throw "Exception";
	}
	void handleerror(){cout << "handleerror" << endl;}

	void mymain()
	{
		try
		{
			MyMethod();
		}
		catch(...)
		{
			handleerror();
		}
	}
}

namespace Tibra33b
{
	//int     subtract2(int n)     { return n - 2; }
	//long    subtract2(long n)    { return n - 2L; }
	//double  subtract2(double n)  { return n - 2.0; }
	// 
	//int main1( )
	//{
	//  int n = subtract2(float (5.3));
	//  return n;
	//};
}

void Tibra34()
{
	char ca[] = {'a', 'e', 'i', 'o', 'u', 'y'};
	char* pca = ca;
	pca += 2;
	char a = *pca;
	cout << "a = " << a << endl;//i
}

namespace Tibra35
{
	class Base 
	{
	public: int a;
	protected: int b;
	private: int c;
	};

	class Derived : Base 
	{
		friend class Friend;
		int d;
	};

	class Friend
	{
		Friend()
		{
		Derived derived;
		int a = derived.a;
		int b = derived.b;
		//int c = derived.c;
		int d = derived.d;
		}
	};
}

namespace Tibra37
{
	int fn()
	{
		int a = 10;
		return a;
	}

	void mymain()
	{
		int b = fn();
	}
}

void Tibra39()
{
	//std::list<int> L;
	//for(int i=0; i<15; i++)
	//	L.push_back(i);
	//list<int>::iterator in_range = find_if(L.begin(), L.end(),
	//	compose2(logical_and<bool>(), bind2nd(greater_equal<int>(), 1),
	//									bin2nd(less_equal<int>(), 10)));

}


namespace Tibra
{
}



//######################### main_Tibra ############################
void main_Tibra()
{
	cout << "main_Tibra" << endl;
	//Tibra2();
	//Tibra4();
	//Tibra7::UserCode();
	//Tibra10::main1();
	//Tibra13::Derived d;
	//Tibra14::mymain();
	//Tibra15();
	//Tibra27::mymain();
	//Tibra22b::mymain();
	//Tibra23::UserCode();
	//Tibra28::mymain();
	//Tibra31();
	//Tibra32::mymain();
	//Tibra33::mymain();
	//Tibra34();
	//Tibra37::mymain();

}
