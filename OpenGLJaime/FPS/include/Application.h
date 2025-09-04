#pragma once
#include "glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Plane.h"
#include <string>
#include <map>
#include <algorithm>
#include <iostream>
class Application
{
private:
	std::map<std::string, GLuint> shaders;
	std::map<std::string, GLuint> geometry;
	std::map<std::string, GLuint> uniforms;
	std::map<std::string, GLuint> textures;

	glm::mat4 projection;
	glm::mat4 camera;
	glm::mat4 accumTrans;
	glm::mat4 accumTransX;
	glm::mat4 accumTransY;
	glm::vec3 eye;
	glm::vec3 center;
	glm::vec2 cameraPos;

	glm::vec3 direction;
	glm::vec3 right;
	glm::vec3 up = glm::vec3(0.0f,-1.0f,0.0f);
	float horizontalAngle = 3.14f;
	float verticalAngle = 0.0f;


	void SetupShaders();
	void SetupShaderPassthru();
	void SetupShaderTransform();
	void SetupGeometry();
	void SetupGeometrySingleArray();
	void CameraFPS();
	GLuint SetupTexture(const std::string& filename);


	float time{ 0.0f };
	float frecuency{ 17.0f };
	float amplitude{ 12.5f };
	GLuint timeID;
	float valueX = 0.0f;
	float valueY = 0.0f;

	//Cosas para el mouse
	double posxMouse{ 0.0 };
	double posyMouse{ 0.0 };

	float posX{ 0.0f };
	float posY{ 0.0f };
	float mouseSpeed = 0.0005f;

	float speed = 0.005f;
	GLuint posxID;
	GLuint posyID;
	//Valores para cambiar los colores
	glm::vec4 outColorRed{ 1.0f,0.0f,0.0f,1.0f };
	glm::vec4 outColorGreen{ 0.0f,1.0f,0.0f,1.0f };
	glm::vec4 outColorBlue{ 0.0f,0.0f,1.0f,1.0f };
	GLuint selectColorIDRed;
	GLuint selectColorIDGreen;
	GLuint selectColorIDBlue;

	Plane plane;




public:
	GLFWwindow* window;

	void Setup();
	void Update();
	void Draw();
	void Keyboard(int key, int scancode, int action, int mods);
	void Keyboard2();
	void MousePosition();
	void SetupPlane();

	const float screen_width = 1280.0f;
	const float screen_height = 960.0f;
};