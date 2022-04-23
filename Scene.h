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

	// Window where everything renders
	GLFWwindow* window;
	// For now only 1 camera
	Camera camera;
	// Scene name
	std::string name;
	// Does the scene paused
	bool isPlaying;

	// Shader data
	/*std::vector<Shader> shaders;*/
	Shader basicShader;
	Shader depthMapShader;

	// Object data
	std::vector<Texture*> textures;
	std::vector<Mesh> meshes;
	std::vector<GameObject> gameObjects;

	// Light data arrays
	LightFactory lightFactory;

public:
	// Default paths
	const std::string texturePath = "Resources\\Textures\\";
	const std::string shaderPath = "Shaders\\";
	const std::string iconPath = "Resources\\Other\\";

	// Create default Scene object
	Scene(const glm::vec3& camPos, const glm::vec3& camOrient);

	// Terminates the programs
	void stop();

	// Shows if the next iteration is ready to be run
	bool nextIteration();
	void iterate();
	
	// Adding elements to the scene
	bool addTexture(Texture* texture);
	Texture* getTexture(const int& index);
	bool removeTexture(const int& index);

	bool addMesh(const Vertex* vertex, const GLuint* indice, const int& textureIndex);
	Mesh& getMesh(const int& index);
	bool removeMeshes(const int& index);

	// Creating object using mesh index and basic inputs
	GameObject& createObject(const int& index, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation);
	GameObject& createObject(const int& index);
	
};

