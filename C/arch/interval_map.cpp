// compile: g++ -g -w -o interval_map interval_map.cpp --std=c++17 -lpthread
// platform: g++ (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0
// run: ./interval_map
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <optional>
#include <iterator>
#include <map>
#include <limits>
#include <cassert>
#define trace(str)(std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << "(): " << str << std::endl)

template<typename K, typename V>
class interval_map {
	std::map<K,V> m_map;

public:
    // constructor associates whole range of K with val by inserting (K_min, val)
    // into the map
    interval_map( V const& val) {
        m_map.insert(m_map.end(),std::make_pair(std::numeric_limits<K>::lowest(),val));
				trace("map size " << m_map.size());
    }

    //friend bool operator>(K const & lhs, K const & rhs) {return rhs<lhs;} // to be implemented by the user
    //friend bool operator==(V const & lhs, V const & rhs) {return rhs==lhs;} // to be implemented by the user

    // Assign value val to interval [keyBegin, keyEnd).
    // Overwrite previous values in this interval.
    // Conforming to the C++ Standard Library conventions, the interval
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval,
    // and assign must do nothing	// delete if interval is smaller.
    void assign( K const& keyBegin, K const& keyEnd, V const& val ) {
// INSERT YOUR SOLUTION HERE
      
      if(!(keyBegin < keyEnd)) return; //this designates an empty interval, and assign must do nothing.
        
      V value_before;	// update only if different
      bool erase = true;	// delete if interval is smaller

			// update
      auto it_start = m_map.lower_bound(keyBegin);
      auto it_start_del = it_start;
      if(it_start != m_map.end() && it_start->first == keyBegin){// if exists then update
      	value_before = it_start->second;
				trace("keyBegin="<<keyBegin << ", val=" << value_before << "->" << val);
      	it_start->second = val;
        ++it_start_del;
        if(it_start_del == m_map.end()){ erase = false; }
      }else{	// insert start of interval
        auto prev = it_start;
        --prev;
        value_before = prev->second;
        if (prev->second != val){
					trace("keyBegin="<<keyBegin << ", val="<<val);
          auto it = m_map.insert(it_start, std::make_pair(keyBegin, val)); 
          it_start = it;
          it_start_del = ++it;   
        }
      }

			// add
      auto it_end = m_map.lower_bound(keyEnd); 
      auto it_end_del = it_end;
      if(it_end_del == it_start_del){ erase = false; }
      if(it_end == m_map.end() || it_end->first != keyEnd){	// insert end of interval
        auto prev = it_end;
        --prev;
        if(prev != it_start){ value_before = prev->second; }
        if (value_before != val) {
					trace("keyEnd="<<keyEnd << ", val_before="<<value_before);
          auto it = m_map.insert(it_end, std::make_pair(keyEnd, value_before)); 
          it_end_del = it;
          if ((++it) != m_map.end() && it->second == value_before) 
            m_map.erase(it);
        }
      }

      //delete items if and where required
      if (erase 
					&& it_start_del != m_map.end() 
					&& it_end_del   != m_map.end() 
					&& it_start_del->first < it_end_del->first){
          m_map.erase(it_start_del, it_end_del); 
				}

    }

bool operator<(const K& other) const {
	return *this < other;
}
bool operator==(const V& other) const{
	return *this == other;
}


			//auto last = insert_upper_bound(std::move(keyEnd));
			//auto first = m_map.lower_bound(keyBegin);
      //m_map.erase(first, last);
      //m_map.insert(last, std::make_pair(std::move(keyBegin), std::move(val)));
      
      //m_map[keyBegin] = val;

/*

		auto insert_upper_bound(K&& keyEnd){
			auto last = m_map.upper_bound(keyEnd);
			if(last == m_map.begin()){
				//return m_map.insert(keyEnd, std::make_pair(std::move(keyEnd), std::optional<K>{}));
				return m_map.insert(keyEnd, std::make_pair(std::move(keyEnd), std::optional<V>{}));
			}
			auto&& value_before = std::prev(last)->second;
			return m_map.insert(keyEnd, std::make_pair(std::move(keyEnd), value_before));
		}

		std::optional<V>
      operator[](const K& key) const // DBJ removed --> & 
          // DBJ removed, see DBJ 01 -- noexcept(std::is_nothrow_callable_v<Compare(const Key&, const Key&)>)
      {
        auto ub = m_map.upper_bound(key);
        if (ub == m_map.begin()) {
          return {};
        }
        return (--ub)->second;
      }
*/

  // lookup
  V const& operator[](K const& key) const {
    return (--m_map.upper_bound(key))->second;
  }
	auto begin(){return m_map.begin();}
	auto end()	{return m_map.end();}
};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of unsigned int intervals to char.


int main(int argc, char** argv)
{
	// testing
  interval_map<unsigned int, char> mm(' ');

	// insert some values
  trace("mm.assign(1,5, 'A');");	mm.assign(1,5, 'A');	
  trace("mm.assign(6,7, 'F');");	mm.assign(6,7, 'F');	
  trace("mm.assign(8,9, 'H');");	mm.assign(8,9, 'H');	

	// printing whole map
  auto it = mm.begin();
  while(it!=mm.end()){ std::cout << "K="<<it->first << ", V="<<it->second << std::endl; it++; }

	// print whole map but differently
	for(int i=0; i<10; i++){ std::cout << "mm["<<i << "]=" << mm[i] << std::endl; }


	// change some value
	trace("mm.assign(6,7, 'X');");	mm.assign(6,7, 'X');
	
	for(int i=0; i<10; i++){ std::cout << "mm["<<i << "]=" << mm[i] << std::endl; }
  
	return 0;
}

