#pragma once
#include <GL\glew.h>

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

using namespace glm;

class Transform
{
public:
	vec3 location;
	vec3 rotation;
	vec3 scale;
	mat4 modelWorld;

	Transform();
	Transform(float x, float y, float z);
	~Transform();

	//methods
	void CalcTransMatrix();//calculate the transform matrix
};

