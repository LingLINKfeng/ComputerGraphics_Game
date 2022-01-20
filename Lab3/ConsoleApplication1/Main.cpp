#include "pch.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <fstream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Model.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
// Macro for indexing vertex buffer
#define BUFFER_OFFSET(i) ((char *)NULL + (i))
using namespace glm;
using namespace std;
//string readFile(const char* fileName);
void callback_mouse_button(int button, int state, int x, int y);
void keyboard_up(unsigned char key, int x, int y);
void keyboard_down(unsigned char key, int x, int y);
GLuint VBO;
GLuint IBO;
MeshTexture* pTexture = NULL;

const char* pFSFileName = "modelLoading.frag";
const char* pVSFileName = "modelLoading.vs";
Shader shader;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

float lookAtX = 0.0f;
float lookAtY = 0.0f;
float lookAtZ = 0.0f;

bool zooming;

static void RenderSceneCB()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader.Use();
	mat4 projection = perspective(camera.GetZoom(), 4.0f / 3.0f, 0.1f, 100.0f);

	//mat4 view = lookAt(vec3(cameraPositionX, cameraPositionY, cameraPositionZ), vec3(lookAtX, lookAtY, lookAtZ), vec3(1.0f, 1.0f, 1.0f));
	mat4 view = camera.GetViewMatrix();
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, value_ptr(projection));

	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, value_ptr(view));
	mat4 model = mat4(1.0f);
	model = translate(model, vec3(0.0f, -1.75f, 0.0f));
	model = scale(model, vec3(2.2f, 2.2f, 2.2f));
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, value_ptr(model));

	glutPostRedisplay();
	glutSwapBuffers();
}


static void InitializeGlutCallbacks()
{
	glutDisplayFunc(RenderSceneCB);
	glutIdleFunc(RenderSceneCB);
}

//static void CreateVertexBuffer()
//{
//	
//	vec2 t00 = vec2(0.0f, 0.0f); //Bottom left
//	vec2 t01 = vec2(0.0f, 1.0f); //Top left
//	vec2 t10 = vec2(1.0f, 0.0f); //Bottom right
//	vec2 t11 = vec2(1.0f, 1.0f); //Top right
//
//	Vertex Vertices[8];
//	//center
//	Vertices[0] = Vertex(vec3(0.5f, 0.5f, 0.5f),t00);
//	Vertices[1] = Vertex(vec3(-0.5f, 0.5f, -0.5f),t01);
//	Vertices[2] = Vertex(vec3(-0.5f, 0.5f, 0.5f),t10);
//	Vertices[3] = Vertex(vec3(0.5f, -0.5f, -0.5f),t11);
//	Vertices[4] = Vertex(vec3(-0.5f, -0.5f, -0.5f),t00);
//	Vertices[5] = Vertex(vec3(0.5f, 0.5f, -0.5f),t10);
//	Vertices[6] = Vertex(vec3(0.5f, -0.5f, 0.5f),t01);
//	Vertices[7] = Vertex(vec3(-0.5f, -0.5f, 0.5f),t11);
//
//	glGenBuffers(1, &VBO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, 6 * 8 * sizeof(GLfloat), Vertices, GL_STATIC_DRAW);
//}

//static void CreateIndexBuffer()
//{
//	unsigned int Indices[] = {
//							   0, 1, 2,
//							   1, 3, 4,
//							   5, 6, 3,
//							   7, 3, 6,
//							   2, 4, 7,
//							   0, 7, 6,
//							   0, 5, 1,
//							   1, 5, 3,
//							   5, 0, 6,
//							   7, 4, 3,
//							   2, 1, 4,
//							   0, 2, 7
//	};
//
//	glGenBuffers(1, &IBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * 12 * sizeof(GLuint), Indices, GL_STATIC_DRAW);
//}

int main(int argc, char** argv)
{
	srand(GetCurrentProcessId());

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1024, 1024);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("Starting opengl");

	//InitializeGlutCallbacks();

	// Must be done after glut is initialized!
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	//GLclampf Red = 0.0f, Green = 0.0f, Blue = 0.0f, Alpha = 0.0f;
	//glClearColor(Red, Green, Blue, Alpha);

	glEnable(GL_DEPTH_TEST);
	//Only front face triangles out of the cube are rendered
	glEnable(GL_CULL_FACE);//Only render the exterior of the mesh
	glFrontFace(GL_CW); //Front face are clock wise
	glCullFace(GL_BACK);

	Model ourModel((GLchar*)"nanosuit.obj");
	shader = Shader(pVSFileName, pFSFileName);


	glutMouseFunc(callback_mouse_button);
	glutKeyboardFunc(keyboard_down);

	glutKeyboardUpFunc(keyboard_up);

	glutDisplayFunc(RenderSceneCB);

	glutMainLoop();

	return 0;
}
//string readFile(const char* filePath) {
//	string content;
//	ifstream fileStream(filePath, ios::in);
//
//	if (!fileStream.is_open()) {
//		cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
//		return "";
//	}
//
//	string line = "";
//	while (!fileStream.eof()) {
//		getline(fileStream, line);
//		content.append(line + "\n");
//	}
//
//	fileStream.close();
//	return content;
//}

void callback_mouse_button(int button, int state, int x, int y) {
	printf("%d %d\n", button, state);
	//0 for the left muse
	//1 for the middle mouse button
	//2 for the right mouse button

	if (button == GLUT_LEFT_BUTTON) {
		if (state == 0) {
			zooming = true; //not implemented
		}
		else {

			zooming = false;
		}
	}
}
void keyboard_down(unsigned char key, int x, int y) {
	printf("down: %d %d %d\n", key, x, y);


	if (key == 'a') {
		//Im changing the camera and I should change the
		lookAtX += 0.3f;
	}
	//keyboard key number
	//poisition x
	//poisition y

}
void keyboard_up(unsigned char key, int x, int y) {
	printf("up: %d %d %d\n", key, x, y);
	//keyboard key number
	//poisition x
	//poisition y
}