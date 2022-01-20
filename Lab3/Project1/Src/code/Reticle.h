#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Retical {
public:
	Retical();
	void draw(GLfloat Vertices[]);
private:
	unsigned int VBO;
	unsigned int VAO;

};