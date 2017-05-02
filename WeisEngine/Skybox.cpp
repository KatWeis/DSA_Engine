#include "Skybox.h"


Skybox::Skybox()
{
	modelFilename = "models/box.obj";
	//set up skybox
	transform = Transform(0, 0, 0);
	transform.scale = vec3(100, 100, 100);
}


Skybox::~Skybox()
{
}

void Skybox::render()
{
	glDisable(GL_CULL_FACE);

	//upload world view matrix
	glUniformMatrix4fv(5, 1, GL_FALSE, &worldView[0][0]);

	cubemap.use();

	model.render();

	glEnable(GL_CULL_FACE);
}

void Skybox::update()
{
}
