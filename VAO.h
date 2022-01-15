#ifndef VAO_CLASS_HEADER
#define VAO_CLASS_HEADER

#include <glad/glad.h>
#include "VBO.h"

class VAO {
private:
	// ID reference for the Vertex Array Object
	GLuint ID;

public:
	// Constructor that generates a VAO ID
	VAO();
	// Links a VBO Attribute such as a position or color to the VAO
	void linkAttribute(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

	// Bind, unbind and delete operation for VAO
	void bind();
	void unbind();
	void deleteVAO();
};

#endif