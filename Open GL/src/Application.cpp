#include "Renderer.h"
#include <GLFW/glfw3.h> // context creation
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "callbacksHeader.h"
#include <iostream>
#include "Texture.h"

//maths library
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

extern glm::mat4 rotate;
extern glm::mat4 view;





float matrixIncrement[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

int main(void)
{


    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) 
        return -1;
 

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, " peng gaal ", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "Error \n";

    glEnable(GL_DEPTH_TEST);
    // ===============================START OF MY CODE===============================================
    {
        float positions[180] = {
            
     // index thingies    // textures
                                                     //(the bottom left of the screen)          // WE COULD SAY THIS LINE REPRESENTS ONE VERTEX
                                                        // (bottom right)
   

    /* 0.055f,  0.041f, -0.1f,                     1.0f, 1.0f,
    -0.055f, -0.041f, -0.1f,                     0.0f, 0.0f,
     0.055f, -0.041f, -0.1f,                     1.0f, 0.0f,
     0.055f,  0.041f, -0.1f,                     1.0f, 1.0f,
    -0.055f, -0.041f, -0.1f,                     0.0f, 0.0f,
    -0.055f,  0.041f, -0.1f,                     0.0f, 1.0f,
                                                       
     */                                                
    -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,    1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,    1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,    1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,    0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,
                          
    -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,    1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,    1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,    1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,    0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,
                           
    -0.5f,  0.5f,  0.5f,    1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,    1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,    1.0f, 0.0f,
                          
     0.5f,  0.5f,  0.5f,    1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,    1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,    0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,    1.0f, 0.0f,
                          
    -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,    1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,    1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,    1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
                        
    -0.5f,  0.5f, -0.5f,    0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,    1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,    1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,    1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,    0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,    0.0f, 1.0f
                                                           
                                                                                            // NOTE THAT TEXTURES ARE BOUND TO THE COORDINATES/POSITIONS HERE, AND ANY TRANSFORMATIONS TO 
                                                                 // THE POSITIONS WILL ACCORDINGLY TRANSFORM THE TEXTURE COORDS. THE TEXTURE IS GLUED TO THESE 
                                                                 // TRIANGLES
                                                                  

                                                                 // ALSO NOTE THAT TEX COORDS ARE RELATIVE TO THE TEXTURE ITSELF. THAT MEANT THAT THESE COORDS DO 
                                                                 // NOT DEFINE WHERE ON THE TRIANGLES THE TEXTURES WILL BE DRAWN, BUT THE COORDS ON THE TEXTURE ARRAY
                                                                 // ITSELF. THIS MEANS THAT BY HALVING THE TEX COORD VALUES, YOU ARE SAYING THAT WHAT SHOULD BE DRAWN
                                                                 // IS HALF OF THE PICTURE, AND BY DOUBLING THEM, YOU WILL HAVE UNOCCUPIED SPACE ON THE TRIANGLES.
        };


        glm::vec3 cubePositions[] = {

            glm::vec3(0.0f,  0.0f,  0.0f),
            glm::vec3(2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f,  2.0f, -2.5f),
            glm::vec3(1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };


        unsigned int index[6] = {
            0, 1, 2,
            2, 4, 5
        

        };


        
       ScanForErrors(VertexArray va);   



       ScanForErrors(VertexBuffer vb(positions , 180 * sizeof(float))); // you see, we need to calculate the size ourselves                       //  CREATE A BUFFER
      
       ScanForErrors(VertexBufferLayout vbl);
       ScanForErrors(vbl.Push<float>(3));
       ScanForErrors(vbl.Push<float>(2));                  // CONFIGURING THE LAYOUT OF THE BUFFER ( actually preparing the info we'll give opengl to read the buffer)


       ScanForErrors(va.addBuffer(vb, vbl));                   // ADD A VERTEX TO THE VERTEX ARRAY

       ScanForErrors(IndexBuffer ib(index, 6);) // in the header and cpp, we knew that index has to be unsigned ints, bcus that's the only choice we gave


       glm::mat4 scale = glm::mat4(1.0f);
       glm::mat4 perspective = glm::mat4(1.0f);

      
       perspective = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
                                                                            // after rotating, we need to move back a little, or up
                                                                            // because the rotation forces the y values of the
                                                                            // projected points above the frustrum, while reducing the z
                                                                            // value, REFER BACK TO SHADER NOTE ABOUT FAR PLANE
       
       //scale = glm::scale(scale, glm::vec3(0.025f, 0.025f, 0.0f)); // creates a matrix, with the far right, top 3 columns as the ones specified

       ScanForErrors(Shader shader("res/shaders/Basic1.shader"));

       ScanForErrors(shader.Bind());
      
       ScanForErrors(Texture texture("openglpng/bbb.jpg"));
      
       
       ScanForErrors(shader.SetUniformMat4f("perspective", 1, GL_FALSE, glm::value_ptr(perspective)));
       ScanForErrors(shader.SetUniformMat4f("scale", 1, GL_FALSE, glm::value_ptr(scale)));

       
      


       
       ScanForErrors(shader.Unbind());
       ScanForErrors(va.Unbind());
       ScanForErrors(ib.Unbind());
        
       ScanForErrors(Renderer renderer);


        // NOTE: YOU NEED TO ADD 'f' AFTER COLOUR FLOATS 








        float r = 0.0f;
        float increment = 0.05f;


        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();
          
                

            // if you've read my notes in the shader file, 
            //you can see that we made a u_colour vairable.
            //however, opengl needs to kinda know where to get this u_colour from, so we use the above function, 
            //giving it the shader id and the name of the variable.
            // NOTE : MUST SPELL THE UNIFORM VARIABLE CORRECTLY;

            shader.Bind();
            ScanForErrors(shader.SetUniform4f("u_colour", r, 0.3f, 0.8f, 1.0f));
            
            
            ScanForErrors(shader.SetUniformMat4f("view", 1, GL_FALSE, glm::value_ptr(view)));
            ScanForErrors(shader.SetUniformMat4f("rotate", 1, GL_FALSE, glm::value_ptr(rotate)));


            
             ScanForErrors(renderer.Draw(va,ib, shader));
             glDrawArrays(GL_TRIANGLES, 0, 36);
           

         

            
                ScanForErrors(texture.Bind(0));
             //  the number of slots and the last parameter for setuniform must be the same
          

            ScanForErrors(shader.SetUniform1i("u_Texture", 0));   //  the number of slots and the last parameter for setuniform must be the same
          

            if (r > 1.0f)
            {
                increment = -0.05f;
            }
            else if (r < 0.0f) {
                increment = 0.05f;
            }

            r += increment;


            processInput(window);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);


            /* Poll for and process events */

            glfwPollEvents();

            glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
            glfwSetKeyCallback(window, key_callback);
            glfwSetScrollCallback(window, scroll_callback);
        }

      

    }



    glfwTerminate();





    return 0;


}