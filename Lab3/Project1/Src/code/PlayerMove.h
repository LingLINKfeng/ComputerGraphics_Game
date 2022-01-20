#pragma once
#include<iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class PlayerMove {
public:
	PlayerMove(glm::mat4 PlayerModel);

	glm::mat4 processInput(GLFWwindow *window, float &deltaTime, float &lastFrame, glm::mat4 &PlayerModel, float &rotate);
	float GetTime(float &deltaTime, float &lastFrame);

private:
	GLFWwindow* window;

	glm::mat4 PlayerModel = glm::mat4(1.0f);

};