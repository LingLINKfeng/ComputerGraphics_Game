#pragma once

class  FrameBuffer
{
private:
	unsigned int m_RendererID;
	
public:
	FrameBuffer(unsigned int SHADOW_WIDTH, unsigned int SHADOW_HEIGHT);

	unsigned int depthMap;
	void Unbind()const;
	void Bind()const;
	unsigned int GetDepthMap();
};