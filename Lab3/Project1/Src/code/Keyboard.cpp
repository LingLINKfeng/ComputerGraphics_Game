#include "Keyboard.h"

Keyboard::Keyboard(glm::vec3& cameraPos, glm::vec3& cameraFront, glm::vec3& cameraUp, GLFWwindow* window)
	:cameraPos(cameraPos), cameraFront(cameraFront), cameraUp(cameraUp),window(window)
{
}

glm::vec3  Keyboard::processInput(GLFWwindow* window, float &deltaTime,float &lastFrame)
{
	float deltatime = GetTime(deltaTime, lastFrame);
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	    
	float cameraSpeed = 2.5 * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraUp;
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraUp;
	return cameraPos;
}

float Keyboard::GetTime(float& deltaTime, float&lastFrame)
{
	float currentFrame = glfwGetTime();
	
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	return deltaTime;
}




