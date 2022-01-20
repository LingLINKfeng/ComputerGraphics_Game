#pragma once
#include<iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class Keyboard {
public:
	Keyboard(glm::vec3& cameraPos, glm::vec3& cameraFront, glm::vec3& cameraUp, GLFWwindow* window);
	
	glm::vec3 processInput(GLFWwindow *window, float &deltaTime, float &lastFrame);
	float GetTime(float &deltaTime, float &lastFrame);

private:
	GLFWwindow* window;
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;



};
