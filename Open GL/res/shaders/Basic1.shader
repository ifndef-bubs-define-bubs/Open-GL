#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCord;

//uniform mat4 u_MVP; /*now this is a uniform for the model view projection 
                    //matrix and represents that proj variable in application.cpp
                    //*/
uniform mat4 rotate; // the tranform uniform from... at this point it's pretty self explanatory
uniform mat4 perspective;
uniform mat4 view;
uniform mat4 scale;
out vec2 v_TexCoord4;

void main()
{
    gl_Position =  perspective  * scale * view * rotate * position; //rotation first because it messes with things like transformations if
                                                          // after, and view next, because if you wanted to change z value
                                                          // after perspective is appplied, then conversion to cartesian coords wiill
                                                          // leave z not equa to 1, which does not get rendered
    v_TexCoord4 = vec2(texCord.x, texCord.y);

};


#shader fragment
#version 330 core

out vec4 colour;

in vec2 v_TexCoord4; // means wer're taking in the tex coords from the vertex shader

uniform sampler2D u_Texture; /* so we've sampled the texture in application.cpp,
                             with that set uniform i thing and "u_Texture" 0 thing. Now, 
                             u_Texture is basically a reference to the actual data of the texure*/
uniform vec4 u_colour;


/* uniforms are basically like variales that you make on the cpu side, and send to the shaders as inputs, 
so they can do stuff wiht them.
*/

void main()
{
    vec4 texColour = texture(u_Texture, v_TexCoord4); /* texture is a glsl function, that sets the starting position
                                                      of where we would like to start drawing our texture from, in this
                                                      case of course: the texture coordinates from the vertex shader.*/
    
    colour = texColour * vec4(u_colour); //* u_colour; // then of course, we set the colour of each pixel to be the colour of the texture pixel



};

/*LOCAL SPACE:

These are basically the coordinates in an object's world -  like a universe, 
where that object is the centre of attention. The origin of other objects may be 0.0f,
but the main idea, is that these local coordinates, are specific to that particular 

WORLD SPACE:

These are the coordintaes that define you're object's coordintates, size, etc. to 
other objects relative to the world - like all your objects, instead of being alond (local),
in a larger world. These coordinates are achieved with the model matrix, which defines where 
everything will be within that world.

VIEW SPACE/CAMERA:

When the world coordintates are transformed to coordinates that are in front of a camera/view.
Put simply, transformed to coordinates that are in front of a particular area in the world view.
This is achieved through several rotations and translations, which of course, are multiplied into
a single matrix - the view matrix.

CLIP SPACE:

OpenGl expects the verticies to be normalized, and so we use a matrix called a projection matrix to 
convert view coordintes into normalized clip vectors. It is called the clip view, as values which are
too high are clipped ( not visible on the screen ).

There are either orthographic or perspective projection matricies.
An example of orthographic is on the right of this picture : https://static.sdcpublications.com/multimedia/9781630570521-sample/ege/ortho/3d_ortho.jpg

Think of orthographic as about how big things really are compared to each other. Like remember those days of
drawing orthographic projections, and how you'd draw lines, connecting different sides of a shape, and
they'd magically connect. 
Perspective however, takes into account that objects may appear to be smaller when further away, 
thus giving a more realistic vibe to it.

transformation with required matrix, then clipping with frustrum

divide happens before matrix addition

an actual visible difference in y values on the graph, making it easier on floats :https://www.scratchapixel.com/images/upload/perspective-matrix/optimized-clip-planes.png
y axis is the computed z axis (after all calculations)

fov determines the top coords, which can be used to find the others
aspect ratio then scales the right coords to the right size


from that png file, the vectors which described the point before, are forced to change 
relative to the true z and y coordintate system, and thus the vecotrs point to these 
new points in space. then, we combine these vectors by adding them together, hence the cos
minus the sine


basically, ration of length of near plane to length of far plane corresponds to ratio of given y value, 
to desired y value https://cdn.discordapp.com/attachments/893582281942401034/904125064767762462/unknown.png

same applies to x


so we basically configure where on the screen the coordiates will land, and without ranges, the coordinates 
could be anywhere, even off the screen. So we use https://cdn.discordapp.com/attachments/893582281942401034/904125734916878346/unknown.png,
which basically makes it so that the right of the screen (pehaps 800) is converted to 1, and the left (0 of course) to -1, which
are the maximum values the gpu will take to reder stuff. so we've effectively restricted which values are valid.

Same applies to the z coord. Except, instead of a range, and using inequalities, we say that when z is equal to the 
given near plane, then this equation needs to be equal to ( A*z/w + B/w ) to -1. Why this equation ? Becuase this 
is just how the A and B values are multiplied.

NOTE : Anything in the z column of the matrix will come out unscathed after the conversion to cartesian coordinates, becuase of:
read Shuba Duck convo


note: what caused all your confusion was that you believed that once all the calculations had been performed, 
they were then divided by z (w) which then gave you what you wanted. However, that isn't true. The calculations
are individual, and had been placed in specific locations to get the desired output. The z column of the matrix
makes it so that after the z division, they come out untouched. While calculations in other columns, e.g the 
y column, are timesed by y. As a result, we get exactly what was pre-calculated  https://cdn.discordapp.com/attachments/893582281942401034/904125064767762462/unknown.png
. The calculation from the z column is the same as before, the division by z, and the multiplication by y 
up top just so happens to form the formula needed to calculate the y value on screen, and the whole thing
is kept in range by the other formulas. Fuckin beautiful.


So in summary, you would tend to think that the actual perspective division happens when the homogenous coords
are converted to cartesian coords and all. But no. The division by z simply aids in fully forming the calculations
to make the points : 
 within a certain range
 perspectiviely divided

The actual idea of perspective divsion isn't simply from dividing the coordinates by z. That division only completes
everything, fufilling the above criteria.

The unit cube represents the values the gpu will take and render, which is why all these matrix 
caluclations aim to map the coorinates between -1 and 1 and stuff. The perspective matrix 
simply maps what you give it, relative to the screen's size, to the range -1 and 1


near plane should be as close to nearest point, and far plane as close to far plane, becuase, it is the far plane which
is mapped to 1, and the near to -1, which means that you want your verticies to have as much space between this 1 and -1, 
so that the floats storing the z value will have more precision.


points would be able to come from anywhere to get the the camera. However, the fov, snips of a specific area, where
only projection lines from points which pass through the area, are rendered. The near plane and the camera is what 
actually does all this. The rest just involves tan and aspect ratio calculaions. https://cdn.discordapp.com/attachments/893582281942401034/904352217195245598/IMG_0700.JPG


As long as the x/y values increase accordingly with the z value, it will be in the frustrum, as it will be timesed by 
n/z to fit into the l and r /b and t ranges, wich are then put in the range -1, 1. If the y/x values are increasing 
but the z isn't, the point will eventually reach a level, where when it is timesed by n/z, it will be higher than 
the r and l/ b and t values, hence higher than 1. Think of this when you are ever confused about the far plane.


when they say that opengl renders on the near plane, they mean that because of the unit cube, and how the 
perspective projection matrix maps the value of the near plane to 1.


WHY THE OBJECT DOES NOT SPIRAL OUT OF CONTROL:

when you change the view matrix to something else, and the rotation matrix to 
something else, there are two things you need to take into account:

the fact that glm mulitplies it's matricies, so that a matrix can hold 
several transformations all in one, so kind of like a memory feature.

and the fact that since glm does this, whenever you times gl_Position by 
anything, it does not have the ability to store the result of that mulitplication
in itslef, it simply outputs the result of the multiplication. Therefore, 
glm's memory matricies act as a kind of... how do I word this properly ...

if you have position 1,2,4, and you times it by a scale matrix, of like 2, 
in languages, you obviously store the matrix within an object. And an object 
holds information, that can be used throughout the code. Therefore, if I 
connect an input, let's say the RIGHT_KEY to make it that the world is
translated left by 2 each time I press it, the object matrix will hold 
all the current information depending on how many times I pressed it of course.

So it will then times gl_Position by this. And linking back to the idea, that
gl_Position cannot store anything, the matrix object acts as a sort of memory, of 
the cube we're rendering's last position, size, rotation, etc.




*/