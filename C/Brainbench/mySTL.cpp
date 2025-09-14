#include "stdafx.h"
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include <functional>   // std::greater
#include <iterator>
#include <memory>
#include <string>
#include <initializer_list>	//C++11 feature
using namespace std;


namespace STL1
{
	void print_value(int a)
	{
		cout << a << endl;
	}

	class print
	{
	public:
		void operator()(int val)	//app operator
		{ cout << val << endl; }
	};

	class random
	{
	public:
		random():i(50){}
		int operator()(){return i++;}	//app operator
	private:
		int i;
	};

	void STL1()
	{
	std::list<int> lst;
	for(int i=0; i<10; i++)
		lst.push_back(i);

	int i=25;
	std::fill_n(back_inserter(lst), 5, 25);	//will insert 25,25 at the end
	//std::generate_n(lst.begin(), 5, random());	//will insert 50-54 at the start
	std::generate_n(front_inserter(lst), 5, random());	//will insert 50-54 at the start

	//std::for_each(lst.begin(), lst.end(), print_value);
	std::for_each(lst.begin(), lst.end(), print());
// copy(A.begin(), A.end(), ostream_iterator<int>(cout, " "));
	}

	std::string repeat(std::string str, int number)
	{
		std::string res;
		while(number--) res += str;
		cout << str << endl;
		return res;
	}

	void print_str(std::string str)
	{
		cout << str << endl;
	}

	void print_pair(std::pair<std::string, int> pair)
	{
		cout << "key=" << pair.first << " value=" << pair.second << endl;
	}

	void trans()
	{
	std::list<std::string> s1;
	s1.push_back("1");
	s1.push_back("2");
	s1.push_back("3");
	std::list<int> n1;
	n1.push_back(1);
	n1.push_back(2);
	n1.push_back(3);
	std::transform(s1.begin(), s1.end(), n1.begin(), s1.begin(), repeat);
	for_each(s1.begin(), s1.end(), print_str);
	}

	//multimap
	void mymultimap()
	{
		std::multimap<string, int> mm;
		mm.insert(pair<string, int>("a", 1));
		mm.insert(pair<string, int>("c", 2));
		mm.insert(pair<string, int>("b", 3));
		mm.insert(pair<string, int>("b", 4));
		mm.insert(pair<string, int>("a", 5));
		mm.insert(pair<string, int>("b", 6));

		cout << "Number of elements with key a: " << mm.count("a") << endl;
		cout << "Number of elements with key b: " << mm.count("b") << endl;
		cout << "Number of elements with key c: " << mm.count("c") << endl;

		cout << "printing multimap values" << endl;
		for_each(mm.begin(), mm.end(), print_pair);

		std::cout << "b => " << mm.find("b")->second << '\n';	// in case of multiple elements, it will print first one

		//find range of pairs with "b" keys
		//std::pair<multimap<string, int>::iterator, multimap<string, int>::iterator> pp;
		auto pp = mm.equal_range("b");	// returning pair of iterator values (start and end)
		multimap<string, int>::iterator itr = pp.first;
		cout << "printing pairs with b" << endl;
		while(itr != pp.second)
		//for(multimap<string, int>::iterator it2 = pp.first; it2 != pp.second;  ++it2)
		{
			print_pair(*itr++);
		}
		mm.clear();
	}

	void fn_deq()
	{
		deque<int> deq;
		for(int i=0; i<10; i++)
			deq.push_front(i);

		std::copy(deq.begin(), deq.end(), std::ostream_iterator<int>(cout, " "));
		std::cout << deq[5] << std::endl;
	}

}	//STL1

namespace STL2
{
	class print
	{
	public:
		void operator()(int val) 
		{ cout << val << endl; }
	};
	void print_value(int i){cout<<i<<endl;}


	int  op_inc(int i){return ++i;}
	int  op_sum(int i, int j){return i+j;}

	//predicates
	bool IsOdd(int i){return (i%2==1);}

	//binary predicates
	bool IsEqual(int i, int j){return (i==j);}
	bool op_less(int i, int j){return i<j;}
	bool op_greater(int i, int j){return i>j;}

	//non-mutating algos
	void non_mutating_algos()
	{
		//std::string str("SALAHUDDIN");
		//std::reverse(str.begin(), str.end());
		int ary[] = {1,2,3,4,4,4,6,7,8,9};
		//int ary2[] = {5,4,6};
		int ary2[] = {1,2,3};
		std::vector<int> v(ary, ary+10);
		std::vector<int> v2(ary2, ary2+3);
		std::vector<int>::iterator itr;

		//Returns an interator to the first occurrence in the range [first1,last1]  of any of the elements in [first2,last2].
		//find_end search the last occurance
		cout << "\nfind_first_of " << endl;
		std::copy(v.begin(), v.end(), ostream_iterator<int>(std::cout, " "));
		std::cout << " , ";
		std::copy(ary2, ary2+3, ostream_iterator<int>(std::cout, " "));
		itr = find_first_of(v.begin(), v.end(), ary2, ary2+3);
		cout << "\nfind_first_of " << *itr << endl;

		//search a sub sequence
		cout << "\nsearch" << endl;
		std::copy(v.begin(), v.end(), ostream_iterator<int>(std::cout, " "));	std::cout << " , ";		std::copy(v2.begin(), v2.end(), ostream_iterator<int>(std::cout, " "));
		itr = std::search(v.begin(), v.end(), v2.begin(), v2.end(), IsEqual);
		cout << "\nsearch " << *itr << endl;

		//searches s set of value
		cout << "\nsearch_n 3, 4" << endl;
		std::copy(v.begin(), v.end(), ostream_iterator<int>(std::cout, " "));
		itr = std::search_n(v.begin(), v.end(), 3, 4, IsEqual);
		cout << "\nsearch_n " << *itr << endl;

		//Searches the range [first,last) for the first occurrence of two consecutive equal elements, and returns an iterator to the first of these two elements.
		cout << "\nadjecent_find" << endl;
		std::copy(v.begin(), v.end(), ostream_iterator<int>(std::cout, " "));
		itr = adjacent_find(v.begin(), v.end());
		cout << "\nadjecent_find " << *itr << endl;

		std::cout << "\ncout and count_if\n";
		std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
		cout << "\ncount ('6' in above collection)=" << std::count(v.begin(), v.end(), 6);
		cout << "\ncount_if (odd in above collection)=" << std::count_if(v.begin(), v.end(), IsOdd) << endl;

		//returns a pair of iterators to the first element in each range which differs in both sequences.
		std::cout << "\nmismatch\n";
		std::copy(v.begin(), v.end(), ostream_iterator<int>(std::cout, " "));	std::cout << " , ";		std::copy(ary2, ary2+3, ostream_iterator<int>(std::cout, " "));
		std::pair<std::vector<int>::iterator, int*> mypair;
		mypair = std::mismatch(v.begin(), v.begin()+4, ary2);//v2.begin());//, IsEqual);
		cout << "\nmismatch first " << *mypair.first << " second " << *mypair.second << endl;

		cout << "\nequal " << std::equal(v.begin(), v.begin()+3, ary2);//v2.begin(), IsEqual);
	};	//non_mutating_algos()

	//mutating algo
	void mutating_algos()
	{
		int myints[] = {1,2,3,4,5,6,7,8,9};
		std::vector<int> v1(myints, myints+9);
		std::vector<int> v2(9);
		//v2.resize(9);

		// initial vector
		std::cout << "\ninitial vector values\n";
		copy(v1.begin(), v1.end(), std::ostream_iterator<int>(cout, " "));

		std::cout << "\n\ncopy\n";
		//std::copy(v1.begin(), v1.begin()+9, v2.begin());
		//cout<<"\ncopy\n";std::for_each(v2.begin(), v2.end(), print());
		copy(v2.begin(), v2.end(), std::ostream_iterator<int>(cout, " "));

		std::cout << "\n\ncopy_backward: maintains same order but position such a way that last point is at v2.end\n";
		std::copy_backward(v1.begin(), v1.begin()+3, v2.end());
		//cout<<"\ncopy_backward\n";std::for_each(v2.begin(), v2.end(), print());
		copy(v2.begin(), v2.end(), std::ostream_iterator<int>(cout, " "));

		std::cout << "\n\nrevers_copy: copies but reverses the order\n";
		std::reverse_copy(v1.begin(), v1.begin()+3, v2.begin());
		//cout<<"\ncopy_backward\n";std::for_each(v2.begin(), v2.end(), print());
		copy(v2.begin(), v2.end(), std::ostream_iterator<int>(cout, " "));
		
		//std::swap(v1, v2);
		//cout<<"\nswap\n";std::for_each(v1.begin(), v1.end(), print());
		
		//std::swap_ranges(v1.begin()+1, v1.begin()+5, v2.begin());
		//cout<<"\nswap_ranges\n";std::for_each(v1.begin(), v1.end(), print());
		
		//cout<<"\nitr_swap before\n";std::for_each(v1.begin(), v1.end(), print());
		//std::iter_swap(v1.begin(), v1.rbegin());
		//cout<<"\nitr_swap after\n";std::for_each(v1.begin(), v1.end(), print());
		
		cout<<"\n\nunary transform(op_in()) before: ";copy(v1.begin(), v1.end(), std::ostream_iterator<int>(cout, " "));//std::for_each(v1.begin(), v1.end(), print());
		std::transform(v1.begin(), v1.end(), v2.begin(), op_inc);
		cout<<"\nunary transform(op_in())  after: ";copy(v2.begin(), v2.end(), std::ostream_iterator<int>(cout, " "));//std::for_each(v2.begin(), v2.end(), print());

		cout<<"\n\nbinary transform(op_sum()) before: ";copy(v1.begin(), v1.end(), std::ostream_iterator<int>(cout, " "));
		std::transform(v1.begin(), v1.end(), v1.begin(), v2.begin(), op_sum);
		cout<<"\nbinary transform(op_sum()) after: ";copy(v2.begin(), v2.end(), std::ostream_iterator<int>(cout, " "));//std::for_each(v2.begin(), v2.end(), print());

		cout<<"\n\nreplace before: ";copy(v2.begin(), v2.end(), std::ostream_iterator<int>(cout, " "));
		std::replace(v2.begin(), v2.end(), 5, 999);
		cout<<"\nreplace  after: ";copy(v2.begin(), v2.end(), std::ostream_iterator<int>(cout, " "));//std::for_each(v2.begin(), v2.end(), print());

		//std::replace_if(v2.begin(), v2.end(), IsOdd, 99);
		//cout<<"\nreplace_if\n";std::for_each(v2.begin(), v2.end(), print());

		cout<<"\n\nreplace_copy before: ";copy(v1.begin(), v1.end(), std::ostream_iterator<int>(cout, " "));
		std::replace_copy(v1.begin(), v1.end(), v2.begin(), 4, 99);
		cout<<"\nreplace_copy  after; ";copy(v2.begin(), v2.end(), std::ostream_iterator<int>(cout, " "));//std::for_each(v2.begin(), v2.end(), print());

		cout<<"\n\nreplace_copy_if before: ";copy(v1.begin(), v1.end(), std::ostream_iterator<int>(cout, " "));
		std::replace_copy_if(v1.begin(), v1.end(), v2.begin(), IsOdd, 99);
		cout<<"\nreplace_copy_if  after: ";copy(v2.begin(), v2.end(), std::ostream_iterator<int>(cout, " "));//std::for_each(v2.begin(), v2.end(), print());
	}	//mutating_algos

	//sorting algos
	void sorting_algos()
	{
		std::cout << __FUNCTION__ << std::endl;
		int myints[] = {10,2,13,4,5,6,7,8,9};
		std::vector<int> v1(myints, myints+9);
		std::vector<int> v2(9);

		//cout<<"\nsort before\n";std::for_each(v1.begin(), v1.end(), print());
		//std::sort(v1.begin(), v1.begin()+4);
		//cout<<"\nsort after\n";std::for_each(v1.begin(), v1.end(), print());
		//std::sort(v1.begin(), v1.end(), op_greater);
		//cout<<"\nsort after\n";std::for_each(v1.begin(), v1.end(), print());

		//sort on left and right of nth
		std::cout << "\n5th_element befor: ";copy(v1.begin(), v1.end(), std::ostream_iterator<int>(std::cout, " "));
		std::nth_element(v1.begin(), v1.begin()+5, v1.end());
		cout<<"\n5th_element after: ";copy(v1.begin(), v1.end(), std::ostream_iterator<int>(std::cout, " "));

		//
		int first[] = {15,10,5,25,20};
		int second[] = {20,40,10,50,30};

		// sort
		cout<<"\n\nsort befor: ";copy(first, first+5, std::ostream_iterator<int>(std::cout, " "));
		std::sort(first, first+5);
		cout<<"\nsort after: ";copy(first, first+5, std::ostream_iterator<int>(std::cout, " "));//std::for_each(first, first+5, print());

		// sort
		cout<<"\n\nsort befor: ";copy(second, second+5, std::ostream_iterator<int>(std::cout, " "));
		std::sort(second, second+5);
		cout<<"\nsort after: ";copy(second, second+5, std::ostream_iterator<int>(std::cout, " "));//std::for_each(second, second+5, print());

		std::cout << "\n\nunion(concatenating two arrays)";
		std::vector<int> vv(10);
		cout<<"\nset_union befor: "; std::cout << "first array ";copy(first, first+5, std::ostream_iterator<int>(std::cout, " ")); std::cout << ", second array ";copy(second, second+5, std::ostream_iterator<int>(std::cout, " "));
		std::set_union(first, first+5, second, second+5, vv.begin());
		cout<<"\nset_union after: ";copy(vv.begin(), vv.end(), std::ostream_iterator<int>(std::cout, " "));
		
		std::cout << "\n\nintersection(common elements between two rows)";
		std::fill(vv.begin(), vv.end(), 0);
		cout<<"\nset_intersection befor: "; std::cout << "first array ";copy(first, first+5, std::ostream_iterator<int>(std::cout, " ")); std::cout << ", second array ";copy(second, second+5, std::ostream_iterator<int>(std::cout, " "));
		std::set_intersection(first, first+5, second, second+5, vv.begin());
		cout<<"\nset_intersection after: ";copy(vv.begin(), vv.end(), std::ostream_iterator<int>(std::cout, " "));
		
		std::cout << "\n\nset_difference(finding first array elements which are not there in second array)";
		std::fill(vv.begin(), vv.end(), 0);
		cout<<"\nset_difference befor: "; std::cout << "first array ";copy(first, first+5, std::ostream_iterator<int>(std::cout, " ")); std::cout << ", second array ";copy(second, second+5, std::ostream_iterator<int>(std::cout, " "));
		std::set_difference(first, first+5, second, second+5, vv.begin());
		cout<<"\nset_difference after: ";copy(vv.begin(), vv.end(), std::ostream_iterator<int>(std::cout, " "));
		
		std::cout << "\n\nset_symmetric_difference(finding elements of both arrays which are NOT common between the two)";
		std::fill(vv.begin(), vv.end(), 0);
		cout<<"\nset_symmetric_difference befor: "; std::cout << "first array ";copy(first, first+5, std::ostream_iterator<int>(std::cout, " ")); std::cout << ", second array ";copy(second, second+5, std::ostream_iterator<int>(std::cout, " "));
		std::set_symmetric_difference(first, first+5, second, second+5, vv.begin());
		cout<<"\nset_symmetric_difference after: ";copy(vv.begin(), vv.end(), std::ostream_iterator<int>(std::cout, " "));
	}	//sorting_algos

	//sorting
	void mysort()
	{
		vector<int> v;
		for(int i=0; i<10; i++)
			v.push_back(rand());

		cout << "\nrandom order" << endl;
		std::copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
		
		cout << "\n\ndefault sort" << endl;
		std::sort(v.begin(), v.end());
		std::copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
		
		cout << "\n\ndescending sort" << endl;
		std::sort(v.begin(), v.end(), std::greater<int>());
		std::copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
		
		cout << "\n\nascending sort" << endl;
		std::sort(v.begin(), v.end(), less<int>());
		std::copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
	}
}	//STL2



namespace smart_pointer
{
  class A
  {
  public:
	  A() {cout << "A ctor" << endl;}
	  ~A() {cout << "A dtor" << endl;}

	  void func(){cout << "this is func" << endl;}
  };
  
  void f1()
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

namespace adapters
{
	void FIFO() //std::queue
	{
		std::cout << "\n" << __FUNCTION__ << std::endl;
		std::list<int> l1;
		std::queue<int, list<int>> q1;

		// FIFO queue
		for(int i=0; i<10; i++)
			q1.push(i);

		std::cout << "FIFO/std::queue operation";
		while(!q1.empty())
		{
			std::cout << " " << q1.front();
			q1.pop();
		}
		std::cout << std::endl;
	}

	void LIFO()	//std::stack
	{
		std::cout << "\n" << __FUNCTION__ << std::endl;
		std::list<int> l1;
		std::stack<int, list<int>> q1;

		// LIFO/Stack
		for(int i=0; i<10; i++)
			q1.push(i);

		std::cout << "LIFO/std::stack operation";
		while(!q1.empty())
		{
			std::cout << " " << q1.top();
			q1.pop();
		}
		std::cout << std::endl;
	}

	void PQ()	//std::priority_queue
	{
		std::cout << "\n" << __FUNCTION__ << std::endl;
		std::priority_queue<int, std::vector<int>, std::greater<int>> myPQ;
		myPQ.push(10);
		myPQ.push(5);
		myPQ.push(15);
		myPQ.push(25);
		myPQ.push(17);

		while(!myPQ.empty())
		{
			std::cout << myPQ.top() << " ";
			myPQ.pop();
		}
	}
}

//#include <initializer_list>
class SequenceClass {
public:
    SequenceClass(std::initializer_list<int> list);
};

void func(std::initializer_list<int> il)
{
	int a;
	int b;
	int c;
	std::cout << "a="<<a << ", b="<<b << ", c="<<c << std::endl;
}

void main_mySTL()
{
	std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << std::endl;
  
	//STL1::STL1();
	//STL1::trans();
	//STL1::mymultimap();
	//STL1::fn_deq();
	//STL2::non_mutating_algos();
	//STL2::mutating_algos();
	//STL2::sorting_algos();
	//STL2::mysort();
	//smart_pointer::f1();
	//adapters::FIFO();
	//adapters::LIFO();
	adapters::PQ();

}
