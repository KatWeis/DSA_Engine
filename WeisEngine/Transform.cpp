#include "Transform.h"



Transform::Transform()
{
	location = vec3(0, 0, 0);//set default location to center of the world
	rotation = vec3(0, 0, 0);//set default rotation at start to zero
	scale = vec3(1, 1, 1);//set starting scale to 1
}

Transform::Transform(float x, float y, float z)
{
	location = vec3(x, y, z);//set location to the floats being passed in
	rotation = vec3(0, 0, 0);//set default rotation at start to zero
	scale = vec3(1, 1, 1);//set starting scale to 1
}


Transform::~Transform()
{
}

void Transform::CalcTransMatrix()
{
	//translate * rotate * scale -- calculate the model to world matrix
	modelWorld = glm::translate(location) * glm::yawPitchRoll(rotation.y, rotation.x, rotation.z) * glm::scale(scale);

	//upload the matrix
	glUniformMatrix4fv(11, 1, GL_FALSE, &modelWorld[0][0]);
}
