#include "Texture2D.h"

Texture2D::Texture2D(const std::string& imgPath, int nDesiredChannels, bool filpOnLoad, bool generateMipMaps)
	:Texture(imgPath, nDesiredChannels, filpOnLoad)
{
	GLuint& textureID = getTextureID();
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Set the texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	if (generateMipMaps)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	// Generate the textures now
	if (nDesiredChannels == 4)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, getWidth(), getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, getImgData());
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, getWidth(), getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, getImgData());

	}

	if (generateMipMaps)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}

}

void Texture2D::BindTexture(GLushort slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, getTextureID());
}

void Texture2D::UnbindTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}