#include "IndexBuffer.h"
#include "Renderer.h"
#include <GL/glew.h>
#include <iostream>

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) // here, he used const unsigned int* so that for the size parameter, he knows how to calculate the size, and only need the count (the number of values) to do so,
                                                                       //look in the VertexBuffer to see what he did there
    :m_count(count)
{
    IfFalseBreak(sizeof(unsigned int) == sizeof(GLuint));  // apparently, the size of GLuint may be different to the size of an unsigend int ( 4 bytes ), depending on the platform 

    ScanForErrors(glGenBuffers(1, &m_RendererId));
    ScanForErrors(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));                                   // What they acutally mean by GL_ARRAY_BUFFER is that we are going to be passing in vertex attributes 
    ScanForErrors(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));


}

IndexBuffer::~IndexBuffer()
{
    ScanForErrors(glDeleteBuffers(1, &m_RendererId));
}

void IndexBuffer::bind() const
{

    ScanForErrors(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));                                   // What they acutally mean by GL_ARRAY_BUFFER is that we are going to be passing in vertex attributes 

}

void IndexBuffer::Unbind() const
{

    ScanForErrors(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));                                   // What they acutally mean by GL_ARRAY_BUFFER is that we are going to be passing in vertex attributes 

}
