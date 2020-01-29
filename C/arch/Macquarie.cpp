#include "stdafx.h"
#include <iostream>
#include <set>
#include <algorithm>
#include <fstream>
#include <string>
#include <string.h>
using namespace std;



/////////////////////////// Macquarie Bank ///////////////////////
//Briony Borrie sent me this test on 17/11/2009 and I sent him the solution on 19/11/2009



//############ Question 1 ##############
//Write a method to determine if a given string is a palindrome (e.g.  "Madam I'm Adam", or "A man, a plan, a canal, Panama").
//
//	a) provide an implementation for: bool is_palindrome(char const * str)
//	b) what assumptions does your code make?
//	c) did you use a computer to do this? 
//	d) how long did it take to do this question?

namespace Macquarie_Palindrome
{
bool is_palindrome(char const* str)
{
	//allocate memory for purified input string
	//remove all characters except a-z
	//convert all lower case to upper case
	//check if string charachters are mirror image (palindromic test)

	//allocate memory for purified input string
	int size = strlen(str);
	char* str2 = new char[size+1];

	//remove all characters except a-z
	//convert all lower case to upper case
	int j=0;
	for(int i=0; i<size; i++)
	{
		char c = *(str+i);
		if(c>='a' && c<='z')
		{
			c=c-'a'+'A';
			*(str2+j++) = c;
		}
		else if(c>='A' && c<='Z')
		{
			*(str2+j++) = c;
		}
	}
	//adding terminating null character
	*(str2+j) = 0;
	size = j;

	//if there is no character assume it a palindrome and return as true
	if(strlen(str2)<=0)
		return true;

	//check if string charachters are mirror image (palindromic test)
	bool res = true;
	int half = (size-size%2)/2;	// taking half of highest even number of size
	for(int i=0; i<half; i++)
	{
		if(*(str2+i) != *(str2+size-1-i))
		{
			res = false;
			break;
		}
	}

	delete[] str2;

	return res;
}
}



//############ Question 2 ##############
//Write a C/C++ function that reverses a doubly-linked list. Do not use any STL.
//
//	a) provide an implementation for: 	void reverseDList(Node*& head)
//	b) what assumptions does your code make?
//	c) did you use a computer to do this? 
//	d) how long did it take to do this question?

namespace Macquarie_DList
{
class Node
{
public:
	Node() : value(0), prev(0), next(0){}
	Node(int val) : value(val), prev(0), next(0){}
	int		value;	//Node value
	Node*	next;	//next node pointer
	Node*	prev;	//previous node pointer
};


void reverseDList(Node*& head)
{
	Node* newList = NULL;
	Node* current = head;
	while(current)							//a,	b,	c	
	{
		Node* next = current->next;			//b,	c,	NULL
		//Node* prev = current->prev;

		current->prev = current->next;		//b,	c,	NULL
		current->next = newList;			//NULL,	a,	b

		newList = current;					//a,	b,	c
		current = next;						//b,	c,	NULL
	}
	head = newList;

}

void TestDList()
{
	//testing reversing of DList
	Node* n1 = new Node(1);
	Node* n2 = new Node(2);
	Node* n3 = new Node(3);
	Node* n4 = new Node(4);
	Node* n5 = new Node(5);

	n1->next = n2;
	n1->prev = NULL;
	n2->next = n3;
	n2->prev = n1;
	n3->next = n4;
	n3->prev = n2;
	n4->next = n5;
	n4->prev = n3;
	n5->next = NULL;
	n5->prev = n4;

	Node* head = n1;

	cout << head->value << endl;
	cout << head->next->value << endl;
	cout << head->next->next->value << endl;
	cout << head->next->next->next->value << endl;
	cout << head->next->next->next->next->value << endl;

	reverseDList(head);
	cout << head->value << endl;
	cout << head->next->value << endl;
	cout << head->next->next->value << endl;
	cout << head->next->next->next->value << endl;
	cout << head->next->next->next->next->value << endl;



	delete n1;
	delete n2;
	delete n3;
	delete n4;
	delete n5;
}
}



//############ Question 3 ##############
//Suppose you have a binary tree containing N nodes. Each node has a Name, a LeftChild and a RightChild. Write a C++  function to print the tree by levels. Print the root first, then all the children of the root, then all the grandchildren of the root, etc.Your algorithm must take O(n) time.
//	a) provide an implementation for:  	void printNodes(const Node * root);
//	b) what assumptions does your code make?
//	c) did you use a computer to do this? 
//	d) how long did it take to do this question?

namespace Macquarie_BinaryTree
{
//Binary Tree Node
class Node
{
public:
	Node() : Name(""), LeftChild(0), RightChild(0){}
	Node(string name) : Name(name), LeftChild(0), RightChild(0){}
	string	Name;		//Node name
	Node*	LeftChild;	//Left child node pointer
	Node*	RightChild;	//Right child node pointer
};

void printNodes(const Node* root)
{
	//print root node(print first level node)
	//note sub nodes (in the same cycle note the next level nodes)
	//loop it thru
	int* p = new int[10];

	int n = 1;		//No of nodes in current level
	int nSub = 1;	//No of nodes in next level

	//nodes of current level
	Node** nodes = new Node*[n];	//Nodes in current level (pointer to array of pointers)
	nodes[0] = const_cast<Node*>(root);

	while(nSub)
	{
		cout << "New level" << endl;
		Node** nodesSub = new Node*[2*n];
		nSub = 0;

		//loop thru the current level
		for(int i=0; i<n; i++)
		{
			//print the current level nodes
			Node* node = nodes[i];
			cout << node->Name << endl;

			//note next level nodes if they are not null
			if(node->LeftChild)
				nodesSub[nSub++] = node->LeftChild;
			if(node->RightChild)
				nodesSub[nSub++] = node->RightChild;
		}
		delete[] nodes;
		cout << endl;
		nodes = nodesSub;
		n = nSub;
	}
	delete[] nodes;
}

void TestBinaryTreeLevelPrint()
{
	//instantiate
	Node* n1 = new Node("25");
	Node* n2 = new Node("18");
	Node* n3 = new Node("30");
	Node* n4 = new Node("7");
	Node* n5 = new Node("19");
	Node* n6 = new Node("45");

	//arrange
	n1->LeftChild = n2;
	n1->RightChild = n3;
	n2->LeftChild = n4;
	n2->RightChild = n5;
	n3->RightChild = n6;

	printNodes(n1);

	//destroy
	delete n1;
	delete n2;
	delete n3;
	delete n4;
	delete n5;
	delete n6;
}
}



//############ Question 4 ##############
//Write a C++ Anagram Solver that generates all permutations for a given word (or phrase) and compares these permutations  to a dictionary. Assume you have access to a file containing a list of dictionary words.  Assume C++ design and readability are more important than execution speed. 
//Please write your own permutation algorithm – do not use stl next_permutation.
//
//	a) provide an implementation for a program that takes characters from argv[1] and outputs to stdout a list of anagrams.
//	b) Would you have written the implementation differently if execution speed was most important?
//	c) what other useful features could you add to this program?
//	d) what was the most difficult part of completing this question?
//	e) if you’d like to: provide an alternative implementation in your favourite language.
//	f) did you use a computer to do this? 
//	g) how long did it take to do this question?

namespace Macquarie_Anagram
{
//this function generate next permuted word from a given character string
//it is like next_permuation in STL algorithms
bool NextPermutation(char* sz)
{
	//cout << sz << "  before" << endl;	
	int size = strlen(sz);
//	char* sz = new char[size+1];
//	strcpy_s(sz, size+1, str);
	for(int i=size-1; i>0; i--)
	{
		//take any two adjecent characters
		if(sz[i-1] < sz[i])
		{
			//swap left character with next higher character on its right hand side
			std::sort(sz+i, sz+size);//sort to make comparison easier
			//cout << sz << "  after sort" << endl;
			for(int j=i; j<size; j++)
			{
				if(sz[j] > sz[i-1])
				{
					//swap the characters
					char tmp = sz[i-1];
					sz[i-1] = sz[j];
					sz[j] = tmp;

					//sort remaining right hand side of characters
					std::sort(sz+i, sz+size);
					break;
				}
			}
			//cout << sz << "  after" << endl;	
			return true;			
		}
	}

//	delete[] sz;
	return false;
}


void LoadWords(ifstream& file, set<string>& words, int size)
{
	char dword[255];	//dictionary word
	while(!file.eof())
	{
		file.getline(dword, 255, ',');

		if(size == strlen(dword))
		{
			//convert it into upper case
			for(int i=0; i<size; i++)
			{
				if(dword[i]>='a' && dword[i]<='z')
					dword[i] = dword[i] - 'a' + 'A';
			}
			words.insert(string(dword));
		}
	}
}

#include<fstream>
void Anagram()
{
	//permutation: P(r) = n!/(n-r)! -> n! (when r=n)
	//all characters are taken
	//no two consective characters in the word (it will work but will treat them as two different words)

	char sz[] = "words";//argv[1]

	//convert it into upper case
	int size = strlen(sz);
	for(int i=0; i<size; i++)
	{
		if(sz[i]>='a' && sz[i]<='z')
			sz[i] = sz[i] - 'a' + 'A';
	}

	//sort it
	sort(sz, sz+size);

	//open dictionary file
	ifstream dict("./mydictionary.txt", ifstream::in);
	if(!dict)
	{
		printf("could not open dictionary file \"../mydictionary.txt\"\n");
		return;
	}

	//loads only words whose length is equal to argv[1] length
	set<string> words;
	LoadWords(dict, words, strlen(sz));
	set<string>::iterator itr = words.begin();
	while(itr!=words.end())
	{
		cout << *itr++ << endl;
	}
	cout << endl;	

	//close disctionary file
	dict.close();

	do{
		//cout << endl;	
		if(words.find(string(sz)) != words.end())
			cout << sz << endl;
	}while(NextPermutation(sz));

}
}



//######################### main_Macquarie ############################
void main_Macquarie()
{
	cout << "main_Macquarie" << endl;
	bool res;
	res = Macquarie_Palindrome::is_palindrome("Madam I'm Adam");	//true
	res = Macquarie_Palindrome::is_palindrome("A man, a plan, my car, a canal, Panama");	//false
	res = Macquarie_Palindrome::is_palindrome("A man, a plan, a canal, Panama");	//true

	//Macquarie_DList::TestDList();
	//Macquarie_BinaryTree::TestBinaryTreeLevelPrint();
	//Macquarie_Anagram::Anagram();
}
