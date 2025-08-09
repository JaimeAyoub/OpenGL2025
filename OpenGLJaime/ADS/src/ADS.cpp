#include "glad.h"
#include "GLFW/glfw3.h"
#include "Application.h"
#include <iostream>

Application application;

    void checkKeyboard(GLFWwindow* window,int key, int scancode, int action, int mods)
    {
        application.Keyboard(key, scancode, action, mods);
    }

int main(void)
{


    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    application.window = glfwCreateWindow(application.screen_width,application.screen_height, "Hello Plane", NULL, NULL);
    if (!application.window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(application.window);
    glfwSetInputMode(application.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {

        std::cout << "Error al inicializar GLAD" << std::endl;
        return -1;
    }

    /* Make the window's context current */
    glfwSetKeyCallback(application.window, checkKeyboard);
    

    application.Setup();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(application.window))
    {
        double currentTime = glfwGetTime();
        
        /* Poll for and process events */
        glfwPollEvents();
        application.Update();
        //application.Keyboard2();
        application.MousePosition();

        //application.Keyboard(window, GLFW_KEY_U,GLFW_PRESS);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        application.Draw();

        
        /* Swap front and back buffers */
        glfwSwapBuffers(application.window);
    }

    glfwTerminate();
    return 0;
}