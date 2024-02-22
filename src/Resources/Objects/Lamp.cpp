#include "Lamp.h"

#include <GLFW/glfw3.h>



    LAMP::LAMP(const glm::vec2& position)
        :Object::Object("LampOFF", position)
    {

        ResourcesManager::loadSprite("LampONSprite", "LampONTexture", "SpriteShader", 75, 75);
        ResourcesManager::loadSprite("LampOFFSprite", "LampOFFTexture", "SpriteShader", 75, 75);
    }

    LAMP::~LAMP()
    {
    }

    void  LAMP::changeState()
    {
        if (isActive)
        {
            m_pSprite = ResourcesManager::getSprite("LampOFFSprite");
            isActive = false;
        }
        else
        {
            m_pSprite = ResourcesManager::getSprite("LampONSprite");
            isActive = true;
        }
    }

    void  LAMP::Control()
    {


        if (GLFW_PRESS == glfwGetKey(m_pWindow, GLFW_KEY_E) && isfirst)
        {
            isfirst = false;
            changeState();
        }

        if (GLFW_RELEASE == glfwGetKey(m_pWindow, GLFW_KEY_E) && !isfirst)
        {
            isfirst = true;

        }


    }
