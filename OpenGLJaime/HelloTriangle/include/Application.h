#pragma once
#include "glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <string>
#include <map>
class Application
{
private:
	std::map<std::string, GLuint> shaders;
	std::map<std::string, GLuint> geometry;
	std::map<std::string, GLuint> uniforms;

	glm::mat4 projection;
	glm::mat4 camera;
	glm::vec3 eye;
	glm::vec3 center;


	void SetupShaders();
	void SetupShaderPassthru();
	void SetupShaderTransform();
	void SetupGeometry();
	void SetupGeometrySingleArray();

	float time{0.0f};
	GLuint timeID;

	//Cosas para el mouse
	double posxMouse{ 0.0 };
	double posyMouse{ 0.0 };

	float posX{ 0.0f };
	float posY{ 0.0f };
	GLuint posxID;
	GLuint posyID;
	//Valores para cambiar los colores
	glm::vec4 outColorRed;
	glm::vec4 outColorGreen;
	glm::vec4 outColorBlue;
	GLuint selectColorIDRed;
	GLuint selectColorIDGreen;
	GLuint selectColorIDBlue;

	
	

public:
	GLFWwindow* window; 

	void Setup();
	void Update();
	void Draw();
	void Keyboard(int key, int scancode, int action, int mods);
	void Keyboard2();
	void MousePosition();
	
	float screen_width = 1280;
	float screen_height = 960;
};