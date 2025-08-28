#include "Application.h"
#include "ShaderFuncs.h"
#include "Plane.h"
#include <iostream>
#include <vector>
#include "glm/gtc/type_ptr.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"



void Application::SetupShaderPassthru()
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
void Application::SetupShaderTransform()
{
	//Cargar shaders
	std::string vertexShader{ loadTextFile("Shaders/vertexTexture.glsl") };
	std::string fragmentShader{ loadTextFile("Shaders/fragmentTexture.glsl") };
	//Crear programa
	shaders["transforms"] = InitializeProgram(vertexShader, fragmentShader);
	uniforms["camera"] = glGetUniformLocation(shaders["transforms"], "camera");
	uniforms["projection"] = glGetUniformLocation(shaders["transforms"], "projection");
	uniforms["accumTrans"] = glGetUniformLocation(shaders["transforms"], "accumTrans");
	uniforms["eye"] = glGetUniformLocation(shaders["transforms"], "eye");
	uniforms["outColorRed"] = glGetUniformLocation(shaders["transforms"], "outColorRed");
	uniforms["outColorGreen"] = glGetUniformLocation(shaders["transforms"], "outColorGreen");
	uniforms["outColorBlue"] = glGetUniformLocation(shaders["transforms"], "outColorBlue");
	uniforms["time"] = glGetUniformLocation(shaders["transforms"], "time");
	uniforms["frecuency"] = glGetUniformLocation(shaders["transforms"], "frecuency");
	uniforms["amplitude"] = glGetUniformLocation(shaders["transforms"], "amplitude");
	uniforms["tex0"] = glGetUniformLocation(shaders["transforms"], "tex0");
	uniforms["tex1"] = glGetUniformLocation(shaders["transforms"], "tex1");
	uniforms["value"] = glGetUniformLocation(shaders["transforms"], "value");

}

void Application::SetupShaders()
{
	//SetupShaderPassthru();
	SetupShaderTransform();
}

void Application::SetupGeometry()
{
	std::vector<GLfloat> triangle
	{
		-1.0f, 1.0f, -1.0f, 1.0f, // vertice 0
		-1.0f, -1.0f, -1.0f, 1.0f,// vertice 1
		1.0f, -1.0f, -1.0f, 1.0f, // vertice 2

		-1.0f, 1.0f, -1.5f, 1.0f, // vertice 0
		-1.0f, -1.0f, -1.5f, 1.0f,// vertice 1
		1.0f, -1.0f,-0.4f, 1.0f,// vertice 2

	};

	std::vector<GLfloat> colors
	{
		1.0f, 0.0f, 0.0f, 1.0f, // RED
		0.0f, 1.0f, 0.0f, 1.0f, // GREEN
		0.0f, 0.0f, 1.0f, 1.0f, // BLUE

		1.0f, 0.0f, 0.0f, 1.0f, // RED
		0.0f, 0.0f, 1.0f, 1.0f, // BLUE
		0.0f, 1.0f, 0.0f, 1.0f, // GREEN
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
		1.0f, 0.0f, 0.0f, 1.0f, // RED
		1.0f, -1.0f, -1.0f, 1.0f, // vertice 2
		0.0f, 1.0f, 0.0f, 1.0f, // GREEN
		-1.0f, -1.0f, -1.0f, 1.0f,// vertice 1
		0.0f, 0.0f, 1.0f, 1.0f, // BLUE
		1.0f, 1.0f, -1.0f, 1.0f, // vertice 3
		1.0f, 1.0f, 1.0f, 1.0f, // White

		//-1.0f, 1.0f, -1.0f, 1.0f, // vertice 3
		//-1.0f, -1.0f, -1.0f, 1.0f,// vertice 4
		//1.0f, 0.0f, 0.0f, 1.0f, // RED
		//0.0f, 0.15f, 0.0f, 1.0f, // GREEN

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
	const GLint stride = 8 * sizeof(GLfloat);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, stride, (GLvoid*)0); //geometria
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(4 * sizeof(GLfloat))); //colores
	glEnableVertexAttribArray(1);
}

void Application::SetupPlane()
{
	
		plane.createPlane(200);

		glGenVertexArrays(1, &plane.vao);
		glBindVertexArray(plane.vao);
		glGenBuffers(1, &plane.vbo);
		glBindBuffer(GL_ARRAY_BUFFER, plane.vbo);


		glBufferData(GL_ARRAY_BUFFER, plane.getVertexSizeInBytes() + plane.getTextureCoordsSizeInBytes(), NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, plane.getVertexSizeInBytes(), plane.plane);
		glBufferSubData(GL_ARRAY_BUFFER, plane.getVertexSizeInBytes(), plane.getTextureCoordsSizeInBytes(), plane.textureCoords);
		plane.cleanMemory();

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(plane.getVertexSizeInBytes()));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
	
}

GLuint Application::SetupTexture(const std::string& filename)
{
	int width, height, channels;
	unsigned char *img = stbi_load(filename.c_str(), &width, &height, &channels, 4);
	if (img == nullptr)
		return -1;
	GLuint texID = -1;
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);

	stbi_image_free(img);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D,0);
	return texID;
	
}
void Application::Setup()
{


	SetupShaders();
	SetupPlane();
	textures["HeightMap"] = SetupTexture("Textures/HeightMap.png");
	textures["Diffuse"] = SetupTexture("Textures/Diffuse.png");
	//SetupGeometry();
	
	//SetupGeometrySingleArray();

	//Inicializar camara
	eye = glm::vec3(0.0f, 0.0f, 5.0f);

	center = glm::vec3(0.0f, 0.0f, -1.0f);
	projection = glm::perspective(glm::radians(45.0f), (1280.0f / 960.0f), 0.1f, 500.0f);
	accumTrans = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

}

void Application::Update()
{

	time += 0.001;
	//frecuency = time;
	//if (time > 255.0f/50)
	//{
	//	time = 0;
	//}
	//Actualizar ojo
	accumTransX = glm::rotate(glm::mat4(1.0f), glm::radians(posY * 20 / screen_height), glm::vec3(1.0f, 0.0f, 0.0f));
	accumTransY = glm::rotate(glm::mat4(1.0f), glm::radians(posX * 20 / screen_width), glm::vec3(0.0f, 1.0f, 0.0f));
	accumTrans = accumTransX * accumTransY;
	eye = glm::vec3(0.0f, 0.0f, 3.0f);
	//std::cout << value << std::endl;
	
	//Actualizar center
	center = glm::vec3(0, 0, 1.0f);
	//Actualizar camara
	camera = glm::lookAt(eye, center, glm::vec3(0.0f, 1.0f, 0.0f));

}

void Application::Draw()
{

	//Seleccionar programa (shaders)
	glUseProgram(shaders["transforms"]);
	//Pasar el resto de los parámetros para el programa
	glUniform1f(uniforms["time"], time);
	glUniform1f(uniforms["value"], value);
	glUniform1f(uniforms["frecuency"], frecuency);
	glUniform1f(uniforms["amplitude"], amplitude);
	glUniform3f(uniforms["eye"], eye.x, eye.y, eye.z);
	glUniform1f(posxID, posX);
	glUniform1f(posyID, posY);
	glUniform4f(uniforms["outColorRed"], outColorRed.x, outColorRed.y, outColorRed.z, outColorRed.w);
	glUniform4f(uniforms["outColorGreen"], outColorGreen.x, outColorGreen.y, outColorGreen.z, outColorGreen.w);
	glUniform4f(uniforms["outColorBlue"], outColorBlue.x, outColorBlue.y, outColorBlue.z, outColorBlue.w);
	glUniformMatrix4fv(uniforms["camera"], 1, GL_FALSE, glm::value_ptr(camera));
	glUniformMatrix4fv(uniforms["projection"], 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(uniforms["accumTrans"], 1, GL_FALSE, glm::value_ptr(accumTrans));

	//Seleccionar las texturas
	glBindTexture(GL_TEXTURE_2D, textures["HeightMap"]);
	glUniform1i(uniforms["tex0"], 0);
	glActiveTexture(GL_TEXTURE0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textures["Diffuse"]);
	glUniform1i(uniforms["tex1"], 1);
	//Seleccionar la geometria (el triangulo)
	glBindVertexArray(plane.vao);

	//glDraw()
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawArrays(GL_TRIANGLES, 0, plane.getNumVertex());
}

void Application::Keyboard(int key, int scancode, int action, int mods)
{
	window = this->window;

	if (value < 0)
		value = 0;
	else if (value > 1)
		value = 1;
	if (key == GLFW_KEY_A && action == GLFW_REPEAT)
	{
		//outColorRed = glm::vec4(posX / 1280, 0.0f, 0.0f, 1.0f);
		//frecuency += 1;
		
	}
	else if (key == GLFW_KEY_S && action == GLFW_REPEAT)
	{
		//outColorGreen = glm::vec4(0.0f, posX / 1280, 0.0f, 1.0f);
		//frecuency -= 1;
		
		
	}
	else if (key == GLFW_KEY_D && action == GLFW_REPEAT)
	{
		outColorBlue = glm::vec4(0.0f, 0.0f, posX / 1280, 1.0f);
	}
	else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, 1);
	}
	else if (key == GLFW_KEY_RIGHT && action == GLFW_REPEAT)
	{
		value -= 0.05;
	}
	else if (key == GLFW_KEY_LEFT && action == GLFW_REPEAT)
	{
		value += 0.05;
	}

}

void Application::Keyboard2()
{
	//Esta funcion de obtener la tecla que se esta presionando la use en el proyecto del anterior trimestre
	//Debido a que no supe como usar la otra funcion, use esta, aunque se que no es lo que pidio profe
	// 
	// Use las teclas A,S,D para referirme al R,G,B.
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
		outColorRed = glm::vec4(posX / 1280, 0.0f, 0.0f, 1.0f);

	}
	else if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
	{
		outColorGreen = glm::vec4(0.0f, posX / 1280, 0.0f, 1.0f);
	}
	else if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
	{
		outColorBlue = glm::vec4(0.0f, 0.0f, posX / 1280, 1.0f);
	}

	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		//activar el flag de salida del probgrama
		glfwSetWindowShouldClose(window, 1);
	}
}

void Application::MousePosition()
{
	glfwGetCursorPos(this->window, &posxMouse, &posyMouse);
	posX = static_cast<float>(posxMouse);
	posY = static_cast<float>(posyMouse);
}
