#include <cassert>

#include "Include/Texture.h"
#include "SOIL/SOIL/soil.h"

NaiveZ3D::Texture::Texture(const std::string & name)
{
	glGenTextures(1, &mTex_);
	glBindTexture(GL_TEXTURE_2D, mTex_);

	unsigned char* image = SOIL_load_image(name.c_str(), &mWidth_, &mHeight_, 0, SOIL_LOAD_RGB);
	assert(image);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth_, mHeight_, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);

	glBindTexture(GL_TEXTURE_2D, 0);
}

NaiveZ3D::Texture::~Texture()
{
	if (glIsTexture(mTex_))
	{
		glDeleteBuffers(1, &mTex_);
	}
}
