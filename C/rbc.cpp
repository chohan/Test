#include <bits/stdc++.h>


using namespace std;

#define trace(str)(std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << "(): " << str << std::endl)
template<typename T> void print(T coll){for(auto x:coll)std::cout<<x<<" "; std::cout<<std::endl;}

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'customSort' function below.
 *
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

struct A
{
    int element;
    int freq;
};

bool comp(A a, A b){
    return (a.freq < b.freq);
}

void customSort(vector<int> arr) {
trace("");

    // first sort based on frequency
    // next sort base on element
    
    // once vector for single uniq elements
    // separte vectors for 
    // separate vector for single element
    //std::count
    // sort
    std::sort(arr.begin(), arr.end());
    cout << "sorted input: "; print(arr);
    
    // find frequcy and move most requet to left
    std::map<int, A> abc;
    for(int i=0; i<arr.size(); ++i){
        int n =0;
        
      if(abc.find(arr[i]) != abc.end())
      {
        auto Aa = abc[i];   // struct A
        
          if(Aa.element == arr[i]){
              ++Aa.freq;
              abc[i] = Aa;
          }
      }
      else{
        A Aa;
        Aa.freq = 1;
        Aa.element = arr[i];
        abc[arr[i]] = Aa;
      }
      
    }   // for

    for(auto x:abc) cout << "key=" << x.first 
      << ", element: " << x.second.element 
      << ", freq: " << x.second.freq  
      << std::endl; 
    
      
    // extract collection of struct A from map
    std::vector<A> aa;
      auto it = abc.begin();
      while(it != abc.end()){
          aa.push_back(it->second);
          ++it;
      }
      
      // how to sort frequency wise
      std::sort(aa.begin(), aa.end(), comp);
      
      // printing the result
      for(auto x : aa){ 
        for(int i=0; i<x.freq; i++){
          std::cout << x.element << ", ";
        }
        cout << std::endl;      
      }

}// custom

int main()
{
    string arr_count_temp;
    std::cout << "pls enter values:\n";

    getline(cin, arr_count_temp);

    int arr_count = stoi(ltrim(rtrim(arr_count_temp)));

    vector<int> arr(arr_count);

    for (int i = 0; i < arr_count; i++) {
        string arr_item_temp;
        getline(cin, arr_item_temp);

        int arr_item = stoi(ltrim(rtrim(arr_item_temp)));

        arr[i] = arr_item;
    }

    customSort(arr);

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
