#pragma once
#include "GameObject.h"
#include "CubeMap.h"

class Skybox: public GameObject
{
public:
	//fields
	CubeMap cubemap;
	mat4 worldView;

	Skybox();
	~Skybox();

	//methods
	void render() override;//renders the object to the screen with the correct texture and model
	void update() override;//updates the objects logic every frame
};

