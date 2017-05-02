#include <iostream>
#include <vector>
#include "Engine.h"

//include w/ " " : it's in project dir (we probably wrote it)
//#include "Include\FreeImage.h"

//include w/ <> : it's in installed library directories (we didn't write it)
#include <FreeImage.h>

#include <GL\glew.h>    //order matters
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>


//declare static window pointer
GLFWwindow* Engine::window;


int main()
{
	GameObject obj1(0, 0, 0);
	GameObject obj2(1, 2, 1, "textures/ship_main_bright.png", "models/GummiShip.obj");

	//add objects to the game loop
	Engine::objects.push_back(obj1);
	Engine::objects.push_back(obj2);

	//end the program if starting the engine doesn't work
	if(!Engine::start()) return -1;

	//set up a game loop
	while (!glfwWindowShouldClose(Engine::window))
	{
		Engine::update();
	}
	Engine::stop(); //stop the engine
	return 0;
}