#pragma once
#include "Renderer.h"



struct VertexBufferElement 
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{

		switch (type)
		{
		case GL_FLOAT:         return 4;
		case GL_UNSIGNED_INT:  return 4;
		case GL_UNSIGNED_BYTE: return 1;
		}
		IfFalseBreak(false);
		return 0;
	}

};


// IGNORE THE ABOVE CLASS, YOU WON'T REALLY NEED TO WORRY ABOUT IT FOR NOW	

class VertexBufferLayout {

private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout()
		:m_Stride(0) {}   // CONSTRUCTOR 

	template<typename T>
	void Push(unsigned int count) 
	{
		static_assert(false);
	}
	
	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });         // CALLING ONE OF THESE FUNCTIONS JUST PUSHES VALUES INTO THE VEVOR , AND INCREMENTS THE STRIDE
		m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;

	}
	template<>
	void Push<unsigned int>( unsigned int count )
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;

	}
	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_BYTE) * count;
		 
	}
	
	inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }

};