#ifndef MESH_CLASS_HEADER
#define MESH_CLASS_HEADER

#include <string.h>
#include <vector>

#include "VAO.h"
#include "EBO.h"
#include "VBO.h"
#include "Camera.h"
#include "Texture.h"

class Mesh
{
private:
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	std::vector <Texture> textures;

	VAO VAO;

public:
	// Empty constructor
	Mesh();
	// Basic constructor to generate usable Mesh object
	Mesh(std::vector <Vertex> vertices, std::vector <GLuint> indices, std::vector <Texture> textures);

	// Put values into the shader so it could calculate the image
	void draw(Shader& shader, Camera& camera);
};
#endif


