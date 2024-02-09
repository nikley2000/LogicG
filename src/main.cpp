#include <iostream>


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

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

int main(void)
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

    glClearColor(0,0,1,1);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}