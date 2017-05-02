#pragma once
#include "Texture.h"

class CubeMap: public Texture
{
public:
	CubeMap();
	~CubeMap();

	//methods
	bool load(char* filename) override;
	void use() override;
};

