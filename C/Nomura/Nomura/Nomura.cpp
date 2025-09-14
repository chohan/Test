// Nomura.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <climits>
#include <fstream>
#include <math.h>
#include <iterator>
using namespace std;



// ###################### Problem 1 - What is the Median? ##########################################
//Problem 1 - What is the Median?
//Median plays an important role in the world of statistics. By definition, it is a value which
//divides an array into two equal parts. In this problem you are to determine the current
//median of some long integers.
//Suppose we have five numbers {1, 3, 6, 2, 7}. In this case, 3 is the median as it has
//exactly two numbers on its each side. {1, 2} and {6, 7}.
//If there are even number of values like {1, 3, 6, 2, 7, 8}, only one value cannot split this
//array into equal two parts, so we consider the average of the middle values {3,6}. Thus,
//the median will be (3+6)/2 = 4.5.
//In this problem, you have to print only the integer part, not the fractional. As a result,
//according to this problem, the median will be 4!
//Input
//The input consists of series of integers X ( 0 <= X < 2^31 ) and total number of integers
//N is less than 10000. The numbers may have leading or trailing spaces.
//Output
//For each input print the current value of the median.
//Sample Input Sample Output
//	1				1
//	3				2
//	4				3
//	60				3
//	70				4
//	50				27
//	2				4

class print
{
public:
	void operator()(int val) 
	{ cout << " " << val; }
};

//this soluction solves this problem using multiset. But problem with multiset is that it does not provide any
//random access iterator. So in order to get middle value one has to move the iterator to the middle.
void Problem1A()	//taking one input and printing corresponding result
{
	std::multiset<int> vals;	//using multiset as they are ordered and allow multiple same values
	std::multiset<int>::iterator itr;

	int N = 10000;
	int size = 0;
	int mid = 0;
	int median;
	int x;

	cout << "Please enter values(minus value to end)" << endl;
	cout << "Input\tOutput" << endl;
	while(!(std::cin >> x))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		cout << "Please enter a valid positive integer" << endl;
	}

	while(x >= 0 || size<N)
	{
		if(x<0 || x>INT_MAX)	//X ( 0 <= X < 2^31 )
			return;	

		vals.insert(x);
		itr = vals.begin();
		++size;
		
		//since it is not random access iterator so move it incrementally
		for(int i=0; i<mid; i++)
			++itr;

		if(size==1)
		{
			median = x;
		}
		else if(size%2)	//if size is odd
		{
			median = *itr;
		}
		else	//size is even
		{
			median = (*itr + *(++itr))/2;
			++mid;
		}

#ifdef _DEBUG
		cout << x << "\t" << median;// << endl;
		for_each(vals.begin(), vals.end(), print());
		cout << endl;
#else
		cout << x << "\t" << median << endl;
#endif

		while(!(std::cin >> x))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
			cout << "Please enter a valid positive integer" << endl;
		}
	}
	cout << "Problem 1(a) finished" << "\n\n\n";
}

//This solution solves this problem using vector as it provides random access iterator to get the middle value.
//But vector by itself is not sorted. It needs to be sorted after every new item is added
void Problem1B()
{
	std::vector<int> vals;

	int size = 0;
	int mid = 0;
	int median;
	int x;

	cout << "Please enter values(minus value to end)" << endl;
	cout << "Input\tOutput" << endl;
	while(!(std::cin >> x))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		cout << "Please enter a valid positive integer" << endl;
	}

	while(x >= 0)
	{
		if(x<0 || x>INT_MAX)	//X ( 0 <= X < 2^31 )
			exit(0);	

		vals.push_back(x);
		std::sort(vals.begin(), vals.end());	//sort it after every insertion
		++size;
		
		if(size==1)
		{
			median = x;
		}
		else if(size%2)	//if size is odd
		{
			median = vals[mid];
		}
		else	//size is even
		{
			median = (vals[mid] + vals[mid+1])/2;
			++mid;
		}

#ifdef _DEBUG
		cout << x << "\t" << median << " ";
		copy(vals.begin(), vals.end(), ostream_iterator<int>(cout, " "));
		cout << endl;
#else
		cout << x << "\t" << median << endl;
#endif

		while(!(std::cin >> x))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
			cout << "Please enter a valid positive integer" << endl;
		}
	}
	cout << "Problem 1(b) finished" << "\n\n\n";
}


// ############################### Problem 2 : Squares #########################
//A square is a 4-sided polygon whose sides have equal length and adjacent sides form 90-
//degree angles. It is also a polygon such that rotating about its centre by 90 degrees gives
//the same polygon. It is not the only polygon with the latter property, however, as a
//regular octagon also has this property.
//So we all know what a square looks like, but can we find all possible squares that can be
//formed from a set of stars in a night sky? To make the problem easier, we will assume
//that the night sky is a 2-dimensional plane, and each star is specified by its x and y
//coordinates.
//Input
//The input consists of a number of test cases. Each test case starts with the integer n (1 <=
//n <= 1000) indicating the number of points to follow. Each of the next n lines specify the
//x and y coordinates (two integers) of each point. You may assume that the points are
//distinct and the magnitudes of the coordinates are less than 20000. The input is
//terminated when n = 0.
//Output
//For each test case, print on a line the number of squares one can form from the given
//stars.
//Sample Input Sample Output
//4 1
//1 0 6
//0 1 1
//1 1
//0 0
//9
//0 0
//1 0
//2 0
//0 2
//1 2
//2 2
//0 1
//1 1
//2 1
//4
//-2 5
//3 7
//0 0
//5 2
//0

//structure showing x,y coordinates of any point(star)
struct XY
{
	int x; int y;
	void print()	{cout << "(" << x << "," << y << ") ";}
	bool operator==(const XY& xy){	return (xy.x==x && xy.y==y); }
};

// Non recursive template function
// combinations Cr = n!/(r!(n-r)!)
// to find next combination of r elements in a collection containing n elements
// n_being: begin input iterator of n collection
// n_end:	end input iterator of n collection
// r_begin: begin output iterator of r collection
// r_end:	end output iterator of r collection
template <class BidIt>
bool next_combination(BidIt n_begin, BidIt n_end, BidIt r_begin, BidIt r_end)
{
	bool boolmarked=false;
	BidIt r_marked;
	BidIt n_it1=n_end;
	--n_it1;

	BidIt tmp_r_end=r_end;
	--tmp_r_end;

	for(BidIt r_it1=tmp_r_end; r_it1!=r_begin || r_it1==r_begin; --r_it1,--n_it1)
	{
		if(*r_it1==*n_it1 )
		{
			if(r_it1!=r_begin) //to ensure not at the start of r sequence
			{
				boolmarked=true;
				r_marked=(--r_it1);
				++r_it1;//add it back again 
				continue;
			}
			else // it means it is at the start the sequence, so return false
				return false;
		}
		else //if(*r_it1!=*n_it1 )
		{
			//marked code
			if(boolmarked==true)
			{
				//for loop to find which marked is in the first sequence
				BidIt n_marked;//mark in first sequence
				for (BidIt n_it2=n_begin;n_it2!=n_end;++n_it2)
					if(*r_marked==*n_it2) {n_marked=n_it2;break;}

				BidIt n_it3=++n_marked;
				for  (BidIt r_it2=r_marked;r_it2!=r_end;++r_it2,++n_it3)
				{
					*r_it2=*n_it3;
				}
				return true;
			}
			for(BidIt n_it4=n_begin; n_it4!=n_end; ++n_it4)
				if(*r_it1==*n_it4)
				{
					*r_it1=*(++n_it4);
					return true;
				}
		}
	}
	return true;//will never reach here    
}

//Prints the vertices/points of an square
void PrintSquare(std::vector<XY> square)
{
	std::vector<XY>::iterator itr = square.begin();
	cout << endl;
	while(itr != square.end())
	{
		cout << "(" << itr->x << "," << itr->y << ") ";
		++itr;
	}
}

//calculates the distance between two vertices/points
inline float Distance(XY A, XY B)
{
	return sqrt((float)((A.x - B.x)*(A.x - B.x) + (A.y - B.y)*(A.y - B.y)));
}

//checked whether a given quadrilateral is an square
//any quadrilateral is a square if
// 1. all its sides are equal in lengths
// 2. lengths of both lines joining the opposite vertices are equal
bool IsSquare(std::vector<XY> square)
{
	std::vector<XY>::iterator itr = square.begin();	

	//A,B,C and D representing four vertices of a quadrilateral
	XY A = *itr;
	XY B = *(++itr);
	XY C = *(++itr);
	XY D = *(++itr);

	//I will select first vetex arbitrarily and would calculate
	//the distance from its adjecent vertices.
	//since I don't know which two points (among remaining three)
	//are adjecent, so I will calculate distance for all three (A-B, A-C, A-D)
	//Among these three distances, two should be equal (which will be adjecent)
	//if they are not then surely it is not a square
	float AB = Distance(A, B);
	float AC = Distance(A, C);
	float AD = Distance(A, D);

	//Try to find adjecent vertices to A
	//e.g. if B and D are adjecent vertices then AB==AD
	if(AB==AD)
	{
		//check distance between other two sides if they are also equal
		float CB = Distance(C, B);
		float CD = Distance(C, D);
		if( (AB==CB) && (AB==CD) )
		{
			//all four sides are equal
			//so it is a quadrangle

			//in a quadrangle (where all four sides are equal)
			//if the distances between two opposite vertices are equal then we can call it square
			float AC = Distance(A, C);
			float BD = Distance(B, D);
			return AC==BD;
		}
		else
		{
			//Not an square
			return false;
		}
	}
	else if(AB==AC)
	{
		//check distance between other two sides if they are also equal
		float DB = Distance(D, B);
		float DC = Distance(D, C);
		if( (AB==DB) && (AB==DC) )
		{
			//all four sides are equal
			//so it is a quadrangle

			//in a quadrangle (where all four sides are equal)
			//if the distances between two opposite vertices are equal then we can call it square
			float AD = Distance(A, D);
			float BC = Distance(B, C);
			return AD==BC;
		}
		else
		{
			//Not an square
			return false;
		}
	}
	else if(AC==AD)
	{
		//check distance between other two sides if they are also equal
		float BC = Distance(B, C);
		float BD = Distance(B, D);
		if( (AC==BC) && (AC==BD) )
		{
			//all four sides are equal
			//so it is a quadrangle

			//in a quadrangle (where all four sides are equal)
			//if the distances between two opposite vertices are equal then we can call it square
			float AB = Distance(A, B);
			float CD = Distance(C, D);
			return AB==CD;
		}
		else
		{
			//Not an square
			return false;
		}
	}
	else //none is equal to others -> not a square
	{
		//Not an square
		return false;
	}
}

void Problem2()
{
	int n;	//(1<=T<=1000) No of points
	const int MAX_PTS = 1000;
	
	//read No of points n
	cout << "Please enter No of points(1<=n<=1000 and 0 to end)" << endl;
	while(!(std::cin >> n))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		cout << "Please enter a valid positive integer" << endl;
	}

	while(n>=1 && n<=MAX_PTS)
	{
		std::vector<XY> coords;
		for(int i=0; i<n; i++)
		{
			//read x, y coordinates
			char szX[255];
			char szY[255];
			cin.getline(szX, 255, ' ');
			cin.getline(szY, 255);
			XY xy;
			xy.x = atoi(szX);
			xy.y = atoi(szY);
			coords.push_back(xy);
		}


		//taking every combination of four vertices
		//and checking if it is a square or not
		int count = 0;
		std::vector<XY> square(4);
		copy(coords.begin(), coords.begin()+4, square.begin());	//copying first four vertices as starting point
		do
		{
			if(IsSquare(square))
			{
				//PrintSquare(square); //to print vertices of the square
				++count;
			}
		}while( next_combination(coords.begin(), coords.end(), square.begin(), square.end()) );

		cout << count << endl;

		//read No of points n
		cout << "Please enter No of points(1<=n<=1000 and 0 to end)" << endl;
		while(!(std::cin >> n))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
			cout << "Please enter a valid positive integer" << endl;
		}
	}
	cout << "Problem 2 finished" << "\n\n\n";
}


// ################################## Problem 3: Gold Coins ####################
//The king pays his loyal knight in gold coins. On the first day of his service, the knight
//receives one gold coin. On each of the next two days (the second and third days of
//service), the knight receives two gold coins. On each of the next three days (the fourth,
//fifth, and sixth days of service), the knight receives three gold coins. On each of the next
//four days (the seventh, eighth, ninth, and tenth days of service), the knight receives four
//gold coins. This pattern of payments will continue indefinitely: after receiving N gold
//coins on each of N consecutive days, the knight will receive N+1 gold coins on each of
//the next N+1 consecutive days, where N is any positive integer.
//Your program will determine the total number of gold coins paid to the knight in any
//given number of days (starting from Day 1).
//Input
//Each line of the input (except the last one) contains data for one test case of the problem,
//consisting of exactly one integer (in the range 1..10000), representing the number of
//days. The end of the input is signaled by a line containing the number 0.
//Output
//There is exactly one line of output for each test case. This line contains the number of
//days from the corresponding line of input, followed by one blank space and the total
//number of gold coins paid to the knight in the given number of days, starting with Day 1.
//Sample Input Sample Output
//10 10 30
//6 6 14
//7 7 18
//11 11 35
//15 15 55
//16 16 61
//100 100 945
//10000 10000 942820
//1000 1000 29820
//21 21 91
//22 22 98
//0

//This solution solves it by calculataing the total payment at runtime.
//This approach is good if this calculation is NOT very oftenly required.
void Problem3A()
{
	int d;
	const int MAX_DAYS = 10000;
	vector<int> days;
	vector<int>::iterator itr;

	cout << "Please enter values(0 to end)" << endl;
	do
	{
		while(!(std::cin >> d))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
			cout << "Please enter a valid positive integer" << endl;
		}
		if(d>=1 && d<=MAX_DAYS)
			days.push_back(d);
	}while(d>=1 && d<=MAX_DAYS);

	//print results
	itr = days.begin();
	while(itr!=days.end())
	{
		d = *itr;
		int n = 1;	//No of days
		int r = 1;	//rate
		int p = 0;	//total payment
		while(n <= d)
		{
			p += r*r;
			n += ++r;
		}
		p += (d-n+r)*r;

		cout << d << " " << p << endl;

		++itr;
	}

	cout << "Problem 3(a) finished" << "\n\n\n";
}

//If I have to calculate it very often then I will calculate it once 
//and store the result in a vector and access those values
class gen
{
	int p;
	int r;
public:
	gen(int pp, int rr) : p(pp), r(rr){}
	int operator()()
	{
		int o = p;
		p += r;
		return o;
	}
};

//calculate salary of last day of previous rate
int PrevRateLastDaySalary(int n)
{
	return (n<=1)? 1 : n*n + PrevRateLastDaySalary(n-1);
}

//This solution first calculates payments for all days (1-10000) and stores them in a vector.
//Day will act as the index to this vector and will fetch the payment corresponding to that day.
//This solution is good if this calculation is quite oftenly required.
void Problem3B()
{
	std::vector<int> v;
	int d;
	const int MAX_DAYS = 10000;
	vector<int> days;
	vector<int>::iterator itr;

	cout << "Please enter values(0 to end)" << endl;
	do
	{
		while(!(std::cin >> d))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
			cout << "Please enter a valid positive integer" << endl;
		}
		if(d>=1 && d<=MAX_DAYS)
			days.push_back(d);
	}while(d>=1 && d<=MAX_DAYS);


	//one off calculations
	int n = 1;	//No of days
	int r = 1;	//rate
	int p = 0;	//total payment on first day of new rate
	while(MAX_DAYS > n)
	{
		p += (r-1)*(r-1)+1;	//caculate first day payment of new rate
		//cout << "r=" << r << "  p=" << p << endl;

		//payments based on current rate for r number of days
		std::generate_n(back_inserter(v), r, gen(p, r));

		n += r++;
	}

	//print results
	itr = days.begin();
	while(itr!=days.end())
	{
		d = *itr;
		cout << d << " " << v[d-1] << endl;
		++itr;
	}

	cout << "Problem 3(b) finished" << "\n\n\n";
}

// ############################### Problem 4 : Super Sale #######################
//There is a SuperSale in a SuperHiperMarket. Every person can take only one object of
//each kind, i.e. one TV, one carrot, but for an extra low price. We are going with a whole
//family to the SuperHiperMarket. Every person can take as many objects as he/she can
//carry from the SuperSale. We are given a list of objects with their respective price and
//weight. We also know the maximum weight that every person can stand. What is the
//maximal value of objects we can buy at SuperSale?
//Input
//The input consists of T test cases. The number of them (1<=T<=1000) is given on the
//first line of the input file. Each test case begins with a line containing a single integer
//number N that indicates the number of objects (1 <= N <= 1000). Then follows N lines,
//each containing two integers: P and W. The first integer (1<=P<=100) corresponds to the
//price of object. The second integer (1<=W<=30) corresponds to the weight of object.
//Next line contains one integer (1<=G<=100) it’s the number of people in our group. Next
//G lines contains maximal weight (1<=MW<=30) that can stand this i-th person from our
//family (1<=i<=G).
//Output
//For every test case your program has to determine one integer. Print out the maximal value of
//goods which we can buy with that family.
//Sample Input Sample Output
//2 72
//3 144
//72 17
//44 23
//31 24
//1
//26
//3
//72 17
//44 23
//31 24
//3
//26
//16
//24

//The question says it should read input from a file but guide says all inputs are from std in and all outputs are to std out
//I created for this problem both version
//Problem4a reads input from a file "F://input.txt"
void Problem4A()
{
	//assuming input file contains valid entries

	int T;	//(1<=T<=1000) No of test cases
	int N;	//(1<=N<=1000) No of objects
	int P;	//(1<=P<=100) Price of the object
	int W;	//(1<=W<=30) Weight of the object
	int G;	//(1<=G<=100) No of people in the group

	char sz[255];
	cout << "Please enter absolute path of file conatining the values (e.g. F:/input.txt" << endl;
	cin >> sz;
	std::ifstream file(sz);
	try
	{
		//read No of test cases T
		file.getline(sz, 255);
		T = atoi(sz);
		if(!(T>=1 && T<=1000))
		{
			cout << "Test case number out of range" << endl;
			return;
		}

		for(int t=0; t<T; t++)
		{
			//read No of objects
			file.getline(sz, 255);
			N = atoi(sz);
			if(!(N>=1 && N<=1000))
			{
				cout << "No of objects out of range" << endl;
				return;
			}

			int maxValue=0;	//maximal value of the group
			map<int, int> PW;

			//read price(P) and weight(W) values
			char szP[100];
			char szW[100];
			for(int n=0; n<N; n++)
			{
				file.getline(szP, 255, ' ');
				file.getline(szW, 255);
				P = atoi(szP);
				W = atoi(szW);
				if(!(P>=1 && P<=100))
				{
					cout << "Price is out of range" << endl;
					return;
				}
				if(!(W>=1 && W<=30))
				{
					cout << "Weight is out of range" << endl;
					return;
				}
				PW[P] = W;
			}

			//read No of persons in the group (G)
			file.getline(sz, 255);
			G = atoi(sz);
			if(!(G>=1 && G<=100))
			{
				cout << "No of people in Goup is out of range" << endl;
				return;
			}

			std::vector<int> MW;

			//read maximal weight by ith person in the group
			int mw;
			for(int g=0; g<G; g++)
			{
				file.getline(sz, 255);
				mw = atoi(sz);
				MW.push_back(mw);
			}


			//Processing
			int maxWt;	//maximal weight capacity by ith person in the group

			//looping thru the group
			std::vector<int>::iterator itrMW = MW.begin();
			while(itrMW != MW.end())
			{
				maxWt = *itrMW;

				//looping thru objects' price and weight
				W = 0;
				std::map<int, int>::reverse_iterator itrPW = PW.rbegin();
				while(itrPW!=PW.rend())
				{
					W += itrPW->second;
					if(W <= maxWt)
					{
						maxValue += itrPW->first;
					}
					else
					{
						break;
					}

					++itrPW;
				}
				++itrMW;
			}

			cout << "Max value = " << maxValue << endl;
		}


	}catch(...)
	{
		cout << "exception while reading file" << endl;
	}
	cout << "Problem 4(a) finished" << "\n\n\n";
}

//Problem4b reads input from std in
void Problem4B()
{
	//assuming input file contains valid entries

	int T;	//(1<=T<=1000) No of test cases
	int N;	//(1<=N<=1000) No of objects
	int P;	//(1<=P<=100) Price of the object
	int W;	//(1<=W<=30) Weight of the object
	int G;	//(1<=G<=100) No of people in the group

	try
	{
		//read No of test cases T
		cout << "Please enter values" << endl;
		cin >> T;
		if(!(T>=1 && T<=1000))
		{
			cout << "Test case number out of range" << endl;
			return;
		}

		for(int t=0; t<T; t++)
		{
			//read No of objects
			cin >> N;
			if(!(N>=1 && N<=1000))
			{
				cout << "No of objects out of range" << endl;
				return;
			}

			int maxValue=0;	//maximal value of the group
			map<int, int> PW;

			//read price(P) and weight(W) values
			char szP[100];
			char szW[100];
			for(int n=0; n<N; n++)
			{
				cin.getline(szP, 255, ' ');
				cin.getline(szW, 255);
				P = atoi(szP);
				W = atoi(szW);
				if(!(P>=1 && P<=100))
				{
					cout << "Price is out of range" << endl;
					return;
				}
				if(!(W>=1 && W<=30))
				{
					cout << "Weight is out of range" << endl;
					return;
				}
				PW[P] = W;
			}

			//read No of persons in the group (G)
			cin >> G;
			if(!(G>=1 && G<=100))
			{
				cout << "No of people in Goup is out of range" << endl;
				return;
			}

			std::vector<int> MW;

			//read maximal weight by ith person in the group
			int mw;
			for(int g=0; g<G; g++)
			{
				cin >> mw;
				MW.push_back(mw);
			}


			//Processing
			int maxWt;	//maximal weight capacity by ith person in the group

			//looping thru the group
			std::vector<int>::iterator itrMW = MW.begin();
			while(itrMW != MW.end())
			{
				maxWt = *itrMW;

				//looping thru objects' price and weight
				W = 0;
				std::map<int, int>::reverse_iterator itrPW = PW.rbegin();
				while(itrPW!=PW.rend())
				{
					W += itrPW->second;
					if(W <= maxWt)
					{
						maxValue += itrPW->first;
					}
					else
					{
						break;
					}

					++itrPW;
				}
				++itrMW;
			}

			cout << "Max value = " << maxValue << endl;
		}
	}catch(...)
	{
		cout << "exception while reading file" << endl;
	}
	cout << "Problem 4(b) finished" << "\n\n\n";
}

namespace TechTest20100202
{
class Node
{
public:
	Node(std::string& name) : label(name), left(0), right(0){}

	Node* left;
	Node* right;
	std::string label;
};

//		a
//	b	  c
//d		e	f
class TreeTraverse
{
public:
	void add(Node* node, Node* parent, bool left)
	{
		if(parent == NULL)
			list = node;
		else if(left)
			parent->left = node;
		else
			parent->right = node;
	}

	//dbefca
	void depthTraverse(Node* node)
	{
		cout << node->label.c_str() << " ";
		if(node->left)
			depthTraverse(node->left);
		if(node->right)
			depthTraverse(node->right);
	}

	//abcdef
	void breadthTraverse(Node* node)
	{
		//print root node(print first level node)
		//note sub nodes (in the same cycle note the next level nodes)
		//loop it thru

		int n = 1;		//No of nodes in current level
		int nSub = 1;	//No of nodes in next level

		//nodes of current level
		Node** nodes = new Node*[n];	//Nodes in current level (pointer to array of pointers)
		nodes[0] = const_cast<Node*>(node);

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
				cout << node->label.c_str() << endl;

				//note next level nodes if they are not null
				if(node->left)
					nodesSub[nSub++] = node->left;
				if(node->right)
					nodesSub[nSub++] = node->right;
			}
			delete[] nodes;
			cout << endl;
			nodes = nodesSub;
			n = nSub;
		}
		delete[] nodes;
	}

	Node* list;

};
	void Noder()
	{
		TreeTraverse tt;
		
		//build list
		Node a(std::string("a"));
		tt.add(&a, NULL, true);

		Node b(std::string("b"));
		tt.add(&b, &a, true);

		Node c(std::string("c"));
		tt.add(&c, &a, false);

		Node d(std::string("d"));
		tt.add(&d, &b, true);

		Node e(std::string("e"));
		tt.add(&e, &c, true);

		Node f(std::string("f"));
		tt.add(&f, &c, false);

		//depthTraverse(dbefca)
		cout << "\ndepthTraverse" << endl;
		tt.depthTraverse(tt.list);

		//breadthTraverse(abcdef)
		cout << "\nbreadthTraverse" << endl;
		tt.breadthTraverse(tt.list);
	}

}


//######################### main_Nomura ############################

int _tmain(int argc, _TCHAR* argv[])
{
	int p = 0;
	cout << "main_Nomura" << endl;

	do 
	{
		cout << "Enter problem No (1-4) to solve. Any other will terminate" << endl;
		while(!(std::cin >> p))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
			cout << "Please enter a valid positive integer" << endl;
		}
		if(p<1 || p>4)
			break;

		switch(p)
		{
		case 1:
			cout << "\nProblem 1 - What is the Median?" << endl;
			cout << "Solution A" << endl;
			Problem1A();

			cout << "\nProblem 1 - What is the Median?" << endl;
			cout << "Solution B" << endl;
			Problem1B();
			break;

		case 2:
			cout << "\nProblem 2 - Squares" << endl;
			cout << "Solution" << endl;
			Problem2();
			break;

		case 3:
			cout << "Problem 3 - Gold Coins" << endl;
			cout << "Solution A" << endl;
			Problem3A();

			cout << "Problem 3 - Gold Coins" << endl;
			cout << "Solution B" << endl;
			Problem3B();
			break;

		case 4:
			cout << "Problem 4 - SuperSale" << endl;
			cout << "Solution A" << endl;
			Problem4A();

			cout << "Problem 4 - SuperSale" << endl;
			cout << "Solution B" << endl;
			Problem4B();
			break;

		default:
			break;
		}

	}while(true);
	cout << "Good Bye" << "\n\n\n";

	return 0;
}
