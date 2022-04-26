#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>
#include <string>

#include "LightFactory.h"
#include "FileManager.h"
#include "GameObject.h"
#include "Camera.h"
#include "Shadow.h"

/*
* Scene class is responsible for the rendering and storing game data
*/

class Scene {
private:
	// Scene name
	std::string name;

	// Window where everything renders
	GLFWwindow* window;
	// For now only 1 camera
	Camera camera;
	// Shader data
	/*std::vector<Shader> shaders;*/
	Shader basicShader;
	Shader depthMapShader;

	// Object data
	std::vector<Texture*> textures;
	std::vector<Mesh> meshes;
	std::vector<GameObject*> gameObjects;

	// Light data arrays
	LightFactory lightFactory;

public:
	// Create default Scene object
	Scene(Camera camera, GLFWwindow* window,
		Shader basicShader, Shader depthMapShader);

	// Shows if the next iteration is ready to be run
	bool nextIteration();
	bool iterate();
	
	// Adding elements to the scene
	bool addTexture(Texture* texture);
	Texture* getTexture(const int& index);
	bool removeTexture(const int& index);

	// bool addMesh(const Vertex* vertex, const GLuint* indice, const int& textureIndex);
	bool addMesh(const Vertex* vertex, unsigned long vertSize,
		const GLuint* indice, unsigned long indSize, const int& textureIndex);
	bool addMesh(Mesh mesh);
	Mesh& getMesh(const int& index);
	bool removeMeshes(const int& index);

	// Creating object using mesh index and basic inputs
	GameObject* createObject(const int& index, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation);
	GameObject* createObject(const int& index);
	bool addObject(GameObject* gameObject);

	// Adding light to the scene
	LightFactory& getLightFactory();
};

