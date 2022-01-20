#include "PlayerMove.h"

PlayerMove::PlayerMove(glm::mat4 PlayerModel)
	:PlayerModel(PlayerModel)
{
}

glm::mat4 PlayerMove::processInput(GLFWwindow * window, float & deltaTime, float & lastFrame, glm::mat4 &PlayerModel,float &rotate)
{
	float deltatime = GetTime(deltaTime, lastFrame);
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	
	float cameraSpeed = 2.5 * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
		PlayerModel = glm::rotate(PlayerModel, glm::radians(-rotate), glm::vec3(1.0f, 1.0f, 0.0f));
		PlayerModel = glm::translate(PlayerModel, glm::vec3(0.0f, 0.0f, 0.1f));
		PlayerModel = glm::rotate(PlayerModel, glm::radians(rotate), glm::vec3(1.0f, 1.0f, 0.0f));
	}	
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS){
		PlayerModel = glm::rotate(PlayerModel, glm::radians(-rotate), glm::vec3(1.0f, 1.0f, 0.0f));
		PlayerModel = glm::translate(PlayerModel, glm::vec3(0.0f, 0.0f, -0.1f));
		PlayerModel = glm::rotate(PlayerModel, glm::radians(rotate), glm::vec3(1.0f, 1.0f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS){
		PlayerModel = glm::rotate(PlayerModel, glm::radians(-rotate), glm::vec3(1.0f, 1.0f, 0.0f));
		PlayerModel = glm::translate(PlayerModel, glm::vec3(-0.1f, 0.0f, 0.0f));
		PlayerModel = glm::rotate(PlayerModel, glm::radians(rotate), glm::vec3(1.0f, 1.0f, 0.0f));
	}	
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS){
		PlayerModel = glm::rotate(PlayerModel, glm::radians(-rotate), glm::vec3(1.0f, 1.0f, 0.0f));
		PlayerModel = glm::translate(PlayerModel, glm::vec3(0.1f, 0.0f, 0.0f));
		PlayerModel = glm::rotate(PlayerModel, glm::radians(rotate), glm::vec3(1.0f, 1.0f, 0.0f));
	}
	return PlayerModel;

}

float PlayerMove::GetTime(float & deltaTime, float & lastFrame)
{
	float currentFrame = glfwGetTime();

	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	return deltaTime;
}
