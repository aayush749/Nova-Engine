#pragma once

#include <GL/glew.h>
#include <stb_image/stb_image.h>
#include <string>
#include <string_view>

class Texture
{
private:
	GLuint m_Id;
	GLubyte* m_Img;
	GLint m_Width, m_Height, m_NChannels;
protected:
	std::string imgSrc;
	Texture(const std::string& imgFilePath, int nDesiredChannels = 3, bool flipOnLoad = true);
	GLuint& getTextureID() { return m_Id; }
public:
	const GLuint getTextureID() const { return m_Id; }
	void setTextureID(GLint texture_Id) { m_Id = texture_Id; }
	int getWidth() const { return m_Width; }
	int getHeight() const { return m_Height; }
	int getNChannels() const { return m_NChannels; }
	const GLubyte* getImgData() const { return m_Img; }
public:
	virtual ~Texture();
	virtual void BindTexture(GLushort slot = 0) = 0;
	virtual void UnbindTexture() = 0;
private:
	void loadImage(std::string_view imgPath, int nDesiredChannels = 0, bool flipOnLoad = true);
};

