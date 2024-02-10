#include "ResourceManager.h"
#include "../Render/ShaderProgram.h"


#include <sstream>
#include <fstream>
#include <iostream>



ResourcesManager::ResourcesManager(const std::string& executablePath)
{
	size_t found = executablePath.find_last_of("/\\");
	m_path = executablePath.substr(0, found);
}

std::shared_ptr<Renderer::ShaderProgram> ResourcesManager::loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
{
	std::string vertexString = getFileString(vertexPath);
	if (vertexString.empty())
	{
		std::cerr << "No vertex shader!" << std::endl;
		return nullptr;
	}


	std::string fragmentString= getFileString(fragmentPath);
	if (fragmentString.empty())
	{
		std::cerr << "No fragment shader!" << std::endl;
		return nullptr;
	}

	std::shared_ptr<Renderer::ShaderProgram> newShader = m_shaderPrograms.emplace(shaderName, std::make_shared<Renderer::ShaderProgram>(vertexString, fragmentString)).first->second;

	if (!newShader->isCompiled())
	{
		std::cerr << "Can't load ShaderProgram!\n" << "Vertex: "
			<< vertexPath << "\nFragment: " 
			<< fragmentPath << std::endl;

		return nullptr;
	}
	

	return newShader;
}

std::shared_ptr<Renderer::ShaderProgram> ResourcesManager::getShaderProgram(const std::string& shaderName)
{
	ShaderProgramsMap::iterator it = m_shaderPrograms.find(shaderName);
	if (it == m_shaderPrograms.end())
	{
		std::cerr << "Can't find this shader program: " << shaderName << std::endl;
		return nullptr;
	}

	return it->second;
}

std::string ResourcesManager::getFileString(const std::string& relativeFilePath) const
{


	std::ifstream f;

	f.open(m_path + '/' + relativeFilePath.c_str(), std::ios::in | std::ios::binary);
	if (!f.is_open())
	{
		std::cerr << "File to open error " << relativeFilePath << std::endl;
		return std::string{};
	}
	
	std::stringstream buffer;
	buffer << f.rdbuf();

	return buffer.str();
}
