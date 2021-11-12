
#include "VertexBuffer.h"



VertexBuffer::VertexBuffer(const void* data, unsigned int size) /* don't forget, a pointer is just a pointer - it has barely any association to the value location it stores. Anyways, here, 
                                                                we don't know what type of data they are passing in, 
                                                                so we used a const void. As a result, we can't calculate the size parameter for the glfunction, as we don't know they type they're passing in. 
                                                                This means that vertexbuffer object constructor parameters will need to constain a pre-calculated size. */
{
    ScanForErrors(glGenBuffers(1,&m_RendererId));         
    ScanForErrors(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));                                   // What they acutally mean by GL_ARRAY_BUFFER is that we are going to be passing in vertex attributes 
    ScanForErrors(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));    // ===================== SO WE LOAD IT INTO THE BUFFER HERE =====================


}


VertexBuffer::~VertexBuffer()
{
    ScanForErrors(glDeleteBuffers(1, &m_RendererId));
}

void VertexBuffer::bind() const
{
   
    ScanForErrors(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));            // WE BIND IT, EASY TO UNDERSTAND, RIGHT ???!!!! ===================                     

}

void VertexBuffer::Unbind() const
{

    ScanForErrors(glBindBuffer(GL_ARRAY_BUFFER, 0));                                   

}
