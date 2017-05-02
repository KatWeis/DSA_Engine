#pragma once
#include "Texture.h"
#include"Transform.h"
#include "Model.h"

class GameObject
{
public:
	//fields
	Transform transform;
	Model model;
	Texture image;
	char* textFilename;
	string modelFilename;

	GameObject();
	GameObject(float x, float y, float z);//parameterized constructor that takes in the position
	GameObject(float x, float y, float z, char* text);//parameterized constructor that takes in the position and the texture of the object
	GameObject(float x, float y, float z, string mod);//parameterized constructor that takes in the position and the model of the object
	GameObject(float x, float y, float z, char* text, string mod);//parameterized constructor that takes in the position, the texture, and the model of an object
	~GameObject();

	//methods
	virtual void render();//renders the object to the screen with the correct texture and model
	virtual void update();//updates the objects logic every frame
};

