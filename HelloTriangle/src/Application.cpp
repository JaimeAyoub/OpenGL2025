#include "Application.h"
#include "ShaderFuncs.h"
#include <iostream>
#include <vector>

void Application::SetupShaders()
{
	//cargar shaders
	std::string vertexShader{ loadTextFile("Shaders/vertexPassthru.glsl") };
	std::string fragmentShader{ loadTextFile("Shaders/fragmentPassthru.glsl") };
	//crear programa
	shaders["passthru"] = InitializeProgram(vertexShader, fragmentShader);
	std::cout << "shaders compilados" << std::endl;

	timeID = glGetUniformLocation(shaders["passthru"], "time");
	posxID = glGetUniformLocation(shaders["passthru"], "posX");
	posyID = glGetUniformLocation(shaders["passthru"], "posY");
	selectColorIDRed = glGetUniformLocation(shaders["passthru"], "outColorRed");
	selectColorIDGreen = glGetUniformLocation(shaders["passthru"], "outColorGreen");
	selectColorIDBlue = glGetUniformLocation(shaders["passthru"], "outColorBlue");

}

void Application::SetupGeometry()
{
	std::vector<GLfloat> triangle
	{
		-1.0f, 1.0f, -1.0f, 1.0f, // vertice 0
		-1.0f, -1.0f, -1.0f, 1.0f,// vertice 1
		1.0f, -1.0f, -1.0f, 1.0f, // vertice 2
	};

	std::vector<GLfloat> colors
	{
		1.0f, 0.0f, 0.0f, 1.0f, // RED
		0.0f, 0.15f, 0.0f, 1.0f, // GREEN
		0.0f, 0.0f, 0.30f, 1.0f, // BLUE
	};

	//Crear VAO
	GLuint VAO_id, VBO_id, VBO_colorsID;
	glGenVertexArrays(1, &VAO_id);
	glBindVertexArray(VAO_id);

	geometry["triangulo"] = VAO_id;

	//crear VBO vertices
	glGenBuffers(1, &VBO_id);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_id);  //Ojo esto todavia no ha reservado memoria
	//Pasar arreglo de vertices
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(GLfloat) * triangle.size(),
		&triangle[0],
		GL_STATIC_DRAW);  //Mandamos la geometria al buffer

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0); //geometria
	glEnableVertexAttribArray(0);

	//crear VBO colores
	glGenBuffers(1, &VBO_colorsID);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_colorsID);  //Ojo esto todavia no ha reservado memoria
	//Pasar arreglo de vertices
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(GLfloat) * colors.size(),
		&colors[0],
		GL_STATIC_DRAW);  //Mandamos la geometria al buffer

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0); //colores
	glEnableVertexAttribArray(1);
}

void Application::SetupGeometrySingleArray()
{
	std::vector<GLfloat> triangle
	{
		-1.0f, 1.0f, -1.0f, 1.0f, // vertice 0
		-1.0f, -1.0f, -1.0f, 1.0f,// vertice 1
		1.0f, -1.0f, -1.0f, 1.0f, // vertice 2

		1.0f, 0.0f, 0.0f, 1.0f, // RED
		0.0f, 0.15f, 0.0f, 1.0f, // GREEN
		0.0f, 0.0f, 0.30f, 1.0f, // BLUE

	};


	//Crear VAO
	GLuint VAO_id, VBO_id;
	glGenVertexArrays(1, &VAO_id);
	glBindVertexArray(VAO_id);

	geometry["triangulo"] = VAO_id;

	//crear VBO vertices
	glGenBuffers(1, &VBO_id);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_id);  //Ojo esto todavia no ha reservado memoria
	//Pasar arreglo de vertices
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(GLfloat) * triangle.size(),
		&triangle[0],
		GL_STATIC_DRAW);  //Mandamos la geometria al buffer

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)&triangle[0]); //geometria
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)&triangle[12]); //colores
	glEnableVertexAttribArray(1);
}

void Application::Setup()
{


	SetupShaders();
	SetupGeometry();

	//SetupGeometrySingleArray();
}

void Application::Update()
{

	time += 0.005;
	glfwGetCursorPos(this->window, &posxMouse, &posyMouse);
	posX = static_cast<float>(posxMouse);
	posY = static_cast<float>(posyMouse);

	//std::cout << posX << std::endl;
	//std::cout << posX/5120 << std::endl;
	
}

void Application::Draw()
{
	//Seleccionar programa (shaders)
	glUseProgram(shaders["passthru"]);
	//Pasar el resto de los parámetros para el programa
	glUniform1f(timeID, time);
	glUniform1f(posxID, posX);
	glUniform1f(posyID, posY);
	glUniform4f(selectColorIDRed, outColorRed.x, outColorRed.y, outColorRed.z, outColorRed.w);
	glUniform4f(selectColorIDGreen, outColorGreen.x, outColorGreen.y, outColorGreen.z, outColorGreen.w);
	glUniform4f(selectColorIDBlue, outColorBlue.x, outColorBlue.y, outColorBlue.z, outColorBlue.w);

	//Seleccionar la geometria (el triangulo)
	glBindVertexArray(geometry["triangulo"]);

	//glDraw()
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Application::Keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//NOTA
	//Esta funcion esta sin utilizar hasta que descubra como poder pasarla a 
	// glfwSetKeyCallback(application.window, application.Keyboard);
	window = this->window;
	if (key == GLFW_KEY_X && action == GLFW_PRESS)
	{
		outColorRed = glm::vec4(posX / 5120, 0.0f, 0.0f, 1.0f);
	}
	else if (key == GLFW_KEY_Y && action == GLFW_PRESS)
	{
		outColorGreen = glm::vec4(0.0f, posX / 5120, 0.0f, 1.0f);
	}
	else if (key == GLFW_KEY_Z && action == GLFW_PRESS)
	{
		outColorBlue = glm::vec4(0.0f, 0.0f, posX / 5120, 1.0f);
	}

}

void Application::Keyboard2()
{
	//Esta funcion de obtener la tecla que se esta presionando la use en el proyecto del anterior trimestre
	//Debido a que no supe como usar la otra funcion, use esta, aunque se que no es lo que pidio profe
	// 
	//Use las teclas A,S,D para referirme al R,G,B.
	// Por lo tanto si presiona A y mueve la posicion del mouse hacia la derecha
	// la tonalidad del rojo aumentara, y si lo mueve para la izquierda disminuira
	// solo se basa en la posicion del mouse en X, por lo que si lo mueve hacia arriba o abajo no cambiara.
	// 
	// Esto aplica igual para las demas teclas S y D.
	// posX se divide en 5120 ya que es mi resolucion x4, esto para que sea mas notorio el cambio y no de golpe.
	// 
	//


	if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS) 
	{
		outColorRed = glm::vec4(posX / 5120, 0.0f, 0.0f, 1.0f);
	}
	else if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
	{
		outColorGreen = glm::vec4(0.0f, posX / 5120, 0.0f, 1.0f);
	}
	else if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
	{
		outColorBlue = glm::vec4(0.0f, 0.0f, posX / 5120, 1.0f);
	}

	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		//activar el flag de salida del probgrama
		glfwSetWindowShouldClose(window, 1);
	}
}
