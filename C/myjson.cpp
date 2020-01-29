// g++ -g -w myjson.cpp -o json --std=c++17 -lpthread

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <chrono>
#include <any>
#include "/d/Projects/chohan-common/C/json.hpp"
using json = nlohmann::json;
#define trace(str)(std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << "(): " << str << std::endl)

struct person{
	std::string name;
	std::string address;
	int age;

	json toJson(){
		json j;
		j["name"] = name;
		j["address"] = address;
		j["age"] = age;
		return j;	
	}

	void fromJson(json j){
		name = j["name"].get<std::string>();
		address = j["address"].get<std::string>();
		age = j["age"].get<int>();
	}

	json toJson2(){
		json j;
		j.push_back(name);
		j[1] = address;
		j.push_back(age);
		return j;
	}

	void fromJson2(json j){
		name = j[0].get<std::string>();
		address = j[1].get<std::string>();
		age = j[2].get<int>();
	}

	std::any get(std::string key){
		if(memcmp(key.c_str(), "name", strlen("name")) == 0) return std::any(name);
		if(memcmp(key.c_str(), "address", strlen("address"))==0) return std::any(address);
		if(memcmp(key.c_str(), "age", strlen("age")) == 0) return std::any(age);
	}
};

int main(int argc, char** argv)
{
	std::cout << "Bismillah\n";

	person p = {"Salah Chohan", "5090 Fairview St", 55};
	json j;
	j["name"] = p.name;
	j["address"] = p.address;
	j["age"] = p.age;

	std::string jstr = j.dump();
	std::cout << "json=" << jstr << std::endl;

	json j2(jstr);
	std::cout << "json2=" << j2.dump() << std::endl;

	json j3 = json::parse(jstr);
	std::cout << "json=" << j3.dump() << std::endl;

	person p1;
	p1.fromJson(j3);
	auto j4 = p1.toJson();
	std::cout << "p1.json=" << j4.dump() << std::endl;

	json j5 = p.toJson2();
	std::string sj5 = j5.dump();
	std::cout << "toJson2=" << sj5 << std::endl;

	json j6 = json::parse(sj5);
	person p6;
	p6.fromJson2(j6);
	std::cout << "toJson2=" << p6.toJson2().dump() << std::endl;

	std::any a = p6.get("age");
trace("");
	std::cout << "name=" << std::any_cast<std::string>(p6.get("name"))
		<< ", address="    << std::any_cast<std::string>(p6.get("address"))
		<< ", age=" << std::any_cast<int>(p6.get("age"))  
		<< std::endl;
{
struct Person
{
	int age;
	float rate;
//	std::string Name;
};

class Msg
{
public:
	Msg(){}
	virtual ~Msg()
	{trace("");
		if(data_size>0)
			free(data);
		trace("");
	}

	void serialize(char* buffer)
	{
		memcpy(buffer, this, sizeof(Msg));
		memcpy(buffer+sizeof(Msg), data, data_size);
	}
	void deserialize(char* buffer)
	{
		memcpy(this, buffer, sizeof(Msg));
		data = malloc(data_size);
		memcpy(data, buffer+sizeof(Msg), data_size);
	}

	unsigned int Start = 0xAAAA;
	unsigned int Length = 20;
	char Type = 'A';
	int data_size=0;
	void* data=0;
};

Person p1 = {55, 4.5};
Msg msg;
msg.data = malloc(sizeof(Person));
msg.data_size = sizeof(Person);
memcpy(msg.data, &p1, sizeof(p1));
char* buf = (char*)malloc(sizeof(Msg) +  msg.data_size);
int buf_size=0;
msg.serialize(buf);

Msg msg2;
msg2.deserialize(buf);
Person p2;
memcpy(&p2, msg2.data, sizeof(p2));
free(buf);
std::cout << "sizeof(Person)="<<sizeof(Person) << ", sizeof(p1)="<<sizeof(p1) << ", sizeof(p2)="<<sizeof(p2)\
	<< ", sizeof(std::string)="<< sizeof(std::string) << std::endl;
std::cout << "age=" << p2.age << ", rate="<<p2.rate << std::endl;
trace("");
}
 






	return true;
}
