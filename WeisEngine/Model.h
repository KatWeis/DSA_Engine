#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

#include <GL\glew.h>    //order matters
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

//helps keep track of data for the 3d models
struct Vertex
{
	glm::vec3 location;//the location of this vertex in space -- between -1 and 1
	glm::vec2 uv;//the texture vertex -- between 0 and 1
	glm::vec3 normal;//the normal vector to this vertex -- perpindicular to the vertex
};

//indexes
struct VertInd
{
	unsigned int locInd, uvInd, normInd;
};

class Model
{
private:
	unsigned int vertCount;
	GLuint vertArr;

public:
	Model();//default constructor
	~Model();//default destructor

	//methods
	bool buffer(std::string objFile);//buffer and setup the model
	void render();//draws the model to the screen
};

