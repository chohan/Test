#include "stdafx.h"
#include <iostream>
#include <memory>
#include <vector>
#include <stdlib.h>
#include "Global.h"
using namespace std;



namespace IKM1
{
	class my_class
	{
	public:
		int i;
	};
	std::ofstream& operator<<(std::ofstream& ofs, const my_class&){return ofs;}
}

void IKM2()
{
}

namespace IKM3
{
	template<typename T>
	class MyArray
	{
		const T& operator[](size_t i) const;
		const T& operator[](size_t i);
	};
}

namespace IKM4
{
	class IIcon{};

	class IGlyph
	{
	public:
		virtual ~IGlyph(){}
		virtual std::string Text()=0;
		virtual IIcon* Icon()=0;
	};

	class IWidgetSelector
	{
	public:
		virtual ~IWidgetSelector(){}
		virtual void AddItem(IGlyph*)=0;
		virtual IGlyph* Selection()=0;
	};

	class MyItem : public IGlyph
	{
	public:
		virtual std::string Text()
		{
			return this->text;
		}
		virtual IIcon* Icon()
		{
			return this->icon.get();
		}
		void Activate()
		{
			std::cout << "My Item Activated" << endl;
		}
		std::string text;
		std::auto_ptr<IIcon> icon;
	};

	void onDoubleClick(IWidgetSelector* ws)
	{
		IGlyph* glyph = ws->Selection();
		MyItem* item  = dynamic_cast<MyItem*>(glyph);
		if(item)
			item->Activate();
		//ws->Selection()->Activate();
	}
}

void IKM7()
{
	int var = 1;
	//int i = i;
}

void IKM11()
{
	class Outer
	{
	public:
		Outer() { cout << "Outer ctor" << endl;}

		class Inner
		{
		public:
			Inner(){cout << "Inner ctor" << endl;}
		};
		Inner in_obj;
	};

	Outer out_obj;
}

void IKM13()
{
	int r = 0;
	int arr[5] = {2,4,6};
	int* p = arr;
	//r = *arr[2];
	r = *(arr+2);
	r=*(arr+*p);
	r = p[2];
	//r = p+2;
}

namespace IKM13b
{
	class SomeClass
	{
	protected:
		int data;
		friend class AnotherClass;
	};

	void SomeFunc(SomeClass sc)
	{
		//sc.data = 5;
	}

	class AnotherClass
	{
	public:
		void Another(SomeClass sc)
		{
			sc.data = 25;
		}
		friend void SomeFunc(SomeClass sc);
	};

	void main1()
	{
		//SomeClass sc;
		//SomeFunc(sc);
		//cout << sc.data;
	}
}

namespace IKM16
{
	class ExBase
	{
	private:
		static int stat;
	public:
		static int GetStat(){return stat;}
	};
	int ExBase::stat = 25;

	class ExDer1 : public ExBase
	{
	public:
//		friend int Der1Fn(){return ExBase::stat;}
	};

	class ExDer2 : public ExBase{};

	class ExDer : public ExDer1, public ExDer2{};

	void mainA()
	{
//		ExDer d;
//		cout << d.Der1Fn() << endl;
	}

	void mainC()
	{
		cout << ExDer1::GetStat() << endl;
	}

	void mainD()
	{
		//ExDer d;
		//cout << d.GetStat() << endl;
	}

	void mainE()
	{
		cout << ExDer1::ExBase::GetStat() << endl;
	}


}

#include <iomanip>
void IKM20()
{
	const double pi = 3.14159265358979323;

	//A (3.14159)
	cout << std::setw(3) << pi << endl;

	//B (3.14)
	cout << std::setprecision(3) <<  pi << endl;

	//C
	//cout << format("%.2f", pi) << endl;

	//D (3.14)
	cout.precision(3);
	cout << pi << endl;

	//E
	cout << "%.2f" << pi << endl;
}

namespace IKM23
{
class Base
{
    public:
    int data;
};

class DerivedOne : virtual public Base {};

class DerivedTwo : virtual public Base {};

class Derived :  public  DerivedOne,  public  DerivedTwo {};

void main1()
{
    Derived obj;
    obj.data = 5;
}
}

namespace IKM24
{
	class Base
	{
	public:
		virtual int number() {return 0;}
		char letter(){return 'b';}
	};
	class Two : public Base
	{
	public:
		virtual int number() {return 2;}
		char letter(){return 't';}
	};
	class Four : public Base
	{
	public:
		virtual int number() {return 4;}
		char letter(){return 'f';}
	};
	void print(Base* base){cout<<base->letter()<<base->number()<<endl;}

	void pq24()
	{
		Base base;
		Two two;
		Four four;

		print(&base);	//b0
		print(&two);	//b2
		print(&four);	//b4

	}
}

namespace IKM26
{
#define language 337			//Line 1
#if language < 400
#undef language					//Line 2
#else							//Line 3
#define language 850			//Line 4
#ifdef language					//Line 5
	printf("%d", language);		//Line 6
#endif
#endif
}

namespace IKM26a
{
	class A
	{
	public:
		A(){cout << "A ctor" << endl;}
		~A(){cout << "A dtor" << endl;}
	};

	void IKM26a()
	{
		A a[3];
	}
}

namespace IKM27
{
#define YEAR_LENGTH 365
#define MONTH_LENGTH 30
#define DAYCALC (y, m, d) ((y * YEAR_LENGTH) + (m * MONTH_LENGTH) + d)

	void cal()
	{
	int x=1;
	int y=3;
	int z=10;
	//cout << DAYCALC(x+12,y,300) << endl;
	//cout << DAYCALC(x,40-y,3+z) << endl;
	//cout << DAYCALC(x,y,(z+50)) << endl;
	//cout << DAYCALC(x*3,y%3,x) << endl;
	//cout << DAYCALC(4%x,y++,z) << endl;
	}
}

namespace IKM28
{
	class A;
	void IKM28(){}
	void IKM28(A* pA=NULL){}
	void IKM28(int a, A* pA=NULL){}
}

void IKM28B()
{
	//const int Mon = 1, Tue = 2;
	//enum DOW{ Mon = 11, Tue = 12 };
	//int var = DOW::Mon;
}

void IKM29()
{
	class Vector
	{
	public:
		Vector(){}
		~Vector(){}
		Vector(const Vector&){}
	};
}

namespace IKM29b
{
	class SomeClass
	{
		public:
			int data;
		protected:
			class Nest
			{
				public:
				int nested;
			};
		public:
			static Nest* createNest(){return new Nest;}

			friend void use_someclass()
			{
				SomeClass::Nest* nst = SomeClass::createNest();
				nst->nested = 5;
			}

	};

	//void use_someclass2()
	//{
	//	SomeClass::Nest* nst = SomeClass::createNest();
	//	nst->nested = 5;
	//}

	//E option
	class DrvSomeClass : public SomeClass
	{
	public:
		SomeClass::Nest* nst;

		void use_someclass()
		{
			SomeClass::Nest* nst = SomeClass::createNest();
			nst->nested = 5;
		}
	};
	
}

void IKM32()
{
	int *(*p)[5];
	p = new int *[3][5];
}

#include <fstream>
void IKM33()
{
	//A
	std::ofstream outfile;
	outfile.open("SomeFile.txt");

	//C
	std::ofstream outfileC("SomeFile.txt");

	//D
	std::ofstream outfileD;
	outfileD.open("SomeFile.txt", std::ios::out);
}

namespace IKM34
{
	class A
	{
	public:
		int n;
	};
	A a;
	void modify(const A& a)
	{
		const A aa = a;
		//aa.n = 10;
	}
}

void IKM34b()
{
//class Outer
//{
//   int m_o;
//   public:
//   class Inner
//   {
//      int m_i;
//      public:
//        Inner(){}
//        Inner(Outer m_outer, int x)
//        {
//           m_outer.m_o = x;
//        }
//   };
//  
//   Outer(int y)
//   {
//       m_inner.m_i = y;
//   }
//   void Display()
//   {
//       using namespace std;
//       cout << m_o << endl
//            << m_inner.m_i << endl;
//   }
//   Inner m_inner;
//};
}

namespace IKM34c
{
class SomeClass
{
    public:
    int iData;
    //...
 	// int* SomeClass::pData = &SomeClass::iData;

};

}

void IKM35()
{
	class SomeClass
	{
	public:
		int iData;

		//SomeClass::*pData = *sc.iData;
		//int SomeClass::*pData=&SomeData::iData;
		//SomeClass::*pData=&SomeClass::iData;
		//int* SomeClass::pData=&SomeClass::iData;
		//int* SomeClass::pData=&sc.iData;
	};
}

namespace IKM36
{
 	 template <class T> void fn(T a){}
 	 template <> void fn<char*>(char* a){}
}

void IKM37()
{
	std::fstream file;
	file.open("/directoryfile.bin");
	file.open(".directoryfile.bin");
	file.open("C:/directoryfile.bin");
	file.open("C:\\directory\\file.bin");
}

void IKM38()
{
	class Base {
	public:
		void func(){cout<<"Base::func"<<endl;}
	};
	class Derived : public Base {
	public:
		void func(){cout<<"Derived::func"<<endl;}
	};

	Derived objDerived;
	objDerived.Base::func();
}

void IKM39()
{
#define ERROR_MSG "You did something very very wrong and now the \
program will terminate."
//#define MESSAGE = "This is a long message, but I know you have"
//#define MESSAGE = MESSAGE + " plenty of time to read it."
#define GREETING = "Hello!"
//	cout << GREETING << endl;
}

//calling virtual function from ctor and dtor
void IKM39b()
{
	class Base{
	public:
		Base(){cout<<"Base::ctor"<<endl;vfun();}
		virtual ~Base(){cout<<"Base::dtor"<<endl;vfun();}
		virtual void vfun(){cout<<"Base::vfun"<<endl;};
		void fun(){cout<<"Base::fun"<<endl;vfun();};
	};
	class Derived : public Base{
	public:
		Derived(){cout<<"Derived::ctor"<<endl;vfun();}
		~Derived(){cout<<"Derived::dtor"<<endl;vfun();}
		void vfun(){cout<<"Derived::vfun"<<endl;};
	};

	cout << "\nBase b" << endl;
	Base b;
	
	cout << "\nDerived d" << endl;
	Derived d;

	cout << "\nBase* pB = new Derived();" << endl;
	Base* pB = new Derived();
	
	cout << "\npB->fun()" << endl;
	pB->fun();
	
	cout << "\ndelete pB" << endl;
	delete pB;
	
	cout << "\ngoing out of scope" << endl;
}

void IKM39c()
{
	class Base
	{
		public:
		Base(){cout << "In Base Ctor\n";}

		class Nest
		{
			public:
			Nest(){cout << "In Nest Ctor\n"; }
		};   
	};

	class Derive : public Base
	{
		public:       
		Derive(){cout << "In Derive Ctor\n"; }
	};

    Derive obj;
}

void IKM40()
{
	class A{};
	try{
		throw new A;
	}
	catch(A* a)
	{
		delete a;
	}


	try{
		GA a;				//its destructor will be called
		GA* p = new GA();	//its destructor will not be called
		throw 10;
		cout << "could not reach" << endl;
	} catch(...)
	{cout << "was GA's dtor called?" << endl;}
}

void IKM40b()
{
	class A{
	public:
		A(){}
		//~A(){try{throw 2;}catch(...){}}
		~A(){throw 2;}
	};

	A* p = new A();
	try{
	delete p;
	}catch(...){cout << "exception caught" << endl;}
}


namespace IKM41
{
	//template<class T> void Display<T>(std::vector<T>& obj);
	//template<class T> void Display(<std::vector& obj);
	//template<class T> void Display<T>(std::vector& obj);
	template<class T>void Display(std::vector<T>& obj){};
	//template<class T, class Q> void Display<T>(std::vector<Q>& obj);
}

void IKM42()
{
	class A{
	public:
		A(){cout<<"A ctor"<<endl;}
		~A(){cout<<"~A dtor"<<endl;}
	};
	class X{
	public:
		X(){cout<<"X ctor"<<endl;}
		~X(){cout<<"~X dtor"<<endl;}
	};
	class Y : public X{
	public:
		Y(){cout<<"Y ctor"<<endl;}
		~Y(){cout<<"~Y dtor"<<endl;}
		A a;
	};
	Y a;
}

void IKM42a()
{
	fstream fs("f:/sample.txt", fstream::in|fstream::out);
	char str[] = "786 Hello World";
	fs.write(str, strlen(str));

	char buf[255];
	//fs.seekg(fstream::
	fs.read(buf, 255);
	cout << buf << endl;
}

void IKM45()
{
	class SomeClass
	{
	public:
		SomeClass(){cout<<"SomeClass ctor"<<endl;}
		~SomeClass(){cout<<"~SomeClass dtor"<<endl;}

		void* operator new(size_t size)//implicitly declared as a static member function
		{
			void * p = malloc(size);
			if (p == 0)  throw "allocation failure";  //instead of std::bad_alloc
			return p; 
		}
		//void* operator new[](size_t, int){return NULL;};
		//SomeClass* operator new(size_t){return this;};
		//SomeClass* operator new(size_t, int){return this;};
		void operator delete (void *p) //implicitly declared as a static member function
		{
			SomeClass* pc = static_cast<SomeClass*>(p); 
			free(p);	
		}
	};
}

void IKM48()
{
	class String{
	public:
		//char* operator char*();
		//String operator char*();
	////	char* operator(){return str;}
		//operator char*();
		//char* operator String();
	  private:
	    char* str;
	};
//	String str;
//	char* sz = static_cast<char*>(str);
}

//IKM1
namespace my_stuff
{
	class my_class
	{
	public:
		int i;
	};
	std::ofstream& operator<<(std::ofstream& f, const my_class&);

}


//######################### main_IKM ############################
void main_IKM()
{
	cout << "main_IKM" << endl;
	//IKM1::func();
	//IKM2();
	//IKM4();
	//IKM11();
	//IKM16::mainD();
	//IKM16::mainE();
	//IKM20();
	//IKM26a::IKM26a();
	//IKM38();
	//IKM39b();
	//IKM39c();
	//IKM40b();
	//IKM40();
	//IKM42a();
}
