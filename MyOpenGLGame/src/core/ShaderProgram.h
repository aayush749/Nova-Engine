#pragma once
#include "Shader.h"
#include <vector>

class ShaderProgram
{
private:
	std::vector<Shader*> shaders;

	GLint m_ProgramID;

public:

	ShaderProgram();

	void LinkAndValidateProgram();

	ShaderProgram& operator<< (Shader& shader)
	{
		shaders.push_back(&shader);
		return *this;
	}
	

	GLint GetProgramID() { return m_ProgramID; }

private:
	void CheckLinkingErrors();
	void CheckValidationErrors();
};

