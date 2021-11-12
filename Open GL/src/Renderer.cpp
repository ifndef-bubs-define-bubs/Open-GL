#include "Renderer.h"
#include "VertexArray.h"
#include <iostream>


void GlClearError() {
    while (glGetError() != GL_NO_ERROR);  /* "while there are still errors remaining", that's basically what this means.
    For some reason, gelGetError only picks one random error.
    By using it in a loop, you can get all the errors from different functions.*/

}

bool GlCheckError(const char* filename, const char* function, int line) {
    while (GLenum error = glGetError()) { // while error is not equal to zero, the code will run
        std::cout << "Opengl Error: " << error << " function: " << function << "  line:  " << line << std::endl;
        return false;
    }
    return true;
}

void Renderer::Clear() const
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

}



void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)const
{
    ScanForErrors(va.Bind());
    ScanForErrors(ib.bind());
    ScanForErrors(shader.Bind());
    

    //ScanForErrors(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
   


}

/*void Renderer::Draw(const VertexArray& va, const Shader& shader, const unsigned int& mode, const int& startingPoint, int count)const
{
    ScanForErrors(va.Bind());
    ScanForErrors(shader.Bind());

   
    ScanForErrors(glDrawArrays(mode, startingPoint, count));
   



}
*/