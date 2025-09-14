#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <map>
#include <vector>
#include <string>

// Assignment sent by Candy Stanley on 08/01/2010

//Follow object oriented programming Concepts & Design Patterns to implement a C++ program that can be used to store a Diagram and load a Diagram. The Diagram will be made up of Shapes.  Shapes include a Circle with radius R and a Square with side A.  
//Requirements
//In-scope:
//•	The program must preserve the position, colour and orientation of the shapes in the diagram - therefore such information must be stored in a file.
//•	The file may be located anywhere, it is expected that the store/load method is passed a string variable containing the path of the file.
//•	Use of Boost/StdLib/Templates is optional
//Out of scope:
//•	Support for removal of shapes from the diagram
//•	User-interactivity is not required (i.e. no need to render diagram)
//Example for file processing:
//#include <iostream>
//ofstream file1(FileName, ios::out);
//ifstream file2(FileName);



class Shape
{

public:
	//get/set radius/side
	void setA(float a)	{A = a;}
	float getA()	{return A;}

	//get/set ID
	void setId(std::string& ID){id = ID;}
	std::string getId(){return id;}

	//get/set position
	void setPosition(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	void getPosition(float& x, float& y)
	{
		x = this->x;
		y = this->y;
	}

	//set/get colour
	void setColour(unsigned char red, unsigned char green, unsigned char blue)
	{
		this->red	= red;
		this->green	= green;
		this->blue	= blue;
	}
	void getColour(unsigned char& red, unsigned char& green, unsigned char& blue)
	{
		red		= this->red;
		green	= this->green;
		blue	= this->blue;
	}

	//set/get orientation
	void setOrientation(float tilt)
	{
		this->tilt	= tilt;
	}
	float getOrientation()
	{
		return tilt;
	}

	bool operator<(const Shape& shape){return shape.A < A;}


protected:
	std::string id;	//shape object id
	float A;	//circle radius or square side

	//position
	float x;
	float y;

	//colour (RGB)
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;

	//orientation
	float tilt;	//tilt angle

private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		//id
		ar & id;

		//radius/side
		ar & A;

		//position
		ar & x;
		ar & y;

		//colour (RGB)
		ar & red;
		ar & green;
		ar & blue;

		//orientation
		ar & tilt;
	}
};


class Circle : public Shape
{
public:
	Circle(float radius, std::string ID)
	{
		A = radius;
		id = ID;
	}
	~Circle(){}

	void Draw()
	{
	}


protected:

private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Shape>(*this);
	}

};

class Square : public Shape
{
public:
	Square(float side, std::string ID)
	{
		A = side;
		id = ID;
	}
	~Square(){}

	void Draw()
	{
	}


protected:
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Shape>(*this);
	}

};


class Diagram
{
public:
	void addShape(Shape& shape)
	{
		shapes[shape.getId()] = shape;
	}

	void delShape(std::string id)
	{
		shapes.erase(id);
	}

	void store(std::string path)
	{
		std::ofstream ofs(path.c_str());
		boost::archive::text_oarchive ar(ofs);
		serialize(ar, 1);
		//ar & shapes;
		//ar & *this;
	}

	void load(std::string path)
	{
		std::ifstream ifs(path.c_str());
		boost::archive::text_iarchive ar(ifs);
		serialize(ar, 1);
		//ar & shapes;
		//ar & *this;
	}

	void printShapes()
	{
		std::cout << "No of shapes=" << shapes.size() << std::endl;
		std::map<std::string, Shape>::iterator itr = shapes.begin();
		while(itr != shapes.end())
		{
			float x, y;
			unsigned char R, G, B;
			itr->second.getPosition(x, y);
			itr->second.getColour(R, G, B);
			
			std::cout << "Id=" << itr->second.getId() << " radius/side=" << itr->second.getA()
				<< " Position=" << x << "," << y
				<< " Colour(RGB)=" << R << "," << G << "," << B
				<< " Orientation=" << itr->second.getOrientation()
				<< std::endl;
			++itr;
		}
	}


protected:
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & shapes;
	}
	std::map<std::string, Shape> shapes;	

};


void main_Candy()
{
	std::cout << "main_Candy" << std::endl;

	Diagram dg;
	dg.printShapes();

	//add shapes
	Circle c1(12.5f, "c1");	c1.setPosition(1.1f, 2.2f);	c1.setColour(10, 110, 210);	c1.setOrientation(00);
	Circle c2(15.6f, "c2");	c2.setPosition(3.3f, 4.4f);	c2.setColour(20, 120, 220);	c2.setOrientation(90);
	Square s1(58.4f, "s1");	s1.setPosition(5.5f, 6.6f);	s1.setColour(30, 130, 230);	s1.setOrientation(180);
	Square s2(25.8f, "s2");	s2.setPosition(7.7f, 8.9f);	s2.setColour(40, 140, 240);	s2.setOrientation(270);
	dg.addShape(c1);
	dg.addShape(c2);
	dg.addShape(s1);
	dg.addShape(s2);
	dg.printShapes();

	//Storing
	std::cout << "\nStoring(serializing) Diagram object" << std::endl;
	dg.store("F:/Candy.txt");


	//Loading
	std::cout << "\nLoadin(deserializing) another Diagram object" << std::endl;
	Diagram dg2;
	dg2.load("F:/Candy.txt");
	dg2.printShapes();
}
