#pragma once
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <string>
#include"Shader.h"
#include"Texture.h"
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
class Terrain
{
public:
	Terrain(std::string terrainfilePath, std::string texturefilePath, std::string ambientfilePath, std::string normalfilePath);
	void drawDepth(Shader shader,Texture texture,unsigned int shadow);
	void draw(Shader shader, Texture texture);
	void setup();
	GLfloat GetTerrainH(int x);
private:
	unsigned int m_TerrainVerticesID;
	unsigned int m_TerrainIndicesID;
	unsigned int m_TerrainUvID;
	unsigned int m_TerrainNormalID;
	unsigned int VAO;

	unsigned int m_Texture;
	unsigned int m_Ambient;
	unsigned int m_Normal;


	cv::Mat textureResImg;
	unsigned char* m_TerrainTexture;
	unsigned char* m_TerrainAmbient;
	unsigned char* m_TerrainNormal;
	int m_Width, m_Height, nrChannels;

	unsigned int TextureID;
	int imgWidth;
	int imgHeihgt;
	float verticeScale = 0.1f;
	float zScale = 5.0f;
	GLfloat* vertices;
	GLfloat* uvs;
	GLfloat* Height;
	GLfloat* normals;
	unsigned int* indices;

};
