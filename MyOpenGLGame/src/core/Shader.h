#pragma once
#include <GL/glew.h>

#include <string>
#include <iostream>

class Shader
{
private:
	GLint m_ShaderID;
	GLenum m_ShaderType;
	std::string m_Source;
	bool isCompiled = false;
public:
	Shader() = default;
	Shader(const char* filepath, GLenum shaderType);

	Shader(const Shader& other)
	{
		std::cout << "Copied shader!";
	}

	void Fit();

	GLint GetShaderID() const { return m_ShaderID; }
	GLenum GetShaderType() const { return m_ShaderType; }
private:
	void Compile();
	void CheckErrors();
};

