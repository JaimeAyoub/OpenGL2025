#include "glad.h"
#include "GLFW/glfw3.h"
#include "Application.h"
#include <iostream>

Application application;





int main(void)
{


    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    application.window = glfwCreateWindow(1280, 960, "Hello Triangle", NULL, NULL);
    if (!application.window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(application.window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Error al inicializar GLAD" << std::endl;
        return -1;
    }

    /* Make the window's context current */
   // glfwSetKeyCallback(application.window, application.Keyboard);
  

    application.Setup();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(application.window))
    {
        double currentTime = glfwGetTime();
        
        

        /* Poll for and process events */
        glfwPollEvents();
        application.Update();
        application.Keyboard2();

        //application.Keyboard(window, GLFW_KEY_U,GLFW_PRESS);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        application.Draw();

        
        /* Swap front and back buffers */
        glfwSwapBuffers(application.window);
    }

    glfwTerminate();
    return 0;
}