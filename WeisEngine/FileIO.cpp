#include "FileIO.h"



FileIO::FileIO()
{
}


FileIO::~FileIO()
{
}

char * FileIO::readBinaryFile(std::string filename)
{
	//open
	std::ifstream instream(filename, std::ios::binary);//opens file, extra parameter allows it to open as a binary file
	if (!instream.is_open()) return nullptr;

	//get length
	instream.seekg(0, std::ios::end); //go to the end of file //first parameter is the offset of where to start
	int length = (int)instream.tellg(); //how long is the file
	instream.seekg(0, std::ios::beg); //go back to the beginning

									  //read entire file
	char* bytes = new char[length + 1]; //allocate memory for contents
	bytes[length] = '\0'; //add null terminator
	instream.read(bytes, length); //read to where, how many bytes

	//close it
	instream.close();//destructor closes it after function exits if you forget

	return bytes;
}

char * FileIO::readTextFile(std::string filename)
{
	//open
	std::ifstream instream(filename);//opens file
	if (!instream.is_open()) return nullptr;

	//get length
	instream.seekg(0, std::ios::end); //go to the end of file //first parameter is the offset of where to start
	int length = (int)instream.tellg(); //how long is the file
	instream.seekg(0, std::ios::beg); //go back to the beginning

	//read entire file
	char* bytes = new char[length + 1]; //allocate memory for contents
	bytes[length] = '\0'; //add null terminator
	instream.read(bytes, length); //read to where, how many bytes

	//close it
	instream.close();//destructor closes it after function exits if you forget

	return bytes;
}
