#include "BaseObject.h"


    Object::Object(const std::string texture, const glm::vec2& position)
    {
        m_pSprite = ResourcesManager::loadSprite(texture + "Sprite", texture + "Texture", "SpriteShader", 75, 75);
        m_position = position;
    }


    void Object::render()
    {
        m_pSprite->setPosition(m_position);
        m_pSprite->render();
    }


    void Object::setPosition(const glm::vec2& position)
    {
        m_position = position;
    }

    void Object::SetWindow(GLFWwindow* pWindow)
    {
        m_pWindow = pWindow;
    }
