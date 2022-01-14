#include <string>
#include <iostream>

#include "Mesh.h"

Mesh::Mesh() {}

Mesh::Mesh(std::vector <Vertex> vertices, std::vector <GLuint> indices, std::vector <Texture> textures)
{
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;

	// Generates Vertex Array Object and binds it
	Mesh::VAO.bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO(vertices);
	// Generates Element Buffer Object and links it to indices
	EBO EBO(indices);

	EBO.bind();

	// Links VBO attributes such as coordinates and colors to VAO
	Mesh::VAO.linkAttribute(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	Mesh::VAO.linkAttribute(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	Mesh::VAO.linkAttribute(VBO, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));

	// Unbind all the elements
	Mesh::VAO.unbind();
	EBO.unbind();
	VBO.unbind();
}

// Drawing function
void Mesh::draw(Shader& shader)
{
	Mesh::VAO.bind();

	// Bind every included texture
	std::string type;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		type = textures[i].getType();
		textures[i].texUnit(shader, type.c_str(), i);
		textures[i].bind();
	}

	// Call a draw function
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}