#ifndef TEXTURE_CLASS_HEADER
#define TEXTURE_CLASS_HEADER

#include <glad/glad.h>
#include <stb/stb_image.h>

#include "ShaderClass.h"

class Texture {
private:
	// ID reference for the Texture and its type
	GLuint ID;
	// Texture type (such as diffuse, specular, etc)
	const char* type;
	// Texture slot at openGL engine
	GLuint unit;

public:
	// Default contructor to create image using array list with this image data
	Texture(const char* image, const char* texType, GLuint slot, GLenum format, GLenum pixelType);
	// Assigns a texture unit to a texture
	void texUnit(Shader& shader, const char* uniform, GLuint unit);

	// Bind, unbind and delete operation for Texture
	void bind();
	void unbind();
	void deleteTexture();
	const char* getType();
};

#endif