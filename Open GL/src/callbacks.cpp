#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "callbacksHeader.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <glm/gtc/type_ptr.hpp>

extern float matrixIncrement[4];

glm::mat4 rotate = glm::mat4(1.0f);
glm::mat4 view = glm::mat4(1.0f);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);



}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    if (key == GLFW_KEY_UP || key == GLFW_KEY_W && action == GLFW_PRESS) {
        rotate = glm::rotate(rotate, glm::radians(7.0f), glm::vec3(7.0f, .0f, .0f));
    }
    else if (key == GLFW_KEY_DOWN || key == GLFW_KEY_S && action == GLFW_PRESS) {
        rotate = glm::rotate(rotate, glm::radians(-7.0f), glm::vec3(50.0f, .0f, .0f));
    }
    else if (key == GLFW_KEY_RIGHT || key == GLFW_KEY_D && action == GLFW_PRESS) {
        //view = glm::translate(view, glm::vec3(.1f, .0f, .0f));
        rotate = glm::rotate(rotate, glm::radians(-7.0f), glm::vec3(.0f, 50.0f, .0f));
    }
    else if (key == GLFW_KEY_LEFT || key == GLFW_KEY_A && action == GLFW_PRESS) {
        //iew = glm::translate(view, glm::vec3(-.1f, .0f, .0f));
        rotate = glm::rotate(rotate, glm::radians(7.0f), glm::vec3(.0f, 50.0f, .0f));
    }
    
    

}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    view = glm::translate(view, glm::vec3(.0f, .0f, (float)yoffset));


}


void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}



/*
You'd expect things to spiral out of control after you've roated and transformed an object once,
because : 
======================================================

I just realized something though. If you rotate it and then transform ( toward the -z axis ) it,
it will rotate about it's centre, and be moved backwards. But after you've rotated it and then 
transformed ( toward the -z axis ) it once, then won't the z values be a larger, and then begin to stop rotating around 
their center, and spiral out of control ? 

======================================================

But that doesn't happen bcus you are applying the matricies to the same coordinates, and so you are 
doing this : 

========================================================

If you re-create a new matrix from scratch every frame, it basically resets the transformation
Basically you say
Frame 1: Rotate by 10 degrees
Frame 2: Rotate by 20 degrees
Frame 3: Rotate by 30 degrees

While if you re-use the matrix, you would do it like this:
Frame 1: Rotate by 10 degrees
Frame 2: Rotate by an extra 20 degrees
Frame 3: Rotate by an extra 30 degrees

(and in that case it would spiral out of control)

==========================================================

And from the above code, you may ask :

=================================================

Why do the rotations work then ? Why don't they 
simply rotate by 7, and then call it quits since they're rotating the original same coordinate
by 7 everytime, which produces the same result.

=================================================

Well it doesn't bcus you're gay.

glm multiplies the rotation matrix by that matrix of 7 degrees each time, then that is what is 
supplied to the vertex shader.

This type of problem frequently arises, so try and always see the difference between actions 
that change the actual thing itself, and actions that increment themselves over time, or bcus of 
something else.
*/