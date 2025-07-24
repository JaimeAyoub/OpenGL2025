#pragma once
#include "glad.h"
#include <iostream>
#include <map>
class Application
{
private:
	std::map<std::string, GLuint> shaders;
	std::map<std::string, GLuint> geometry;
	void SetupShaders();
	void SetupGeometry();
public:
	void Setup();
	void Update();
	void Draw();
	void Keyboard();

};
