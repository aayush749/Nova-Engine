#pragma once
#include "Shader.h"
#include <vector>
#include <unordered_map>

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

	void BindUniform1f(float val, const char* uniformName)
	{
		auto u_Loc = glGetUniformLocation(m_ProgramID, uniformName);
		glProgramUniform1f(m_ProgramID, u_Loc, val);
	}

private:
	void CheckLinkingErrors();
	void CheckValidationErrors();
};

