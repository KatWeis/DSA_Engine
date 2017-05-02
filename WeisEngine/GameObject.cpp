#include "GameObject.h"


GameObject::GameObject()
{
	transform = Transform();//start with default transform
	textFilename = "textures/TestTexture.png";
	modelFilename = "models/box.obj";
}

GameObject::GameObject(float x, float y, float z)
{
	transform = Transform(x, y, z);//start with given transform
	textFilename = "textures/TestTexture.png"; //default texture
	modelFilename = "models/box.obj";//default model
}

GameObject::GameObject(float x, float y, float z, char * text)
{
	transform = Transform(x, y, z);//start with given transform
	textFilename = text; //texture filepath that is being passed in
	modelFilename = "models/box.obj";//default model
}

GameObject::GameObject(float x, float y, float z, string mod)
{
	transform = Transform(x, y, z);//start with given transform
	textFilename = "textures/TestTexture.png"; //default texture
	modelFilename = mod;//the model filepath being passed in
}

GameObject::GameObject(float x, float y, float z, char* text, string mod)
{
	transform = Transform(x, y, z);//start with given transform
	transform.rotation.y = -1;
	transform.scale = vec3(.01f, .01f, .01f);
	textFilename = text;//have a texture with the given filepath
	modelFilename = mod;//use the model with the given filepath
}


GameObject::~GameObject()
{

}

void GameObject::render()
{
	//use the correct texture that is on the object
	image.use();

	//calculate the transform matrix for each object
	transform.CalcTransMatrix();

	//render game objects
	model.render();
}

void GameObject::update()
{
}
