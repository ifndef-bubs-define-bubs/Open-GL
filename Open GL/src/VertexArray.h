#pragma once
#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include <vector>

class VertexArray {
	

private:

	unsigned int m_RendererID;


public :
	std::vector<float> circleCoords;
	VertexArray();
	~VertexArray();

	void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	
	void Bind() const;
	
	void Unbind() const;

    /*void* genCircle(const float& diameter, const float& zcoord, const float& increment);

	inline const unsigned int getVectorSize() {
		return circleCoords.size() * sizeof(float);
	}; 
	const auto getVectorCount() {
		return circleCoords.size();
	};*/
};