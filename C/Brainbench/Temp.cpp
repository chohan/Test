//write a code/pseudo-code to factorise an integer (< ULONG_MAX) into it's prime components.
#include "stdafx.h"
#include <iostream>
#include <math.h>
#include <list>


//this function returns prime number equal to or greater than N
unsigned long NextPrimeNumber(unsigned long N)
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

void Factorize(unsigned long N)
{
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
	while(P<=(N/2.0))
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

void main_temp()
{
	std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << std::endl;
  //volatile long a = 10;
  //_InterlockedIncrement(&a);

  //for(int i=0; i<100; i++)
	 // Factorize(i);
	 // //std::cout << i << ", " << NextPrimeNumber(i) << std::endl;

}
