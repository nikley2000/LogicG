#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

#include "Render/ShaderProgram.h"
#include "Resources/ResourceManager.h"




GLfloat point[] = {
    0.0f, 0.6f, 0.0f,
    0.5f, -0.6f, 0.0f,
    -0.5f,-0.6f, 0.0f
   
 
};


GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};


size_t g_window_sizeX = 640;
size_t g_window_sizeY = 480;

void glfwWIndowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    g_window_sizeX = width;
    g_window_sizeY = height;
    glViewport(0, 0, g_window_sizeX, g_window_sizeY);
}


void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
}

int main(int argc, char** argv)
{


    


    /* Initialize the library */
    if (!glfwInit())   
    {
        std::cout << "GLFW Init Error!\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pWindow = glfwCreateWindow(g_window_sizeX, g_window_sizeY, "LogicG", nullptr, nullptr);
    if (!pWindow)
    {
        std::cout << "GLFW Window creating Error!\n";
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */

    glfwSetWindowSizeCallback(pWindow, glfwWIndowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);




    glfwMakeContextCurrent(pWindow);
    

    

    if(!gladLoadGL())
    {
        std::cout << "Can't load GLAD" << std::endl;
        return -1;
    }
    std::cout << "Render: " << glGetString(GL_RENDERER) << '\n';
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << '\n';

    glClearColor(0,0,0,1);
    {
        ResourcesManager resourceManager(argv[0]);
        //resourceManager.~ResourcesManager();
        auto pDefaultShaderProgram = resourceManager.loadShaders("DefaultShader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");

        if (!pDefaultShaderProgram)
        {
            std::cerr << "Can't create shader program - DefaultShader" << std::endl;
            return -1;
        }

        GLuint points_vbo = 0;
        glGenBuffers(1, &points_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

        GLuint colors_vbo = 0;
        glGenBuffers(1, &colors_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);


        GLuint vao = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(pWindow))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            pDefaultShaderProgram->use();
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            /* Swap front and back buffers */
            glfwSwapBuffers(pWindow);

            /* Poll for and process events */
            glfwPollEvents();
        }

        
    }
    

    glfwTerminate();
    return 0;
}