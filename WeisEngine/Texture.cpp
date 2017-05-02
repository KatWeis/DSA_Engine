#include "Texture.h"


//allocate space for the texture on the graphics card
void Texture::use()
{
	glBindTexture(GL_TEXTURE_2D, textID);
}

//delete the texture off the graphics card
void Texture::unload()
{
	glDeleteTextures(1, &textID);
}

bool Texture::load(char* filename)
{
	//load the texture using free image
	FIBITMAP* image = FreeImage_Load(FreeImage_GetFileType(filename, 0), filename);
	//make sure that it worked
	if (image == nullptr) return false;

	//convert the original texture to a 32bit bmp
	FIBITMAP* image32Bit = FreeImage_ConvertTo32Bits(image);

	//unload the original image from memory
	FreeImage_Unload(image);

	//generate and bind a new texture
	glGenTextures(1, &textID);
	glBindTexture(GL_TEXTURE_2D, textID);
	
	//get info on the image
	GLuint width = FreeImage_GetWidth(image32Bit);
	GLuint height = FreeImage_GetHeight(image32Bit);
	BYTE* address = FreeImage_GetBits(image32Bit);

	//upload the texture bytes
	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)address);

	//set min filter to linear instead of mipmap linear
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//clear the texture from the RAM
	FreeImage_Unload(image32Bit);

	//unbind the texture once it is done loading
	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}

//public default constructor
Texture::Texture()
{

}

//parameterized constructor taking in the file name of the texture
Texture::Texture(string filename)
{
	texture = filename;
}

//public default destructor
Texture::~Texture()
{

}
