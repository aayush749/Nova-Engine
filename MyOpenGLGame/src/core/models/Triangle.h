#pragma once
#include <GL/glew.h>
#include <glm/vec2.hpp>
#include "../Shader.h"
#include "../ShaderProgram.h"

#include <array>
#include <functional>

template <typename T = glm::vec2>
class Triangle
{
	using VertexType = T;

private:
	std::array<VertexType, 3> vertices;

	GLuint m_vao, *m_vbo;
	Shader m_VertexShader, m_FragmentShader;
	ShaderProgram m_ShaderProgram;
public:

	Triangle() = default;

	Triangle(Shader& vShader, Shader& fShader, int n_VBOS,
		std::function<void(std::array<VertexType, 3>&, GLuint*)> vboSpecFn)
		:m_VertexShader(vShader), m_FragmentShader(fShader)
	{
		glCreateVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		m_vbo = new GLuint[n_VBOS];

		vboSpecFn(vertices, m_vbo);

		glBindVertexArray(0);

		// fit the shaders
		try
		{
			m_VertexShader.Fit();
			m_FragmentShader.Fit();
		}
		catch (const std::exception& e)
		{
			std::cerr << "Exception thrown while fitting shaders: " << e.what() << std::endl;
			std::cout << "Could not load shader for the triangle" << std::endl;
			return;
		}

		CreateShaderProgram();
	}
	

	void Model(Shader& vShader, Shader& fShader, int n_VBOS,
		std::function<void(std::array<VertexType, 3>&, GLuint*)> vboSpecFn)
	{
		m_VertexShader = vShader, m_FragmentShader = fShader;

		glCreateVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);


		m_vbo = new GLuint[n_VBOS];

		vboSpecFn(vertices, m_vbo);

		glBindVertexArray(0);

		// fit the shaders
		try
		{
			m_VertexShader.Fit();
			m_FragmentShader.Fit();
		}
		catch (const std::exception& e)
		{
			std::cerr << "Exception thrown while fitting shaders: " << e.what() << std::endl;
			std::cout << "Could not load shader for the triangle" << std::endl;
			return;
		}

		CreateShaderProgram();
	}

	
	VertexType& operator[](const size_t& offset)
	{
		return vertices[offset];
	}

	void Render()
	{
		glUseProgram(m_ShaderProgram.GetProgramID());
		glBindVertexArray(m_vao);


		glDrawArrays(GL_TRIANGLES, 0, 3);

	}

	ShaderProgram& GetRenderingProgram() { return m_ShaderProgram; }

	~Triangle()
	{
		glDeleteShader(m_VertexShader.GetShaderID());
		glDeleteShader(m_FragmentShader.GetShaderID());

		glDeleteProgram(m_ShaderProgram.GetProgramID());

		delete m_vbo;
	}

private: 
	void CreateShaderProgram()
	{
		// create the shader program
		try
		{
			// add the shaders to the shader program
			m_ShaderProgram << m_VertexShader << m_FragmentShader;

			m_ShaderProgram.LinkAndValidateProgram();
		}
		catch (std::exception& e)
		{
			std::cerr << "Unable to link and validate the shader program. Error: " 
					  << e.what() << std::endl;
		}
	}
};

