#ifndef EBO_CLASS_HEADER
#define EBO_CLASS_HEADER

#include <glad/glad.h>
#include <vector>

class EBO {
private:
	// Reference of Elements Buffer Object
	GLuint ID;

public:
	// Generates a Elements Buffer Object and links it to indices
	EBO(std::vector<GLuint>& indices);

	// Bind, unbind and delete operation for EBO
	void bind();
	void unbind();
	void deleteEBO();
};

#endif
