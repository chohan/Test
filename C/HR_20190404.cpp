// g++ -g -w -o HR404 HR404.cpp --std=c++17 -lpthread && ./HR404
#include <iostream>
#include <sstream>
#include <fstream>

#include <algorithm>
#include <utility>
#include <iterator>
#include <vector>
#include <tuple>
#include <map>
#include <set>
#include <limits>
#define trace(str)(std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << "(): " << str << std::endl)


namespace n1
{
/*
remove all elements from a singly linked list which are greater than k
*/
class Node
{public:
	int data;
	Node* next=nullptr;
};

Node* fillList(std::vector<int>& v)
{
	Node *N1, *prev, *curr;
	prev=nullptr;
	auto it=v.begin();
	while(it != v.end()){
		curr = new Node();
		curr->data = *it;
		if(prev==nullptr){
			prev = curr;
			N1 = curr;
			++it;
			continue;
		}
		prev->next = curr;
		prev = curr;
		++it;
	}
	return N1;
}
void printList(Node* head)
{
	std::cout << head->data << " ";
	if(head->next) printList(head->next);
}
void n1(int argc, char** argv)
{trace("");
	std::vector<int> v = {100,105,50,200,250,75,125};
	int k = 200;
	Node *N1 = fillList(v);
	printList(N1);
	trace("");

	Node *N2, *curr, *c2, *p2;
	curr = N1;
	p2 = nullptr;
	do{
		if(curr->data <= k){
			c2 = new Node; c2->data = curr->data;
			//c2 = curr; c2->next=nullptr;
			if(p2==nullptr){
				p2 = c2;
				N2 = c2;
			}else{
				p2->next = c2;
				p2 = c2;
			}
		}
		curr = curr->next;
	}while(curr!=nullptr);
	printList(N2);
}
}

namespace n2
{

void n2(int argc, char** argv)
{trace("");

}
}

namespace n3
{
/*
find max diff between any two elements of an array. Such that
a[j] - a[i] where o<=i<j<n and a[i] < a[j]
*/
void n3(int argc, char** argv)
{trace("");
	std::vector<int> v = {2,3,10,2,4,8,1};
	//std::vector<int> v = {3,4,11,1,4,10,1};
	for(auto x:v) std::cout << x << " ";
	std::vector<int>::iterator iL, iH;
	int diff = 0;
	int size = v.size();
	for(auto i=0; i<size-1; i++){
		for(auto j=i+1; j<size; j++){
			std::cout << "v[j]="<<v[j] << ", v[i]="<<v[i] << ", diff="<<diff<<"\n";
			if(v[j]-v[i] > diff){
				diff = v[j]-v[i];
				iL=v.begin()+i; iH=v.begin()+j;
				std::cout << "\tv[j]="<<v[j] << ", v[i]="<<v[i] << ", diff="<<diff<<"\n";
			}
		}
	}
}
}

namespace n4
{

void n4(int argc, char** argv)
{trace("");

}
}

namespace n5
{

void n5(int argc, char** argv)
{trace("");

}
}

int main(int argc, char** argv)
{
	std::cout << "Bismillah" << std::endl;
	n1::n1(argc, argv);
	n2::n2(argc, argv);
	n3::n3(argc, argv);
	n4::n4(argc, argv);
	n5::n5(argc, argv);

	return true;
}
