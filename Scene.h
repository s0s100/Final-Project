#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>
#include <string>

#include "LightFactory.h"
#include "FileManager.h"
#include "GameObject.h"
#include "Camera.h"
#include "Shadow.h"

class Scene {
private:
	// Default paths
	const std::string texturePath = "Resources\\Textures\\";
	const std::string shaderPath = "Shaders\\";
	const std::string iconPath = "Resources\\Other\\";

	// Window where everything renders
	GLFWwindow* window;

	// Scene name
	std::string name;

	// Data arrays
	std::vector<Texture> textures;
	std::vector<Mesh> meshes;
	std::vector<GameObject> gameObjects;

	// Light implementation
	LightFactory lightFactory;


public:
	// Create default Scene object
	Scene(const std::string& name);
	Scene();

	// Initialize basic opengl window
	void initialize();
	void stop();
};

