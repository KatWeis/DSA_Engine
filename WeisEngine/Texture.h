#pragma once
#include <string>

#include <FreeImage.h>

#include <GL\glew.h>    //order matters
#include <GLFW\glfw3.h>

using namespace std;

class Texture
{
protected:
	//fields
	GLuint textID;
	string texture;	

public:
	Texture();
	Texture(string filename);//parameterized constructor taking in the file name of the texture
	~Texture();

	//methods
	virtual bool load(char* filename);
	virtual void use();
	void unload();
};

