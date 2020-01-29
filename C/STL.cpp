// g++ STL.cpp -g -w --std=c++17 -lpthread
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

#define trace(str)(std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << "(): " << str << std::endl)
template<typename T> void print(T coll){for(auto x:coll)std::cout<<x<<" "; std::cout<<std::endl;}
void print_value(int i){std::cout << i << " ";}
void print_str(std::string str){std::cout << str << " ";}
void print_pair(std::pair<std::string, int> pair){std::cout << "key=" << pair.first << " value=" << pair.second << std::endl;}

class print_op
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
std::string repeat(std::string str, int number)
{
	std::string res;
	while(number--) res += str;
	cout << str << endl;
	return res;
}

int  op_inc(int i){return ++i;}
int  op_sum(int i, int j){return i+j;}

//predicates
bool IsOdd(int i){return (i%2==1);}

//binary predicates
bool IsEqual(int i, int j){return (i==j);}
bool op_less(int i, int j){return i<j;}
bool op_greater(int i, int j){return i>j;}



namespace STL1 // new C++ 11 features
{
void test_lambda()	//lamdaExpression
{
//	[=]	// pass by value
//	[&]	// pass by ref
	[](int x, int y) -> int { return x + y; };

	// count upper case letters
	char s[] = "Hello World";
	int Uppercase = 0;
	std::for_each(s, s+sizeof(s), [&Uppercase](char c) { if (isupper(c)) Uppercase++; }	// lamda expression
	);
	std::cout << "String: " << s << ", uppercase=" << Uppercase << std::endl;
}

void test_uniformInitialization()
{
	class C {
		int a; int b;
		int arr[4];
	public:
		C(int i, int j) : arr{ 1, 2, 3, 4 } {};	// member array initialization

		std::vector<std::string> vs = { "Amir", "Ammar", "Sana" };
		std::map<std::string, int> ms = { {"Amir", 1}, {"Ammar", 2}, {"Sana", 3} };
	};

	C c{ 0, 0 };	// equivalent to C c(0, 0);	
}

void test_defualt_delete()
{
	class C {
	public:
		C() = default;	// compiler will generate default implementation
		virtual ~C() = default;	// compiler will generate default implementation

		C & operator =(const C &) = delete;	// compiler will NOT generate assignment operator
		C(const C &) = delete;	// compiler will NOT generate copy constructor
	};

	C c;
//	C b(c);	// compiler error
}

void test_delegating_constructor()
{
	class C
	{
		int x, y;
		char *p;
	public:
		C() :C(4) { std::cout << "ctr without parameter" << std::endl; }
		C(int a) : x(a), y(0) { std::cout << "ctr with parameter" << std::endl; }
	};

	C c;
}

void test_regex()
{
	const char *reg_esp = "[ ,.\\t\\n;:]"; //list separator charactors
	std::regex rgx(reg_esp);
	std::cmatch match;
	const char *target = "Unseen, University - Ankh-Morpork; hello: world";
	if (std::regex_search(target, match, rgx)) {
		const size_t n = match.size();
		for (size_t a = 0; a < n; a++) {
			std::string str(match[a].first, match[a].second);
			std::cout << "\nregex: " << str << "\n";
		}
	}
}

namespace ExplicitOverride	// it forces compiler to check and generate an error if the signature of overriding virtual funciton in derived class is different from base class
{
	class Base
	{
	public:
		virtual void vfunc(int a){std::cout << __func__ << std::endl;}
	};

	class Derived : public Base
	{
		virtual void vfunc(int a) override {std::cout << __FUNCTION__ << std::endl;}
	};
}	// ExplicitOverride

namespace final
{
	// final virtual fuction cannot be overridden
	class Base
	{
	public:
		virtual void vfunc(int a) final {std::cout << __FUNCTION__ << std::endl;}
		// non virtual func cannot be declared as final
	};

	class Derived : public Base
	{
		//void vfunc(int a) {std::cout << __FUNCTION__ << std::cout << std::endl;}	// a virtual and final function cannnot be overridde in derived class
	};

	// final base class cannot be overriden
	class Base2 final{};
	//class Derived2 : public Base2 {};	// a final base class cannot be derived from
}	// final

void test_NewStringLiterals()
{
	char*		  utf8	= u8"I am UTF-8 string";
	char16_t*	utf16	= u"I am UTF-16 string";
	char32_t*	utf32	= U"I am UTF-32 string";
	std::cout << "utf8: " << utf8 << "\tutf16: " << utf16 << "\tutf32: " << utf32 << std::endl;
}

void test(int argc, char** argv)
{
	test_lambda();
	test_uniformInitialization();
	test_defualt_delete();
	test_delegating_constructor();
	test_regex();
	test_NewStringLiterals();
}
}	// STL1


namespace STL2
{

//non-mutating algos
void non_mutating_algos()
{
	// all_of, any_of, none_of
	std::cout << "\nall_of, any_of, none_of\n";
	std::vector<int> all_positive = { 1,2,3,4 };
	std::vector<int> some_positive = { -1,2,-3,4 };
	std::vector<int> none_positive = { -1,-3,-5,-8 };

	// std::string ops;

	// ops = "std::all_of"; auto first = all_positive.begin();
	// std::cout << ops << ": " << std::all_of(first, first + 4, [](int n) { return n >= 0; }) << std::endl;

	// ops = "std::any_of"; first = some_positive.begin();
	// std::cout << ops << ": " << std::any_of(first, first + 4, [](int n) { return n >= 0; }) << std::endl;

	// ops = "none_of"; first = none_positive.begin();
	// std::cout << ops << ": " << std::none_of(first, first + 4, [](int n) { return n >= 0; }) << std::endl;


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

	//searches 3 times 4
	cout << "\nsearch_n, searches 3 times 4" << endl;
	std::copy(v.begin(), v.end(), ostream_iterator<int>(std::cout, " "));
	itr = std::search_n(v.begin(), v.end(), 3, 4, IsEqual);	
	cout << "\nsearch_n " << *itr << endl;

	//Searches the range [first,last) for the first occurrence of two consecutive equal elements, and returns an iterator to the first of these two elements.
	cout << "\nadjecent_find, two consecutive equal elements" << endl;
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
	cout << "\nmismatch first " << *mypair.first << ", second " << *mypair.second << endl;

	cout << "\nequal " << bool(std::equal(v.begin(), v.begin()+3, ary2));//v2.begin(), IsEqual);
};	//non_mutating_algos()

//mutating algo
void mutating_algos()
{
	trace("\n\n\n");
	int myints[] = {1,2,3,4,5,6,7,8,9};
	std::vector<int> v1(myints, myints+9);
	std::vector<int> v2(9);
	//v2.resize(9);

	// initial vector
	std::cout << "\ninitial vector values\nv1: ";
	copy(v1.begin(), v1.end(), std::ostream_iterator<int>(cout, " "));
	std::for_each(v1.begin(), v1.end(), print_op());

	std::cout << "\n\ncopy v1, v2\nv2: ";
	std::copy(v1.begin(), v1.begin()+9, v2.begin()); print(v2);

	std::cout << "\n\ncopy_backward: maintains same order but position such a way that last point is at v2.end\n";
	std::cout << "v1: "; print(v1); std::cout << "v2: "; print(v2);
	std::copy_backward(v1.begin(), v1.begin()+3, v2.end());
	std::cout << "copy_backward, v2: "; print(v2); 

	std::cout << "\nrevers_copy: copies but reverses the order\n";
	std::reverse_copy(v1.begin(), v1.begin()+3, v2.begin());
	std::cout << "v1: "; print(v1); std::cout << "v2: "; print(v2);
	
	std::cout << "\nswap\n";
	std::swap(v1, v2);
	std::cout << "v1: "; print(v1); std::cout << "v2: "; print(v2);
	
	std::cout << "\nswap_ranges(1-4)\n";
	std::swap_ranges(v1.begin()+1, v1.begin()+5, v2.begin());
	std::cout << "v1: "; print(v1); std::cout << "v2: "; print(v2);
	
	std::cout<<"\nitr_swap(swaping second element)\n";
	std::iter_swap(v1.begin()+1, v2.begin()+1);
	std::cout << "v1: "; print(v1); std::cout << "v2: "; print(v2);
	
	cout<<"\ntrans (unary, op_inc())\n";
	std::transform(v1.begin(), v1.end(), v2.begin(), op_inc);
	std::cout << "v1: "; print(v1); std::cout << "v2: "; print(v2);

	cout<<"\ntransform (binary, op_sum())\n";
	std::transform(v1.begin(), v1.end(), v2.begin(), v2.begin(), op_sum);
	std::cout << "v1: "; print(v1); std::cout << "v2: "; print(v2);

	std::cout<<"\nreplace(v2, 5=>999)\n";
	std::replace(v2.begin(), v2.end(), 5, 999);
	std::cout << "v1: "; print(v1); std::cout << "v2: "; print(v2);

	std::cout << "\nreplace_if(v1, IsOdd()=>77)\n";
	std::replace_if(v1.begin(), v1.end(), IsOdd, 77);
	std::cout << "v1: "; print(v1); std::cout << "v2: "; print(v2);

	std::cout<<"\nreplace_copy(v1, 77=>99)\n";
	std::replace_copy(v1.begin(), v1.end(), v2.begin(), 77, 99);
	std::cout << "v1: "; print(v1); std::cout << "v2: "; print(v2);

	std::cout<<"\nreplace_copy_if(v1, IsOdd=>88)\n";
	std::replace_copy_if(v1.begin(), v1.end(), v2.begin(), IsOdd, 88);
	std::cout << "v1: "; print(v1); std::cout << "v2: "; print(v2);

	std::cout << "\nfill_n(v1, 5x25 at back)\n";
	std::fill_n(std::back_inserter(v1), 5, 25);
	std::cout << "v1: "; print(v1); std::cout << "v2: "; print(v2);
	
// 	std::cout << "\generate_n(v2, 5x50 at front)\n";
// 	std::generate_n(std::back_inserter(v2), 5, 50);
// 	std::cout << "v1: "; print(v2); std::cout << "v2: "; print(v2);
}	//mutating_algos

//sorting algos
void sort_set()
{
	trace("\n\n\n");
	std::vector<int> a1 = {15,10,5,25,20};
	std::vector<int> a2 = {20,40,10,50,30};
	std::vector<int> vv = {10,2,13,4,5,6,7,8,9};
	std::cout << "a1: "; print(a1); std::cout << "a2: "; print(a2); std::cout << "vv: "; print(vv);

	// std::cout<< "\nnth_element, (sort on left and right of 5th)\n";
	// std::nth_element(vv.begin(), vv.begin()+5, vv.end());
	// std::cout << "vv: "; print(vv);

	std::cout << "\nunion(concatenating two arrays)\n";
	std::fill(vv.begin(), vv.end(), 0);
	std::set_union(a1.begin(), a1.end(), a2.begin(), a2.end(), vv.begin());
	
	std::cout << "\nintersection(common elements between two rows)\n";
	std::fill(vv.begin(), vv.end(), 0);
	std::set_intersection(a1.begin(), a1.begin()+5, a2.begin(), a2.begin()+5, vv.begin());
	std::cout << "a1: "; print(a1); std::cout << "a2: "; print(a2); std::cout << "vv: "; print(vv);
	
	std::cout << "\nset_difference(finding first array elements which are not there in second array)\n";
	std::fill(vv.begin(), vv.end(), 0);
	std::set_difference(a1.begin(), a1.begin()+5, a2.begin(), a2.begin()+5, vv.begin());
	std::cout << "a1: "; print(a1); std::cout << "a2: "; print(a2); std::cout << "vv: "; print(vv);
	
	std::cout << "\nset_symmetric_difference(finding elements of both arrays which are NOT common between the two)\n";
	std::fill(vv.begin(), vv.end(), 0);
	std::set_symmetric_difference(a1.begin(), a1.begin()+5, a2.begin(), a2.begin()+5, vv.begin());
	std::cout << "a1: "; print(a1); std::cout << "a2: "; print(a2); std::cout << "vv: "; print(vv);
}	//sorting_algos

void FIFO() //std::queue
{
	trace("\n");
	std::queue<int, list<int>> q1;
	for(int i=0; i<10; i++)	q1.push(i);

	std::cout << "FIFO/std::queue operation: ";
	while(!q1.empty())
	{
		std::cout << q1.front() << " ";
		q1.pop();
	}
	std::cout << std::endl;
}

void LIFO()	//std::stack
{
	trace("\n");
	std::stack<int, std::vector<int>> q1;
	for(int i=0; i<10; i++)	q1.push(i);

	std::cout << "LIFO/std::stack operation: ";
	while(!q1.empty())
	{
		std::cout << q1.top() << " ";
		q1.pop();
	}
	std::cout << std::endl;
}

void PriorityQ()	//std::priority_queue
{
	trace("\n");
	std::priority_queue<int, std::vector<int>, std::less<int>> pq;
	pq.push(10);
	pq.push(5);
	pq.push(15);
	pq.push(25);
	pq.push(17);

	std::cout << "\nPriority > operation: ";
	while(!pq.empty())	
	{
		std::cout << pq.top() << " ";
		pq.pop();
	}
	std::cout << std::endl;
}

//multimap
void mymultimap()
{
	trace("\n");
	std::multimap<string, int> mm;
	mm.insert(pair<string, int>("a", 1));
	mm.insert(pair<string, int>("c", 2));
	mm.insert(pair<string, int>("b", 3));
	mm.insert(pair<string, int>("b", 4));
	mm.insert(pair<string, int>("a", 5));
	mm.insert(pair<string, int>("b", 6));
	for_each(mm.begin(), mm.end(), print_pair);

//	for(auto e:mm) std::cout << "K/V: " << e.first << "/" << e.second << " ";
	cout << "Number of elements with key a: " << mm.count("a") << endl;
	cout << "Number of elements with key b: " << mm.count("b") << endl;
	cout << "Number of elements with key c: " << mm.count("c") << endl;

	cout << "printing multimap values" << endl;

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
	trace("\n");
	deque<int> deq;
	for(int i=0; i<10; i++)
		deq.push_front(i);

	std::copy(deq.begin(), deq.end(), std::ostream_iterator<int>(cout, " "));
	std::cout << deq[5] << std::endl;
}

void test(int argc, char** argv)
{
	STL2::non_mutating_algos();
	STL2::mutating_algos();
	STL2::sort_set();
	STL2::FIFO();
	STL2::LIFO();
	STL2::PriorityQ();
	STL2::mymultimap();
	STL2::fn_deq();
}
}	//STL2



namespace STL3
{
void algo(int argc, char** argv)
{
	trace("");

	{trace("\n\niota: adds X number of elements with incrementing each");
		int a[5] = { 0 };
		char c[3] = { 0 };
		std::iota(a, a + 5, 10);
		std::iota(c, c + 3, 'a');
		std::copy(a, a + 5, std::ostream_iterator<int>(std::cout, " ")); std::cout << "\n";
		std::copy(c, c + 3, std::ostream_iterator<char>(std::cout, " ")); std::cout << "\n";
//		std::cout<<"\n\n";
	}

	{trace("\n\ngenerate");
		std::srand(unsigned(std::time(0)));
		std::vector<int> v(10);
		std::generate(v.begin(), v.end(), [](){return std::rand()%100;}); print(v);
	}
		
	{trace("\n\ntransform");
		std::vector<int> v1 = {1,2,3,4,5,6,7,8,9};
		std::vector<int> v2 = {1,2,3,4,5,6,7,8,9};
		std::vector<int> r1,r2;
		r1.resize(v1.size());
		r2.resize(v2.size());
		class doubler
		{public:		
			int operator()(int i){return i*2;}
			int operator()(int i, int j){return i+j;}
		};
		std::transform(v1.begin(),v1.end(), r1.begin(), doubler());
		print(v1);print(r1);
		std::transform(v1.begin(), v1.end(), v2.begin(), r2.begin(), doubler());
		print(v1);print(v2);print(r2);
	}

	{	trace("\n\nincludes");
		std::vector<int> V = {4,6,2,8,19,23,90,45,12,66};
		std::vector<int> v = {19,8,23};
		std::sort(V.begin(), V.end());
		std::sort(v.begin(), v.end());
		if(std::includes(V.begin(), V.end(), v.begin(), v.end()))
			std::cout << "V contains all elements of v";
	}
	{	std::vector<int> V = {4,6,2,8,19,23,90,45,12,66};
		std::vector<int> v = {19,8,23};
		std::sort(V.begin(), V.end());
		std::sort(v.begin(), v.end());
		//std::inplace_merge(V.begin(), V.end(), v.begin(), v.end());
		//std::copy(
	}

	{	trace("\n\nheap (binary tree with min/max at top");
		std::vector<int> v = {1,3,7,3,9,4,8,5,90};
		print(v);
		std::cout << (std::is_heap(v.begin(), v.end())? "heap structure":"not heap struc") << std::endl;
		std::sort(v.begin(), v.end()); print(v);
		std::reverse(v.begin(), v.end()); print(v);
		auto last = std::is_heap_until(v.begin(), v.end());
		std::cout << (last-v.begin()) << " first elements are heap\n";
		std::make_heap(v.begin(), v.end());	
		std::cout << (std::is_heap(v.begin(), v.end())? "it is heap structure":"not heap struc");std::cout << " "; print(v);
		std::pop_heap(v.begin(), v.end());print(v);
		std::push_heap(v.begin(), v.end());print(v);
		std::sort_heap(v.begin(), v.end());print(v);
	}

	{trace("\n\nis_permutation/2 array contains same elements");
		std::array<int,5> a1 = {1,2,3,4,5};
		std::array<int,5> a2 = {4,3,5,2,1};
		if(std::is_permutation(a1.begin(), a1.end(), a2.begin()))
			std::cout << "both arrays contain same elements\n";
		else std::cout << "both arrays do NOT contain same elements\n";
		
		std::cout << "next_permutation\n";
		int i=0;
		std::array<int, 3> ar1 = {3,4,5};//{4,3,5,2};
		do{
			std::cout << i++ << ": ";print(ar1);
		} while(std::next_permutation(ar1.begin(), ar1.end()));
		
		std::cout << "prev_permutation\n";
		int j=0;
		std::array<int, 3> ar2 = {4,5,3};//{4,3,5,2};
		do{
			std::cout << j++ << ": ";print(ar2);
		} while(std::prev_permutation(ar2.begin(), ar2.end()));
	}

	{trace("\n\nlower(>= or end)/upper_bound(> or end)");
		std::vector<int> v = {10,20,30,40,60,70,90,100}; print(v);
		int val = 5;
		auto L = std::lower_bound(v.begin(), v.end(), val);
		auto U = std::upper_bound(v.begin(), v.end(), val);
		std::cout << "Value=" << val << ", Lower bound=" << L-v.begin() << ", Upper bound=" << U-v.begin() << std::endl;
		val = 10;
		L = std::lower_bound(v.begin(), v.end(), val);
		U = std::upper_bound(v.begin(), v.end(), val);
		std::cout << "Value=" << val << ", Lower bound=" << L-v.begin() << ", Upper bound=" << U-v.begin() << std::endl;
		val = 50;
		L = std::lower_bound(v.begin(), v.end(), val);
		U = std::upper_bound(v.begin(), v.end(), val);
		std::cout << "Value=" << val << ", Lower bound=" << L-v.begin() << ", Upper bound=" << U-v.begin() << std::endl;
		val = 60;
		L = std::lower_bound(v.begin(), v.end(), val);
		U = std::upper_bound(v.begin(), v.end(), val);
		std::cout << "Value=" << val << ", Lower bound=" << L-v.begin() << ", Upper bound=" << U-v.begin() << std::endl;
		val = 100;
		L = std::lower_bound(v.begin(), v.end(), val);
		U = std::upper_bound(v.begin(), v.end(), val);
		std::cout << "Value=" << val << ", Lower bound=" << L-v.begin() << ", Upper bound=" << U-v.begin() << std::endl;
		val = 500;
		L = std::lower_bound(v.begin(), v.end(), val);
		U = std::upper_bound(v.begin(), v.end(), val);
		std::cout << "Value=" << val << ", Lower bound=" << L-v.begin() << ", Upper bound=" << U-v.begin() << std::endl;
	}
		
	{trace("\n\nmin/max_element");
		std::array<int,8> ar = {33,1,56,2,3,89,4,50}; print(ar);
		auto it_min = std::min_element(ar.begin(), ar.end());
		auto it_max = std::max_element(ar.begin(), ar.end());
		std::cout << "Max=" << *it_max << ", Min=" << *it_min << std::endl;
		auto res = std::minmax(ar.begin(), ar.end());//{33,1,56,2,3,89,4,50});
		std::cout << "Max=" << *res.first << ", Min=" << *res.second << std::endl;
	}
		
	{trace("\n\nmerge");
		int ar1[] = {5,10,15,20,25};
		int ar2[] = {8,16,24};
		std::vector<int> v(8);
		std::merge(ar1, ar1+5, ar2, ar2+3, v.begin());
		for(auto x:v) std::cout << x << " "; std::cout << "\n";
	}
		
	{trace("\n\nmove");
		std::string s1 = "sring#1";
		std::string s2 = "sring#2";
		std::cout << "\nBefore move, s1=" << s1 << ", s2=" << s2 << std::endl;
		s2 = std::move(s1);
		std::cout << "\nAfter move, s1=" << s1 << ", s2=" << s2 << std::endl;

		std::vector<int> v1 = {1,2,8,4,9,10};
		std::vector<int> v2(6);
		std::vector<int> v3(6);
		std::vector<int> v4(6);
		std::cout << "\ninitial state\n";
		std::cout << "v1\t"; for(auto x:v1) std::cout << x << " "; std::cout << std::endl;
		std::cout << "v2\t"; for(auto x:v2) std::cout << x << " "; std::cout << std::endl;

		std::move(v1.begin(), v1.end(), v2.begin());
		std::cout << "\nstd::move(v1.begin(), v1.end(), v2.begin());\n";
		std::cout << "v1\t"; for(auto x:v1) std::cout << x << " "; std::cout << std::endl;
		std::cout << "v2\t"; for(auto x:v2) std::cout << x << " "; std::cout << std::endl;

		v3 = std::move(v1);
		std::cout << "\nv3 = std::move(v1);\n";
		std::cout << "v1\t"; for(auto x:v1) std::cout << x << " "; std::cout << std::endl;
		std::cout << "v3\t"; for(auto x:v3) std::cout << x << " "; std::cout << std::endl;

		std::move_backward(v3.begin(), v3.end(), v4.end());
		std::cout << "\nstd::move_backward(v3.begin(), v3.end(), v4.end());\n";
		std::cout << "v3\t"; for(auto x:v3) std::cout << x << " "; std::cout << std::endl;
		std::cout << "v4\t"; for(auto x:v4) std::cout << x << " "; std::cout << std::endl;
		std::cout<<"\n"; }
		
	{trace("\n\nall_of/any_of/none_of");
		std::array<int, 5> a1 = {8,2,6,4,10};
		std::array<int, 5> a2 = {8,2,5,4,10};
		for(auto x:a1) std::cout << x << " "; std::cout<<std::endl;
		for(auto x:a2) std::cout << x << " "; std::cout<<std::endl;
		std::cout << std::endl << (std::all_of(a1.begin(), a1.end(), [](int i){return i%2==0;})? "a1: all are even" : "a1: not all even") << "\n"; 
		std::cout << std::endl << (std::all_of(a2.begin(), a2.end(), [](int i){return i%2==0;})? "a2: all are even" : "a2: not all even") << "\n"; 
		std::cout << std::endl << (std::any_of(a1.begin(), a1.end(), [](int i){return i%2;})? "a1: any is odd" : "a1: none odd") << "\n"; 
		std::cout << std::endl << (std::any_of(a2.begin(), a2.end(), [](int i){return i%2;})? "a2: any is odd" : "a2: none odd") << "\n"; 
		std::cout << std::endl << (std::none_of(a1.begin(), a1.end(), [](int i){return i%2;})? "a1: none odd" : "a1: not all even") << "\n"; 
		std::cout << std::endl << (std::none_of(a2.begin(), a2.end(), [](int i){return i%2;})? "a2: none odd" : "a2: not all even") << "\n"; 
		std::cout<<"\n"; }
		
	{trace("\nnth_element");
		std::vector<int> v;
		for(int i=0; i<10; i++){v.push_back(i);}
		for(auto x:v) std::cout << x <<" "; std::cout<<std::endl;
		std::random_shuffle(v.begin(), v.end());
		for(auto x:v)std::cout<<x<<" "; std::cout<<std::endl;
		std::nth_element(v.begin(), v.begin()+4, v.end());
		for(auto x:v)std::cout<<x<<" "; std::cout<<std::endl;
		std::cout<<"\n"; }
		
	{trace("\npartital_sort,partial_sort_copy,sort");
		std::vector<int> v;
		std::vector<int> v1(4);
		for(int i=0; i<10; i++){v.push_back(i);}print(v);
		
		std::cout << "\nsimple sort";
		std::random_shuffle(v.begin(), v.end());print(v);
		std::sort(v.begin(), v.end()); print(v);

		std::cout << "\nascending sort";
		std::random_shuffle(v.begin(), v.end());print(v);
		std::sort(v.begin(), v.begin()+10, std::less<int>()); print(v);

		std::cout << "\ndecending sort";
		std::random_shuffle(v.begin(), v.end());print(v);
		std::sort(v.begin(), v.begin()+10, std::greater<int>()); print(v);
		
		std::cout << "\npartial sort";
		std::random_shuffle(v.begin(), v.end());print(v);
		std::partial_sort(v.begin(),v.begin()+4, v.end()); print(v);	// does not seem to work

		std::cout << "\npartial sort copy";
		std::random_shuffle(v.begin(), v.end());print(v);
		std::partial_sort_copy(v.begin(),v.begin()+4, v1.begin(), v1.end()); print(v1);
		std::sort(v.begin(),v.end()); print(v);

		std::cout << "\nstable sort";
		std::random_shuffle(v.begin(), v.end());print(v);
		std::stable_sort(v.begin(), v.end());print(v);

		std::vector<int> vec = {3,5,7,2,4,1,7,4,8,5};
		std::sort(vec.begin(), vec.end());
		std::cout << "sort/binary_search" << std::binary_search(vec.begin(), vec.end(), 8) << std::endl;
		std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " ")); std::cout<<std::endl;
		std::for_each(v.begin(), v.end(), [](int a){std::cout << a << " ";}); std::cout<<std::endl;
		for(auto x:v) std::cout << x << " ";
		std::cout<<"\n\n";}
		
	{trace("\npartition,partition_copy,partition_point");
		std::vector<int> v,odd(10),even(10);
		for(int i=0; i<10; i++){v.push_back(i);}print(v);
		std::partition(v.begin(), v.end(), [](int i){return i%2;});print(v);
		std::partition_copy(v.begin(), v.end(), odd.begin(), even.begin(), [](int i){return i%2;});
		print(odd);print(even);
		std::cout << "partition_point="; print(v);
		auto it = std::partition_point(v.begin(), v.end(), [](int i){return i%2;});
		std::cout << "first of !(i%2)=" << *it << std::endl; 
		std::random_shuffle(v.begin(), v.end());print(v);
		std::stable_partition(v.begin(), v.end(), [](int i){return i%2;});print(v);
		std::cout<<"\n"; }
		
	{trace("\nremove,replace,reverse,rotate");
		std::vector<int> v = {4,3,6,3,7,5,9,4};
		print(v);
		std::remove(v.begin(), v.end(), 3);print(v);
		std::replace(v.begin(), v.end(), 4,99);print(v);
		std::reverse(v.begin(), v.end());print(v);
		std::rotate(v.begin(), v.begin()+4, v.end());print(v);
		std::cout<<"\n"; }
		
	{trace("\nsearch,search_n");
		std::array<int, 13> a1 = {1,2,2,6,5,7,8,10,6,5,7,11,10};
		std::array<int, 3> a2 = {6,5,7};
		print(a1);print(a2);
		auto it = std::search(a1.begin(),a1.end(), a2.begin(),a2.end());
		if(it==a1.end())	std::cout << "search not found\n";
		else std::cout << "search found\n";
		it = std::search_n(a1.begin(),a1.end(),2,10);
		if(it==a1.end())	std::cout << "search not found\n";
		else std::cout << "search found\n";
		std::cout<<"\n"; }
		
	{trace("\nset_difference,set_symmetric_difference");
		int a1[] = {1,2,3,4,5,7,8,9,10,11};
		int a2[] = {4,5,6};
		std::vector<int> v1(10), v2(10), v3(10);
		for(auto x:a1)std::cout<<x<<" ";std::cout<<std::endl;
		for(auto x:a2)std::cout<<x<<" ";std::cout<<std::endl;
		auto it = std::set_difference(a1,a1+10, a2,a2+3, v1.begin());
		v1.resize(it-v1.begin());
		print(v1);
		auto it2 = std::set_symmetric_difference(a1,a1+10, a2,a2+3, v3.begin());
		v3.resize(it2-v3.begin());
		print(v3);
		auto first1=a1, last1=a1+10;
		auto first2=a2, last2=a2+3;
		auto res = v2.begin();
		while(first1!=last1 && first2!=last2){
			if(*first1<*first2){*res = *first1; ++res; ++first1;}
			else if(*first2<*first1) ++first2;
			else {++first1; ++first2; }
		}
		std::copy(first1,last1,res);
		//v2.resize(res-v2.begin());
		print(v2);
		std::cout<<"\n"; }
		
	{trace("\nset_intersection,set_union");
		int a1[] = {1,2,3,4,5,7,8,9,10,11};
		int a2[] = {4,5,6,7};
		std::vector<int> v1(10), v2(10), v3(15);
		auto first1=a1, last1=a1+10;
		auto first2=a2, last2=a2+4;
		auto res = v1.begin();
		while(first1!=last1 && first2!=last2){
			if  (*first1<*first2)	++first1;
			else if(*first2<*first1)	++first2;
			else{*res = *first1; ++res; ++first1; ++first2;}
		}
		print(v1);
		first1=a1, last1=a1+10;
		first2=a2, last2=a2+4;
		res = v2.begin();
		auto it = std::set_intersection(first1,last1, first2,last2, res);
		v2.resize(it-v2.begin());
		print(v2);

		auto res3 = v3.begin();
		auto it3 = std::set_union(first1,last1, first2,last2, res3);
		v3.resize(it3-v3.begin());
		print(v3);
		std::cout<<"\n"; }
		
	{trace("\nswap,sway_ranges");
		std::vector<int> v1(4,10), v2(6,20);
		print(v1);print(v2);
		std::swap(v1,v2);
		print(v1);print(v2);
		std::swap_ranges(v1.begin()+1, v1.begin()+3, v2.begin()+1);
		print(v1);print(v2);
		std::cout<<"\n"; }
		
	{trace("unique");
		std::array<int, 10> ar={1,2,3,3,4,5,6,6,7,8};
		print(ar);
		std::unique(ar.begin(), ar.end());print(ar);
		std::cout<<"\n"; }
		
	{trace("");
		std::cout<<"\n"; }
	
}	
}	// STL3



namespace bind
{

int multiply(int x, int y)
{
	return x*y;
}

void test(int argc, char** argv)
{
	// constructs a fn obj from fn and its args
	int a = 11;
	int b = 22;
	auto f1 = std::bind(multiply, 10, 20);
	auto f2 = std::bind(multiply, std::placeholders::_1, 20);
	auto f3 = std::bind(multiply, std::placeholders::_1, std::placeholders::_2);
	auto f4 = std::bind(multiply, std::placeholders::_2, std::placeholders::_1);
	std::function<int ()> f5 = std::bind(multiply, a, b);
  std::cout << "f1()=" << f1() << std::endl;
  std::cout << "f2(100)=" << f2(100) << std::endl;
  std::cout << "f3(2,3)=" << f3(2,3) << std::endl;
  std::cout << "f4(5,4)=" << f4(5,4) << std::endl;
	std::cout << "f5(a=11, b=22)=" << f5() << std::endl;

	auto bind2Neg = std::bind2nd(std::less<int>(), 0);
	auto bind2Pos = std::bind2nd(std::greater<int>(), 0);
	std::cout << "bind2Neg(-10) =" << bind2Neg(-10) << std::endl;
	std::cout << "bind2Neg(0)   =" << bind2Neg(0) << std::endl;
	std::cout << "bind2Neg(10)  =" << bind2Neg(10) << std::endl;
	std::cout << "bind2Pos(-10) =" << bind2Pos(-10) << std::endl;
	std::cout << "bind2Pos(0)   =" << bind2Pos(0) << std::endl;
	std::cout << "bind2Pos(10)  =" << bind2Pos(10) << std::endl;

	int nums[] = {10, -20, -30, 40, -50};
	// constructs unary func obj from binary func obj and second arg
	int cx = count_if(nums, nums+5, std::bind2nd(std::less<int>(), 0));
	for(auto x:nums){std::cout << x << " ";}
	std::cout << "\ncount < 0  = " << cx << std::endl; 
}
}	// bind



int main(int argc, char** argv)
{
	std::cout << "Bismillah" << std::endl;
	std::cout << "Usage: ./a.out bind" << std::endl;
	std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << std::endl;

	if(argc < 2) { trace("insufficient No of parameters."); return false;}
	else if(memcmp(argv[1], "STL1", strlen("STL1")) == 0)		STL1::test(argc, argv);
	else if(memcmp(argv[1], "STL2", strlen("STL2")) == 0)		STL2::test(argc, argv);
	else if(memcmp(argv[1], "STL3", strlen("STL3")) == 0)		STL3::algo(argc, argv);
	else if(memcmp(argv[1], "bind", strlen("bind")) == 0)		bind::test(argc, argv);
	// else if(memcmp(argv[1], "", strlen("")) == 0)		();
	// else if(memcmp(argv[1], "", strlen("")) == 0)		();
	// else if(memcmp(argv[1], "", strlen("")) == 0)		();
	// else if(memcmp(argv[1], "", strlen("")) == 0)		();
	// else if(memcmp(argv[1], "", strlen("")) == 0)		();
	// else if(memcmp(argv[1], "", strlen("")) == 0)		();
	else std::cout << argv[1] << " not found.\n";

	return true;
}
