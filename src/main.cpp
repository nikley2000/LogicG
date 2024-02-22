#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vec2.hpp>
#include <mat4x4.hpp>
#include <gtc/matrix_transform.hpp>

#include <vector>


#include "Render/ShaderProgram.h"
#include "Resources/ResourceManager.h"
#include "Resources/Objects/Objects.h"
#include "Render/Texture2D.h"
#include "Render/Sprite.h"
#include "Render/UI/selector.h"









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

    glClearColor(1, 1, 1, 1);

    {
        ResourcesManager::setExexutablePath(argv[0]);
   
        auto pSpriteShaderProgram = ResourcesManager::loadShaders("SpriteShader", "res/shaders/vSprite.txt", "res/shaders/fSprite.txt");
        if (!pSpriteShaderProgram)
        {
            std::cerr << "Can't create shader program: " << "SpriteShader" << std::endl;
            return -1;
        }

        Object::SetWindow(pWindow);
        ResourcesManager::loadTexture("AndTexture", "res/textures/AND.png");
        ResourcesManager::loadTexture("OrTexture", "res/textures/or.png");
        ResourcesManager::loadTexture("LampOFFTexture", "res/textures/LAMP_OFF.png");
        ResourcesManager::loadTexture("LampONTexture", "res/textures/LAMP_ON.png");


        glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(g_windowSize.x), 0.f, static_cast<float>(g_windowSize.y), -100.f, 100.f);
        


        pSpriteShaderProgram->use();
        pSpriteShaderProgram->setInt("tex", 0);
        pSpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);

        AND obj1;
        AND obj2;
        OR obj3;
        LAMP obj4;
        
        

        std::vector<std::shared_ptr<Object>> Objects;
        Objects.push_back(std::make_shared<AND>(glm::vec2(12,152)));
        Objects.push_back(std::make_shared<OR>(glm::vec2(200, 312)));
  
        UI::selector::init();
        glfwSetScrollCallback(pWindow, UI::scroll_callback);

        double xpos = 110;
        double ypos = 110;
        while (!glfwWindowShouldClose(pWindow))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);



            if (glfwGetMouseButton(pWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS )
            {

                glfwGetCursorPos(pWindow, &xpos, &ypos);
                Objects.push_back(std::make_shared<Object>(UI::selector::getObject()));
            }
            for (auto& i : Objects)
            {
                i->render();
            }
          
            glfwGetCursorPos(pWindow, &xpos, &ypos);
         

            UI::selector::update(pWindow);
            UI::selector::render();
            
            

            glfwSwapBuffers(pWindow);
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}