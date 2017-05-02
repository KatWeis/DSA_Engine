#include "Engine.h"
#include <stdlib.h>

std::map<int, bool> Engine::keyIsDown;
std::map<int, bool> Engine::keyWasDown;

//anonymous namespace for holding methods for input (keyboard and mouse)
namespace
{
	//define and set click function
	void mouseClick(GLFWwindow* windowPtr, int button, int action, int mods)
	{
		Engine::keyIsDown[button] = action;
	}

	//define and set keypress function
	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Engine::keyIsDown[key] = action;
	}
}

Timer Engine::timer;
Shader Engine::sh;
Camera Engine::cam;
Model Engine::sphere;
Texture Engine::textTest;
Skybox Engine::skybox;
bool Engine::wireframe;
vector<GameObject> Engine::objects;
vector<Model> Engine::models;

//initialize the open gl window
bool Engine::initWin()
{
	//proves that all the external files were loaded correctly
	if (glfwInit() == GL_FALSE)
	{
		return false;
	}

	//initialize the window library

	//create a windowed mode window and save its address to a pointer
	Engine::window = glfwCreateWindow(800, 600, "Weis DSA1 Engine", NULL, NULL);

	//make it the currently active window, or quit
	if (Engine::window != nullptr)
	{
		glfwMakeContextCurrent(Engine::window);
	}
	else
	{
		glfwTerminate();
		return false;
	}

	//Initialize GLEW or quit
	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return false;
	}
	return true;
}

//buffer the models
bool Engine::bufferModels()
{
	//buffer all the gameobjects
	for(int i = 0; i < objects.size(); i++)
	{
		if (objects[i].model.buffer(objects[i].modelFilename) == false)
		{
			return false;
		}
	}
	//buffer the skybox model
	if (skybox.model.buffer(skybox.modelFilename) == false)
	{
		return false;
	}
	return true;
}

bool Engine::loadTextures()
{

	//load in each texture applied to the objects in the program
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i].image.load(objects[i].textFilename) == false)
		{
			return false;
		}
	}
	//load in the skybox's cubemap
	if (skybox.cubemap.load("") == false)
	{
		return false;
	}
	return true;
}

//starts the engine
bool Engine::start()
{
	//initialize the window
	if (!Engine::initWin()) return false;

	glEnable(GL_DEPTH_TEST);

	//set the click function when loading the game
	glfwSetMouseButtonCallback(Engine::window, mouseClick);

	//set the keypress function when loading game
	glfwSetKeyCallback(Engine::window, keyCallback);

	//start the camera
	cam.start();

	//load the skybox shader before the game loop
	if (sh.load(true))
	{
		//if it loads correctly, use the shader
		sh.useSky();
	}
	//load the shader before the game loop
	if (sh.load(false))
	{
		//if it loads correctly, use the shader
		sh.use();
	}

	//setup to draw the quad
	if (bufferModels() == false)
	{
		return false;
	}

	//setup to draw the quad
	if (loadTextures() == false)
	{
		return false;
	}

	//change the background color of the window --set it once -- aets color when we clear the screen --- color values are btw 0 and 1 rgba
	glClearColor(.392f, .584f, .929f, 1.0f); //cornflower blue

	//set the stength of the ambient lighting
	glUniform1f(8, .25f);

	//set the stength of the specular lighting
	glUniform1f(9, .5f);

	//set the location of the light
	glUniform3f(6, 15, 15, 0);

	//set wireframing to false
	wireframe = false;

	return true;
}

//closes and terminates everything so that there are no memory leaks
void Engine::stop()
{
	sh.unload();//unload the shaders
	for (int i = 0; i < objects.size(); i++)//unload the textures
	{
		objects[i].image.unload();
	}
	glfwTerminate();//must be called before engine is closed or there will be memory leaks
}

//update the engine
void Engine::update()
{
	//update the timer
	timer.update();

	//clear the console
	//system("cls");//////////////////////////////////////////////

	//update the time uniform in the shader
	glUniform1f(4, Engine::timer.t);

	//update the camera position in the shader
	glUniform3f(7, cam.getLocation().x, cam.getLocation().y, cam.getLocation().z);

	//update and upload the camera matrix to the shader
	cam.update();

	//update physical simulation

	//draw buffered models
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//clear canvas --- passes in buffers as paramaters

	//use the correct shader for the skybox
	sh.useSky();

	//send info of cameras matrix to the skybox
	skybox.worldView = cam.getSkyView();

	//render the skybox
	skybox.render();

	glClear(GL_DEPTH_BUFFER_BIT);//clear canvas --- passes in buffers as paramaters

	//switch back to normal shader
	sh.use();

	//render each object to the screen
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i].render();
	}

	glBindVertexArray(0);
	//unbind an object after drawing it

	//swap the front (what the screen displays) and back (what OpenGL draws to) buffers --- the screen cannot read from the buffer as the graphics card writes to it, so you have to swap it
	glfwSwapBuffers(Engine::window);

	//process input/window events
	Engine::keyWasDown = Engine::keyIsDown;
	glfwPollEvents(); //process queued window, mouse & keyboard callback events

	//if user presses esc, exit the gameloop
	if (keyIsDown[GLFW_KEY_ESCAPE])
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	//toggle wireframe
	if (keyIsDown[GLFW_KEY_TAB] && !keyWasDown[GLFW_KEY_TAB])
	{
		wireframe = !wireframe;
	}

	//determine whether to draw in wireframe or not
	if (wireframe == true)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}


