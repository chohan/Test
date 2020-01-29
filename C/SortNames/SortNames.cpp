// SortNames.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	if(argc<3)
	{
		cout << "Usage: SortNames.exe 10 input.txt output.txt" << endl;
		return 1;
	}

	int maxnames = 0;
	string fileInput;
	string fileOutput;
	maxnames	= atoi(argv[1]);
	fileInput	= argv[2];
	fileOutput	= argv[3];

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


	return 0;
}


