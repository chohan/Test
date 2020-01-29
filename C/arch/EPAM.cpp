#include "stdafx.h"
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <deque>
#include <algorithm>
#include <fstream>
#include <iterator>




namespace EPAM
{
//q.1
//what is the purpose of friend keyword?
//a)	it informs the linker that the current class should be linked closely to the friend class or function.
//b)	it allows the current class to access the friend class’s private members.
//c)	it specifies that the friend functions or classes are allowed to use a class.
//d)	it allows the friend function to be notified when member variables change.
//e)	it allows the friend class or function to access the current class’s private members.

//Q. 2
//You are writing a function that needs to be able to write to both standard output (typically the console screen) and files.
//Referring to the scenario above, which one of the following function declarations satisfies that need?
//a)	void print (ostream &os);
//b)	void print (cout);
//c)	void print (isream &is);
//d)	void print (isream is);
//e)	void print (ofsream ofs);


//Q. 3
//std::vector<int>  vi(100);
//for(unsigned int i=0; i<100; i++)
//	vi[i] = i*i;
//int x = 100;
//std::find(vi.begin(), vi.end(), x);
//int y=7;
//std::find((vi.begin(), vi.end(), y);
//
//Referring to the above sample code, what are the return values from std::find() after the call using x and the call using y?
//a)	x:  &vi(10)		y: NULL
//b)	x: vi(10)			y: std::vector::npos
//c)	x: vi.begin()+10		y: vi.end()
//d)	x: vi.at(10)		y: vi.at(-1)
//e)	x: vi(10)			y: -1


//Q. 4
//std:vector<int> items;
//Referring the sample code above, how do you remove all elements from the items collections that are greater than 50?
//a)	std::remove_if_greater(items.begin(), items.end(), 50);
//b)	std::remove_if(item.begin(), items.end(), std::greater<int>(50));
//c)	std::remove_if(items.begin(), items.end(), std::bind2nd(std::greater<int>(), 50));
//d)	items.erase(std::remove_if(items.begin(), items.end(), std::bind2nd(std::greater<int>(), 50)), items.end());
//e)	items.erase(std::remove_if(items.begin(), items.end(), std::bind1st(std::less_equal<int>(), 50)), items.end());



//Q. 5
//	class String{
//	public:
//		explicit String(char ch, int n=1){} //line 1
//		String(const char* p){}
//	private:
//		void operator=(const char*){}	//line 2
//	};
//
//Int main()
//{
//	String s1 = 'a';	//line 3
//	String s2 = "abc";	//line 4
//return 0;
//}
//
//When the sample code above is compiled, which, if any, of the labelled lines has as error?
//a)	Line 1
//b)	Line 2
//c)	Line 3
//d)	Line 4
//e)	The code compiles with no errors

//Q. 6
//	struct A{
//		int i, j;
//	public:
//		A(int ii, int jj):i(ii),j(jj){}
//		A(const A& a)
//		{
//			std::cout << "(" << a.i << "," << a.j << ")";
//		}
//		A& operator=(const A& a)
//		{
//			std::cout << "[" << i << "," << j << "]";
//			return *this;
//		}
//	};
//
//int main(void)
//{
//
//	A x(1,2);
//	A y(3,4);
//	A z = (x=y);
//
//rturn 0;
//}
//Assuming all necessary headers are included, what does the sample code above print when it is run?
//a)	[3,4](1,2)
//b)	[1,2](3,4)
//c)	[1,2][3,4]
//d)	[1,2](1,2)
//e)	[1,2][1,2]

////Q. 7
////You have a class whose internal representation is not exposed to the user and can change transparently?
////The above scenario is an example of which one of the following?
//a)	Polymorphism
//b)	Inheritance
//c)	Derivation
//d)	Encapsulation
//e)	Abstraction


//Q. 8
//class Value {
//	std::string s_val:
//	int		i_val;
//public:
//	Value(std::string s, int i) : s_val(s), i_val(i)
//	{}
//};

//Referring to the sample code above, which one of the following operations do you need to override in order to be able to use the container “std::set<Value>”?
//a)	operator !=
//b)	operator <
//c)	operator >=
//d)	operator >
//e)	operator <=

//Q. 9
//Which one of the following defines the word “polymorphism”?
//a)	The ability to overload functions based on parameter lists
//b)	The nesting of one type within another type
//c)	The ability to process objects differently depending on their actual type
//d)	The result that occurs when all classes within a system are concrete
//e)	The ability to type cast a class into one of its base classes


//Q. 10
//How do you use the Standard Template Library’s std::sort() algorithm to sort an array declared as: int v[1000]; ?
//a)	std::sort((void*) v, (void*) &v+1000, sizeof(int));
//b)	std::sort(v.begin(), v.end());
//c)	std::sort(v);
//d)	std::sort((void*) v, 1000, sizeof(int), sortInt); (assuming sortInt is defined properly)
//e)	std::sort(v, v+1000);



//Q. 11
//#include <iostream>
//#include <iomanip>
//int main()
//{
//	int n = 12;
//	std::cin >> std::hex >> n;
//	std::cout << std::setprecision(2) << n;
//	return 0;
//}
//Referring to the sample code above, what is the output of program if input is 12?
//a)	12
//b)	12.00
//c)	18
//d)	18.00
//e)	1.80e+001

//Q. 12
//template<class T> void foo(T op1, T op2) {}
//Template function foo has to print to the console the sum of parameters when T is int. How do you implement foo?
//a)	template<class T> void foo(T op1, T op2)
//{ if(T is int)
//std::cout << “op1 + op2 = “ << op1 + op2 << std::endl;
//}
//b)	template<typename T> void foo(T op1, T op2){}
//template<typename T> void fooIint op1, int op2)
//{
//std::cout << “op1 + op2 = “  << op1 + op2 << std::endl;
//}
//c)	template<typename T> void foo(T op1, T op2){}
//template< > void foo<int>(int op1, int op2)
//{
//std::cout << “op1 + op2 = “  << op1 + op2 << std::endl;
//}
//d)	void foo<int>(int op1, int op2)
//{
//std::cout << “op1 + op2 = “  << op1 + op2 << std::endl;
//}
//e)	template<typename T : int> void foo(T op1, T op2)
//{
//std::cout << “op1 + op2 = “  << op1 + op2 << std::endl;
//}

//Q. 13
//	class SomeClass
//	{
//		int x;
//	public:
//		SomeClass(int xx) : x(xx){}
//	};
//
//	SomeClass a(10);
//	SomeClass b(a);
//
//Referring to the sample code above, which one of the following statements is true?
//a)	The code compiles, but objects a and b are not destructed properly because SomeClass is missing a destructor.
//b)	The code does not compile because SomeClass does not have a default constructor.
//c)	The code compiles and executes correctly
//d)	The code does not compile because SomeClass does not have a copy constructor.
//e)	The code does not compile because SomeClass does not have an assignment operator

//Q. 14
//	class Base {
//	public:
//		Base(){}
//		~Base(){}
//		int getBaseNum(){return 0;}
//	private:
//		int baseNum;
//	};
//
//	class A : public Base {
//	public:
//		A(){}
//		~A(){}
//		float getBaseNum(){return 0;}
//	private:
//		float baseNum;
//	};
//
//What concept does the sample code above represent?
//a)	Polymorphism
//b)	Recursion
//c)	Function overloading
//d)	Function overriding
//e)	Inheritance
//f)	Virtual function


//Q. 15
//	template<typename T> class DynArray
//	{
//		T *contents;
//		int size;
//	public:
//		explicit DynArray(int initial_size){};
//	};
//	void main()
//	{
//		DynArray<std::string> a(7);	// 1
//		DynArray<std::string> b('7');	// 2
//		DynArray<std::string> c = 7;	// 3
//		DynArray<std::string> d(a);	// 4
//		DynArray<std::string> e = b;	// 5
//	}
//
//On which of the labelled lines above does a compile error occur?
//a)	1
//b)	2
//c)	3
//d)	4
//e)	5



//Q. 16
//An error occurred when compiling the following code:
//	class Foo{
//	public:
//		Foo(int i){}
//	};
//
//	class Bar : virtual Foo{
//	public:
//		Bar(){}
//	};
//	Bar b;
//
//Referring to the scenario above, adding which one of the following allows the code to compile successfully?
//a)	Foo() to the Bar constructor
//b)	A constructor to Bar that takes an int parameter
//c)	Foo(0) to the Bar::Bar initializer list
//d)	A Virtual destructor to the class Bar
//e)	A copy constructor to the class Foo



//Q. 17
//#include <iostream>
//#include <iomanip>
//int main()
//{
//	int n = 18;
//	/* code here */
//	return 0;
//}
//
//Referring to the sample code above, which of the following statements prints 0x12 to console?
//a)	std::cout << std::hex() << std::showbase() << n;
//b)	std::cout << std::setbase(16) << std::showbase() << n;
//c)	std::cout << std::setbase(16) << n;
//d)	std::cout << std::sethex(true) << std::setshowbase(true) << n;
//e)	std::cout << std::hex << std::showbase << n;


//Q. 18
//	class A
//	{
//	public:
//		A() {cout << "A::A()\n";}
//		virtual void Foo() {cout << "A::Foo()\n";}
//	};
//
//	class B : public A
//	{
//	public:
//		B() { cout << "B::B()\n";}
//		virtual void Foo() {cout << "B::Foo()\n";}
//	};
//
//	int main()
//	{
//	try{
//		throw B();
//	}
//	catch(A ex) {ex.Foo();}	//since it is not a reference so it will call A::Foo() 
//	catch(B& ex) {ex.Foo();}
//	return 0;
//}
//
//What is the output of the sample code above?
//a)	B::B()
//B::Foo()
//b)	B::B()
//A::A()
//B::Foo()
//c)	A::A()
//B::B()
//A::Foo()
//B::Foo()
//d)	A::A()
//B::B()
//A::Foo()



//Q. 19
//#include <iostream>
//	struct Foo {
//		Foo() {cout << "d";}
//		Foo(int i) {cout << "i";}
//		Foo(char c) {cout << "c";}
//		Foo(long l) {cout << "l";}
//		Foo(float f) {cout << "f";}
//	};
//
//	int main()
//	{
//	Foo f1('a');
//	Foo f2('a' + 1);
//	Foo f3(1);
//	Foo f4(0x01);
//	Foo f5(0x0001L);
//	Foo f6(1.0f);
//	return 0;
//}
//
//Referring to the above sample code, what is the output when the program is executed?
//a)	cciilf
//b)	ciiilf
//c)	iiilf
//d)	iciilf
//e)	ciillf


//Q. 20
//	extern void print(int *ia, int sz);
//	void print(int *array, int size);
//
//Does the sample code above compile?
//a)	No, there are two functions named print that have the same signature.
//b)	No, the function name print cannot be extern.
//c)	Yes, it does.
//d)	No, there are two functions named print.
//e)	No, functions print cannot return void.
//
//void q11()
//{
//	int v[1000];
//	//std::sort(v);
//	std::sort(v, v+1000);
//	//std::sort(v.begin(), v.end());
//	//std::sort((void*)v, (void*)&v+1000, sizeof(int));
//}

};



//////////////////////////////////////////////////////////////////
void main_EPAM()
{
	std::cout << "main_EPAM" << std::endl;
	//EPAM::q1();
	//EPAM::q2();
	//EPAM::q3();
	//EPAM::q4();
	//EPAM::q5();
	//EPAM::q6();
	//EPAM::q7();
	//EPAM::q8();
	//EPAM::q9();
	//EPAM::q10();
	//EPAM::q11();
	//EPAM::q12();
	//EPAM::q13();
	//EPAM::q14();
	//EPAM::q15();
	//EPAM::q16();
	//EPAM::q17();
	//EPAM::q18();
	//EPAM::q19();
	//EPAM::q20();
}
