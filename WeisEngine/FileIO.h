#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class FileIO
{
public:
	FileIO();
	~FileIO();

	//methods
	static char* readBinaryFile(std::string filename);//reads in a file as binary
	static char* readTextFile(std::string filename);//reads in a file as text
};

