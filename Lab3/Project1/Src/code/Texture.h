#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include<string>
class Texture 
{
private:
	int m_Width, m_Height, nrChannels;
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	
public:
	Texture(const std::string& filepath);
	~Texture();

	unsigned int GetID()const;
	void Bind(unsigned int slot = 0)const;
	void Unbind()const;
	inline int GetWidth()const { return m_Width; };
	inline  int GetHeight()const { return m_Height; };
};
