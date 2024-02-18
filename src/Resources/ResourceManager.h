#pragma once
#include <string>
#include <memory>
#include <map>



namespace Renderer
{
	class ShaderProgram;
	class Texture2D;
	class Sprite;


}








class ResourcesManager
{
public:
	ResourcesManager(const std::string& executablePath);
	static void setExexutablePath(const std::string& executablePath);
	static void unloadAllResources();

	~ResourcesManager() = delete;
	ResourcesManager() = delete;
	ResourcesManager(const ResourcesManager&) = delete;
	ResourcesManager& operator=(const ResourcesManager&) = delete;
	ResourcesManager& operator=(ResourcesManager&&) = delete;
	ResourcesManager(ResourcesManager&&) = delete;

	static std::shared_ptr<Renderer::ShaderProgram> loadShaders(const std::string& shaderName, const std::string& VertexPath, const std::string& fragmentPath);
	static std::shared_ptr<Renderer::ShaderProgram> getShaderProgram(const std::string& shaderName);

	
	

	static std::shared_ptr<Renderer::Texture2D> loadTexture(const std::string& textureName, const std::string& texturePath);
	static std::shared_ptr<Renderer::Texture2D> getTexture(const std::string& textureName);


	static std::shared_ptr<Renderer::Sprite> loadSprite(const std::string& spriteName,
												const std::string& textureName,
												const std::string& shaderName,
												const unsigned int spriteWidth,
												const unsigned int spriteHeight);



	static std::shared_ptr<Renderer::Sprite> getSprite(const std::string& spriteName);

private:
	static std::string getFileString(const std::string& relativeFilePath);

	typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
	static ShaderProgramsMap m_shaderPrograms;

	typedef std::map<const std::string, std::shared_ptr<Renderer::Texture2D>> TexturesMap;
	static TexturesMap m_textures;

	typedef std::map<const std::string, std::shared_ptr<Renderer::Sprite>> SpritesMap;
	static SpritesMap m_sprites;

	static std::string m_path;
};