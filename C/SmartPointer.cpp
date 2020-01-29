// g++ -g -w -o SmartPointer SmartPointer.cpp --std=c++17 -lpthread
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <memory>
#include <utility>
#define trace(str)(std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << "(): " << str << std::endl)



namespace smart_pointer
{
using namespace std;
class A
{
public:
	A() {cout << "A ctor" << endl;}
	~A() {cout << "A dtor" << endl;}

	void func(){cout << "this is func" << endl;}
};

void test(int argc, char** argv)
{
	//check auto_ptr ownership transfer
	std::cout << "\nauto_ptr\n";
	auto_ptr<A> a(new A());
	std::auto_ptr<A> b;
	a->func();
	b = a;
	//a->func();	//it will crash here as it transferred the ownership in above statement
	b->func();

	std::cout << "\nunique_ptr\n";
	std::unique_ptr<A> up1(new A());
	up1->func();
	std::unique_ptr<A> up2;
	//up2 = up1;	//compile time error

	std::cout << "\nshared_ptr\n";
	std::shared_ptr<A> sp1(new A());
	std::shared_ptr<A> sp2;
	sp2 = sp1;
	sp1->func();
	sp2->func();
}
}



class SM
{public:
	SM() {std::cout << "ctor is called" << std::endl;}
	~SM(){std::cout << "dtor is called" << std::endl;}
};

void autoP()
{
	trace("");
	std::auto_ptr<SM> p(new SM());
	try{
	if(3>2){ throw "exception thrown in before delete"; }
	}catch(...){ std::cout << "Exception is caught\n"; }	
}

void sharedP()
{
	trace("");
	std::shared_ptr<SM> p1(new SM());
	std::cout << "p1 count=" << p1.use_count() << std::endl;
	std::shared_ptr<SM> p2 = p1;
	std::cout << "std::shared_ptr<SM> p2 = p1;" << std::endl;
	std::cout << "p1 count=" << p1.use_count() << std::endl;
	std::cout << "p2 count=" << p2.use_count() << std::endl;
	std::shared_ptr<SM> p3;
	std::cout << "std::shared_ptr<SM> p3;" << std::endl;
	std::cout << "p3 count=" << p3.use_count() << std::endl;
	p3 = p2;
	std::cout << "p3 = p2;" << std::endl;
	std::cout << "p1 count=" << p1.use_count() << std::endl;	// 3
	std::cout << "p2 count=" << p2.use_count() << std::endl;	// 3
	std::cout << "p3 count=" << p3.use_count() << std::endl;	// 3
}

void sharedP_with_custom_delete()
{
	trace("");
	//std::shared_ptr<SM> p(new SM[10]); // will crash
	std::shared_ptr<SM[]> p(new SM[4]); // will work
	//std::shared_ptr<SM> p(new SM[4], [](SM* p){delete[] p;}); // will work
	try{
	if(3>2){ throw "exception thrown in before delete"; }
	}catch(...){ std::cout << "Exception is caught\n"; }	
}


namespace circularRef
{
class BB;
class AA
{public:
	AA(){std::cout << "AA ctor is called" << std::endl;}
	~AA(){std::cout << "AA dtor is called" << std::endl;}
	BB *_pB;
};
class BB
{public:
	BB(){std::cout << "BB ctor is called" << std::endl;}
	~BB(){std::cout << "BB dtor is called" << std::endl;}
	AA *_pA;
};
void testNoSmart()
{trace("circularRef::testNoSmart()");
	AA *pA = new AA;
	BB *pB = new BB;
	pA->_pB = pB;
	pB->_pA = pA;
	delete pA;
	delete pB;
}

class B;
class A
{public:
	A(){std::cout << "A ctor is called" << std::endl;}
	~A(){std::cout << "A dtor is called" << std::endl;}
	//std::shared_ptr<B> _spB;	// dtor is not called
	std::weak_ptr<B> _spB;	// to avoid circular ref
};
class B
{public:
	B(){std::cout << "B ctor is called" << std::endl;}
	~B(){std::cout << "B dtor is called" << std::endl;}
	//std::shared_ptr<A> _spA;	// dtor is not called
	std::weak_ptr<A> _spA;	// to avoid circular ref
};

void test()
{trace("circularRef::test()");
	std::shared_ptr<A> spA(new A);
	std::shared_ptr<B> spB(new B);
	spA->_spB = spB;
	spB->_spA = spA;
	std::cout << "A shared_ptr cout " << spA.use_count() << std::endl;
	std::cout << "B shared_ptr cout " << spB.use_count() << std::endl;
	std::cout << "B weak_ptr cout " << spA->_spB.use_count() << std::endl;
	std::cout << "A weak_ptr cout " << spB->_spA.use_count() << std::endl;
}
}

void shared_weak()
{
	trace("");
  class B; // forward declaration 
  // for clarity, add explicit destructor to see that they are not called
  class A {public: std::shared_ptr<B> b; ~A(){std::cout << "~A()\n";}}; 
  class B {public: std::shared_ptr<A> a; ~B(){std::cout << "~B()\n";}};
  std::shared_ptr<A> x(new A);  //x->b share_ptr is default initialized
  x->b = std::make_shared<B>(); // you can't do "= new B" on shared_ptr
  x->b->a = x;
  std::cout << x.use_count() << std::endl;  
}


namespace unique
{
void test()
{
	trace("unique::test");
	std::unique_ptr<SM> p1(new SM());
	std::cout << std::boolalpha << static_cast<bool>(p1) << std::endl;
	std::unique_ptr<SM> p2(std::move(p1));
	std::cout << std::boolalpha << static_cast<bool>(p1) << std::endl;
	std::cout << std::boolalpha << static_cast<bool>(p2) << std::endl;
	std::unique_ptr<SM> p3(new SM);
	p3.reset(new SM);
	SM *pSM = new SM;
	p3.reset(pSM);
}
}


int main(int argc, char** argv)
{
	std::cout << "Bismillah\n";
	smart_pointer::test(argc, argv);
	autoP();
	sharedP();
	circularRef::testNoSmart();
	circularRef::test();
	unique::test();
	sharedP_with_custom_delete();
	shared_weak();
	return true;
}

