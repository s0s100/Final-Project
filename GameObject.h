#ifndef GAME_OBJECT_CLASS_HEADER
#define GAME_OBJECT_CLASS_HEADER

#include "Mesh.h"

class GameObject {
private:
	// Contains model with vertices, indices and textures
	Mesh mesh;

	// Basic attributes
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation; // Radians

	// Matrix to define location of the object
	glm::mat4 model;

public:
	// Constructor with default values
	GameObject(Mesh mesh);
	GameObject(Mesh mesh, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation);

	// Setting up the matrix model view
	// void matrixSetup(Shader shader);

	// Put all the parameters into shader and call a shader
	void draw(Shader& shader);

	/**
	* Getters/setter (includes model change methods)
	**/
	
	// Default setters
	void setPosition(glm::vec3 position);
	void setScale(glm::vec3 scale);
	void setRotation(glm::vec3 rotation);

	// Default changers
	void changePosition(glm::vec3 position);
	void changeScale(glm::vec3 scale);
	void changeRotation(glm::vec3 rotation);
};

#endif
