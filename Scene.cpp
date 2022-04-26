#include "Scene.h"
#include <glfw3.h>

Scene::Scene(Camera camera, GLFWwindow* window, Shader basicShader, Shader depthMapShader) 
	: name("Default scene"),
	basicShader(basicShader), depthMapShader(depthMapShader), window(window), camera(camera){
}

bool Scene::nextIteration() {
	if (glfwWindowShouldClose(window)){
		return false;
	}

	return true;
}

bool Scene::iterate() {
	// Read camera inputs and update its matrix
	camera.inputs2(window);
	camera.updateMatrix();

	// Depth map rendering
	depthMapShader.activateShader();
	lightFactory.updateShadowMaps(depthMapShader, gameObjects);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glViewport(0, 0, DEFAULT_MONITOR_WIDTH, DEFAULT_MONITOR_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Basic rendering
	basicShader.activateShader();
	camera.setCameraPosition(basicShader, "camPos");
	camera.setCameraMatrix(basicShader, "camMatrix");
	lightFactory.update(basicShader);
	/*for (GameObject* object : gameObjects) {*/
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects.at(i)->draw(basicShader);
	}

	// Refresh image with a new rendered data
	glfwSwapBuffers(window);
	glfwPollEvents();

	// At the end update game object values
	for (GameObject* object : gameObjects) {
		object->updateValues();
	}

	return true;
}

// Adding textures, meshes, gameObjects, time/fps for improving calculation quality, add light, object speed/etc
bool Scene::addTexture(Texture* texture) {
	textures.push_back(texture);
	return true;
}

Texture* Scene::getTexture(const int& index) {
	return textures.at(index);
}

bool Scene::removeTexture(const int& index) {
	textures.erase(textures.begin() + index);
	return true;
} 

bool Scene::addMesh(const Vertex* vertex, unsigned long vertSize,  
	const GLuint* indice, unsigned long indSize, const int& textureIndex) {
	// std::vector<Vertex> verts(vertex, vertex + sizeof(vertex) / sizeof(Vertex));
	// std::vector<GLuint> inds(indice, indice + sizeof(indice) / sizeof(GLuint));1
	std::vector<Vertex> verts(vertex, vertex + vertSize / sizeof(Vertex));
	std::vector<GLuint> inds(indice, indice + indSize / sizeof(GLuint));

	Texture* texture = textures.at(textureIndex);
	std::vector<Texture> texs(texture, texture + sizeof(texture) / sizeof(Texture));

	Mesh mesh(verts, inds, texs);
	meshes.push_back(mesh);

	return true;
}

bool Scene::addMesh(Mesh mesh) {
	meshes.push_back(mesh);

	return true;
}

bool Scene::removeMeshes(const int& index) {
	meshes.erase(meshes.begin() + index);
	return true;
}

Mesh& Scene::getMesh(const int& index) {
	return meshes.at(index);
}

GameObject* Scene::createObject(const int& index, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation) {
	Mesh mesh = getMesh(index);
	GameObject* newObject = new GameObject(mesh, position, scale, rotation);
	gameObjects.push_back(newObject);

	return newObject;
}

GameObject* Scene::createObject(const int& index) {
	Mesh mesh = getMesh(index);
	GameObject* newObject = new GameObject(mesh);
	gameObjects.push_back(newObject);

	return newObject;
}

bool Scene::addObject(GameObject* gameObject) {
	gameObjects.push_back(gameObject);
	
	return true;
}

LightFactory& Scene::getLightFactory() {
	return lightFactory;
}