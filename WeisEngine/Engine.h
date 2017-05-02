#pragma once
//header files
#include "Timer.h"
#include "Camera.h"
#include "Shader.h"
#include "Model.h"
#include "Texture.h"
#include "GameObject.h"
#include "Skybox.h"
#include <map>
#include <vector>

//include w/ " " : it's in project dir (we probably wrote it)
//#include "Include\FreeImage.h"

//include w/ <> : it's in installed library directories (we didn't write it)
#include <FreeImage.h>

#include <GL\glew.h>    //order matters
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

class Engine
{
private:
	static Shader sh;
	static Camera cam;
	static Model sphere;
	static Texture textTest;
	static Skybox skybox;

	//fields
	static bool wireframe;

	//list of models necesary to load
	static vector<Model> models;

	//methods
	static bool initWin();//initialize the window
	static bool bufferModels(); //setup everything so that a quad can be drawn
	static bool loadTextures();//load all textures created in the engine
public:
	static Timer timer;
	static GLFWwindow* window;
	static std::map<int, bool> keyIsDown;
	static std::map<int, bool> keyWasDown;
	static vector<GameObject> objects;

	static bool start();//starts running the game engine
	static void stop();//stops running the game engine
	static void update();//updates the game engine
};

