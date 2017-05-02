#pragma once
#include <GL\glew.h>    //order matters
#include <GLFW\glfw3.h>
#include <string>
#include "FileIO.h"

class Shader
{
public:
	Shader();//default constructor
	~Shader();//destructor

	//fields
	GLuint program, vprogram, fprogram, skyv, skyf, skyprog;//GLuint stands for open gl unsigned int
	std::string filenamev = "shaders/vshader.glsl";
	std::string filenamef = "shaders/fshader.glsl";
	std::string filenameskyv = "shaders/vsky.glsl";
	std::string filenameskyf = "shaders/fsky.glsl";

	//methods

	//deallocate the shaders off the graphics card
	bool load(bool sky);

	//helper-method used by load to read and compile a shader file and save the index
	bool compile(GLenum shaderType, bool sky);

	//uses shaders
	void use();

	//uses shaders
	void useSky();

	//deallocate the shaders off the graphics card
	void unload();
	
};

