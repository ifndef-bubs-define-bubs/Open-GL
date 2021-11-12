
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include <iostream>


VertexArray::VertexArray()
{
	ScanForErrors(glGenVertexArrays(1, &m_RendererID));

}

VertexArray::~VertexArray()
{
	ScanForErrors(glDeleteVertexArrays(1, &m_RendererID));
}

// VertexBufferLayout object with 10 floats pushed back, 4 indicies pushed back


void VertexArray::addBuffer(const VertexBuffer& vb,  const VertexBufferLayout& layout) // we've genereated a VertexBufferLaout 
{
	Bind(); // bind vertex array, then under, we bind a buffer to it
	vb.bind(); // bunch of bytes in mem

	const std::vector<VertexBufferElement>& elements = layout.GetElements();// SO ELEMENTS, IS BASICALLY JUST m_Elements FROM THAT VERTEXBUFFERLAYOUT CLASS
	unsigned int offset = 0;

	//for (const auto& elements : elements) = for each element, stored in elements 
	for(unsigned int i = 0; i < elements.size(); i++) // size() IS A FUNCTION FROM THE VECTOR CLASS, NOT MADE BY US 
	{

		/* 
		USE AS EXAMPLE:

		float positions[8] = {
            -0.5, -0.5,  
             0.5,  -0.5,
             0.5, 0.5,          say we push in <float>(8) like : {GL_FLOAT, 2 , GL_FALSE}
             -0.5,  0.5,

        };

		i (below) is equal to the number of VertexElements in the vector.
		The above example only has one, therefore, the code below only gets called once.

		2 is .count
		GL_FLOAT is .type
		GL_FALSE is .normalized 

		NOTE: DON'T FORGET THAT ONCE YOU'VE SPECIFIED ALL THE ATTRIBUTES, THE STRIDE WILL NOT CHANGE ; YOU WILL ENTER THE SAME STRIDE VALUE OVER AND OVER
*/
		const VertexBufferElement& element = elements[i]; // SO WE SET ELEMENT EQUAL TO ONE OF THOSE RVALUES IN THE VECTOR OBJECT
		ScanForErrors(glVertexAttribPointer(i, element.count,element.type, /* SO SINCE ELEMENT IS ONE OF THE VERTEX ELEMENT OBJECTS, WE CAN
			                                                                ACCESS PARTS OF IT AS IF IT WERE AN LVALUE, LIKE element.count, element.type, ETC.*/
			element.normalized, layout.GetStride(), (const void*)offset));
		ScanForErrors(glEnableVertexAttribArray(i));

		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	};
	
 	
}

void VertexArray::Bind() const
{

	ScanForErrors(glBindVertexArray(m_RendererID));

}

void VertexArray::Unbind() const
{

	ScanForErrors(glBindVertexArray(0));
}

/*void* VertexArray::genCircle(const float& diameter, const float& zcoord, const float& increment)
{


	float xcoord = -1 * (std::pow(diameter, 0.5f));
	float xholder;

	for (xcoord; xcoord < (float)(std::pow(diameter, 0.5f)); xcoord += increment) {



		    float ycoord = (float)(std::round((std::pow(diameter - std::pow(xcoord, 2.0f), 0.5f) * 100))) / 100.0f;

			circleCoords.push_back(xcoord);
			std::cout << xcoord << " = x ==> 1" << std::endl;
			circleCoords.push_back(ycoord);
			std::cout << ycoord << " = y ==> 1" << std::endl;
			circleCoords.push_back(-zcoord);

			if (xcoord > (float)(std::pow(diameter, 0.5f))) {
				xholder = (xcoord - (5.0f * increment));
			}
			else {
				xholder = (xcoord + (5.0f * increment));
			}

			float ycoord2 = (float)(std::round((std::pow(diameter - std::pow(xholder, 2.0f), 0.5f) * 100))) / 100.0f;

			circleCoords.push_back(xholder);
			std::cout << xholder << " = x ==> 2" << std::endl;
			circleCoords.push_back(ycoord2);
			std::cout << ycoord2 << " = y ==> 2 " << std::endl;
			circleCoords.push_back(-zcoord);

			float newxcoord = (xholder + xcoord) / 2.0f;
			float newycoord = (ycoord2 + ycoord) / 2.0f;


			circleCoords.push_back(-newxcoord);
			std::cout << -newxcoord << " = x ==> 3" << std::endl;
			circleCoords.push_back(-newycoord);
			std::cout << -newycoord << " = y ==> 3 " << std::endl;
			circleCoords.push_back(-zcoord);




	}
		void* coordinates = circleCoords.data();
		return  coordinates;
}

*/