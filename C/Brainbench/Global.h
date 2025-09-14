#include <iostream>
using namespace std;

class GA
{
public:
  GA(){std::cout << "GA default ctor" << std::endl;}
  GA(int i):n(i){std::cout << "GA ctor" << std::endl;}
  GA(const GA& a){std::cout << "GA copy ctor" << std::endl;}
  GA& operator=(const GA& a){std::cout << "GA assignment operator" << std::endl;}
  ~GA(){std::cout << "GA dtor" << std::endl;}
private:
  int n;
};

