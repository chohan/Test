// g++ -g -Wall -o Exane Exane.cpp --std=c++17 -lpthread
#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <chrono>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#define trace(str)(std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << "(): " << str << std::endl)


void median(const int argc, char** argv)
{
	std::multiset<int> arr;
	int size=0;
	std::string data;
	while(getline(std::cin, data))
	{
		if(strcmp(data.c_str(), "exit") == 0) return;
		int x = atoi(data.c_str());
		if(x==0)	return; 	// presuming zero is not a valid item
		arr.insert(x);
		//std::copy(arr.begin(), arr.end(), std::ostream_iterator<int>(std::cout, " "));
		++size;
		int mid=(size-1)/2;
		//std::cout << "size=" << size << ", mid="<<mid << std::endl;
		if(size%2){	// odd
			x = *std::next(arr.begin(), size/2);
			std::cout << x << std::endl;
		}
		else{	// even
			auto it = std::next(arr.begin(), mid);
			x = (*it + *(++it))/2;
			std::cout << x << std::endl;
		}
	}
}


/**
	this function can be avoided to improve memory footprint by embedding this code in ssquare function. But I prefer clarity and made a separate function
*/
std::vector<std::vector<int>> combi(int N, int K)
{
	//std::cin >> N >> K;
	std::vector<std::vector<int>> res;

  std::string bitmask(K, 1); // K leading 1's
  bitmask.resize(N, 0); // N-K trailing 0's
 
  // print integers and permute bitmask
  do {
		std::vector<int> s;
    for (int i = 0; i < N; ++i) // [0..N-1] integers
    {
      if (bitmask[i]) {
				//std::cout << " " << i; 
				s.push_back(i);
			}
    }
    //std::cout << std::endl;
		res.push_back(s);
  } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
	//std::cout <<"combinations="<< res.size()<<std::endl;
	return res;
}

struct Point{int x; int y; void print(){std::cout << "("<<x << "," <<y <<")";}};
inline bool operator<(const Point& lhs, const Point& rhs){if(lhs.x==rhs.x) return lhs.y<rhs.y; else return lhs.x<rhs.x;};
float sqD(Point a, Point b)
{
	return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}

bool isSquare(Point p1, Point p2, Point p3, Point p4) 
{ 
  int d2 = sqD(p1, p2); // from p1 to p2 
  int d3 = sqD(p1, p3); // from p1 to p3 
  int d4 = sqD(p1, p4); // from p1 to p4 
  
  if (d2 == d3 && 2 * d2 == d4 && 2 * d2 == sqD(p2, p3)) { 
      int d = sqD(p2, p4); 
      return (d == sqD(p3, p4) && d == d2); 
  } 
  
  if (d3 == d4 && 2 * d3 == d2 && 2 * d3 == sqD(p3, p4)) { 
      int d = sqD(p2, p3); 
      return (d == sqD(p2, p4) && d == d3); 
  } 
  if (d2 == d4 && 2 * d2 == d3 && 2 * d2 == sqD(p2, p4)) { 
      int d = sqD(p2, p3); 
      return (d == sqD(p3, p4) && d == d2); 
  } 
  
  return false; 
}

std::vector<Point> _pts;
void squares(const int argc, char** argv)
{
	std::string data;
	while(true)
	{
		_pts.clear();
		int N=0; std::cin >> N; if(N == 0) return;

		std::vector<std::set<Point>> square;	// squares found
	
		// taking input points
		for(int i=0; i<N; i++){
			Point p;
			std::cin >> p.x >> p.y;
			_pts.push_back(p);
		}
		//{auto it=_pts.begin();while(it!=_pts.end()){it->print();it++;}std::cout<<std::endl;}
		
		// create sets
		//std::cout << "N, K " << N << " " << 4 << std::endl;
		std::vector<std::vector<int>> combis = combi(N, 4);
		auto it=combis.begin();
		while(it!=combis.end()){
			int p0=(*it)[0], p1=(*it)[1], p2=(*it)[2], p3=(*it)[3];
			//std::cout << p0 << " " << p1 << " " << p2 << " " << p3 << std::endl;
			//std::cout << p0 << "(" << _pts[p0].x << "," << _pts[p0].y << ") "
			//					<< p1 << "(" << _pts[p1].x << "," << _pts[p1].y << ") "
			//					<< p2 << "(" << _pts[p2].x << "," << _pts[p2].y << ") "
			//					<< p3 << "(" << _pts[p3].x << "," << _pts[p3].y << ")" << std::endl;
			if(isSquare(_pts[p0], _pts[p1], _pts[p2], _pts[p3])){
				//std::cout << "potencially found a square " << p0 << " " << p1 << " " << p2 << " " << p3 << std::endl;

				// check if not already found
				{
					bool alreadyfound=false;
					auto it = square.begin();
					while(it!=square.end()){
						auto sqr = *it;
						//{auto itt=sqr.begin();while(itt != sqr.end()){Point pt=*itt; pt.print();itt++;}std::cout<<std::endl;}
						if(  (sqr.find(_pts[p0])!=sqr.end())
							&& (sqr.find(_pts[p1])!=sqr.end())
							&& (sqr.find(_pts[p2])!=sqr.end())
							&& (sqr.find(_pts[p3])!=sqr.end()) ){
								alreadyfound=true;
								//std::cout << "already found" << std::endl;
								break;
						}
						it++;
					}
					if(!alreadyfound){
						std::set<Point> sq;
						sq.insert(_pts[p0]);sq.insert(_pts[p1]);
						sq.insert(_pts[p2]);sq.insert(_pts[p3]);
						square.push_back(sq);
						//std::cout << "certainly found new square" << " squares="<<square.size() << " sq="<<sq.size() << std::endl;
					}
				}
			}
			it++;
		}
		std::cout << "Squares=" << square.size() << std::endl;
	}
}


void coins(int argc, char** argv)
{
	int days=0;
	//while(true){
	while((std::cin >> days) && (days > 0) ){

		int r = 1;
		int d = 1;
		int coins = 0;
		while(d<=days){
			for(int i=1; i<=r; i++){
				coins += r;
				//std::cout << "d="<<d << ", r="<<r << ", coins="<<coins << std::endl;
				d++;
				if(d > days) break;
			}
			r++;
		}
		std::cout << days << " " << coins << std::endl;
	}
}


int main(int argc, char** argv)
{
			 	if(memcmp(argv[1], "median", strlen("median")) == 0)	median(argc, argv);
	else 	if(memcmp(argv[1], "squares", strlen("squares")) == 0)	squares(argc, argv);
	else 	if(memcmp(argv[1], "coins", strlen("coins")) == 0)	coins(argc, argv);
	else 	if(memcmp(argv[1], "combi", strlen("combi")) == 0)	combi(0,0);

	return true;
}

