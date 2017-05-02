#define _USE_MATH_DEFINES

#include "Camera.h"
//include the engine's header
#include "Engine.h"
#include <math.h>

using glm::normalize;

Camera::Camera()
{
}

Camera::~Camera()
{

}

//set the uniform of the matrix
void Camera::upload()
{
	//world view matrix = projection matrix * look at matrix
	worldView = perspectiveMat * glm::lookAt(location, location+rotMat*glm::vec3(0, 0, -1), rotMat * glm::vec3(0, 1, 0));
	glUniformMatrix4fv(5, 1, GL_FALSE, &worldView[0][0]);
}

//moves the rigidbody of the camera around
void Camera::move()
{
	glm::vec3 dir;

	//adjust camera position based on keyboard input
	if (glfwGetKey(Engine::window, GLFW_KEY_UP))
	{
		dir.z -= 1;
	}
	if (glfwGetKey(Engine::window, GLFW_KEY_DOWN))
	{
		dir.z += 1;
	}
	if (glfwGetKey(Engine::window, GLFW_KEY_LEFT))
	{
		dir.x -= 1;
	}
	if (glfwGetKey(Engine::window, GLFW_KEY_RIGHT))
	{
		dir.x += 1;
	}

	//check that the direction is not zero
	if (dir != glm::vec3()) dir = normalize(dir);//then normalize the direction vector

	//make velocity have a forward vector of the direction
	velocity = rotMat*dir*speed;

	//add velocity to the location
	location += Engine::timer.dt * velocity;
}

//rotate the rigidbody of the camera
void Camera::turn()
{
	//get the size of the window and store it in temp variables
	glfwGetWindowSize(Engine::window, &width, &height);

	//get the location of the cursor and store it in temp variables
	glfwGetCursorPos(Engine::window, &x, &y);

	//set the rotation of the camera based on mouse position
	rot.y -= (float)(sensitivity * (x - width/2));//yaw
	rot.x -= (float)(sensitivity * (y - height/2));//pitch

	//clamp the x rotation at 90 degrees
	x = glm::clamp(rot.x, (float)-M_PI / 2, (float)M_PI / 2);

	//set the cursor to the center
	glfwSetCursorPos(Engine::window, width/2, height/2);

	//set the rotation matrix
	rotMat = glm::mat3(glm::yawPitchRoll(rot.y, rot.x, rot.z));
}

//update the camera
void Camera::update()
{
	//put actual update logic/math here
	turn();//rotate the camera based on mouse pos
	move();//move the camera based on keyboard input

	upload();
}

//set world view matrix as the identity matrix
void Camera::start()
{
	worldView = glm::mat4();
	location = { 0,0,0 };
	rot = { 0, 0, 0 };
	glfwSetCursorPos(Engine::window, width / 2, height / 2);

}

glm::vec3 Camera::getLocation()
{
	return location;
}

glm::mat4 Camera::getSkyView()
{
	return perspectiveMat * glm::lookAt(vec3(0,0,0), vec3(0, 0, 0) + rotMat*glm::vec3(0, 0, -1), rotMat * glm::vec3(0, 1, 0));
}
