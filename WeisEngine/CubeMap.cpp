#include "CubeMap.h"



CubeMap::CubeMap()
{
}


CubeMap::~CubeMap()
{
}

bool CubeMap::load(char * filename)
{
	//allocate space on graphics card for one texture and give us its id
	glGenTextures(1, &textID);

	//bind the new texture to the cubemap binding point
	glBindTexture(GL_TEXTURE_CUBE_MAP, textID);

	//iterate through the skybox's 6 sides
	for (int i = 0; i < 6; i++)
	{
		char* f = "";

		switch (i)
		{
			case 0: f = "textures/blue/right1.png";
				break;
			case 1: f = "textures/blue/left1.png";
				break;
			case 2: f = "textures/blue/top1.png";
				break;
			case 3: f = "textures/blue/bottom1.png";
				break;
			case 4: f = "textures/blue/front1.png";
				break;
			case 5: f = "textures/blue/back1.png";
				break;
		}

		//load the texture using free image
		FIBITMAP* image = FreeImage_Load(FreeImage_GetFileType(f, 0), f);
		//make sure that it worked
		if (image == nullptr) return false;

		//convert the original texture to a 32bit bmp
		FIBITMAP* image32Bit = FreeImage_ConvertTo32Bits(image);

		//unload the original image from memory
		FreeImage_Unload(image);

		FreeImage_FlipVertical(image32Bit);

		//generate and bind a new texture
		glGenTextures(1, &textID);
		glBindTexture(GL_TEXTURE_2D, textID);

		//get info on the image
		GLuint width = FreeImage_GetWidth(image32Bit);
		GLuint height = FreeImage_GetHeight(image32Bit);
		BYTE* address = FreeImage_GetBits(image32Bit);

		//upload the texture bytes
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_SRGB_ALPHA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)address);

		//set texture parameters to prevent seams from being visible between textures
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		//clear the texture from the RAM
		FreeImage_Unload(image32Bit);

		//unbind the texture once it is done loading
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	return true;
}

void CubeMap::use()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, textID);
}
