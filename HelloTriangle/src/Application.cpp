#include "Application.h"
#include <iostream>
#include "ShaderFuncs.h"
#include <vector>


void Application::SetupShaders()
{
	//Cargar Shaders
	std::string vertexShader{ loadTextFile("Shaders/vertexPassthru.glsl") };
	std::string fragmentShader{ loadTextFile("Shaders/fragmentPassthru.glsl") };

	//Crear Programa
	shaders["passthru"] = InitializeProgram(vertexShader, fragmentShader);
	std::cout << "shaders compilados" << std::endl;
}

void Application::SetupGeometry()
{
	std::vector<GLfloat> triangle
	{
		 -1.0f,1.0f,-1.0f,1.0f,  //Vertice 0
		-1.0f,-1.0f,-1.0f,1.0f,	//Vertice 1
		1.0f,-1.0f,-1.0f,1.0f, //Vertice 2
	};
	//Crear VAO 
	GLuint VAO_id, VBO_id;
	glGenVertexArrays(1, &VAO_id);
	glBindVertexArray(VAO_id);
	geometry["triangulo"] = VAO_id;

	//Crear VBO
	glGenBuffers(1, &VBO_id);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * triangle.size(), &triangle[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0); //Geometria.El 4 es de cuanto es nuetro Array de vertices, en este caso x ,y,z y w

	glEnableVertexAttribArray(0); //El 0 del vertex passthru, permite la entrada de este.

	//Pasar arreglo de vertices
}

void Application::Setup()
{
	SetupShaders();
}

void Application::Update()
{
	std::cout << "Application::Update()" << std::endl;
}

void Application::Draw()
{
	//Seleccionar programa (shaders)
	glUseProgram(shaders["passthru"]);

	//Pasar el resto de los parametros para el programa.


	//Seleccionar geometria(el triangulo)
	glBindVertexArray(geometry["triangulo"]);

	//glDraw()
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
void Application::Keyboard()
{
	std::cout << "Application::Keyboard()" << std::endl;
}
