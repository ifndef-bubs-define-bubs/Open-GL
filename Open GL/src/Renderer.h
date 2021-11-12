#pragma once 

#include <GL/glew.h> // defines function locations
#include "Shader.h"
#include "IndexBuffer.h"

//maths library
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>


#define IfFalseBreak(x) if (!(x))__debugbreak();/* basically, define IfFalseBreak(x), 
and if x is false,
then use the compiler
specific function debugbreak(), which breaks
the code. This function is only
available in Vs, that's why you can't control click it*/
#define ScanForErrors(x) GlClearError(); x; IfFalseBreak(GlCheckError(__FILE__, #x,__LINE__)) // x is basically the opengl 
//function being cuccooned in the error 
//checking thing, the asssert checks for errors, breaking if so
//' # ' turns macro variables into strings.
// the doubele underscore thing "__" means that the identifier belongs to this compiler - the Visual Studio compiler
//. Line is for the line of code, file, etc .

class VertexArray;

void GlClearError();  

bool GlCheckError(const char* filename, const char* function, int line);


class Renderer {


private:
	
public:

	void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)const;

	
	// void Draw(const VertexArray& va, const Shader& shader, const unsigned int& mode, const int& startingPoint,  int count)const;

};