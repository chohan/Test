// Iteractive Broker Group IBG

// g++ -g -Wall -o ibg IBG.cpp --std=c++17 -lpthread
#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <chrono>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#define trace(str)(std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << "(): " << str << std::endl)



class A{
public: int i=10;
friend std::ostream& operator<<(std::ostream& os, const A& a);
};
std::ostream& operator<<(std::ostream& os, const A& a){os<<a.i; return os;}

namespace Q10{
class A{ public:
int i=10;
A& operator++(){i++; return *this;}
}; }

namespace Q11{
class A{ public:
  virtual ~A(){f();}
  virtual void f(){std::cout <<"A::f" << std::endl;}
};
class B : public A {
  ~B(){}
  virtual void f(){std::cout <<"B::f" << std::endl;}
};
}

namespace Q12{
struct A{ ~A(){std::cout << "~A";}};
struct B:public A{ virtual ~B(){std::cout << "~B";}};
}

namespace Q13{
  struct Base { virtual void print(int x=1){std::cout<<"Base"<< x <<std::endl;}};
  struct Derived:Base{virtual void print(int x=2){std::cout<<"Derived:"<< x <<std::endl;}}; 
}

namespace Q17{
  class Animal{
    private: std::string m_strName;
    protected:
      Animal(const std::string& strName): m_strName(strName){}
    public:
      const std::string& GetName(){return m_strName;}
      const char* Speak(){return "???";}           
  };

  class Cat:public Animal{
    public: Cat(const std::string& strName):Animal(strName){}
    const char* Speak(){return "Meow";}
  };

  class Dog:public Animal{
    public: Dog(const std::string& strName):Animal(strName){}
    const char* Speak(){return "Woof";}
  };
}




int main(int argc, char** argv)
{
	std::cout << "Bismillah" << std::endl;

{int x, y;
int a=(y=(x=5)*2+7)/4;
std::cout << a << std::endl;}

{int i=2;
int j=2;
int s=(i++)+(++j);
std::cout << "i=" << i << ", j="<<j << ", s="<<s <<std::endl;}

{//Q6
int a=5; int b=0; int &r=a; r=b++;
std::cout << a << r << b << std::endl;}
{//Q8
unsigned int a=20; unsigned int b=14; int c=a^b;
std::cout << c << std::endl;;}

{//Q9
A aa;
std::cout << aa << std::endl;}

{//Q10
Q10::A aa; ++aa;
std::cout << aa.i << std::endl;}

{//Q11
Q11::A* a=new Q11::B;
delete a;}

{//Q12
Q12::A* a = new Q12::B();
delete a;}

{//Q13
Q13::Base* B = new Q13::Derived;
B->print();}

{//Q15 deleting a map element while iterating
  std::map<int, int> mm;
  mm[0] = 0;
  mm[1] = 1;
  mm[2] = 2;
  mm[3] = 3;
  mm[4] = 4;
  auto it=mm.begin();
  while(it!=mm.end()){std::cout << it->first << " " << it->second << std::endl;it++;}

  it=mm.begin();
  while(it!=mm.end()){
    //if(it->first==3) it=mm.erase(it);else it++;
    if(it->first==3) 
      mm.erase(it++);
      //not working {it=it+1;mm.erase(it);}
      // not working {mm.erase(++it);}
    else ++it;
  }
  it=mm.begin();
  while(it!=mm.end()){std::cout << it->first << " " << it->second << std::endl;it++;}
}

{//Q16
  struct A {void f(){}; };
  struct B {int f(){};};
  struct C:A, B{};
  C* pc;
  //pc->A();  //  compile error
  pc->A::f(); //
  pc->B::f(); //
  //pc->A::B::f();  // compile error
}

{//Q17
  Q17::Cat cCat("Fred");
  Q17::Animal* pAnimal = &cCat;
  std::cout << "Animal is named " << pAnimal->GetName() << ", and says " << pAnimal->Speak() << std::endl;
}

{//Q19
  double a = 52.0562;
  float b = 14.25;
  int c;
  c = (int)a;
  a = (double)b;
  std::cout << c << " " << a << std::endl;
}




  return 0;
}
