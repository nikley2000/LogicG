#include "ShaderProgram.h"
#include <iostream>
#include <gtc/type_ptr.hpp>


namespace Renderer
{
	
	ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
	{
		GLuint vertexShaderID;
		if (!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID))
		{
			std::cerr << "VERTEX_SHADER compile error\n" << std::endl;
			return;
		}
		
		GLuint fragmentShaderID;
		if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID))
		{
			std::cerr << "FRAGMENT_SHADER compile error\n" << std::endl;
			glDeleteShader(vertexShaderID);
			return;
		}

		m_ID = glCreateProgram();

		glAttachShader(m_ID, vertexShaderID);
		glAttachShader(m_ID, fragmentShaderID);
		glLinkProgram(m_ID);

		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);


		GLint success;
		glGetShaderiv(m_ID, GL_LINK_STATUS, &success);

		if (!success)
		{
			GLchar infolog[1024];
			glGetShaderInfoLog(m_ID, 1024, nullptr, infolog);
			std::cerr << "ERROR::SHADER: Link-time error:\n" << infolog << std::endl;
		}
		else
		{
			m_isCompiled = true;
		}



	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_ID);
	}

	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept
	{
		glDeleteProgram(m_ID);
		m_ID = shaderProgram.m_ID;
		m_isCompiled = shaderProgram.m_isCompiled;

		shaderProgram.m_ID = 0;
		shaderProgram.m_ID = false;
		return *this;

	}

	ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept
	{
		m_ID = shaderProgram.m_ID;
		m_isCompiled = shaderProgram.m_isCompiled;

		shaderProgram.m_ID = 0;
		shaderProgram.m_ID = false;

		
	}



	void ShaderProgram::use() const
	{
		glUseProgram(m_ID);
	}

	void ShaderProgram::setInt(const std::string& name, const GLint value)
	{
		glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);

	}

	void ShaderProgram::setMatrix4(const std::string& name, const glm::mat4x4& matrix)
	{

		glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));

	}


	bool ShaderProgram::createShader(const std::string& source, const GLenum sharedType, GLuint& shaderID)
	{
		shaderID = glCreateShader(sharedType);
		const char* code = source.c_str();
		glShaderSource(shaderID, 1, &code, nullptr);
		glCompileShader(shaderID);
		
		GLint success;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			GLchar infolog[1024];
			glGetShaderInfoLog(shaderID, 1024, nullptr, infolog);
			std::cerr << "ERROR::SHADER: Compile-time error:\n" << infolog << std::endl;
			return false;
		}

		return true;
	}

}