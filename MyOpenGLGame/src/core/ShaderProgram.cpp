#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
	m_ProgramID = glCreateProgram();
}

void ShaderProgram::LinkAndValidateProgram()
{
	for (const Shader* s : shaders)
	{
		glAttachShader(m_ProgramID, s->GetShaderID());
	}

	glLinkProgram(m_ProgramID);
	CheckLinkingErrors();

	
	glValidateProgram(m_ProgramID);
	CheckValidationErrors();

}

void ShaderProgram::CheckLinkingErrors()
{
	int result;
	glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &result);

	if (result == GL_FALSE)
	{
		int length;
		glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH,
			&length);

		char* msg = (char*)(alloca(sizeof(char) * length));

		glGetProgramInfoLog(m_ProgramID, length,
			&length, msg);

		throw std::exception(
			("Error while linking shader program: " +
				std::string(msg)
				).c_str()
		);
	}
}

void ShaderProgram::CheckValidationErrors()
{
	int result;
	glGetProgramiv(m_ProgramID, GL_VALIDATE_STATUS, &result);

	if (result == GL_FALSE)
	{
		int length;
		glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH,
			&length);

		char* msg = (char*)(alloca(sizeof(char) * length));

		glGetProgramInfoLog(m_ProgramID, length,
			&length, msg);

		throw std::exception(
			("Error while linking shader program: " +
				std::string(msg)
				).c_str()
		);
	}

}
