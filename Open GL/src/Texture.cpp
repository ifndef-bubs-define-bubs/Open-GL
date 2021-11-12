#include "Texture.h"
#include "Image2Array/stb_image.h"


Texture::Texture(const std::string& path)
	:m_rendererId(0), m_FilePath(path), m_LocationBuffer(nullptr), m_width(0), m_height(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);  /* this turns the texture(the picture) upside down
										  we need to do this, as opengl sees the bottom left of the screen as 0,0. This means that
						    			  it feeds in images from the top right, and so if we don't flip it, then it will be upside
										  down */

	m_LocationBuffer = stbi_load(m_FilePath.c_str(), &m_width, &m_height, &m_BPP, 4); /*  c_str() converts a string into a const char.
																				Also, the last parameter is about how many channels we want.
	// SETTINGS FOR THE TEXTURE TO WORK - MUST SPECIFY																			We want 4 (RGBA).*/
	// this is known as the internal format, and is how opengl will store the texture data

	ScanForErrors(glGenTextures(1, &m_rendererId));
	ScanForErrors(glBindTexture(GL_TEXTURE_2D, m_rendererId)); 

	ScanForErrors(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));  // 2nd parameter is about how the picture will be rendererd down, if it
																					  // needs to be minimised
																						
	ScanForErrors(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));   
																					/* 2nd parameter is about how the image will be resized
																					if we render our image on an area that is larger ( in pixels )
																					texture size. It needs to scale it up */
	ScanForErrors(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)); // S is a horizontal wrap. We are telling it not to extend the area
	ScanForErrors(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));// same above

	// GIVEING THE TEXTURE TO OPENGL
	// this is known as format, and is the format of the data you are giving opengl

	ScanForErrors(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocationBuffer)); // RGBA tells opegngl how we want to interpret the image
																			   						


}

Texture::~Texture()
{
	if (m_LocationBuffer) // if the buffer contains data
		stbi_image_free(m_LocationBuffer); // then we free the buffer

	ScanForErrors(glDeleteTextures(1, &m_rendererId));
}

void Texture::Bind(unsigned int slot) const
{
	ScanForErrors(glActiveTexture(GL_TEXTURE0 + slot)); /* this brings back the idea of opengl being 
														a state machine. We can select slots for textures
														that we want to currently use. After being called,
														this texture will always be the one in use, unless
														another texture is bound.*/
	ScanForErrors(glBindTexture(GL_TEXTURE_2D, m_rendererId));
}

void Texture::Unbind() const
{
	ScanForErrors(glBindTexture(GL_TEXTURE_2D, 0));
}
