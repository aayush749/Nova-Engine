#pragma once
#include "Shader.h"
#include <vector>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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

	void BindUniformMatrix4fv(glm::mat4& matrix, const char* uniformName)
	{
		auto u_Loc = glGetUniformLocation(m_ProgramID, uniformName);
		glProgramUniformMatrix4fv(m_ProgramID, u_Loc, 1, GL_FALSE, glm::value_ptr(matrix));
	}

private:
	void CheckLinkingErrors();
	void CheckValidationErrors();
};

