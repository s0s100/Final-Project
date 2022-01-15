#ifndef VBO_CLASS_HEADER
#define VBO_CLASS_HEADER

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texUV;
};

class VBO {
private:
	// Reference of buffered object vertices
	GLuint ID;

public:
	// Generates a Vertex Buffer Object and links it to vertices	
	VBO(std::vector<Vertex>& vertices);

	// Bind, unbind and delete operation for VBO
	void bind();
	void unbind();
	void deleteVBO();
};

#endif