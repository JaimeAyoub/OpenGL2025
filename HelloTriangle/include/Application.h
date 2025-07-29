#pragma once
#include "glad.h"
#include "GLFW/glfw3.h"
#include "glm.hpp"
#include <string>
#include <map>
class Application
{
private:
	std::map<std::string, GLuint> shaders;
	std::map<std::string, GLuint> geometry;
	void SetupShaders();
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
	//Para elegir el vertice
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
	void Keyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
	void Keyboard2();
	
};