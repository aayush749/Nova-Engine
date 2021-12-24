#include "Shader.h"

#include <fstream>
#include <exception>
#include <iostream>

Shader::Shader(const char* filepath, GLenum shaderType)
    :m_ShaderType(shaderType)
{
    try
    {

        std::ifstream file(filepath, std::ios::in);

        if (file.good())
        {
            file.seekg(0, std::ios::end);
            size_t size = file.tellg();
            file.seekg(0, std::ios::beg);

            m_Source.resize(size + 1);

            file.read(&m_Source[0], size);
        }
        else
            throw std::exception("Could not read file");


        file.close();
    }
    catch (std::exception& e)
    {
        std::cerr << "Error opening shader file : " << filepath<< "\tError Message: " << e.what() << std::endl;
    }
}

void Shader::Fit()
{
    m_ShaderID = glCreateShader(m_ShaderType);
    auto shaderCStr = m_Source.c_str();
    glShaderSource(m_ShaderID, 1, &shaderCStr, NULL);

    Compile();
    CheckErrors();
}

void Shader::Compile()
{
    if (!isCompiled)
    {
        glCompileShader(m_ShaderID);
        isCompiled = true;
    }
}

void Shader::CheckErrors()
{
    int result;
    glGetShaderiv(m_ShaderID, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(m_ShaderID, GL_INFO_LOG_LENGTH,
            &length);

        char* msg = (char*)(alloca(sizeof(char) * length));

        glGetShaderInfoLog(m_ShaderID, length,
            &length, msg);

        throw std::exception(
            (std::string("Error while compiling ") + (m_ShaderType == GL_VERTEX_SHADER ? "vertex shader" : "fragment shader") +
                std::string(msg)
                ).c_str()
        );
    }
}
