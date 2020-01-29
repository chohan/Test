#include "stdafx.h"
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <deque>
#include <algorithm>
#include <fstream>
#include <iterator>
using namespace std;

// This quiz was sent on 19/01/2010 by Vlastimil Chvojka at Barcap
// I submitted the assignment on 20/01/2010
// Agent Darrell Cameron-Webb from The JM Group






namespace Barcap
{
//########## Question 2 (comment) #############
//2. Comment on the following bits of code, explain how they can be improved

	//=== A. ===
	//std::list<int> mylist;
	//for (std::list<int>::iterator it = mylist.begin(), end = mylist.end(); it != end; it++)
	//{
	//	if (*it < 0)
	//		mylist.erase(it);
	//}
	void q2A()
	{
		std::list<int> mylist;
		mylist.push_back(1);
		mylist.push_back(5);
		mylist.push_back(-7);
		mylist.push_back(-8);
		mylist.push_back(2);
		mylist.push_back(4);
		mylist.push_back(3);
		cout << "before erase loop" << endl;
		std::copy(mylist.begin(), mylist.end(), std::ostream_iterator<int>(cout, " "));
		for (std::list<int>::iterator it = mylist.begin(), end = mylist.end(); it != end; it++)
		{
			if (*it < 0)
			{
				it = mylist.erase(it);
				--it;
			}
		}
		cout << "\nafter erase loop" << endl;
		std::copy(mylist.begin(), mylist.end(), std::ostream_iterator<int>(cout, " "));
	}

	//=== B. ===
	//class A {
	//	typedef std::deque<EntryID> Entries;
	//	Entries entries_;
	//public:
	//	typedef Entries::const_iterator entry_iterator;
	//	// ...
	//	entry_iterator Move(entry_iterator what, entry_iterator where)
	//	{
	//		EntryID id = *what;
	//		entries_.erase(entries_.begin() + (what - entries_.begin()));
	//		return entries_.insert(entries_.begin() + (where - entries_.begin()), id);
	//	}
	//};
	void q2B()
	{
		//class EntryID{};
		typedef int EntryID;
		class A
		{
			typedef std::deque<EntryID> Entries;
			Entries entries_;
		public:
			A()
			{
				entries_.push_back(1);
				entries_.push_back(2);
				entries_.push_back(3);
				entries_.push_back(4);
				entries_.push_back(5);
				cout << "before Move" << endl;
				std::copy(entries_.begin(), entries_.end(), std::ostream_iterator<EntryID>(cout, " "));
				entry_iterator itr2 = std::find(entries_.begin(), entries_.end(), 2);
				entry_iterator itr4 = std::find(entries_.begin(), entries_.end(), 4);
				Move2(itr2, itr4);
				cout << "\nafter Move" << endl;
				std::copy(entries_.begin(), entries_.end(), std::ostream_iterator<EntryID>(cout, " "));
			}
			typedef Entries::const_iterator entry_iterator;
			// ...
			//original
			entry_iterator Move(entry_iterator what, entry_iterator where)
			{
				EntryID id = *what;
				entries_.erase(entries_.begin() + (what - entries_.begin()));
				return entries_.insert(entries_.begin() + (where - entries_.begin()), id);
			}

			//sol#1
			entry_iterator Move1(entry_iterator what, entry_iterator where)
			{
				EntryID id = *what;
				EntryID idWhere = *where;
				entries_.erase(entries_.begin() + (what - entries_.begin()));
				entry_iterator itr = std::find(entries_.begin(), entries_.end(), idWhere);
				return entries_.insert(itr, id);
			}

			//sol#2
			entry_iterator Move2(entry_iterator what, entry_iterator where)
			{
				EntryID id = *what;

				//store relative position
				int RelPos = where - entries_.begin();

				entries_.erase(entries_.begin() + (what - entries_.begin()));
				return entries_.insert(entries_.begin() + RelPos, id);
			}
		};

		A a;
	}

	//=== C. ===
	//int number;
	//number = number++;
	void q2C()
	{
		int number = 1;
		number = number++;
		cout << number << endl;

	}


//#################### Question 3 (Stack Implementation)
//3. What is a stack data structure? Where is it used? How does one create a stack in C++?

	//int myfunc2(const std::string& str) throw(int)
	//{
	//	int a;
	//	a = atoi(str.c_str());
	//	if(a==0) throw(a);
	//	else
	//	return a;
	//}

	//Stack using array
	template<typename T> class Stack
	{
	public:
		Stack(const int capacity) : size(0){items = new T[capacity];}
		~Stack(){delete[] items;}
		void push(T t){items[size++] = t;}
		T pop(){return items[--size];}
		int count(){return size;}
		
	private:
		int size;
		T *items;
	};

	//Stack using linked list
	template<typename T> class Stack2
	{
	public:
		Stack2() : size(0), slot(0){}
		~Stack2()
		{
			while(slot != NULL)
			{
				Slot* next = slot->next;
				delete slot;
				slot = next;
			}
		}
		void push(T t)
		{
			Slot* next = slot;
			slot = new Slot(t);
			slot->next = next;
			++size;
		}
		T pop()
		{
			T item = slot->item;
			--size;
			Slot* next = slot->next;
			delete slot;
			slot = next;
			return item;
		}
		int count(){return size;}
		
	private:
		struct Slot
		{
			Slot(T t):item(t), next(0){}
			T item;
			Slot* next;
		};
		int size;
		Slot* slot;
	};

	void q3()
	{
		//int a = 10;
		//int b = 0;
		//int c;
		//try{
		//c = a/b;
		//}catch(...)
		//{
		//	cout << "divide by zero error" << endl;
		//}

		//Testing Stack implementation from array
		Stack<int> stk(100);
		stk.push(0);
		stk.push(1);
		stk.push(2);
		cout << "pushed 0,1,2" << endl;
		cout << "pop 2 items and then display. Size=" << stk.count() << endl;
		for(int i=0; i<2; ++i)
			cout << "item=" << stk.pop() << " size=" << stk.count() << endl;
		cout << "push 3 items and then display. Size=" << stk.count() << endl;
		stk.push(3);
		stk.push(4);
		stk.push(5);
		cout << "pushed 3,4,5" << endl;
		cout << "pop all" << endl;
		int size = stk.count();
		for(int i=0; i<size; ++i)
			cout << "item=" << stk.pop() << " size=" << stk.count() << endl;


		//Testing Stack implementation from linked list
		cout << "\n\nStack using linked list" << endl;
		Stack2<int> stk2;
		stk2.push(20);
		stk2.push(21);
		stk2.push(22);
		cout << "pushed 20,21,22" << endl;
		cout << "pop 2 items and then display. Size=" << stk2.count() << endl;
		for(int i=0; i<2; ++i)
			cout << "item=" << stk2.pop() << " size=" << stk2.count() << endl;
		cout << "push 3 items and then display. Size=" << stk2.count() << endl;
		stk2.push(23);
		stk2.push(24);
		stk2.push(25);
		cout << "pushed 23,24,25" << endl;
		cout << "pop all" << endl;
		int size2 = stk2.count();
		for(int i=0; i<size2; ++i)
			cout << "item=" << stk2.pop() << " size=" << stk2.count() << endl;


		//Testing Stack implementation from STL
		std::stack<int, vector<int>> stk3;


	}



//############### Question 4 (CPU registers programming) #################
//4. Assume that you have a CPU with 4 (r1, r2, r3, r4) registers, which supports the following operations
//	zero(r) -- resets register value to zero
//	inc(r) - increments register value by one
//	loop(r) { /* loop body */ } repeats everything in the loop body x times where x is the value in the register r. The number of iterations does not change if x changes inside the loop body.
//	All the registers are integer numbers, not less than zero, and less than infinity. No operations, except from described above. One can not create additional registers or variables.
//
//	In this language, implement a function "r1 = r4 - 1" (assuming that r4 > 0), i.e.
//	dec_r4_and_store_in_r1() {
//		...
//	}
	void q4()
	{
		////set r2=1
		//zero(r2)
		//inc(r2)

		//zero(r1)
		//loop(r4)
		//{
		//	inc(r1)

		//	//this loop will be called only once
		//	loop(r2) { zero(r2),  zero(r1) }
		//}
	}

}



//////////////////////////////////////////////////////////////////
void main_Barcap()
{
	cout << "main_Barcap" << endl;
	//Barcap::q2A();
	//Barcap::q2B();
	//Barcap::q2C();
	//Barcap::q3();
}
