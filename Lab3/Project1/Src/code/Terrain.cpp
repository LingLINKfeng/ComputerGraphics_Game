#include "Terrain.h"
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>
#include"std_image/stb_image.h"
#include<iostream>

using namespace cv;
Terrain::Terrain(std::string filePath, std::string texturefilePath, std::string ambientfilePath, std::string normalfilePath)
{
	Mat img = imread(filePath);
	int imgType = img.type();
	Mat resImg = Mat(img.rows, img.cols, imgType);
	resize(img, resImg, resImg.size(), 0, 0, cv::INTER_LINEAR);
	Mat gImg = Mat(img.rows, img.cols, CV_8UC1); //灰度图
	cvtColor(resImg, gImg, CV_BGR2GRAY);//bgr转灰度
	imgWidth = resImg.rows;
	imgHeihgt = resImg.cols;

	vertices = new GLfloat[imgWidth*imgHeihgt * 3];
	Height = new GLfloat[imgWidth*imgHeihgt];
	int index = 0;
	int k1 = 0;
	for (int i = 0; i < imgWidth; i++)
	{
		for (int j = 0; j < imgHeihgt; j++)
		{
			int c = (int)gImg.at<uchar>(i, j);			
			vertices[k1++] = verticeScale * (float)j;
			vertices[k1++] = zScale * (float)c / 255.0f;
			vertices[k1++] = verticeScale * (float)i;
			Height[index++]= zScale * (float)c / 255.0f;
			//fprintf(stderr,"gray color %d  %d %d",i,j ,(int)gImg.at<uchar>(i, j));
			
		}
	}
	indices = new unsigned int[(imgWidth - 1)*(imgHeihgt - 1) * 6];
	int k2 = 0;

	for (int i = 0; i < imgWidth - 1; i++)
	{
		for (int j = 0; j < imgHeihgt - 1; j++)
		{
			indices[k2++] = i * imgHeihgt + j;			
			indices[k2++] = i * imgHeihgt + j + 1;			
			indices[k2++] = i * imgHeihgt + j + imgHeihgt;			
			indices[k2++] = i * imgHeihgt + j + imgHeihgt;
			indices[k2++] = i * imgHeihgt + j + 1;
			indices[k2++] = i * imgHeihgt + j + imgHeihgt + 1;
		}
	}
	
	uvs = new  GLfloat[imgWidth*imgHeihgt * 2];
	int k3 = 0;
	for (int i = 0; i < imgWidth; i++)
	{
		for (int j = 0; j < imgHeihgt; j++)
		{
			uvs[k3++] = (float)i / (float)(imgWidth);
			uvs[k3++] = (float)j / (float)(imgHeihgt);
		}
	}
	
	normals = new GLfloat[imgWidth*imgHeihgt * 3];
	int k = 0;
	//遍历索引三角
	for (size_t i = 0; i < (imgWidth - 1)*(imgHeihgt - 1) * 6; i += 3)
	{
		static  unsigned int pIndex1 = indices[i];
		static	unsigned int pIndex2 = indices[i + 1];
		static	unsigned int pIndex3 = indices[i + 2];
		static	float x1 = vertices[pIndex1];
		static float y1 = vertices[pIndex1 + 1];
		static	float z1 = vertices[pIndex1 + 2];
		static	float x2 = vertices[pIndex2];
		static float y2 = vertices[pIndex2 + 1];
		static	float z2 = vertices[pIndex2 + 2];
		static	float x3 = vertices[pIndex3];
		static	float y3 = vertices[pIndex3 + 1];
		static	float z3 = vertices[pIndex3 + 2];
		//求边
		static	float vx1 = x2 - x1;
		static	float vy1 = y2 - y1;
		static	float vz1 = z2 - z1;
		static	float vx2 = x3 - x1;
		static	float vy2 = y3 - y1;
		static	float vz2 = z3 - z1;
		//叉乘求三角形法线
		static	float xN = vy1 * vz2 - vz1 * vy2;
		static	float yN = vz1 * vx2 - vx1 * vz2;
		static	float zN = vx1 * vy2 - vy1 * vx2;
		static	float Length = sqrtf(xN * xN + yN * yN + zN * zN);
		xN /= Length;
		yN /= Length;
		zN /= Length;
		//顶点法线更新
		normals[pIndex1] += xN;
		normals[pIndex1 + 1] += yN;
		normals[pIndex1 + 2] += zN;
		normals[pIndex2] += xN;
		normals[pIndex2 + 1] += yN;
		normals[pIndex2 + 2] += zN;
		normals[pIndex3] += xN;
		normals[pIndex3 + 1] += yN;
		normals[pIndex3 + 2] += zN;
	}
	
	stbi_set_flip_vertically_on_load(1);
	m_TerrainTexture = stbi_load(texturefilePath.c_str(), &m_Width, &m_Height, &nrChannels, 3);
	m_TerrainAmbient = stbi_load(ambientfilePath.c_str(), &m_Width, &m_Height, &nrChannels, 3);
	m_TerrainNormal = stbi_load(normalfilePath.c_str(), &m_Width, &m_Height, &nrChannels, 3);
	//Mat textureImg = imread("grass.jpg");
	//Mat textureResImg = Mat(256, 256, textureImg.type());
	//resize(textureImg, textureResImg, textureResImg.size(), 0, 0, cv::INTER_LINEAR);
	//cvtColor(textureResImg, textureResImg, CV_BGR2RGB);
	setup();
}



void Terrain::drawDepth(Shader shader, Texture texture, unsigned int shadow)
{
	glBindVertexArray(VAO);
	texture.Bind(0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, shadow);
	//glActiveTexture(GL_TEXTURE0);
	//glGenTextures(1, &m_Texture);
	//glBindTexture(GL_TEXTURE_2D, m_Texture);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//重复纹理
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//滤波
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, m_TerrainTexture);//设定纹理 
	//glGenerateMipmap(GL_TEXTURE_2D);
	//glActiveTexture(GL_TEXTURE1);
	//glGenTextures(1, &m_Ambient);
	//glBindTexture(GL_TEXTURE_2D, m_Ambient);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//重复纹理
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//滤波
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, m_TerrainAmbient);//设定纹理 
	//glGenerateMipmap(GL_TEXTURE_2D);
	//glActiveTexture(GL_TEXTURE2);
	//glGenTextures(1, &m_Normal);
	//glBindTexture(GL_TEXTURE_2D, m_Normal);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//重复纹理
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//滤波
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, m_TerrainNormal);//设定纹理 
	//glGenerateMipmap(GL_TEXTURE_2D);
	glDrawElements(GL_TRIANGLES, (imgWidth - 1)*(imgHeihgt - 1) * 6 , GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Terrain::draw(Shader shader, Texture texture)
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, (imgWidth - 1)*(imgHeihgt - 1) * 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Terrain::setup()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &m_TerrainVerticesID);
	glGenBuffers(1, &m_TerrainIndicesID);
	glGenBuffers(1, &m_TerrainUvID);
	glGenBuffers(1, &m_TerrainNormalID);
	glBindVertexArray(VAO);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_TerrainVerticesID);
	glBufferData(GL_ARRAY_BUFFER, imgWidth	*	imgHeihgt * 3 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_TerrainIndicesID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (imgWidth - 1)*(imgHeihgt - 1) * 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_TerrainUvID);
	glBufferData(GL_ARRAY_BUFFER, imgWidth*imgHeihgt * 2 * sizeof(GLfloat), uvs, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, m_TerrainNormalID);
	glBufferData(GL_ARRAY_BUFFER, imgWidth*imgHeihgt * 3 * sizeof(GLfloat), normals, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	
	

	glBindVertexArray(0);
}

GLfloat Terrain::GetTerrainH(int x)
{
	return Height[x];
}
