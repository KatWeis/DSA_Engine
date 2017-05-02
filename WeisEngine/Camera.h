#pragma once
#include <GL\glew.h>    //order matters
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

class Camera
{
private:
	//fields
	glm::mat4 worldView;//matrix for world view
	glm::mat3 rotMat;//matrix for rotation
	glm::vec3 velocity; //vector 3 for the velocity of the camera
	glm::vec3 location; //vector 3 for the camera's location
	glm::vec3 rot; //vector 3 for the camera's rotation
	float speed = 1;
	float sensitivity = .01f;//determines how touchy the camera controls are
	double x, y;//x and y location of camera

	//perspective fields
	float zoom = 1.f;//zoom of the camera
	int width = 800;//aspect ratio x
	int height = 600;//aspect ratio y
	float fovy = 3.14159f * .4f / zoom;//field of view in the y direction
	float aspect = (float)width / (float)height;//aspect ratio
	float zNear = .01f;
	float zFar = 1000.f;

	//perspective matrix
	glm::mat4 perspectiveMat = glm::perspective(fovy, aspect, zNear, zFar);

	//methods
	void upload();//set the uniform of the matrix
	void move();
	void turn();

public:
	Camera();//default constructor
	~Camera();//default destructor

	//methods
	void update();
	void start();//set world view matrix as the identity matrix

	//properties
	glm::vec3 getLocation();
	glm::mat4 getSkyView();//gets the worldview matrix when the camera is at (0,0,0)
};

