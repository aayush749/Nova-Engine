#include "Texture.h"

Texture::Texture(const std::string& imgFilePath, int nDesiredChannels, bool flipOnLoad)
	:imgSrc{ imgFilePath }, m_Img{ nullptr }
{
	loadImage(imgFilePath, nDesiredChannels, flipOnLoad);
}

Texture::~Texture()
{
	if (m_Img)
	{
		stbi_image_free(m_Img);
	}
	if (m_Id > 0)
	{
		glDeleteTextures(1, &m_Id);
	}
}

void Texture::loadImage(std::string_view imgPath, int nDesiredChannels, bool flipOnLoad)
{
	if (flipOnLoad)
		stbi_set_flip_vertically_on_load(true);

	m_Img = stbi_load(imgPath.data(), &m_Width, &m_Height, &m_NChannels, nDesiredChannels);

	// reset the flip vertically on load of stb image back to false
	stbi_set_flip_vertically_on_load(false);
}