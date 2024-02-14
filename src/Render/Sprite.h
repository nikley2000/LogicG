#pragma once

#include <glad/glad.h>
#include <memory>
#include <vec2.hpp>


namespace Renderer
{
	class Texture2D;
	class ShaderProgram;
	class Sprite
	{
	public:
		Sprite(const std::shared_ptr<Texture2D> pTexture,
			const std::shared_ptr<ShaderProgram> pShaderProgramm,
			const glm::vec2 position = glm::vec2(0.f),
			const glm::vec2 size = glm::vec2(1.f),
			const float rotation = 0.f);

		~Sprite();

		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;


		void render() const;
		void setPosition(const glm::vec2 position);
		void setSize(const glm::vec2 size);
		void SetRotatition(const float rotation);

	private:
		std::shared_ptr<ShaderProgram> m_pShaderProgram;
		std::shared_ptr<Texture2D> m_pTexture;
		glm::vec2 m_position;
		glm::vec2 m_size;
		float m_rotation;
		GLuint m_VAO;
		GLuint m_vertexCoordsVBO;
		GLuint m_textureCoordsVBO;
	};
}