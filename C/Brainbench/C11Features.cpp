// config/suffix.hpp
//#if defined(BOOST_NO_INITIALIZER_LISTS) && !defined(BOOST_NO_0X_HDR_INITIALIZER_LIST)
//#  define BOOST_NO_0X_HDR_INITIALIZER_LIST
//#endif

// config/compilers/visualc.hpp
//#if _MSC_VER <= 1500  || !defined(BOOST_STRICT_CONFIG) // 1500 == VC++ 9.0
//#  define BOOST_NO_INITIALIZER_LISTS
//#endif
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

namespace ExplicitOverride	// it forces compiler to check and generate an error if the signature of overriding virtual funciton in derived class is different from base class
{
	class Base
	{
	public:
		virtual void vfunc(int a){std::cout << __FUNCTION__ << std::cout << std::endl;}
	};

	class Derived : public Base
	{
		virtual void vfunc(int a) override {std::cout << __FUNCTION__ << std::cout << std::endl;}
	};
}

namespace final
{
	// final virtual fuction cannot be overridden
	class Base
	{
	public:
		virtual void vfunc(int a) final {std::cout << __FUNCTION__ << std::cout << std::endl;}
	};

	class Derived : public Base
	{
		//void vfunc(int a) {std::cout << __FUNCTION__ << std::cout << std::endl;}	// a virtual and final function cannnot be overridde in derived class
	};

	// final base class cannot be overriden
	class Base2 final{};
	//class Derived2 : public Base2 {};	// a final base class cannot be derived from
}

namespace NewStringLiterals
{
//	char*		utf8	= u8"I am UTF-8 string";
//	char16_t*	utf16	= u "I am UTF-16 string";
//	char32_t*	utf32	= U"I am UTF-32 string";
}

namespace new_features
{
	// not yet available
//	struct NonCopyable
//	{
//		NonCopyable() = default;
//		NonCopyable(const NonCopyable&) = delete;
//		NonCopyable& operator=(const NonCopyable&) = delete;
//	};

	struct OnlyDouble {
		void f(double d);
		template<class T> void f(T) = delete;
	};
template<typename... Values> class tuple;
//tuple<int, std::vector<int>, std::map<std::string, std::vector<int>>> some_instance_name;
	
	void f1()
	{
		//const char *reg_esp = "[ ,.\\t\\n;:]";  // List of separator characters.
 
		//// this can be done using raw string literals:
		//// const char *reg_esp = R"([ ,.\t\n;:])";
 
		//std::regex rgx(reg_esp); // 'regex' is an instance of the template class
		//						 // 'basic_regex' with argument of type 'char'.
		//std::cmatch match; // 'cmatch' is an instance of the template class
		//				   // 'match_results' with argument of type 'const char *'.
		//const char *target = "Unseen University - Ankh-Morpork";
 
		//// Identifies all words of 'target' separated by characters of 'reg_esp'.
		//if (std::regex_search(target, match, rgx)) {
		//	// If words separated by specified characters are present.
 
		//	const size_t n = match.size();
		//	for (size_t a = 0; a < n; a++) {
		//		std::string str (match[a].first, match[a].second);
		//		std::cout << str << "\n";
		//	}
		//}
	}

	void f_auto_for()
	{
		std::vector<int> v1;
		auto size = 10;
		//for(auto i:size)	// auto can be used with anything with begin() and end() functions
		for (auto i=0; i<size; i++)
		{
			v1.push_back(i);
		}

		auto it1 = v1.begin();	// auto can be used with anything with begin() and end() functions
		while(it1 != v1.end())
		{
			std::cout << *it1 << std::endl;
			++it1;
		}
	}

}



void main_C11Features()
{
	std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << std::endl;
  
	new_features::f_auto_for();
}
