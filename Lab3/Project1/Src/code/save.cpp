//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
//#include<string>
//#include <cstdlib>
//#include<glm/gtx/vector_angle.hpp>
//
//#include"VertexBuffer.h"
//#include"VertexArray.h"
//#include"VertexBufferLayout.h"
//#include"IndexBuffer.h"
//#include"Renderer.h"
//#include"Texture.h"
//#include"Keyboard.h"
//#include"Mesh.h"
//#include"Model.h"
//#include"PlayerMove.h"
//#include"std_image/stb_image.h"
//#include"CubemapTexture.h"
//#include"Terrain.h"
//#include"Reticle.h"
//
//const unsigned int SCR_WIDTH = 1920;
//const unsigned int SCR_HEIGHT = 1080;
//glm::vec3 cameraPos;
//glm::vec3 cameraFront;
//glm::vec3 cameraUp;
//
//glm::vec3 cameraPos0 = glm::vec3(1.0f, 3.0f, 1.0f);
//glm::vec3 cameraFront0 = glm::vec3(0.0f, 0.0f, 1.0f);
//glm::vec3 cameraUp0 = glm::vec3(0.0f, 1.0f, 0.0f);
//
//glm::vec3 cameraPos1 = glm::vec3(10.0f, 10.0f, 10.0f);
//glm::vec3 cameraFront1 = glm::vec3(0.0f, 0.0f, 1.0f);
//glm::vec3 cameraUp1 = glm::vec3(0.0f, 1.0f, 0.0f);
//int isMainCamera = 0;
//bool isPpreesed0 = false;
//bool isPpreesed1 = false;
//
//bool isWin = false;
//bool isFalse = false;
//
//float deltRotate = 0.0f;
//float deltRotatey = 0.0f;
//float deltGunRotatey;
//glm::vec3 lightPos(2.0f, 4.0f, 2.0f);
//GLfloat RotateZ = 0.0f;
//
//float enemyGenerateTime = 0.0f;
//int GunType = 1;
//int GunPower = 1;
//int PlayerHP = 5;
//bool firstMouse = true;
//float yaw0 = 90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
//float pitch0 = 0.0f;
//float yaw = 90.0f;
//float pitch = 0.0f;
//float lastX = 1920.0f / 2.0;
//float lastY = 1080.0f / 2.0;
//float fov = 60.0f;
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//float Speed = 0.5f;
//float deltaShootTime = 0.0f;
//float lastShootFrame = 0.0f;
//float finalHeight;
//std::vector<glm::mat4> Bullet;
//std::vector<glm::vec3> BulletPosition;
//std::vector<glm::vec3> BulletDirection;
//std::vector<glm::mat4> Enemy;
//struct Enemy_Property {
//	glm::vec3 enemyPosition;
//	float x, y, z;
//	int HP = 5;
//};
//struct Prop_Property {
//	glm::mat4 initProperty;
//	float x, y, z;
//	int type;
//};
//std::vector<Enemy_Property> enemyProperty;
//std::vector<Prop_Property> propProperty;
////struct EnemyProperty enemyProperty[300];
//void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//	glViewport(0, 0, width, height);
//}
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	float xoffset0;
//	float yoffset0;
//	float xoffset;
//	float yoffset;
//	glm::vec3 front0;
//	glm::vec3 front;
//	if (isMainCamera % 2) {
//		if (firstMouse)
//		{
//			lastX = xpos;
//			lastY = ypos;
//			firstMouse = false;
//		}
//
//		xoffset0 = xpos - lastX;
//		yoffset0 = lastY - ypos; // reversed since y-coordinates go from bottom to top
//		lastX = xpos;
//		lastY = ypos;
//
//		float sensitivity = 0.1f; // change this value to your liking
//		xoffset0 *= sensitivity;
//		yoffset0 *= sensitivity;
//
//		yaw0 += xoffset0;
//		pitch0 += yoffset0;
//
//		// make sure that when pitch is out of bounds, screen doesn't get flipped
//		if (pitch0 > 89.0f)
//			pitch0 = 89.0f;
//		if (pitch0 < -89.0f)
//			pitch0 = -89.0f;
//
//		front0.x = cos(glm::radians(yaw0)) * cos(glm::radians(pitch0));
//		front0.y = sin(glm::radians(pitch0));
//		front0.z = sin(glm::radians(yaw0)) * cos(glm::radians(pitch0));
//		cameraFront1 = glm::normalize(front0);
//	}
//	else {
//		//playerController
//		if (firstMouse)
//		{
//			lastX = xpos;
//			lastY = ypos;
//			firstMouse = false;
//		}
//
//		xoffset = xpos - lastX;
//		yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//		lastX = xpos;
//		lastY = ypos;
//
//		float sensitivity = 0.1f; // change this value to your liking
//		xoffset *= sensitivity;
//		yoffset *= sensitivity;
//
//		yaw += xoffset;
//		pitch += yoffset;
//
//		// make sure that when pitch is out of bounds, screen doesn't get flipped
//		if (pitch > 89.0f)
//			pitch = 89.0f;
//		if (pitch < -89.0f)
//			pitch = -89.0f;
//		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
//		front.y = sin(glm::radians(pitch));
//		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//		cameraFront0 = glm::normalize(front);
//		deltRotate = -yaw;
//		deltRotatey = -pitch;
//		//deltGunRotatey = deltRotatey;
//	}
//
//}
//void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
//{
//	float currentFrame = glfwGetTime();
//	deltaShootTime = currentFrame - lastShootFrame;
//	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
//		if (deltaShootTime > 0.5f) {
//			deltGunRotatey = deltRotatey - 5;
//			glm::mat4 bulletModel = glm::mat4(1.0f);
//			bulletModel = glm::translate(bulletModel, cameraPos0);
//			bulletModel = glm::rotate(bulletModel, glm::radians(deltRotate + 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//			bulletModel = glm::rotate(bulletModel, glm::radians(deltRotatey), glm::vec3(1.0f, 0.0f, 0.0f));
//			bulletModel = glm::translate(bulletModel, glm::vec3(0.0f, 0.0f, 0.5f));
//			bulletModel = glm::rotate(bulletModel, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//			bulletModel = glm::scale(bulletModel, glm::vec3(0.01f));
//			Bullet.push_back(bulletModel);
//			glm::vec3 Position = cameraPos0 + 0.1f*cameraFront0;
//			BulletPosition.push_back(Position);
//			BulletDirection.push_back(cameraFront0);
//			lastShootFrame = currentFrame;
//		}
//
//		//std::cout << "press" << std::endl;
//	}
//}
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//	fov -= (float)yoffset;
//	if (fov < 1.0f)
//		fov = 1.0f;
//	if (fov > 45.0f)
//		fov = 45.0f;
//}
//void processInput(GLFWwindow *window, Terrain terrain)
//{
//	float currentFrame = glfwGetTime();
//
//	deltaTime = currentFrame - lastFrame;
//	lastFrame = currentFrame;
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//	float cameraSpeed = Speed * deltaTime;
//
//	if (!(isMainCamera % 2))
//	{
//		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
//			isPpreesed0 = true;
//		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE && isPpreesed0 == true) {
//			isPpreesed0 = false;
//			isMainCamera++;
//		}
//		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//			cameraPos0 += cameraSpeed * cameraFront0;
//		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//			cameraPos0 -= cameraSpeed * cameraFront0;
//		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//			cameraPos0 -= glm::normalize(glm::cross(cameraFront0, cameraUp0)) * cameraSpeed;
//		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//			cameraPos0 += glm::normalize(glm::cross(cameraFront0, cameraUp0)) * cameraSpeed;
//		if (cameraPos0.x < 1.0f)
//			cameraPos0.x = 1.0f;
//		if (cameraPos0.z < 1.0f)
//			cameraPos0.z = 1.0f;
//
//		float xLower = (float)(int)(cameraPos0.x * 10) / 10;
//		float xHigher = xLower + 0.1;
//		float zLower = (float)(int)(cameraPos0.z * 10) / 10;
//		float zHigher = zLower + 0.1;
//		float xRelative = (cameraPos0.x - xLower) / (xHigher - xLower);
//		float zRelative = (cameraPos0.z - zLower) / (zHigher - zLower);
//
//		int LD = (xLower * 10 + zLower * 10 * 1600);
//		int LU = LD + 1;
//		int RD = LD + 1600;
//		int RU = LD + 1601;
//		float HeightLD = terrain.GetTerrainH(LD);
//		float HeightLU = terrain.GetTerrainH(LU);
//		float HeightRD = terrain.GetTerrainH(RD);
//		float HeightRU = terrain.GetTerrainH(RU);
//		if (xRelative + zRelative < 1) {
//			//在左下角三角形内
//			finalHeight = HeightLD;
//			finalHeight += xRelative * (HeightLU - HeightLD);
//			finalHeight += zRelative * (HeightRD - HeightLD);
//		}
//		else {
//			finalHeight = HeightRU;
//			finalHeight += (1.0f - xRelative) *(HeightLU - HeightRU);
//			finalHeight += (1.0f - zRelative) *(HeightRD - HeightRU);
//		}
//		cameraPos0.y = finalHeight + 1;
//	}
//	else {
//		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
//			isPpreesed1 = true;
//		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE && isPpreesed1 == true) {
//			isPpreesed1 = false;
//			isMainCamera++;
//		}
//		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//			cameraPos1 += cameraSpeed * cameraFront1;
//		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//			cameraPos1 -= cameraSpeed * cameraFront1;
//		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//			cameraPos1 -= glm::normalize(glm::cross(cameraFront1, cameraUp1)) * cameraSpeed;
//		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//			cameraPos1 += glm::normalize(glm::cross(cameraFront1, cameraUp1)) * cameraSpeed;
//	}
//
//}
//int main(void)
//{
//	GLFWwindow* window;
//	if (!glfwInit())
//		return -1;
//	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LingFengZhang", NULL, NULL);
//	if (!window) {
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//	glfwSwapInterval(3);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//	glfwSetMouseButtonCallback(window, mouse_button_callback);
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//close mouse
//	if (glewInit() != GLEW_OK)
//		std::cout << "error!" << std::endl;
//	glEnable(GL_DEPTH_TEST);
//	GLfloat vertices[] = {
//		//vertics        
//	-0.5f, -0.5f, -0.5f,
//	 0.5f, -0.5f, -0.5f,
//	 0.5f,  0.5f, -0.5f,
//	 0.5f,  0.5f, -0.5f,
//	-0.5f,  0.5f, -0.5f,
//	-0.5f, -0.5f, -0.5f,
//
//	-0.5f, -0.5f,  0.5f,
//	 0.5f, -0.5f,  0.5f,
//	 0.5f,  0.5f,  0.5f,
//	 0.5f,  0.5f,  0.5f,
//	-0.5f,  0.5f,  0.5f,
//	-0.5f, -0.5f,  0.5f,
//
//	-0.5f,  0.5f,  0.5f,
//	-0.5f,  0.5f, -0.5f,
//	-0.5f, -0.5f, -0.5f,
//	-0.5f, -0.5f, -0.5f,
//	-0.5f, -0.5f,  0.5f,
//	-0.5f,  0.5f,  0.5f,
//
//	 0.5f,  0.5f,  0.5f,
//	 0.5f,  0.5f, -0.5f,
//	 0.5f, -0.5f, -0.5f,
//	 0.5f, -0.5f, -0.5f,
//	 0.5f, -0.5f,  0.5f,
//	 0.5f,  0.5f,  0.5f,
//
//	-0.5f, -0.5f, -0.5f,
//	 0.5f, -0.5f, -0.5f,
//	 0.5f, -0.5f,  0.5f,
//	 0.5f, -0.5f,  0.5f,
//	-0.5f, -0.5f,  0.5f,
//	-0.5f, -0.5f, -0.5f,
//
//	-0.5f,  0.5f, -0.5f,
//	 0.5f,  0.5f, -0.5f,
//	 0.5f,  0.5f,  0.5f,
//	 0.5f,  0.5f,  0.5f,
//	-0.5f,  0.5f,  0.5f,
//	-0.5f,  0.5f, -0.5f,
//	};
//	glm::vec3 PointLightPositions[] =
//	{
//		glm::vec3(-3.0f,  5.0f,  -3.0f)
//		/*glm::vec3(2.0f,  7.0f, 15.0f),
//		glm::vec3(5.5f, 8.5f, 22.5f),
//		glm::vec3(10.8f, 6.0f, 30.0f),
//		glm::vec3(15.8f, 6.0f, 60.0f),
//		glm::vec3(25.8f, 6.0f, 40.0f),
//		glm::vec3(35.8f, 6.0f, 80.0f),
//		glm::vec3(40.8f, 6.0f, 15.0f),
//		glm::vec3(60.8f, 6.0f, 70.0f),
//		glm::vec3(70.8f, 6.0f, 50.0f),
//		glm::vec3(80.8f, 6.0f, 8.0f),
//		glm::vec3(90.8f, 6.0f, 90.0f),
//		glm::vec3(100.8f, 6.0f, 66.0f),
//		glm::vec3(120.8f, 6.0f, 12.0f),
//		glm::vec3(150.8f, 6.0f, 110.0f),
//		glm::vec3(130.8f, 6.0f, 10.0f),
//		glm::vec3(33.8f, 6.0f, 50.0f),
//		glm::vec3(66.8f, 6.0f, 10.0f),
//		glm::vec3(99.8f, 6.0f, 4.0f),
//		glm::vec3(110.8f, 6.0f, 30.0f)*/
//
//	};
//	GLfloat skyboxVertices[] = {
//		// 位置          
//		-1.0f,  1.0f, -1.0f,
//		-1.0f, -1.0f, -1.0f,
//		1.0f, -1.0f, -1.0f,
//		1.0f, -1.0f, -1.0f,
//		1.0f,  1.0f, -1.0f,
//		-1.0f,  1.0f, -1.0f,
//
//		-1.0f, -1.0f,  1.0f,
//		-1.0f, -1.0f, -1.0f,
//		-1.0f,  1.0f, -1.0f,
//		-1.0f,  1.0f, -1.0f,
//		-1.0f,  1.0f,  1.0f,
//		-1.0f, -1.0f,  1.0f,
//
//		1.0f, -1.0f, -1.0f,
//		1.0f, -1.0f,  1.0f,
//		1.0f,  1.0f,  1.0f,
//		1.0f,  1.0f,  1.0f,
//		1.0f,  1.0f, -1.0f,
//		1.0f, -1.0f, -1.0f,
//
//		-1.0f, -1.0f,  1.0f,
//		-1.0f,  1.0f,  1.0f,
//		1.0f,  1.0f,  1.0f,
//		1.0f,  1.0f,  1.0f,
//		1.0f, -1.0f,  1.0f,
//		-1.0f, -1.0f,  1.0f,
//
//		-1.0f,  1.0f, -1.0f,
//		1.0f,  1.0f, -1.0f,
//		1.0f,  1.0f,  1.0f,
//		1.0f,  1.0f,  1.0f,
//		-1.0f,  1.0f,  1.0f,
//		-1.0f,  1.0f, -1.0f,
//
//		-1.0f, -1.0f, -1.0f,
//		-1.0f, -1.0f,  1.0f,
//		1.0f, -1.0f, -1.0f,
//		1.0f, -1.0f, -1.0f,
//		-1.0f, -1.0f,  1.0f,
//		1.0f, -1.0f,  1.0f
//	};
//	GLfloat reticleVertices[] =
//	{
//		-0.5f,0.5f,0.0f,
//		-0.5f,-0.5f,0.0f,
//		0.5f,0.5f,0.0f,
//		0.5f,0.5f,0.0f,
//		-0.5f,-0.5f,0.0f,
//		0.5f,-0.5f,0.0f
//	};
//	std::vector<std::string> faces
//	{
//		"Src/vendor/Model/skybox2/right.png",
//		"Src/vendor/Model/skybox2/left.png",
//		"Src/vendor/Model/skybox2/top.png",
//		"Src/vendor/Model/skybox2/bottom.png",
//		"Src/vendor/Model/skybox2/front.png",
//		"Src/vendor/Model/skybox2/back.png"
//	};
//	GLfloat imageVertices[] = {
//		-1.0f,-1.0f,0.0f,0.0f,
//		 1.0f,-1.0f,1.0f,0.0f,
//		 1.0f,1.0f,1.0f,1.0f,
//		-1.0f,1.0f,0.0f,1.0f,
//	};
//	unsigned int imageIndices[] = {
//		0,1,2,
//		2,3,0
//	};
//
//	//LIGHT 
//	VertexArray lightVA;
//	Shader lightShader("res/shader/light.shader");
//	VertexBuffer lightVertex(vertices, 3 * 6 * 6);
//	VertexBufferLayout lightLayout;
//	lightLayout.Push<float>(3);
//	lightVA.AddBuffer(lightVertex, lightLayout);
//	//SKY BOX
//	VertexArray va;
//	CubemapTexture skybox(faces);
//	Shader SkyboxShader("res/shader/Skybox.shader");
//	VertexBuffer skyboxVertex(skyboxVertices, 18 * 6);
//	VertexBufferLayout skyboxLayout;
//	skyboxLayout.Push<float>(3);
//	va.AddBuffer(skyboxVertex, skyboxLayout);
//	glm::mat4 skyboxModel = glm::mat4(1.0f);
//	skyboxModel = glm::scale(skyboxModel, glm::vec3(50.0f));
//	//Reticle
//	VertexArray vaReticle;
//	Shader ReticelShader("res/shader/Reticle.shader");
//	VertexBuffer reticleVertex(reticleVertices, 3 * 6);
//	VertexBufferLayout reticleLayout;
//	reticleLayout.Push<float>(3);
//	vaReticle.AddBuffer(reticleVertex, reticleLayout);
//	//Trrain
//	Terrain terrain("Src/vendor/Model/jotunheimen.png", "Src/vendor/Model/Terrain_texture.jpg",
//		"Src/vendor/Model/Terrain_ambient.jpg", "Src/vendor/Model/Terrain_normal.jpg");
//	Texture rock("Src/vendor/Model/Terrain_texture.jpg");
//	Shader depthShader("res/shader/depth.shader");
//	Shader terrainShader("res/shader/shadow.shader");
//	terrainShader.SetUniform1i("terrainTexture", 0);
//	terrainShader.SetUniform1i("shadowMap", 1);
//	//terrainLightSet
//	{
//		terrainShader.SetUniform3f("dirLight.position", 0.0f, 0.0f, 0.0f);
//		terrainShader.SetUniform3f("dirLight.ambient", 0.3f, 0.3f, 0.3f);
//		terrainShader.SetUniform3f("dirLight.diffuse", 0.2f, 0.2f, 0.2f);
//		terrainShader.SetUniform3f("dirLight.specular", 0.5f, 0.5f, 0.5f);
//		std::string Position, Ambient, Diffuse, Specular, Constant, Linear, Quadratic;
//		for (int i = 0; i < 20; i++)
//		{
//			std::stringstream position, ambient, diffuse, specular, constant, linear, quadratic;
//			position << "pointLights[" << i << "].position"; Position = position.str();
//			ambient << "pointLights[" << i << "].ambient"; Ambient = ambient.str();
//			diffuse << "pointLights[" << i << "].diffuse"; Diffuse = diffuse.str();
//			specular << "pointLights[" << i << "].specular"; Specular = specular.str();
//			constant << "pointLights[" << i << "].constant"; Constant = constant.str();
//			linear << "pointLights[" << i << "].linear"; Linear = linear.str();
//			quadratic << "pointLights[" << i << "].quadratic"; Quadratic = quadratic.str();
//
//			terrainShader.SetUniformVec3(Position, PointLightPositions[i]);
//			terrainShader.SetUniform3f(Ambient, 0.2f, 0.2f, 0.2f);
//			terrainShader.SetUniform3f(Diffuse, 0.1f, 0.1f, 0.1f);
//			terrainShader.SetUniform3f(Specular, 1.0f, 1.0f, 1.0f);
//			terrainShader.SetUniformf(Constant, 1.0f);
//			terrainShader.SetUniformf(Linear, 0.09f);
//			terrainShader.SetUniformf(Quadratic, 0.032f);
//		}
//		terrainShader.SetUniformf("shininess", 16.0f);
//	}
//	glm::mat4 MVP = glm::mat4(1.0f);
//	//PlayerModel
//	Model playerModel("Src/vendor/Model/nanosuit/nanosuit.obj");
//	Model batteryModel("Src/vendor/Model/battery/13468_12_Volt_Economy_Battery_v1_L3.obj");
//	Model shoesModel("Src/vendor/Model/shoes/shoes.obj");
//	Model handGunModel("Src/vendor/Model/gun/obj/Handgun_obj.obj");
//	Model laserGunModel("Src/vendor/Model/gun/Laser_Rifle/13894_Laser_Rifle_V1_l2.obj");
//	Model crownModel("Src/vendor/Model/crown/crown.obj");
//
//	Model spiderModel("Src/vendor/Model/spider/Only_Spider_with_Animations_Export.obj");
//	Shader propShader("res/shader/prop.shader");
//	Shader ModelShader("res/shader/Modelshader.shader");
//
//	Model bullet("Src/vendor/Model/45.obj");
//	//ModelLightSet
//	{
//		ModelShader.SetUniform3f("dirLight.position", 0.0f, 0.0f, 0.0f);
//		ModelShader.SetUniform3f("dirLight.ambient", 0.05f, 0.05f, 0.05f);
//		ModelShader.SetUniform3f("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
//		ModelShader.SetUniform3f("dirLight.specular", 0.5f, 0.5f, 0.5f);
//
//		ModelShader.SetUniformVec3("pointLights[0].position", PointLightPositions[0]);
//		ModelShader.SetUniform3f("pointLights[0].ambient", 0.2f, 0.2f, 0.2f);
//		ModelShader.SetUniform3f("pointLights[0].diffuse", 0.1f, 0.1f, 0.1f);
//		ModelShader.SetUniform3f("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
//		ModelShader.SetUniformf("pointLights[0].constant", 1.0f);
//		ModelShader.SetUniformf("pointLights[0].linear", 0.09f);
//		ModelShader.SetUniformf("pointLights[0].quadratic", 0.032f);
//		ModelShader.SetUniformVec3("pointLights[1].position", PointLightPositions[1]);
//		ModelShader.SetUniform3f("pointLights[1].ambient", 0.2f, 0.2f, 0.2f);
//		ModelShader.SetUniform3f("pointLights[1].diffuse", 0.1f, 0.1f, 0.1f);
//		ModelShader.SetUniform3f("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
//		ModelShader.SetUniformf("pointLights[1].constant", 1.0f);
//		ModelShader.SetUniformf("pointLights[1].linear", 0.09f);
//		ModelShader.SetUniformf("pointLights[1].quadratic", 0.032f);
//		ModelShader.SetUniformVec3("pointLights[2].position", PointLightPositions[2]);
//		ModelShader.SetUniform3f("pointLights[2].ambient", 0.2f, 0.2f, 0.2f);
//		ModelShader.SetUniform3f("pointLights[2].diffuse", 0.1f, 0.1f, 0.1f);
//		ModelShader.SetUniform3f("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
//		ModelShader.SetUniformf("pointLights[2].constant", 1.0f);
//		ModelShader.SetUniformf("pointLights[2].linear", 0.09f);
//		ModelShader.SetUniformf("pointLights[2].quadratic", 0.032f);
//		ModelShader.SetUniformVec3("pointLights[3].position", PointLightPositions[3]);
//		ModelShader.SetUniform3f("pointLights[3].ambient", 0.2f, 0.2f, 0.1f);
//		ModelShader.SetUniform3f("pointLights[3].diffuse", 0.1f, 0.1f, 0.1f);
//		ModelShader.SetUniform3f("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
//		ModelShader.SetUniformf("pointLights[3].constant", 1.0f);
//		ModelShader.SetUniformf("pointLights[3].linear", 0.09f);
//		ModelShader.SetUniformf("pointLights[3].quadratic", 0.032f);
//
//		ModelShader.SetUniformf("shininess", 16.0f);
//	}
//	//Image
//	VertexArray ImageVA;
//	Shader imageShader("res/shader/image.shader");
//	Texture gameover("Src/vendor/Model/gameover.jpg");
//	Texture gamewin("Src/vendor/Model/win.jpg");
//	VertexBuffer ImageVertex(imageVertices, 4 * 6);
//	IndexBuffer imageIB(imageIndices, 6);
//	VertexBufferLayout ImageLayout;
//	ImageLayout.Push<float>(2);
//	ImageLayout.Push<float>(2);
//	ImageVA.AddBuffer(ImageVertex, ImageLayout);
//	gameover.Bind();
//	imageShader.SetUniform1i("u_Texture", 0);
//	//prop set
//	{
//	Prop_Property prop;
//	glm::mat4 shoes = glm::mat4(1.0f);
//	shoes = glm::translate(shoes, glm::vec3(5.0f, 4.0f, 5.0f));
//	prop.x = 5.0f; prop.y = 4.0f; prop.z = 5.0f; prop.type = 2;
//	shoes = glm::scale(shoes, glm::vec3(0.05f));
//	prop.initProperty = shoes;
//	propProperty.push_back(prop);
//
//	glm::mat4 lasergun = glm::mat4(1.0f);
//	lasergun = glm::translate(lasergun, glm::vec3(3.0f, 4.0f, 5.0f));
//	lasergun = glm::rotate(lasergun, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
//	prop.x = 3.0f; prop.y = 4.0f; prop.z = 5.0f; prop.type = 3;
//	lasergun = glm::scale(lasergun, glm::vec3(0.01f));
//	prop.initProperty = lasergun;
//	propProperty.push_back(prop);
//
//	glm::mat4 baby = glm::mat4(1.0f);
//	baby = glm::translate(baby, glm::vec3(2.0f, 4.0f, 2.0f));
//	baby = glm::rotate(baby, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
//	prop.x = 2.0f; prop.y = 4.0f; prop.z = 2.0f; prop.type = 4;
//	baby = glm::scale(baby, glm::vec3(0.01f));
//	prop.initProperty = baby;
//	propProperty.push_back(prop);
//	for (int i = 0; i < 30; i++) {
//		glm::mat4 battery = glm::mat4(1.0f);
//		//生成[a,b]的随机数
//		int a = 10, b = 1590;
//		float x = 0, z = 0;
//		x = (float)(rand() % (b - a + 1) + a) / 10;
//		z = (float)(rand() % (b - a + 1) + a) / 10;
//		int index = (x * 10 + z * 10 * 1600);
//		float initialHeight = terrain.GetTerrainH(index);
//		battery = glm::translate(battery, glm::vec3(x, initialHeight, z));
//		battery = glm::rotate(battery, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
//		battery = glm::scale(battery, glm::vec3(0.02f));
//
//		prop.x = x; prop.y = initialHeight; prop.z = z; prop.type = 1;
//		prop.initProperty = battery;
//		propProperty.push_back(prop);
//	}
//	}
//	
//
//	Renderer renderer;
//	//enemy generate
//	for (int i = 0; i < 20; i++)
//	{
//		//生成[a,b]的随机数
//		int a = 20, b = 150;
//		float x = 0, z = 0;
//		x = (float)(rand() % (b - a + 1) + a) / 10 + cameraPos0.x;
//		z = (float)(rand() % (b - a + 1) + a) / 10 + cameraPos0.z;
//
//		int index = (x * 10 + z * 10 * 1600);
//		float initialHeight = terrain.GetTerrainH(index);
//		glm::mat4 enemyMatrix = glm::mat4(1.0f);
//		enemyMatrix = glm::translate(enemyMatrix, glm::vec3(x, initialHeight, z));//x,y,z
//		enemyMatrix = glm::scale(enemyMatrix, glm::vec3(0.01f));
//		Enemy.push_back(enemyMatrix);
//		glm::vec3 enemyPosition = glm::vec3(x, initialHeight, z);
//		Enemy_Property property;
//		property.enemyPosition = enemyPosition;
//		property.x = x;
//		property.y = initialHeight;
//		property.z = z;
//		enemyProperty.push_back(property);
//	}
//	//Deepmap
//	unsigned int depthMapFBO;
//	glGenFramebuffers(1, &depthMapFBO);
//	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
//
//	unsigned int depthMap;
//	glGenTextures(1, &depthMap);
//	glBindTexture(GL_TEXTURE_2D, depthMap);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//
//	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
//	glDrawBuffer(GL_NONE);
//	glReadBuffer(GL_NONE);
//
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//	while (!glfwWindowShouldClose(window))
//	{
//		glfwSetCursorPosCallback(window, mouse_callback);
//		//cameraPos0=keyboard.processInput(window,deltaTime,lastFrame);
//		processInput(window, terrain);
//		glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 5000.0f);
//		/* Render here */
//		renderer.Clear();
//		glm::mat4 view;
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		glm::mat4 lightProjection, lightView;
//		glm::mat4 lightSpaceMatrix;
//		float near_plane = 1.0f, far_plane = 7.5f;
//		lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
//		lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
//		lightSpaceMatrix = lightProjection * lightView;
//		depthShader.Bind();
//		depthShader.SetUniformMat4f("lightSpaceMatrix", lightSpaceMatrix);
//
//		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
//		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
//		glClear(GL_DEPTH_BUFFER_BIT);
//		glm::mat4 modelTerrain = glm::mat4(1.0f);
//		depthShader.SetUniformMat4f("model", modelTerrain);
//		terrain.draw(depthShader, rock);
//		for (int i = 0; i < Enemy.size(); i++) {
//			glm::mat4 enemyMatrix = glm::mat4(1.0f);
//			enemyMatrix = glm::translate(enemyMatrix, glm::vec3(enemyProperty[i].x, enemyProperty[i].y, enemyProperty[i].z));
//			enemyMatrix = glm::scale(enemyMatrix, glm::vec3(0.005f));
//
//			depthShader.SetUniformMat4f("model", enemyMatrix);
//			spiderModel.Draw(depthShader);
//		}
//		glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//		//reset viewport
//		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		if (!isWin && !isFalse) {
//
//			if (isMainCamera % 2) {
//				view = glm::lookAt(cameraPos1, cameraPos1 + cameraFront1, cameraUp1);
//			}
//			else
//				view = glm::lookAt(cameraPos0, cameraPos0 + cameraFront0, cameraUp0);
//			//enemy
//			ModelShader.Bind();
//			for (int i = 0; i < Enemy.size(); i++) {
//				glm::mat4 enemyMatrix = glm::mat4(1.0f);
//				enemyMatrix = glm::translate(enemyMatrix, glm::vec3(enemyProperty[i].x, enemyProperty[i].y, enemyProperty[i].z));
//				enemyMatrix = glm::scale(enemyMatrix, glm::vec3(0.005f));
//				ModelShader.SetUniformMat4f("model", enemyMatrix);
//				ModelShader.SetUniformMat4f("view", view);
//				ModelShader.SetUniformMat4f("projection", projection);
//				spiderModel.Draw(ModelShader);
//			}
//			//PlayerModel
//			{
//				ModelShader.Bind();
//				glm::mat4 modelSpider = glm::mat4(1.0f);
//				modelSpider = glm::translate(modelSpider, cameraPos0);
//				//modelSpider = glm::rotate(modelSpider, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//				modelSpider = glm::rotate(modelSpider, glm::radians(deltRotate + 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//				modelSpider = glm::translate(modelSpider, glm::vec3(0.0f, -1.0f, -0.1f));
//				modelSpider = glm::scale(modelSpider, glm::vec3(0.08f));
//				ModelShader.SetUniformMat4f("model", modelSpider);
//				ModelShader.SetUniformMat4f("view", view);
//				ModelShader.SetUniformMat4f("projection", projection);
//				playerModel.Draw(ModelShader);
//				//Gunmodel
//				glm::mat4 handGun = glm::mat4(1.0f);
//				handGun = glm::translate(handGun, cameraPos0);
//				handGun = glm::rotate(handGun, glm::radians(deltRotate + 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//				handGun = glm::rotate(handGun, glm::radians(deltGunRotatey), glm::vec3(1.0f, 0.0f, 0.0f));
//				deltGunRotatey = deltRotatey;
//				if (GunType == 1) {
//					handGun = glm::translate(handGun, glm::vec3(0.0f, -0.1f, 0.2f));
//					handGun = glm::rotate(handGun, glm::radians(-75.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//					handGun = glm::scale(handGun, glm::vec3(0.01f));
//					ModelShader.SetUniformMat4f("model", handGun);
//					ModelShader.SetUniformMat4f("view", view);
//					ModelShader.SetUniformMat4f("projection", projection);
//					handGunModel.Draw(ModelShader);
//				}
//				else if (GunType == 2) {
//					handGun = glm::translate(handGun, glm::vec3(0.0f, -0.1f, 0.2f));
//					handGun = glm::rotate(handGun, glm::radians(-80.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//					handGun = glm::scale(handGun, glm::vec3(0.01f));
//					ModelShader.SetUniformMat4f("model", handGun);
//					ModelShader.SetUniformMat4f("view", view);
//					ModelShader.SetUniformMat4f("projection", projection);
//					laserGunModel.Draw(ModelShader);
//				}}
//			//prop
//			for (int i = 0; i < propProperty.size(); i++) {
//				if (propProperty[i].type == 2) {
//					propShader.Bind();
//					propProperty[i].initProperty = glm::rotate(propProperty[i].initProperty, glm::radians(5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//					propShader.SetUniformMat4f("model", propProperty[i].initProperty);
//					propShader.SetUniformMat4f("view", view);
//					propShader.SetUniformMat4f("projection", projection);
//					shoesModel.Draw(propShader);
//				}
//				if (propProperty[i].type == 1) {
//					ModelShader.Bind();
//					propProperty[i].initProperty = glm::rotate(propProperty[i].initProperty, glm::radians(5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
//					ModelShader.SetUniformMat4f("model", propProperty[i].initProperty);
//					ModelShader.SetUniformMat4f("view", view);
//					ModelShader.SetUniformMat4f("projection", projection);
//					batteryModel.Draw(ModelShader);
//				}
//				if (propProperty[i].type == 3) {
//					ModelShader.Bind();
//					propProperty[i].initProperty = glm::rotate(propProperty[i].initProperty, glm::radians(5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
//					ModelShader.SetUniformMat4f("model", propProperty[i].initProperty);
//					ModelShader.SetUniformMat4f("view", view);
//					ModelShader.SetUniformMat4f("projection", projection);
//					laserGunModel.Draw(ModelShader);
//				}
//				if (propProperty[i].type == 4) {
//					ModelShader.Bind();
//					propProperty[i].initProperty = glm::rotate(propProperty[i].initProperty, glm::radians(5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
//					ModelShader.SetUniformMat4f("model", propProperty[i].initProperty);
//					ModelShader.SetUniformMat4f("view", view);
//					ModelShader.SetUniformMat4f("projection", projection);
//					crownModel.Draw(ModelShader);
//				}
//			}
//			//Contact
//			for (int k = 0; k < propProperty.size(); k++) {
//				if (cameraPos0.z < propProperty[k].z + 0.2f && cameraPos0.z > propProperty[k].z - 0.2f&& cameraPos0.x < propProperty[k].x + 0.2f && cameraPos0.x > propProperty[k].x - 0.2f&&cameraPos0.y < propProperty[k].y + 1.0f && cameraPos0.y > propProperty[k].y - 1.0f)
//					if (propProperty[k].type == 2)
//					{
//						Speed = 1.0f;
//						propProperty.erase(propProperty.begin() + k);
//					}
//					else if (propProperty[k].type == 1)
//					{
//						if (PlayerHP < 5) {
//							PlayerHP += 1;
//						}
//						propProperty.erase(propProperty.begin() + k);
//					}
//					else if (propProperty[k].type == 3)
//					{
//						GunType = 2;
//						GunPower = 5;
//						propProperty.erase(propProperty.begin() + k);
//					}
//					else if (propProperty[k].type == 4)
//					{
//						isWin = true;
//					}
//
//			}
//			for (int k = 0; k < Enemy.size(); k++) {
//				if (cameraPos0.z < enemyProperty[k].z + 0.2f && cameraPos0.z > enemyProperty[k].z - 0.2f
//					&& cameraPos0.x < enemyProperty[k].x + 0.2f && cameraPos0.x > enemyProperty[k].x - 0.2f
//					&&cameraPos0.y < enemyProperty[k].y + 1.0f && cameraPos0.y > enemyProperty[k].y - 1.0f)
//				{
//					PlayerHP--;
//					if (PlayerHP == 0)
//						isFalse = true;
//					Enemy.erase(Enemy.begin() + k);
//					enemyProperty.erase(enemyProperty.begin() + k);
//				}
//			}
//			//Bullet
//			for (int i = 0; i < Bullet.size(); i++)
//			{
//				bool hit = false;
//				Bullet[i] = glm::translate(Bullet[i], glm::vec3(0.0f, 30.0f, 0.0f));
//				ModelShader.SetUniformMat4f("model", Bullet[i]);
//				ModelShader.SetUniformMat4f("view", view);
//				ModelShader.SetUniformMat4f("projection", projection);
//				bullet.Draw(ModelShader);
//				for (int j = 0; j < 100; j++) {
//					BulletPosition[i] = BulletPosition[i] + BulletDirection[i] * 0.5f;
//					//子弹越界，删除
//					if (BulletPosition[i].x > 160 || BulletPosition[i].x < -5 || BulletPosition[i].y>30 || BulletPosition[i].y < -15 || BulletPosition[i].z>160 || BulletPosition[i].z < -5) {
//						BulletPosition.erase(BulletPosition.begin() + i);
//						BulletDirection.erase(BulletDirection.begin() + i);
//						Bullet.erase(Bullet.begin() + i);
//						break;
//					}
//					if (Bullet.size() > 0) {
//						for (int k = 0; k < Enemy.size(); k++) {
//							if (BulletPosition[i].z < enemyProperty[k].z + 0.5f && BulletPosition[i].z > enemyProperty[k].z - 0.5f
//								&& BulletPosition[i].x < enemyProperty[k].x + 0.5f && BulletPosition[i].x > enemyProperty[k].x - 0.5f
//								&&BulletPosition[i].y < enemyProperty[k].y + 0.5f && BulletPosition[i].y > enemyProperty[k].y - 0.5f)
//							{
//								enemyProperty[k].HP -= GunPower;
//								if (enemyProperty[k].HP == 0) {
//									Enemy.erase(Enemy.begin() + k);
//									enemyProperty.erase(enemyProperty.begin() + k);
//								}
//								hit = true;
//								BulletPosition.erase(BulletPosition.begin() + i);
//								BulletDirection.erase(BulletDirection.begin() + i);
//								Bullet.erase(Bullet.begin() + i);
//								break;
//							}
//						}
//					}
//					if (hit)
//						break;
//				}
//			}
//
//			//Terrain
//			terrainShader.Bind();
//			glm::mat4 modelTerrain = glm::mat4(1.0f);
//			terrainShader.SetUniformMat4f("model", modelTerrain);
//			terrainShader.SetUniformMat4f("view", view);
//			terrainShader.SetUniformMat4f("projection", projection);
//			terrainShader.SetUniformMat4f("lightSpaceMatrix", lightSpaceMatrix);
//			terrain.drawDepth(terrainShader, rock, depthMap);
//
//			//Reticle
//			{
//				vaReticle.Bind();
//				ReticelShader.Bind();
//				glm::mat4 modelReticel = glm::mat4(1.0f);
//				glm::mat4 newmodelReticel = glm::mat4(1.0f);
//				modelReticel = glm::translate(modelReticel, cameraPos0);
//				modelReticel = glm::rotate(modelReticel, glm::radians(deltRotate + 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//				modelReticel = glm::rotate(modelReticel, glm::radians(deltRotatey), glm::vec3(1.0f, 0.0f, 0.0f));
//
//				newmodelReticel = glm::translate(modelReticel, glm::vec3(0.0f, 0.01f, 0.5f));
//				newmodelReticel = glm::scale(newmodelReticel, glm::vec3(0.002f, 0.01f, 1.0f));
//				ReticelShader.SetUniformMat4f("model", newmodelReticel);
//				ReticelShader.SetUniformMat4f("view", view);
//				ReticelShader.SetUniformMat4f("projection", projection);
//				glDrawArrays(GL_TRIANGLES, 0, 6);
//				newmodelReticel = glm::translate(modelReticel, glm::vec3(0.0f, -0.01f, 0.5f));
//				newmodelReticel = glm::scale(newmodelReticel, glm::vec3(0.002f, 0.01f, 1.0f));
//				ReticelShader.SetUniformMat4f("model", newmodelReticel);
//				ReticelShader.SetUniformMat4f("view", view);
//				ReticelShader.SetUniformMat4f("projection", projection);
//				glDrawArrays(GL_TRIANGLES, 0, 6);
//				newmodelReticel = glm::translate(modelReticel, glm::vec3(0.01f, 0.0f, 0.5f));
//				newmodelReticel = glm::scale(newmodelReticel, glm::vec3(0.01f, 0.002f, 1.0f));
//				ReticelShader.SetUniformMat4f("model", newmodelReticel);
//				ReticelShader.SetUniformMat4f("view", view);
//				ReticelShader.SetUniformMat4f("projection", projection);
//				glDrawArrays(GL_TRIANGLES, 0, 6);
//				newmodelReticel = glm::translate(modelReticel, glm::vec3(-0.01f, 0.0f, 0.5f));
//				newmodelReticel = glm::scale(newmodelReticel, glm::vec3(0.01f, 0.002f, 1.0f));
//				ReticelShader.SetUniformMat4f("model", newmodelReticel);
//				ReticelShader.SetUniformMat4f("view", view);
//				ReticelShader.SetUniformMat4f("projection", projection);
//				glDrawArrays(GL_TRIANGLES, 0, 6);
//				for (int i = 0; i < PlayerHP; i++) {
//					newmodelReticel = glm::translate(modelReticel, glm::vec3(0.04f - 0.02f*i, -0.1f, 0.2f));
//					newmodelReticel = glm::scale(newmodelReticel, glm::vec3(0.02f, 0.002f, 1.0f));
//					ReticelShader.SetUniformMat4f("model", newmodelReticel);
//					ReticelShader.SetUniformMat4f("view", view);
//					ReticelShader.SetUniformMat4f("projection", projection);
//					glDrawArrays(GL_TRIANGLES, 0, 6);
//				}
//			}
//			//SkyBox
//			glDepthFunc(GL_LEQUAL);
//			SkyboxShader.Bind();
//			va.Bind();
//			skybox.Bind();
//			glm::mat4 skyboxView = glm::mat4(glm::mat3(view));
//			SkyboxShader.SetUniformMat4f("model", skyboxModel);
//			SkyboxShader.SetUniformMat4f("view", skyboxView);
//			SkyboxShader.SetUniformMat4f("projection", projection);
//			glDrawArrays(GL_TRIANGLES, 0, 36);
//			glDepthFunc(GL_LESS);
//
//		}
//		else if (isWin) {
//			gamewin.Bind();
//			imageShader.Bind();
//			ImageVA.Bind();
//			renderer.Draw(imageIB, imageShader);
//		}
//		else if (isFalse) {
//			gameover.Bind();
//			imageShader.Bind();
//			ImageVA.Bind();
//			renderer.Draw(imageIB, imageShader);
//		}
//
//		/* Swap front and back buffers */
//		glfwSwapBuffers(window);
//		/* Poll for and process events */
//		glfwPollEvents();
//	}
//	glfwTerminate();
//	return 0;
//}
//
