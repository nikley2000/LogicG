#pragma once

#include <memory>
#include <string>
#include <vec2.hpp>

#include "../../Render/Sprite.h"
#include "../../Resources/ResourceManager.h"

struct GLFWwindow;

class Object
{
public:
    Object(const std::string texture, const glm::vec2& position = glm::vec2(0.f));
    

    void render();
   

    void setPosition(const glm::vec2& position);
  

    static void SetWindow(GLFWwindow* pWindow);
  
protected:
    std::shared_ptr<Renderer::Sprite> m_pSprite;
    glm::vec2 m_position;
    static inline GLFWwindow* m_pWindow = nullptr;
};