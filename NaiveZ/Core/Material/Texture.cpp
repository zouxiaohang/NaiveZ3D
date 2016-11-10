#include <cassert>
#include <tuple>
using namespace std;

#include "Include/Texture.h"
#include "SOIL/SOIL/soil.h"
#include "Include/MaterialMgr.h"

NaiveZ3D::Texture::Texture(const std::string & name)
{
	glGenTextures(1, &mTex_);
	glBindTexture(GL_TEXTURE_2D, mTex_);

	unsigned char* image = nullptr;
	if (MaterialMgr::Instance().HasImageData(name))
	{
		const auto& imageData = MaterialMgr::Instance().GetImageData(name);
		image = get<0>(imageData);
		mWidth_ = get<1>(imageData);
		mHeight_ = get<2>(imageData);
	}
	else
	{
		image = SOIL_load_image(name.c_str(), &mWidth_, &mHeight_, 0, SOIL_LOAD_RGB);
		MaterialMgr::Instance().AddImageData(name, image, mWidth_, mHeight_);
	}
	assert(image);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth_, mHeight_, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	//纹理格式设置
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//mipmap
	glGenerateMipmap(GL_TEXTURE_2D);

	//SOIL_free_image_data(image);

	glBindTexture(GL_TEXTURE_2D, 0);
}

NaiveZ3D::Texture::~Texture()
{
	if (glIsTexture(mTex_))
	{
		glDeleteBuffers(1, &mTex_);
	}
}
