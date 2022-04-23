#include "Scene.h"
#include <glfw3.h>

Scene::Scene(const glm::vec3& camPos, const glm::vec3& camOrient) : name("Default scene"), isPlaying(true), 
	basicShader(Shader((shaderPath + "default.vert").c_str(), (shaderPath + "default.frag").c_str())), 
	depthMapShader(Shader((shaderPath + "depthMapShader.vert").c_str(), (shaderPath + "depthMapShader.frag").c_str())){

	// Initialize GLFW with glfw know the version of OpenGL and that we are using Core profile
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window with the game scene
	this->window = glfwCreateWindow(DEFAULT_MONITOR_WIDTH, DEFAULT_MONITOR_HEIGHT, "Default window", NULL, NULL);
	// Create full screen window with the game scene
	// GLFWwindow* window = glfwCreateWindow(DEFAULT_MONITOR_WIDTH, DEFAULT_MONITOR_HEIGHT, "Test window", glfwGetPrimaryMonitor(), NULL);

	// Adding icon
	GLFWimage windowIcon[1]{ FileManager::getImageContent((iconPath + "Fox_icon.png").c_str()) };
	glfwSetWindowIcon(window, 1, windowIcon);

	// Error checker
	if (window == NULL)
	{
		glfwTerminate();\
	}

	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Initialize glad
	gladLoadGL();

	// Map the NDC coordinates to the framebuffer coordinates and enable depth testing
	glEnable(GL_DEPTH_TEST);
	// Enable gamma correction
	// glEnable(GL_FRAMEBUFFER_SRGB);

	// Upload shaders
	this->basicShader = Shader((shaderPath + "default.vert").c_str(), (shaderPath + "default.frag").c_str());
	this->depthMapShader = Shader((shaderPath + "depthMapShader.vert").c_str(), (shaderPath + "depthMapShader.frag").c_str());

	// Initialize scene camera
	this->camera = Camera(DEFAULT_MONITOR_WIDTH, DEFAULT_MONITOR_HEIGHT, camPos, camOrient);
}

void Scene::stop() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

bool Scene::nextIteration() {
	/*if (glfwWindowShouldClose(window) || !isPlaying){
		return false;
	}*/

	return true;
}

void Scene::iterate() {
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
	for (auto &object : gameObjects) {
		object.draw(basicShader);
	}

	// Refresh image with a new rendered data
	glfwSwapBuffers(window);
	glfwPollEvents();
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

bool Scene::addMesh(const Vertex* vertex, const GLuint* indice, const int& textureIndex) {
	std::vector<Vertex> verts(vertex, vertex + sizeof(vertex) / sizeof(Vertex));
	std::vector<GLuint> inds(indice, indice + sizeof(indice) / sizeof(GLuint));

	Texture* texture = textures.at(textureIndex);
	std::vector<Texture> texs(texture, texture + sizeof(texture) / sizeof(Texture));

	Mesh mesh(verts, inds, texs);
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

GameObject& Scene::createObject(const int& index, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation) {
	Mesh mesh = getMesh(index);
	GameObject newObject(mesh, position, scale, rotation);
	gameObjects.push_back(newObject);

	return newObject;
}

GameObject& Scene::createObject(const int& index) {
	Mesh mesh = getMesh(index);
	GameObject newObject(mesh);
	gameObjects.push_back(newObject);

	return newObject;
}