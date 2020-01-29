// g++ -g -w -o LeetCodeBook LeetCodeBook.cpp --std=c++17 -lpthread
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <thread>
#include <mutex>
#include <future>
#include <chrono>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>
#include <set>
#include <cassert>
#include <cstring>
#include <cmath>
#define trace(str)(std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << "(): " << str << std::endl)


std::vector<std::string> parser(const std::string& line, char delim)
{
	std::vector<std::string> fields;
	std::stringstream ss(line);
	std::string word;
	while(getline(ss, word, delim)){
		fields.push_back(word);
	}
	return fields;
}

void twoSum(const int argc, char** argv)
{
	int target = atoi(argv[2]);
	std::vector<int> number;
	for(int i=3; i<argc; i++){
		number.push_back(atoi(argv[i]));
	}
	std::map<int, int> map;
	for(auto i=0; i<number.size(); i++){
		int x = number[i];
		std::cout << "i="<<i << ", x="<<x <<std::endl;
		if(map[target-x]){ 
			std::cout << map[target-x]+1 << ", " << i+1 << std::endl;
			return;			
		}
		map[x] = i;
	}
}

void twoSumSortedInput(const int argc, char** argv)
{
	int target = atoi(argv[2]);
	std::vector<int> number;
	for(int i=3; i<argc; i++){
		number.push_back(atoi(argv[i]));
	}

	int i=0;
	int j=number.size()-1;
	while(i<j){
		int sum = number[i] + number[j];
		std::cout << "i="<<i << ", j="<<j << ", sum="<<sum << std::endl;
		if(sum == target){ std::cout << i+1 << ", " << j+1 << std::endl; return;}
		if(sum < target){i++; continue;}
		if(sum > target){j--; continue;}
	}
	std::cout << "not a valid target/array" << std::endl;
}

void palindrome(int argc, char** argv)
{
	std::string str = std::string(argv[2]);
	int i=0, j=str.size()-1;

	while(i!=j && i<j){
		char ci = tolower(str[i]);
		char cj = tolower(str[j]);

		// filter out any non-alphanumeric character
		while(!( (ci>='a' && ci<='z') || (ci>='0' && ci<='9') )) { ci = tolower(str[++i]); }
		while(!( (cj>='a' && cj<='z') || (cj>='0' && cj<='9') )) { cj = tolower(str[--j]); }
		//std::cout << "i,j=" << i << "," << j << std::endl;

		if(ci != cj){
			std::cout << "input string is not a palindrome" << std::endl;
			return;
		}
		i++;j--;
	}
	std::cout << "input string is a palindrome" << std::endl;
}


int strstr(int argc, char** argv)
{
	char* S = argv[2];
	char* s = argv[3];
	int n = std::strlen(argv[2]);
	int m = std::strlen(argv[3]);
	if(m==0) {std::cout<<"always a match"<<std::endl;return 0;}	// always a match
	if(m>n)	{std::cout<<"can never be a match"<<std::endl;return -1;}
	for(int i=0; i<n-m+1; i++){
		int j=0;
		//std::cout << "before while S["<<i<<"]="<< *(S+i) << ", s["<<j<<"}="<< *(s+j) << std::endl;
		while(*(S+i) == *(s+j) && j<m){
			//std::cout << "S["<<i<<"]="<< *(S+i) << ", s["<<j<<"}="<< *(s+j) << std::endl;
			i++;j++;
		}
		if(j==m){
			std::cout << "sub string found at " << i-m << std::endl;
			return i-m;
		}
	}
	std::cout << "no match found " << -1 << std::endl;
	return -1;
}


void reverseWords(int argc, char** argv)
{
	std::vector<std::string> v = parser(std::string(argv[2]), ' ');
	auto it = v.end();
	do{
		it--;
		std::cout << *it << " ";
	}while(it!=v.begin());
}

void reverseWordsInplace(int argc, char** argv)
{// ./LeetCodeBook reverseWords "the sky is blue"
	trace("");
	std::string str(argv[2]);
	int p2=str.size();
	int p1 =  p2;
	while(p1>=0){
		p2=p1-1;
		p1 = str.rfind(' ', p2);
		int d = p2 - p1;
trace("p1="<<p1 << ", p2="<<p2 << ", d="<<d);
		if(p1>0){ std::cout << str.substr(p1+1, d)  << std::endl; }
		else    { std::cout << str.substr(0, p2+1) << std::endl; }
	}
}

int main(int argc, char** argv)
{
	std::cout << "Bismillah" << std::endl;

	if(argc < 1) { trace("insufficient No of parameters."); return false;}
	     	if(strcmp(argv[1], "twoSum") == 0)							twoSum(argc, argv);
	else 	if(strcmp(argv[1], "twoSumSortedInput") == 0)		twoSumSortedInput(argc, argv);
	else 	if(strcmp(argv[1], "palindrome") == 0)		palindrome(argc, argv);
	else 	if(strcmp(argv[1], "strstr") == 0)		strstr(argc, argv);
	else 	if(strcmp(argv[1], "reverseWords") == 0)		reverseWordsInplace(argc, argv);


	return true;
}

