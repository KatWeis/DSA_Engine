#include "Shader.h"
#include <fstream>
#include <iostream>

//default constructor
Shader::Shader()
{
}

//default destructor
Shader::~Shader()
{
}

//deallocate the shaders off the graphics card
//loads shaders
bool Shader::load(bool sky)
{
	GLuint tempProg;
	GLuint tempf;
	GLuint tempv;
	//will set value of programs to 0 if it fails
	
	//compile the vertex and fragment shaders
	if (compile(GL_VERTEX_SHADER, sky) == false || compile(GL_FRAGMENT_SHADER, sky) == false)
	{
		return false;
	}

	if (sky == true)
	{
		tempProg = skyprog;
		tempf = skyf;
		tempv = skyv;
	}
	else
	{
		tempProg = program;
		tempf = fprogram;
		tempv = vprogram;
	}

	//create shader
	tempProg = glCreateProgram();
	//attach the shaders
	glAttachShader(tempProg, tempv);
	glAttachShader(tempProg, tempf);
	//link the program
	glLinkProgram(tempProg);

	//determine if the program linked correctly
	GLint linkResult;
	glGetProgramiv(tempProg, GL_LINK_STATUS, &linkResult);

	if (linkResult != 0)
	{
		if (sky == true)
		{
			skyprog = tempProg;
			skyf = tempf;
			skyv = tempv;
		}
		else
		{
			program = tempProg;
			fprogram = tempf;
			vprogram = tempv;
		}

		return true;
	}

	// if it didn't link correctly print out the info log
	//start by getting the length of the log
	GLint logLength;
	glGetProgramiv(tempProg, GL_INFO_LOG_LENGTH, &logLength);

	//then get the actual log
	GLchar* log = new GLchar[logLength + 1];
	glGetProgramInfoLog(tempProg, logLength, 0, log);
	//print out the log
	std::cout << log << std::endl;

	//delete the program
	glDeleteProgram(tempProg);
	delete[] log;
	return false;
}

//helper-method used by load to read and compile a shader file and save the index
bool Shader::compile(GLenum shaderType, bool sky)
{
	char* source = nullptr;
	GLuint tempProg;

	if (shaderType == GL_VERTEX_SHADER && sky == true)
	{
		//read in the content of the shader file based on the type passed in
		source = FileIO::readBinaryFile(filenameskyv);

		//set temp variable to vprogram
		tempProg = skyv;
	}
	else if (shaderType == GL_VERTEX_SHADER && sky == false)
	{
		//read in the content of the shader file based on the type passed in
		source = FileIO::readBinaryFile(filenamev);

		//set temp variable to fprogram
		tempProg = vprogram;
	}
	else if (shaderType == GL_FRAGMENT_SHADER && sky == true)
	{
		//read in the content of the shader file based on the type passed in
		source = FileIO::readBinaryFile(filenameskyf);

		//set temp variable to fprogram
		tempProg = skyf;
	}
	else
	{
		//read in the content of the shader file based on the type passed in
		source = FileIO::readBinaryFile(filenamef);

		//set temp variable to fprogram
		tempProg = fprogram;
	}

	//check that they read in correctly
	if (source == nullptr)
	{
		//print error message
		std::cout << "File was not loaded successfully \n" << std::endl;
		return 0;
	}

	//call create shader and save the index it returns
	tempProg = glCreateShader(shaderType);

	//call shader source
	glShaderSource(tempProg, 1, &source, 0);

	//delete the char array
	delete[] source;

	//call compile shader
	glCompileShader(tempProg);

	//check that it compiled
	GLint compileResult;
	glGetShaderiv(tempProg, GL_COMPILE_STATUS, &compileResult);

	if (compileResult != 0)
	{
		if (shaderType == GL_VERTEX_SHADER && sky == true)
		{
			//set temp variable to vprogram
			skyv = tempProg;
		}
		else if (shaderType == GL_VERTEX_SHADER && sky == false)
		{
			//set temp variable to vprogram
			vprogram = tempProg;
		}
		else if (shaderType == GL_FRAGMENT_SHADER && sky == true)
		{
			//set temp variable to vprogram
			skyf = tempProg;
		}
		else
		{
			//set temp variable to fprogram
			fprogram = tempProg;
		}
		return true;
	}

	// if it didn't compile correctly print out the info log
	//start by getting the length of the log
	GLint logLength;
	glGetShaderiv(tempProg, GL_INFO_LOG_LENGTH, &logLength);

	//then get the actual log
	GLchar* log = new GLchar[logLength + 1];
	glGetShaderInfoLog(tempProg, logLength, 0, log);
	//print out the log
	std::cout << log << std::endl;

	//delete the shader
	glDeleteShader(tempProg);
	delete[] log;
	return false;
}

//uses shaders
void Shader::use()
{
	glUseProgram(program);//function wrapper, encapsulation
}

//uses shader for the skybox
void Shader::useSky()
{
	glUseProgram(skyprog);//function wrapper, encapsulation
}

//deallocate the shaders off the graphics card
void Shader::unload()
{
	//delete programs
	glDeleteProgram(program);
	glDeleteProgram(vprogram);
	glDeleteProgram(fprogram);

	glDeleteProgram(skyprog);
	glDeleteProgram(skyv);
	glDeleteProgram(skyf);

	//set all ints to 0
	program = 0;
	vprogram = 0;
	fprogram = 0;

	skyprog = 0;
	skyv = 0;
	skyf = 0;
}
