#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vec2.hpp>
#include <mat4x4.hpp>
#include <gtc/matrix_transform.hpp>



#include "Render/ShaderProgram.h"
#include "Resources/ResourceManager.h"
#include "Render/Texture2D.h"
#include "Render/Sprite.h"


class Object
{
public:
    Object(const std::string texture, const glm::vec2& position = glm::vec2(0.f))
    {

        m_pSprite = ResourcesManager::loadSprite(texture + "Sprite", texture + "Texture", "SpriteShader", 75, 75);
        m_position = position;
    }

    void render()
    {
        m_pSprite->setPosition(m_position);
        m_pSprite->render();
    }

    void setPosittion(const glm::vec2& position)
    {
        m_position = position;
        
    }

private:
    std::shared_ptr<Renderer::Sprite> m_pSprite;
    glm::vec2 m_position;
};


class OR : public Object
{
public:
    OR(const glm::vec2& position = glm::vec2(0.f))
        :Object("Or", position)
    {

    }

    ~OR()
    {
    }

private:

};

class AND : public Object
{
public:
    AND(const glm::vec2& position = glm::vec2(0.f))
        :Object("And", position)
    {

    }

    ~AND()
    {
    }

private:

};

glm::vec2 g_windowSize(640, 480);


glm::vec2 saposition(0, 0);

void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    g_windowSize.x = width;
    g_windowSize.y = height;
    glViewport(0, 0, g_windowSize.x, g_windowSize.y);
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }

    if (key == GLFW_KEY_K && action == GLFW_REPEAT)
    {
        //std::cout << "key - k - pressed" << std::endl;
        saposition.x += 10;
    }

    if (key == GLFW_KEY_K && action == GLFW_RELEASE)
    {
        //std::cout << "key - k - pressed" << std::endl;
        saposition.x -= 100;
    }
}


void glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{

}

int main(int argc, char** argv)
{
    /* Initialize the library */


    
    if (!glfwInit())
    {
        std::cout << "glfwInit failed!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pWindow = glfwCreateWindow(g_windowSize.x, g_windowSize.y, "Battle City", nullptr, nullptr);
    if (!pWindow)
    {
        std::cout << "glfwCreateWindow failed!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);
    glfwSetMouseButtonCallback(pWindow, glfwMouseButtonCallback);
    
    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);

    if (!gladLoadGL())
    {
        std::cout << "Can't load GLAD!" << std::endl;
    }

    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    glClearColor(1, 1, 0, 1);

    {
        ResourcesManager::setExexutablePath(argv[0]);
   
        auto pSpriteShaderProgram = ResourcesManager::loadShaders("SpriteShader", "res/shaders/vSprite.txt", "res/shaders/fSprite.txt");
        if (!pSpriteShaderProgram)
        {
            std::cerr << "Can't create shader program: " << "SpriteShader" << std::endl;
            return -1;
        }


        ResourcesManager::loadTexture("OrTexture", "res/textures/or.png");
        ResourcesManager::loadTexture("AndTexture", "res/textures/AND.png");
       

      



        glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(g_windowSize.x), 0.f, static_cast<float>(g_windowSize.y), -100.f, 100.f);
        


        pSpriteShaderProgram->use();
        pSpriteShaderProgram->setInt("tex", 0);
        pSpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);

        AND obj1;
        AND obj2;
        double xpos = 110;
        double ypos = 110;
        while (!glfwWindowShouldClose(pWindow))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);
            
           
            glfwGetCursorPos(pWindow, &xpos, &ypos);
            obj1.setPosittion({ xpos, g_windowSize.y - ypos });
            obj2.setPosittion({ xpos + 200, g_windowSize.y - ypos });
            obj1.render();
            obj2.render();
            



            glfwSwapBuffers(pWindow);
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}