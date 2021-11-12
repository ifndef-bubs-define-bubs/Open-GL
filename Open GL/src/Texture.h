#pragma once
#include "Renderer.h"


class Texture
{
private:
	unsigned int m_rendererId;
	std::string m_FilePath; // file path of image(texture)
	unsigned char* m_LocationBuffer; // local storage for the texture 
	int m_width, m_height, m_BPP;  // width, heigt, and bits per pixel



public:
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const;  // if you don't specify the variable 'slot', it will be 0
	void Unbind()const;

	inline int GetWidth()const { return m_width; }
	inline int GetHeight()const { return m_height; }
};

