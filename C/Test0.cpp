#include "stdafx.h"
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <stack>
#include <algorithm>
#include <math.h>
#include <typeinfo>
#include <stdio.h>
#include <string>
#include <string.h>
#include <fstream>
#include <iterator>

using namespace std;

#if defined WIN32
#include <winsock.h>
#elif defined __linux__
#include <unistd.h>
#endif

typedef unsigned long DWORD;
typedef void* HANDLE;

#define SQ(x)((x)*(x))


//singleton
class Singleton
{
public:
	static Singleton* GetInstance()
	{
		if(p==NULL)
			p = new Singleton();

		return p;
	}
private:
	Singleton(){cout << "Singleton ctor" << endl;}
	static Singleton* p;
};
Singleton* Singleton::p = NULL;

void t2()
{
	Singleton* p1 = Singleton::GetInstance();
	Singleton* p2 = Singleton::GetInstance();
}

//variable number of arguments
#include <stdarg.h>
void t3(int a, int b, ...)
{
	va_list args;
	va_start(args, b);
	va_arg(args, int);
	va_end(args);
	//cout << a
}






////////////// Binary Search Tree starts //////////////////////////
namespace BinaryTree
{

//check the validity of a binary tree
//empty tree is a valid binary tree
//Every child will have only one parent
//Every parent can have up to two children
//no node can have any of its ancester as its child
//leaf are those which do not have any child
class Node
{
public:
	Node(std::string str, int val):name(str), value(val), left(0), right(0){}
	Node* left;
	Node* right;
	std::string	name;
	int		value;
};


//check validity of binary search tree
std::set<Node*> bn;
bool IsValidBinaryTree(Node* node)
{
	//check if this node is already used
	//Every child will have only one parent
	//no node can have any of its ancester as its child

	//check if this node is already used
	if(node!=NULL)
	{
		if(bn.end()==bn.find(node))
			bn.insert(node);
		else
			return false;
	}

	// check its left child
	if(node->left)
		if(!IsValidBinaryTree(node->left))
			return false;

	// check its right child
	if(node->right)
		if(!IsValidBinaryTree(node->right))
			return false;

	return true;
}

//Find a node in a Binary search tree
Node* FindNode(Node* root, Node* node)
{
	if(node->value < root->value)
		return (root->left!=NULL)? FindNode(root->left, node) : NULL;
	if(node->value > root->value)
		return (root->right!=NULL)?  FindNode(root->right, node) : NULL;

	return node;
}

//find parent
//assume node is present in the tree
//returns null if it is root
Node* FindParent(Node* root, Node* node)
{
	if(root == node)
		return NULL;

	//check if root childern is one of the node
	if(root->left && (root->left == node) )
		return root;

	if(root->right && (root->right == node) )
		return root;


	//find in left sub tree
	if(node->value < root->value)
		return FindParent(root->left, node);

	//find in right sub tree
	if(node->value > root->value)
		return FindParent(root->right, node);

	return NULL;
}

//insert node in a binary search tree
void InsertNode(Node* root, Node* node)
{
	if(node->value < root->value)
	{
		if(root->left==NULL)
			root->left = node;
		else
			InsertNode(root->left, node);
	}
	else
	{
		if(root->right==NULL)
			root->right = node;
		else
			InsertNode(root->right, node);
	}
}

//deletes node from a binary search tree
void DeleteNode(Node* root, Node* node)
{
	Node* parent = FindParent(root, node);
	if(parent->left == node)
		parent->left = NULL;
	else if(parent->right == node)
		parent->right = NULL;

	if(node->left)
		InsertNode(root, node->left);
	if(node->right)
		InsertNode(root, node->right);
}

void print(Node* node)
{
	cout << node->name << ", Value=" << node->value << ", Left=" << ((node->left!=0)? node->left->value : 0)  << ", Right=" << ((node->right!=0)? node->right->value : 0) << endl;
}

// depth first search (DFS)
//print a BST in ascending order
void printBSTAscending(Node* node)
{
	//first option
	//if(node->left!=NULL)
	//{
	//	printBSTAscending(node->left);
	//	cout << node->name << "=" << node->value << endl;
	//}
	//else
	//{
	//	cout << node->name << "=" << node->value << endl;
	//}
	//if(node->right!=NULL)
	//{
	//	printBSTAscending(node->right);
	//}

	//Second option
	if(node->left)
		printBSTAscending(node->left);

	cout << node->name << "=" << node->value << endl;

	if(node->right)
		printBSTAscending(node->right);
}

//print a BST in descending order
void printBSTDescending(Node* node)
{
	if(node->right)
		printBSTDescending(node->right);

	cout << node->name << "=" << node->value << endl;

	if(node->left)
		printBSTDescending(node->left);
}

// breath first search (BFS)
//print first level then second then third and so on
// using a queue
void print_BFS3(Node* head)
{
	std::deque<Node*> nodes;	//list of children of elements in current list (nodes)

	// print current nodes and pushing their children
	cout << "New level" << " ";

	// pushing head
	nodes.push_back(head);

	auto itr = nodes.begin();
	while(itr != nodes.end())
	{
		Node* node = *itr;
		cout << node->name << "=" << node->value << " ";

		if(node->left)
			nodes.push_back(node->left);

		if(node->right)
			nodes.push_back(node->right);

		++itr;
	}
	std::cout << std::endl;
}

// breath first search (BFS)
//print first level then second then third and so on
// using recursive
void print_BFS2(std::vector<Node*> nodes)
{
	std::vector<Node*> nodes2;	//list of children of elements in current list (nodes)

	// print current nodes and pushing their children
	cout << "New level" << " ";
	auto itr = nodes.begin();
	while(itr != nodes.end())
	{
		Node* node = *itr;
		cout << node->name << "=" << node->value << " ";

		if(node->left)	nodes2.push_back(node->left);
		if(node->right)	nodes2.push_back(node->right);

		++itr;
	}
	std::cout << std::endl;
	if(nodes2.size())
	{
		print_BFS2(nodes2);
	}
}

// breath first search (BFS)
//print first level then second then third and so on
// does not work correctly
void print_BFS(Node* node)
{
	//print root node(print first level node)
	//note sub nodes (in the same cycle note the next level nodes)
	//loop it thru

	int nCurrLevelNodes = 1;	//No of nodes in current level
	int nNextLevelNodes = 1;	//No of nodes in next level

	//nodes of current level
	Node** nodes = new Node*[nCurrLevelNodes];	//Nodes in current level (pointer to array of pointers)
	nodes[0] = const_cast<Node*>(node);

	while(nNextLevelNodes)
	{
		cout << "New level" << " ";
		Node** nodesSub = new Node*[2* nCurrLevelNodes];
		nNextLevelNodes = 0;

		//loop thru the current level
		for(int i=0; i<nCurrLevelNodes; i++)
		{
			//print the current level nodes
			Node* node = nodes[i];
			cout << node->name << "=" << node->value << " ";

			//note next level nodes if they are not null
			if(node->left)
				nodesSub[nNextLevelNodes++] = node->left;
			if(node->right)
				nodesSub[nNextLevelNodes++] = node->right;
		}
		delete[] nodes;
		cout << endl;
		nodes = nodesSub;
		nCurrLevelNodes = nNextLevelNodes;
	}
	delete[] nodes;
}

void putInMultiLevelMap(Node* node, int level)
{
	static std::map<int, std::list<Node*>> mapNodes;
	
	auto itr = mapNodes.find(level);
	if(itr == mapNodes.end())
	{
		std::list<Node*> lstNodes;
		mapNodes[level] = lstNodes;
		itr = mapNodes.find(level);
	}
	std::list<Node*> nodes = itr->second;

	if(node->left)
	{
		nodes.push_back(node->left);
		putInMultiLevelMap(node->left, level+1);
	}

	if(node->right)
	{
		nodes.push_back(node->right);
		putInMultiLevelMap(node->right, level+1);
	}
}

void BinaryNodes()
{
	::std::vector<Node*> nodes;


	Node* n0 = new Node("n0", 15);
	nodes.push_back(n0);

	Node* n1a = new Node("n1a", 25);
	Node* n1b = new Node("n1b", 32);
	Node* n1c = new Node("n1c", 30);
	nodes.push_back(n1a);
	nodes.push_back(n1b);
	nodes.push_back(n1c);

	Node* n2a = new Node("n2a", 20);
	Node* n2b = new Node("n2b", 8);
	Node* n2c = new Node("n2c", 85);
	nodes.push_back(n2a);
	nodes.push_back(n2b);
	nodes.push_back(n2c);

	Node* n3a = new Node("n3a", 56);
	Node* n3b = new Node("n3b", 78);
	nodes.push_back(n3a);
	nodes.push_back(n3b);

	//n0->left = n1a;
	//n0->right = n1b;
	//
	//n1a->left = n2a;
	//n1a->right = n2b;

	//n1b->left = NULL;//n2b;//
	//n1b->right = n2c;

	//n2a->left = NULL;
	//n2a->right = n3a;

	//n2b->left = NULL;
	//n2b->right = NULL;

	//n2c->left = n3b;
	//n2c->right = NULL;

	//n3a->left = NULL;
	//n3a->right = NULL;

	//n3b->left = NULL;
	//n3b->right = NULL;


	//bool res = IsValidBinaryTree(n0);
	//cout << res << endl;
	//for_each(bn.begin(), bn.end(), print);

	Node* n23 = new Node("n23", 23);
	//Node* n20 = new Node("n20", 20);
	nodes.push_back(n23);
	//nodes.push_back(n20);

	//populate binary search tree
	::std::vector<Node*>::iterator itr = nodes.begin();
	Node* root = *itr++;
	while(itr!=nodes.end())
	{
		InsertNode(root, *itr++);
	}

	//check validity of BST
	bool res = IsValidBinaryTree(root);
	cout << res << endl;

	//print BST
	cout << "\nprinting thru for_each" << endl;
	for_each(nodes.begin(), nodes.end(), print);
	cout << "\nprinting thru printBSTAscending" << endl;
	printBSTAscending(root);
	cout << "\nprinting thru printBSTDescending" << endl;
	printBSTDescending(root);

	cout << "\nprinting thru breath first search (print_BFS)" << endl;
	print_BFS(root);

	cout << "\nprinting thru breath first search (print_BFS2)" << endl;
	std::vector<Node*> nodes2;
	nodes2.push_back(root);
	print_BFS2(nodes2);

	cout << "\nprinting thru breath first search (print_BFS3)" << endl;
	print_BFS3(root);

	//find a root
	Node* node = new Node("hello", 18);
	if(FindNode(root, node))
		cout<<node->value<<endl;
	else
		cout << "Nod not found" << endl;

	//find a parent
	Node* parent = FindParent(root, n1b);
	if(parent)
		cout << "Name=" << parent->name << " Value=" << parent->value << endl;

	//delete a node
	DeleteNode(root, n1b);
	cout << "\nprinting thru printBSTBreadth" << endl;
	print_BFS(root);
//	printBSTBreadth2(root);

	//delete all nods
	itr = nodes.begin();
	while(itr != nodes.end())
	{
		Node* node = *itr++;
		cout << node->name << "=" << node->value << endl;
		delete node;
	}
	nodes.clear();
}

}
////////////// Binary Search Tree ends //////////////////////////



////////////// Singlly Linked List starts //////////////////////////
namespace SingleLinkedList
{
	class Node
	{
	public:
		Node(int val, Node* nxt):value(val), next(nxt){}
		int value;
		Node* next;
	};

	//reverses the singly linked list
	Node* reverse(Node* head)
	{
		Node* newList = NULL;
		Node* current = head;
		while(current)
		{
			Node* next = current->next;
			current->next = newList;

			newList = current;
			current = next;
		}
		return newList;
	}

	//find nth node from the end in single pass
	//n=0,1,2,3,....
	Node* FindNthEndNode(Node* head, int nth)
	{
		int i=0;
		Node* temp=NULL;
		for(Node* inode=head; inode!=NULL; inode=inode->next)
		{
			if(i==nth)
				temp = head;
			else if(i>nth)
			{
				temp = temp->next;
			}
			i++;
		}
		return temp;
	}

	// find middle node in single pass/traverse
	Node* FindMiddleNode(Node* head)
	{
		Node* next = head;
		Node* mid  = head;
		int i=0;
		while(next != NULL)
		{
			++i;
			next = next->next;
			if(i%2 == 0)
			{
				mid = mid->next;
			}
		}
		return mid;
	}

	//swap two nodes in list
	bool Swap(Node* head, Node* &n1, Node* &n2)
	{
		Node* prev1 = NULL;
		Node* prev2 = NULL;
		Node* current = head;
		while(current != NULL)
		{
			//find the previous/parent of n1 and n2
			if(current->next == n1)
				prev1 = current;
			if(current->next == n2)
				prev2 = current;

			current = current->next;
		}

		//check if n1 and n2 are adjecent nodes
		if(n1->next == n2)
		{
			Node* next2 = n2->next;

			//update links
			prev1->next = n2;
			n2->next = n1;
			n1->next = next2;
			return true;

		}
		if(n2->next == n1)
		{
			Node* next2 = n1->next;

			//update links
			prev2->next = n1;
			n1->next = n2;
			n2->next = next2;
			return true;
		}



		//swap
		Node* next1 = n1->next;
		Node* next2 = n2->next;
		Node* temp = n1;
		n1 = n2;
		n2 = temp;
		prev1->next = n1;
		prev2->next = n2;
		n1->next = next1;
		n2->next = next2;

		return true;
	}

	//sort a linked list
	void Sort(Node *head)
	{
		Node* n1 = head;
		while(n1->next != NULL)
		{
			Node* n2 = n1->next;
			while(n2 != NULL)
			{
				if(n1->value > n2->value)
				{
					Swap(head, n1, n2);
				}
				n2 = n2->next;
			}
			n1 = n1->next;
		}
	}

	//Print list
	void Print(Node* head)
	{
		Node* n = head;
		while(n->next != NULL)
		{
			cout << n->value << endl;
			n = n->next;
		}
	}

	//insert in sorted list
	void InsertInSorted(Node* head, Node* n)
	{
		Node* prev = NULL;
		Node* current = head;
		while(current != NULL)
		{
			if(current->value > n->value)
			{
				prev->next = n;
				n->next = current;
				break;
			}
			prev = current;
			current = current->next;
		}
	}

	void main1()
	{
		cout << __FUNCTION__ << endl;

		::std::vector<Node*> nodes;

		//populate
		Node* n10 = new Node(100, NULL);
		nodes.push_back(n10);
		Node* n9 = new Node(90, n10);
		nodes.push_back(n9);
		Node* n8 = new Node(80, n9);
		nodes.push_back(n8);
		Node* n7 = new Node(70, n8);
		nodes.push_back(n7);
		Node* n6 = new Node(60, n7);
		nodes.push_back(n6);
		Node* n5 = new Node(50, n6);
		nodes.push_back(n5);
		Node* n4 = new Node(40, n5);
		nodes.push_back(n4);
		Node* n3 = new Node(30, n4);
		nodes.push_back(n3);
		Node* n2 = new Node(20, n3);
		nodes.push_back(n2);
		Node* n1 = new Node(10, n2);
		nodes.push_back(n1);
		Node* n0 = new Node(0, n1);
		nodes.push_back(n0);

		//print original list
		Print(n0);

		//find nth node
		cout << endl << "print nthnode from the last" << endl;
		cout << "0th " << FindNthEndNode(n0, 0)->value << endl;
		cout << "1st " << FindNthEndNode(n0, 1)->value << endl;
		cout << "3rd " << FindNthEndNode(n0, 3)->value << endl;
		cout << "4th " << FindNthEndNode(n0, 4)->value << endl;
		cout << "5th " << FindNthEndNode(n0, 5)->value << endl;
		cout << "9th " << FindNthEndNode(n0, 9)->value << endl;
		cout << "10th " << FindNthEndNode(n0, 10)->value << endl;
		cout << "11th " << (FindNthEndNode(n0, 11)? FindNthEndNode(n0, 11)->value : 0) << endl;
		cout << "15th " << (FindNthEndNode(n0, 11)? FindNthEndNode(n0, 15)->value : 0) << endl;

		// find middle node
		cout << "\n***Middle " << FindMiddleNode(n0)->value << endl;

		//Swap
		Swap(n0, n4, n3);
		cout << "printing after swap" << endl;
		Print(n0);

		//reverse
		//cout << "printing reverse list" << endl;
		//Node* nr = reverse(n0);
		//Print(nr);

		//Sort
		Sort(n0);
		cout << "printing sorted list" << endl;
		Print(n0);

		//Insert in sorted list
		Node* nn = new Node(55, NULL);
		InsertInSorted(n0, nn);
		cout << "printing after Insert in sorted list" << endl;
		Print(n0);

		delete n0;
		delete n1;
		delete n2;
		delete n3;
		delete n4;
		delete n5;
		delete n6;
		delete n7;
		delete n8;
		delete n9;
		delete n10;
	}
}
////////////// Singlly Linked List ends //////////////////////////

////////////// Doublly Linked List starts //////////////////////////
namespace DoublyLinkedList
{
	class Node
	{
	public:
		Node*	next;
		Node*	prev;
		int		value;
	};

	void deleteNode(Node* node)
	{
		Node* next = node->next;
		Node* prev = node->prev;
		prev->next = node->next;
		next->prev = node->prev;
	}
}
////////////// Doublly Linked List ends //////////////////////////

void ReverseString(char* str)
{
	cout << str << endl;
	int i=0; //forward iterator
	int size=strlen(str);
	int n = size/2;
	for(i=0; i<n; i++)
	{
		char ci = *(str+i);
		*(str+i) = *(str+size-1-i);
		*(str+size-1-i) = ci;
	}
	cout << str << endl;
}

void FindLastInstanceOfAChar(char* str, char a)
{
	std::cout << str << " " << a << std::endl;

	int len = strlen(str);
	for(int i=len-1; i>=0; i--)
	{
		if(*(str+i) == a)
		{
			std::cout << "pos=" << i;
			break;
		}
	}
}

void ToUpper(char* str)
{
	cout << str << endl;
	char cur = *str;
	int i=0;
	while(cur)
	{
		if(cur>='a' && cur<='z')
			*(str+i) = cur-'a'+'A';
		cur = *(str+(++i));
	}
	cout << str << endl;
}

void Multiply7(int num)
{
	int res = (num<<3) - num;
	cout << "num=" << num << " Ans=" << res << endl;
}

//generate fib numbers
void fib(int size)
{
	int i = 0;
	int f1 = 0;
	int f2 = 1;
	int f3;
	while(i<size)
	{
		f3 = f1 + f2;
		cout << f3 << endl;

		f1 = f2;
		f2 = f3;
		i++;
	}
}


//############## Stack implemented as singly linked list ##############
namespace MyStack
{
	template<typename T> class Stack
	{
	public:
		class Node;

		Stack()
		{
			head	= NULL;
		}

		~Stack()
		{
			while(head != NULL)
			{
				Node* next = head->next;
				delete head;
				head = next;
			}
			//do{
			//	Node* next = head->next;
			//	delete head;
			//	head = next;
			//}while(head);
		}

		void push(T& t)
		{
			Node* node	= new Node(t);
			node->next	= head;
			head		= node;
		}

		void push(T t)
		{
			Node* node	= new Node(t);
			node->next	= head;
			head		= node;
		}

		T pop()
		{
			if(head == NULL) return NULL;

			Node* node = head;
			head = head->next;
			T t = node->t;
			delete node;
			return t;
		}

		void print()
		{
			if(head == NULL)
			{
				cout << "stack is empty" << endl;
				return;
			}

			Node* node = head;
			do{
				cout << node->t << endl;
				node = node->next;
			}while(node);
		}

	private:
		Node* head;

		class Node
		{
		public:
			Node(T& tt) : t(tt), next(0){}
			Node* next;
			T t;
		private:
		};

	};

	void func()
	{
		Stack<int> stack;
		stack.push(1);
		stack.push(3);
		stack.push(5);
		stack.push(7);
		stack.push(9);
		stack.print();
		cout << stack.pop() << endl;
		cout << stack.pop() << endl;
		stack.print();
		cout << stack.pop() << endl;
		cout << stack.pop() << endl;
		cout << stack.pop() << endl;
		stack.print();
	}
}


//############## Queue implemented as singly linked list ##############
namespace MyQueue
{
	template<typename T> class Queue
	{
	public:
		class Node;

		Queue()
		{
			head = tail = 0;
		}

		~Queue()
		{
			while(head != NULL)
			{
				Node* next = head->next;
				delete head;
				head = next;
			}
		}

		void push_back(T t)
		{
			Node* node	= new Node(t);
			if(tail == NULL)
			{
				head = tail = node;
				return;
			}
			tail->next	= node;
			tail = node;
		}

		T pop_front()
		{
			if(head == NULL) return NULL;

			Node* node = head;
			head = head->next;
			T t = node->t;
			delete node;
			return t;
		}

		void print()
		{
			if(head == NULL)
			{
				cout << "Queue is empty" << endl;
				return;
			}
			Node* node = head;
			do{
				cout << node->t << endl;
				node = node->next;
			}while(node);
		}

	private:
		Node* head;
		Node* tail;

		class Node
		{
		public:
			Node(T tt) : t(tt), next(0) {}

			T t;
			Node* next;
		};


	};

	void func()
	{
		Queue<int> q;
		q.push_back(1);
		q.push_back(3);
		q.push_back(5);
		q.push_back(7);
		q.push_back(9);
		q.print();
		cout << q.pop_front() << endl;
		cout << q.pop_front() << endl;
		q.print();
		cout << q.pop_front() << endl;
		cout << q.pop_front() << endl;
		cout << q.pop_front() << endl;
		q.print();
	}
}



//////////////////////////////////////////////////////////////////
//write a code/pseudo-code to factorise an integer (< ULONG_MAX) into it's prime components.
//Assume the code is to run on a machine with N cores
#include <list>
#include <math.h>

//this function returns prime number equal to or greater than N
//ULONG NextPrimeNumber(ULONG N)
//{
//	switch(N)
//	{
//	case 0: return 1;
//	case 1: return 1;
//	case 2: return 2;
//	case 3: return 3;
//	case 4: return 5;
//	case 5: return 5;
//	}
//
//	//convert into odd if even
//	ULONG NN = (N%2)? N:N+1;
//	ULONG D = 3;
//	while(D<=sqrt((double)NN))
//	{
//		if(NN%D==0)
//		{
//			NN = ((NN+2)%5)? NN+2 : NN+4;
//			D = 3;
//			continue;
//		}
//		D += 2;
//	}
//	return NN;
//}
//
//void Factorize(ULONG N)
//{
//	//for smaller number just give number
//	if(N<4)
//	{
//		std::cout << N << "=" << N << std::endl;
//		return;
//	}
//
//	std::list<ULONG> factors;	//list containing factors
//	ULONG Q = N;	//Q will be sub number whose factor is needed
//	ULONG P = 2;	//prime numbers making factors
//	ULONG X = 1;
//	while(P<=(N/2.0))
//	{
//		//std::cout << "          Q=" << Q << ", P=" << P << std::endl;
//		if((Q%P)==0)
//		{
//			factors.push_back(P);
//			X *= P;
//
//			if(X==N)break;	//if product of all factors is equal to initial number then break
//			
//			Q = Q/P;
//			continue;
//		}
//		P = NextPrimeNumber(P+1);	//get next prime number
//	}
//
//	//if it is a prime number
//	if(factors.size()==0)
//	{
//		std::cout << N << "=" << N << std::endl;
//		return;
//	}
//
//	//printing the results
//	std::list<ULONG>::iterator itr = factors.begin();
//	std::cout << N << "=" << *itr;
//	++itr;
//	while(itr!=factors.end())
//	{
//		std::cout << "x" << *itr;
//		++itr;
//	}
//	std::cout << std::endl;
//}

long Factorial(unsigned No)
{
	if(No<2)return 1;
	return No*Factorial(No-1);
}


int NoofBits(int No)
{
	int i = 0;
	for(i=0;No; i++)
		No &= No-1;
	return i;
}

void PrintNoWithPutChar(int n)
{
	if(n==0)return;
	PrintNoWithPutChar(n/10);
	putchar('0'+n%10);
}

//Write a function that takes in a string parameter
//and checks to see whether or not it is an integer,
//and if it is then return the integer value.
void Str2Int(char* str)
{
	//check if plus or minus sign is there
	int sign = (*str == '-')? -1 : 1;
	if(sign == -1) ++str;

	int size = strlen(str);
	int i=0;
	int No=0;
	while(*str)
	{
		if(*str<'0' || *str>'9')
		{
			cout << "Not an integer" << endl;
			return;
		}
		int digit = *str - '0';
		No += digit*(int)pow(10.0, size-i-1);
		++str;
		++i;
	}
	cout << sign*No << endl;
}

//Write a function to convert a signed integer into a string
string Int2Str(int n)
{
	char sign = (n<0)? '-' : '+';
	n *= (n<0)? -1 : 1;	//taking absolute value
	std::string str;
	
	while(n>0)
	{
		int a = n%10;
		char c = a + '0';
		str.push_back(c);
		n /= 10;
	}
	str.push_back(sign);
	int size = str.size();
	char* p = new char[size+1];
	strcpy_s(p, size+1, str.c_str());
	for(int i=0; i<size/2; ++i)
	{
		char c = *(p+i);
		*(p+i) = *(p+size-1-i);
		*(p+size-1-i) = c;
	}
	string str2(p);
	delete[] p;
	return str2;
}


string binarise(int n)
{
	if(n==0) return "0";
	if(n%2 == 1) return binarise(n/2) + "1";
	else return binarise(n/2) + "0";		
}

//switch case
void q123()
{
	int n=0;
	int i;
	i=2;
	switch(1)
	{
	case 0:
		{
		do{
		case 1:n++;
		case 2:n++;
		}
		while(--i>0);
		}
	}
	printf("n==%d",n);	//4
}

void q124()
{
	class A
	{
	public:
		A(){cout << "A()" << endl; A(10);}
		A(int a){cout << "A(int a)" << endl;}
		void func(){cout << "A's func()" << endl;}
	};

	class B : public A
	{
	public:
		void func(){cout << "B's func()" << endl;}
	};

	//A a;
	B b;
	b.func();
	b.A::func();
}


void mythrow() throw()
{
	int a = 10;
//	throw a;
	cout << a << endl;
}



// Recursive template function
template <class RanIt, class Func>
void recursive_combination(RanIt nbegin, RanIt nend, int n_column,
    RanIt rbegin, RanIt rend, int r_column,int loop, Func func)
{
  int r_size=rend-rbegin;

  int localloop=loop;
  int local_n_column=n_column;

  //A different combination is out
  if(r_column>(r_size-1))
  {
    func(rbegin,rend);
    return;
  }
  //===========================

  for(int i=0;i<=loop;++i)
  {
    RanIt it1=rbegin;
    for(int cnt=0;cnt<r_column;++cnt)
    {
      ++it1;
    } 
    RanIt it2=nbegin;
    for(int cnt2=0;cnt2<n_column+i;++cnt2)
    {
      ++it2;
    } 

    *it1=*it2;

    ++local_n_column;

    recursive_combination(nbegin,nend,local_n_column,
      rbegin,rend,r_column+1,localloop,func);
      
    --localloop;
  }
}

namespace Deadlock
{


}

//check unwinding of objects in exception
void template1()
{
	class A
	{
	public:
		A() {cout << "A ctor" << endl;}
		~A() {cout << "A dtor" << endl;}
	};

	try
	{
		//A* a = new A();
		A a;
		throw 4;
	}
	catch(...)
	{ cout << "Exceptioon caught" << endl;}
}

//check if base pointer can call derived function
void ex2()
{
	class A
	{
	public:
		A() {cout << "A ctor" << endl;}
		~A() {cout << "A dtor" << endl;}

		void func(){cout << "this is funcA" << endl;}
	};
	class B : public A
	{
	public:
		B() {cout << "B ctor" << endl;}
		~B() {cout << "B dtor" << endl;}

		void func(){cout << "this is funcB" << endl;}
	};
	A* a = new B;
	a->func();
}

//check user defined default arguments
	class AAA{};
	void myfunc(AAA* a=NULL){}
	void myfunction1(int a){}
	void myfunction1(int a, int b=1){}
	void myfunction1(int a, int b=1, int c=1){}
void defarg()
{
	//myfunction1(2);	//ambiguous call
}

void TypeIDs()
{
	int i=0;
	int *p=&i;

	cout << "i type: " << typeid(i).name() << endl;
	cout << "int type: " << typeid(int).name() << endl;
	cout << "p type: " << typeid(p).name() << endl;

	class A{};
	A a;
	A* pa = &a;
	cout << "A type: " << typeid(A).name() << endl;
	cout << "a type: " << typeid(a).name() << endl;
	cout << "pa type: " << typeid(pa).name() << endl;

}

void ClassSize()
{
	class A {
	public:
		void AA(int a) { cout << "base class" << endl;}
	};
	class B : public A {
	public:
		void AA(int a, int b) { cout << "derived class" << endl;}
	};

	B b;
	b.AA(0, 2);
	int m = sizeof(B);
	int n = sizeof(b);

	std::vector<int> v;
	int p = sizeof(v);
	for(int i=0; i<999; i++)
		v.push_back(i);
	int size = v.size();
	int q = sizeof(v);

}


void delete_this()
{
	//int n = 12;
	//std::cin >> std::hex >> n;
	//std::cout << std::setprecision(2) << n;

	class MyClass{
	public:
		MyClass()
		{
			//delete this;
		};
		void suicide()
		{
			delete this;
		}
		~MyClass()
		{
			cout << "destructor is called" << endl;
		};
	};
	MyClass myclass;
	myclass.suicide();
	int a = 10;

}

namespace Functor1
{
	class MyFunct
	{
	public:
		//MyFunct(){cout << "MyFunct ctor" << endl;}
		//MyFunct(int i, int j){}
		int operator()(int a, int b)
		{
			return a+b;
		}
	};

	void functor1()
	{
		int a = 4;
		int b = 5;
		MyFunct f;
		cout << f(a, b) << endl;
	}
}

//finding mean using functor
namespace Functor2
{
	class Mean
	{
	private:
		int count;
		float sum;
		float avg;

	public:
		Mean():sum(0), count(0){}
		float operator()(float x)
		{
			sum += x;
			++count;
			avg = sum/count;
			cout << "Count=" << count << " val=" << x << " sum=" << sum << " Avg=" << avg << endl;
			return avg;
		}
	};

	void functor2()
	{
		vector<float> v;
		for(int i=0; i<10; i++)
			v.push_back((float)rand());
		for_each(v.begin(), v.end(), Mean());
	}
}

//calling a constructor from another constructor
namespace Ex1
{
	class A
	{
	public:
		A(int aa)
		{
			cout << "A ctor with 1 param" << endl;
			a = aa;
			A(a, 20);
		}
		A(int aa, int bb)
		{
			cout << "A ctor with 2 params" << endl;
		}

		int a, b;
	};

	void ex1()
	{
		A a(10);
		cout << "a=" << a.a << " b=" << a.b << endl;
	}
}

//Morgan Levy Questions
namespace MorganLevy
{
	class BB
	{
	public:
		virtual void vfunc()=0;
		void func()
		{
			vfunc();
		}
	};

	class Base
	{
	public:
		void print(){cout << 'B';}
		//void run()=0;
		//virtual int a;
	};
	class Derived : public Base
	{
	public:
		virtual void print(){cout << 'D';}
	};

	void q1()
	{
		Derived d;
		Base* p = &d;
		p->print();
		d.print();
	}

	class A
	{
	public:
		virtual int Calc(int a, int b){return 0;};
	};
	typedef int (A::*Type)(int, int);
	//typedef A::*int(Type)(int, int);
	//typedef virtual int Type(int, int);
	//typedef int(A::*)(int, int)Type;
	//typedef int(class::*Type)(int, int);

	void q2()
	{
		class A{public: void run(){}};
		A a;
		A *const p1 = &a;
		A *p = p1;
		p->run();
	}

	void q5()
	{
		Type pF = &A::Calc;
		A a;
		A* pA = &a;
		
		//pA->pF(3,4);
		//a.pF(3,4);
		(pA->*pF)(3,4);
		//(a.pF)(3,4);
		//pF(1,3,4);
		//pF(3,4);
		(a.*pF)(3,4);
	}
}

namespace UBS
{
	class Base
	{
	public:
		int i;
		Base() : i(0)
		{
			add(1);
		}		
		virtual void add(int v)
		{
			i += v;
		}

		void print(){ cout << i << endl;}
	};

	class Extension : public Base
	{
	public:
		Extension()
		{
			add(2);
		}
		void add(int v)
		{
			i += v*2;
		}
	};

	void bogo(Base& b)
	{
		b.add(8);
		b.print();
	}

	void UBS()
	{
		Extension ex;
		bogo(ex);
	}


}

namespace ThomsonReuters
{
	class Rectangle
	{
	public:
		void setWidth(float x){w=x;}
		void setHeight(float y){h=y;}
		float getArea(){return w*h;}
		float getDiag(){return sqrt(w*w + h*h);}
	protected:
		float w, h;
	};

	class Square : protected Rectangle
	{
	public:
		void setSide(float x){setWidth(x); setHeight(x);}
		float getArea(){return Rectangle::getArea();}
		float getDiag(){return Rectangle::getDiag();}
		double x, y;
	};

	void TR()
	{
		class abc{void get(){float b=8;}
		int set(int a){return a;}
		};
		int a0= sizeof(abc);
		int a = sizeof(Rectangle);
		int b = sizeof(Square);
		int c = sizeof(new Rectangle());
		int d = sizeof(new Square());
		//Rectangle rect;
		abc aa;
		int e = sizeof(aa);
	}
}

//creating multicast client and server sockets
namespace multicast
{//ws2_32.lib 
//wsock32.lib

	class MulticastServer
	{
	public:
		MulticastServer(std::string add, unsigned short port) : address(add), port(port)
		{
			//Initialize sockets
#if defined WIN32
			WSADATA wsa;
			WSAStartup(MAKEWORD(2,0),&wsa);
#endif

			CreateSocket(add, port);
			Send("786 Hello World");
		}
		~MulticastServer()
		{
#if defined WIN32
			WSACleanup();
#endif
		}

		void CreateSocket(std::string add, unsigned short port) //throw(std::exception)
		{
			if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
			{
				cout << "Error: " << __FUNCTION__ << " Socket allocating failed. " << WSAGetLastError() << endl;
				exit(-1);
			}

			//set up destination address
			memset(&addr, 0, sizeof(addr));
			addr.sin_family		= AF_INET;
			addr.sin_addr.s_addr= inet_addr(add.c_str());
			addr.sin_port		= htons(port);
		}

		void Send(std::string msg)
		{
			if(sendto(sock, msg.c_str(), strlen(msg.c_str()), 0, (struct sockaddr*)&addr, sizeof(addr)) < 0)
			{
				cout << "Error: " << __FUNCTION__ << " sendto failed. " << WSAGetLastError() << endl;
			}
		}

	protected:
		std::string	address;	//multicast ip address
		unsigned short	port;	//multicast port
		int sock;
		struct sockaddr_in addr;
	};

	class MulticastClient
	{
	public:
		MulticastClient(std::string add, unsigned short port) : address(add), port(port)
		{
			//Initialize sockets
#if defined WIN32
			WSADATA wsa;
			WSAStartup(MAKEWORD(2,0),&wsa);
#endif

			CreateSocket(add, port);
			Receive();
		}
		~MulticastClient()
		{
#if defined WIN32
			WSACleanup();
#endif
		}

		void CreateSocket(std::string add, unsigned short port) //throw(std::exception)
		{
			if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
			{
				cout << "Error: " << __FUNCTION__ << " Socket allocating failed. " << WSAGetLastError() << endl;
				exit(1);
			}

			// allow multiple sockets to use the same PORT number
			const unsigned int yes = 1;
			if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&yes, sizeof(yes)) < 0)
			{
				perror("Reusing ADDR failed");
				exit(1);
			}

			//set up destination address
			memset(&addr, 0, sizeof(addr));
			addr.sin_family		= AF_INET;
			addr.sin_addr.s_addr= htonl(INADDR_ANY);
			addr.sin_port		= htons(port);

			//bind to receive address
			//if(bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0 )
			//{
			//	perror("bind");
			//	exit(1);
			//}

			//use setsockopt() to request that the kernel join a multicast group
			struct ip_mreq mreq;
			mreq.imr_multiaddr.s_addr=inet_addr(add.c_str());
			mreq.imr_interface.s_addr=htonl(INADDR_ANY);
			if(setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mreq, sizeof(mreq)) < 0)
			{
				perror("setsockopt");
				exit(1);
			}

		}

		void Receive()
		{
			for(int i=0; i<3; ++i)
			{
				int nbytes;
				const int MSGBUFSIZE = 255;
				char msgbuf[MSGBUFSIZE];
				int addrlen = sizeof(addr);
				if((nbytes=recvfrom(sock, msgbuf, MSGBUFSIZE, 0,
			       (struct sockaddr *) &addr,&addrlen)) < 0)
				{
					perror("recvfrom");
					exit(1);
				}
				//puts(msgbuf);
				cout << std::string(msgbuf) << endl;
			}
		}

	protected:
		std::string	address;	//multicast ip address
		unsigned short	port;	//multicast port
		int sock;
		struct sockaddr_in addr;
	};
}

namespace FunctionPtr
{
	//Function Pointer
	float func(int a, char* str){return 0;};	//function declaration
	float (*pf)(int a, char* str);				//function pointer declaration
	void f1()
	{
		pf = &func;								//function pointer initialization
		float x  = (*pf)(10, "Hello");			//function pointer call
	}


	//Member Function Pointer
	class A
	{
	public:
		A() : pf(&A::func){};					//function pointer initialization in initializer list
		float func(int a, char* str);			//function declaration
		float (A::*pf)(int a, char* str);		//function pointer declaration

		void f1()
		{
			pf = &A::func;						//function pointer initialization
			float x = (this->*pf)(10, "Hello");	//function pointer call
		}
	};

}

//################### Dealhub assignment ##########################
// Recruiter: Robbie Green from Huxley
// Date: 05-02-2010
// Submitted on: 08/02/2010

//The Problem
//  A program to sort a list of names is required.
//  The file also contains the person’s age and phone number.
//  The main challenge is that the entire list can not fit into
//    physical memory at any given time.
//  There is no limit to the amount of physical disk space.
//
//The Input
//  An ASCII TSV (Tab Separated values) file containing a list of names.
//  Each line is of the format:
//  <Last Name>, <First Name><tab><age><tab><Phone Number><CR>
//
//The Output
//  A file in the same format sorted by Last Name.
//
//The Program
//  The final program must take three arguments
//
//    Maxnames – the maximum number of names which can be loaded
//               into memory at any given time
//    Input    - name of the input file
//    Output   – name of the results output file
//
//For example: SortNames.exe 10 input.txt output.txt
//
//The Solution
//You must provide 
//1. compilable c++ source code
//2. compiled working executable
//3. sample output file 
//
//The above should be zipped into a single zip file and emailed to devtest@dealhub.com

// Input sample
//Kalou, Salomon	30	476-2769
//Adebayor, Emmanuel	31	310-4951
//Morais, Nuno	37	660-6290
//Poom, Mart	34	469-8379
//Shevchenko, Andriy	26	922-2033
//Obi, Mikel	35	888-9370
//Ljungberg, Fredrik	34	492-1755
//Davenport, Calum	28	240-7734
//O'Hara, Jamie	30	333-5168
//vanPersie, Robin	33	363-4590
//Hallfresson, Emil	26	402-4246
//Johnson, Glen	33	793-3668
//Reid, Andy	36	910-1364
//Assou-Ekotto, Benoit	21	366-7451
//Berbatov, Dimitar	38	882-3330
//Smith, Jimmy	38	685-6050
//Zokora, Didier	25	143-4763
//Routledge, Wayne	34	450-3505
//Connolly, Matthew	28	239-1471
//King, Ledley	31	854-1648
//Gardner, Anthony	22	688-8382
//Robinson, Paul	31	775-8168
//Ziegler, Reto	29	555-8974
//Huddlestone, Tom	38	673-9691
//Ballack, Michael	26	303-5072
//Poom, Mart	27	938-8087
//Keane, Robbie	35	710-3165
//Stalteri, Paul	22	105-8767
//Clichy, Gael	32	735-3308
//Davids, Edgar	39	120-6298

//output sample
//Adebayor, Emmanuel	31	310-4951
//Aliadiere, Jeremie	21	189-9207
//Almunia, Manuel	36	480-5386
//Assou-Ekotto, Benoit	21	366-7451
//Ballack, Michael	26	303-5072
//Barnard, Lee	20	690-8146
//Bendtner, Nicklas	30	600-7601
//Berbatov, Dimitar	38	882-3330
//Bridge, Wayne	28	665-4884
//Carvalho, Ricardo	35	930-7797
//Cech, Petr	37	428-4820
//Cerny, Radek	34	401-1042
//Clichy, Gael	32	735-3308
//Cole, Ashley	21	832-8769
//Cole, Joe	32	338-7275
//Connolly, Matthew	28	239-1471
//Crespo, Hernan	37	177-7697
//Cudicini, Carlo	25	471-4850
//Cygan, Pascal	33	850-9612
//Davenport, Calum	28	240-7734
//Davids, Edgar	39	120-6298
//Dawson, Michael	35	570-4864
//Defendi, Rodrigo	27	340-2870
//Defoe, Jermaine	21	546-8731
//Diaby, Abou	30	386-1215


void SortNames(int maxnames, string fileInput, string fileOutput)
{
	//if(argc<3)
	//{
	//	cout << "Usage: SortNames.exe 10 input.txt output.txt" << endl;
	//	return 1;
	//}

	//int maxnames = 0;
	//string fileInput;
	//string fileOutput;
	//maxnames	= atoi(argv[1]);
	//fileInput	= argv[2];
	//fileOutput	= argv[3];

	//read maxnames line from input file
	//take first line from it
	//since output is sorted
	//so check where this line should go into the output file
	//once position is finalized then write it int output file at designated place.
	//repeat the same process for remaining lines
	//next next maznames lines repeat the process

	std::ifstream ifs(fileInput.c_str());	//file object to read input file
	std::ofstream ofs(fileOutput.c_str(), ios::out);	//file object to write into the output file
	std::ifstream ifsO(fileOutput.c_str());	//file object to read output file

	int pos = 0;
	char szI[255];
	char szO[255];
	int n=0;
	while(!ifs.eof())
	{
		for(int i=0; i<maxnames; ++i)
		{
			pos = 0;
			ifsO.seekg(0);

			ifs.getline(szI, 255);
			ifsO.getline(szO, 255);

			//check if output file is empty
			if(ifsO.tellg() < 0)
			{
				ofs << szI;
				ofs << endl;
				ofs.flush();
				ifsO.seekg(0);
				continue;
			}

			//read records till you reach the record which is greater than the inserting record
			while(strcmp(szI, szO)>0)
			{
				pos = ifsO.tellg();
				ifsO.getline(szO, 255);
				if(strlen(szO)<=0)
					break;
			}

			// get size of file
			ifsO.seekg(0,ifstream::end);
			int size = ifsO.tellg();
			size -= (pos+0);

			// allocate memory for file content
			char* buffer = new char [size];

			// read content of infile
			ifsO.seekg(pos);
			ifsO.read(buffer,size);
			int count = ifsO.gcount();

			// write new record
			ofs.seekp(pos);
			ofs << szI;
			ofs << endl;
			ofs.write(buffer, count);
			ofs.flush();
			ifsO.seekg(0);

			delete[] buffer;
		}
	}
	ifs.close();
	ifsO.close();
	ofs.close();
}
//################### Dealhub assignment ends ##########################

namespace RuleFinancial1
{
	class A
	{
	public:
		virtual void  foo(){cout << "foo in A" << endl;}
		void bar(){cout << "bar in A" << endl;}
	};
	class B : public A
	{
	public:
		void foo(){cout  << "foo in B" << endl;}
		void bar(){cout << "bar in B" << endl;}
	};

	void func()
	{
		B* pB;
		A* pA;
		B theB;
		pA = &theB;
		pB = &theB;
		pA->foo();		//foo in B
		pA->bar();		//bar in A
		pB->foo();		//foo in B
		pB->bar();		//bar in B
		((A*)pB)->foo();//foo in B
	}
}

namespace RuleFinancial2
{
	class A	{
	public:	~A(){cout << "~A()" << endl;}
	inline int & operator[] (unsigned i);
	};
	class A1 : public A {
	public:	~A1(){cout << "~A1()" << endl;}};

	class B	{
	public:	virtual ~B(){cout << "~B()" << endl;}
	};
	class B1 : public B {
	public:	~B1(){cout << "~B1()" << endl;}};

	void func()
	{
		A* pA = new A1();
		B* pB = new B1();
		delete pA;	//~A()
		delete pB;	//~B1()	~B()
	}
}

void testConst( int& arg)
{
	arg = 10;
}

namespace operator_conversion
{
	class ABC
	{
	public: ABC(): i(1), c('C'), aa(*this){std::cout << __FUNCTION__ << std::endl; }
			~ABC(){std::cout << __FUNCTION__ << std::endl;}
		int i;
		char c;
		ABC & aa;

		//operator conversion
		operator const char*(){return "hello world";}
		operator int(){return i;}
		operator char(){return c;}

		//app operator/functor
		void operator()(int ii){ std::cout << ii << std::endl;}
		int operator()(int a, int b, int c){return a+b+c+i;}

		//predicate
		bool operator()(char a){return true;}			// predicate
		bool operator()(int a, int b){return a+b+i;}	// binary predicate
	};

	void func()
	{
		try{
	ABC abc;
		ABC & ab = abc;
	//ABC *pa = new ABC();
	//delete pa;
	const char* str = abc;
	int a = abc;
	char cc = abc;
	std::cout << abc << " " << a << " " << cc << " " << str << " "
		<< abc(2,3) <<std::endl;

	//int inta[] = {1,2,3};
	//for_each(inta, inta+3, abc);
		}catch(...){}
	}

}

#include <time.h>
// N by N puzzle
namespace puzzle
{
	struct Location
	{
		Location(int r, int c): row(r), col(c){}
		int row;
		int col;
		bool operator<(const Location& ll) const
		{
			if(ll.row < row || ((ll.row == row) && (ll.col < col)))
				return true;
			else
				return false;
		}
		//Location(const Location & lloc){}
	};
	bool operator==(const Location& left, const Location& right)
	{
		return ((left.col == right.col) && (left.row == right.row));
	}

	//struct Cell
	//{
	//	bool isFilled;
	//};

	class NxNPuzzle
	{
		const int rows;
		const int cols;
		std::list<Location> unfilled;
		std::list<Location> filled;
//		std::map <Location, Cell> filled;
//		std::map <Location, bool> matrix;

	public:
		NxNPuzzle(const int size) : rows(size), cols(size)
		{
			NxNPuzzle(size, size);
		}

		NxNPuzzle(const int r, const int c) : rows(r), cols(c)
		{
			play();
		}

	protected:
		void play()
		{
			std::cout << "\ngame started!\n";
			srand (time(NULL));	//initialize random seed
			generateEmptyMatrix();	// generate emmpty cells of N x N matrix
			randomFiller();
			printMatrix();
		}

		void generateEmptyMatrix()
		{
			std::cout << __FUNCTION__ << std::endl;

			// generate empty cells where index represent location
			int size = rows * cols;
			for(int i=0; i<rows; i++)
			{
				for(int j=0; j<cols; j++)
				{
					unfilled.push_back(Location(i, j));
				}
			}
		}

		void randomFiller()
		{
			std::cout << __FUNCTION__ << std::endl;

			// generate a random number between 0 to size of unfilled
			do{
				Location loc = getUnfilledRandomLocation();

				// whether this location is valid or not, we should removed it from unfilled collection to avoid rechecking it again
				unfilled.remove(loc);

				// check validity
				if(isValid2Fill(loc))
				{
					// enter in filled collection
					filled.push_back(loc);
				}

			}while(unfilled.size()>0);
		}

		void printMatrix()
		{
			std::cout << __FUNCTION__ << std::endl;

			for(int r=0; r<rows; r++)
			{
				std::cout << '\n';

				for(int c = 0; c < cols; c++)
				{
					Location loc(r, c);
					//if(filled..find(loc) != filled.end())
					if(std::find(filled.begin(), filled.end(), loc) != filled.end())
					{
						// print a 'X'
						std::cout << 'X';
					}
					else
					{
						// print a blank space
						std::cout << ' ';
					}
				}
			}
		}

		
		Location getUnfilledRandomLocation()
		{
			// generates a random in the range of 0 <= range < unfilled.size()
			int rnd = rand()%unfilled.size();
			//std::cout << __FUNCTION__ << " unfilled.size()=" << unfilled.size() << ", random=" << rnd << std::endl;

			auto itr = unfilled.begin();
			for(int i=0; i<rnd; i++)
				++itr;
			return *itr;
		}

		//Location Index2Location(const int ind)
		//{
		//	//std::cout << __FUNCTION__ << std::endl;

		//	return Location(ind/rows, ind%rows);
		//}

		//int Location2Index(Location loc)	//1,1 in 4x4 matrix => 5
		//{
		//	//std::cout << __FUNCTION__ << std::endl;

		//	return loc.row*rows + loc.col;
		//}

		bool isValid2Fill(Location loc)
		{
			//std::cout << __FUNCTION__ << std::endl;

			if(isFilled(loc))	// if already there then return false
			{
				return false;
			}
			
			// check surrounding cells
			int row = loc.row;
			int col = loc.col;

			for(int i=-1; i<2; i++)
			{
				row = loc.row - i;
				for(int j=-1; j<2; j++)
				{
					col = loc.col - j;
					if(row==loc.row && col==loc.col)//skip self
						continue;

					//apply conditions here

					// if any diagonal cell is already filled=> false
					if(row != loc.row && col != loc.col)
						if(isFilled(Location(row, col)))
							return false;
				}
			}

			return true;
		}

		bool isFilled(Location loc)
		{
			//return (filled.find(loc) != filled.end());
			return (std::find(filled.begin(), filled.end(), loc) != filled.end());
		}


	};	// NxNPuzzle

	void f1()
	{
		NxNPuzzle puzzle(16);
	}
}	// puzzle

#include <queue>
#include <algorithm>
#include <functional>   // std::greater
//#include <iostream>

namespace FindFirstTopNElements
{
	int arr[] = {10,5,6,23,34,67,76,4,6,34};
	int size = 10;
	int N = 3;

	void using_priority_queue()
	{
		std::cout << "\n" << __FUNCTION__ << std::endl;
		std::copy(arr, arr+size, std::ostream_iterator<int>(std::cout, " "));

		// first first 3 top elements
		std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
		pq.push(arr[0]);
		for( auto a : arr)
		{
			if(a > pq.top())
			{
				if(pq.size() >= N)
				{
					pq.pop();
				}
				pq.push(a);
			}
		}

		// print top N elements
		std::cout << "\ntop " << N << " elements using priority_queue\n";
		while(!pq.empty())
		{
			std::cout << pq.top() << " ";
			pq.pop();
		}
	}

	void using_nth_element()
	{
		std::cout << "\n" << __FUNCTION__ << std::endl;
		std::copy(arr, arr+size, std::ostream_iterator<int>(std::cout, " "));
		std::nth_element(arr, arr+N, arr+10, std::greater<int>());
		std::cout << "\n"; std::copy(arr, arr+size, std::ostream_iterator<int>(std::cout, " "));
	}
}

namespace miscellaneous
{
// find if two words are ananogram
// ananogram are are those words with equal number and same set of characters but if different order
bool ananogram_using_sort(char w1[], char w2[])
{
	std::cout << __FUNCTION__ << std::endl;
	std::cout << "\nW1=" << w1 << " W2=" << w2 << std::endl;

	if(std::strlen(w1) != std::strlen(w2))
		return false;

	int size = strlen(w1);
	std::sort(w1, w1+2);
	std::sort(w2, w2+size);
	bool res = true;
	for(int i=0; i<size; ++i)
	{
		if(w1[i] != w2[i])
		{
			res = false;
			break;
		}
	}
	std::cout << "\n" << (res? "true" : "false") << std::endl;
	return res;
}

bool ananogram_using_map(char w1[], char w2[])
{
	std::cout << __FUNCTION__ << std::endl;
	std::cout << "\nW1=" << w1 << " W2=" << w2 << std::endl;

	bool res = false;

	if(std::strlen(w1) != std::strlen(w2))
	{
		std::cout << "\nfalse\n";
		return false;
	}

	int size = strlen(w1);

	// put w1 in map
	std::map<char, int> mapw1;
	for(int i=0; i<size; ++i)
	{
		char c = w1[i];
		int count = 0;
		auto itr = mapw1.find(c);
		if(itr != mapw1.end())
		{
			count = itr->second;
		}
		mapw1[c] = ++count;
	}

	// checking w2 against w1
	res = true;
	for(int i=0; i<size; ++i)
	{
		char c = w2[i];
		int count = 0;
		auto itr = mapw1.find(c);
		if(itr == mapw1.end())
		{
			res = false;
			break;
		}
		else
		{
			count = itr->second;
			if(count == 1)
			{
				mapw1.erase(c);
			}
			else
			{
				mapw1[c] = --count;
			}
		}
	}
	std::cout << "\n" << (res? "true" : "false") << std::endl;
	return res;
}


// remove all all Bs from a vector in-place
void removeAllBs()
{
	std::cout << __FUNCTION__ << std::endl;
	char arr[] = {'B', 'A', 'C', 'B', 'D', 'Z', 'E', 'F', 'B', 'X', 'W', 'B'};
	std::vector<char>v(arr, arr+sizeof(arr)/sizeof(char));
	std::cout << "\n";	std::copy(v.begin(), v.end(), std::ostream_iterator<char>(std::cout, " "));


	int count = 0;
	for(int i=0; i<v.size(); ++i)
	{
		if(count>0)
			v[i] = v[i+count];

		char c = v[i];
		if(c == 'B')
		{
			++count;
			--i;
		}
	}

	// remove last count elements as those are already moved
	for(int i=0; i<count; ++i)
	{
		auto itr = v.end()-1;
		v.erase(itr);
	}
	std::cout << "\n";	std::copy(v.begin(), v.end(), std::ostream_iterator<char>(std::cout, " "));
}

// implement pre and post operators for a class
template<typename T> class A
{
public:
	A(T tt): t(tt)	{	}
	~A()	{	}
	A& operator++()	// pre increment
	{
		t = t + 1;
		return *this;
	}
	A& operator--()	// post increment
	{
		A a = *this;
		t = t + 1;
		return a;
	}

	T getValue(){return t;}

private:
	T t;
};	// template<typename T> class A

void PrePostInc()
{
	std::cout << __FUNCTION__ << std::endl;
/*	A<int> a(10);
	A<int> b(20);
	a++;
	A<int> bb = b--;
	int a_val = a.getValue();
	int b_val = b.getValue();
	int bb_val= bb.getValue();

	std::cout << "\nA=" << a_val;
	std::cout << "\nB=" << b_val;
	std::cout << "\nBB=" << bb_val;
*/
}	// void PrePostInc()

}	// miscellaneous

namespace sum_of_continguous_subarray
{
	int largestSubarraySum(int arr[], int size)
	{
		// using Kadane's algorithm
		int curr_max = INT_MIN;
		int final_max = 0;

		for (int i = 0; i < size; i++)
		{
			final_max = final_max + arr[i];
			if (curr_max < final_max)
				curr_max = final_max;

			if (final_max < 0)
				final_max = 0;
		}
		return curr_max;
	}

	void sum_of_continguous_subarray()
	{
		//int X[] = { -2, -3, 4, -1, -2, 1, 5, -3 };		// 7
		//int X[] = { 1, 3, 2};		// 6
		int X[] = { 1, 3, 2,4};
		int size = sizeof(X) / sizeof(X[0]);
		std::cout << "\nsize=" << size << ", sizeof(X)=" << sizeof(X) << ", sizeof(X[0])=" << sizeof(X[0]);
		int max_sum = largestSubarraySum(X, size);
		std::cout << "\nmaximum sum=" << max_sum;
	}

}
//////////////////////////////////////////////////////////////////
void main_Test()
{
	std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << std::endl;
  


	//t1();7
	//t3();
	//IKMTest();
	//BinaryTree::BinaryNodes();
	//SingleLinkedList::main1();
  //MyStack::func();
  //MyQueue::func();
	sum_of_continguous_subarray::sum_of_continguous_subarray();
	//char str[] = "abcd";
	//ReverseString(str);
	//FindLastInstanceOfAChar("asdfasdfasfasf", 's');
	//ToUpper(str);
	//Multiply7(5);
	//fib(8);
	//operator_conversion::func();
	//puzzle::f1();
	//FindFirstTopNElements::using_priority_queue();
	//FindFirstTopNElements::using_nth_element();

	char w1[] = "aad";
	char w2[] = "dad";
	//miscellaneous::ananogram_using_sort(w1, w2);
	//miscellaneous::ananogram_using_map(w1, w2);

	//miscellaneous::removeAllBs();
	//miscellaneous::PrePostInc();



  //cout << Int2Str(123).c_str() << endl;
  //cout << Int2Str(-1234).c_str() << endl;
  //cout << Int2Str(+1234).c_str() << endl;
  //cout << binarise(10) << endl;
	//PrintNoWithPutChar(123);
	//PrintInteger("-1234");
	//main_macquarie();
	//cout << Factorial(5) << endl;
	//cout << NoofBits(7) << endl;
	//+--q123();
	//q124();
	//q125::q125();
	//Functor1::functor1();
	//Functor2::functor2();
	//Ex1::ex1();
	//MorganLevy::q1();
  //UBS::UBS();
  //ThomsonReuters::TR();
  //RuleFinancial1::func();
  //RuleFinancial2::func();
  //multicast::MulticastServer server("230.0.0.1", 4444);
  //multicast::MulticastClient client("230.0.0.1", 4444);


	//char* p = new char[1000];
	//string* str = new (p)string("hello");
	////delete str;
	//delete[] p;







	//try{
	//mythrow();
	//}catch(...){cout << "exception caught" << endl;}



	//class A
	//{
	//public:
	//	A(){cout << "A ctor" << endl;}
	//	~A(){cout << "A dtor" << endl;}
	//};

	//class B
	//{
	//public:
	//	B(){cout << "B ctor" << endl;}
	//	~B(){cout << "B dtor" << endl;}
	//};

	//try{
	//	A a;
	//	B* b = new B();
	//	throw "hello";
	//}catch(...)
	//{
	//	cout << "Exception" << endl;
	//}

  //volatile long a = 10;
  //_InterlockedIncrement(&a);

  //for(int i=0; i<100; i++)
	 // Factorize(i);
	  //std::cout << i << ", " << NextPrimeNumber(i) << std::endl;

	// cannot access derived class members from base class pointer
	//class B
	//{
	//public: B() : i(1) {std::cout << __FUNCTION__ << std::endl;}
	//		int i;
	//};
	//class D : public B
	//{
	//public: D() : di(2){std::cout << __FUNCTION__ << std::endl;}
	//		int di;
	//};

	//B *b = new D;
	//std::cout << b->i << b->di;

	


}

