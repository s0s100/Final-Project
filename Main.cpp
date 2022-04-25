#include <string>
#include <iostream>
#include <glm/gtx/string_cast.hpp>

#include "Scene.h"

// Default paths
const std::string texturePath = "Resources\\Textures\\";
const std::string shaderPath = "Shaders\\";
const std::string iconPath = "Resources\\Other\\";

// Defined functions
//void renderQuad();
GLFWwindow* glInitialize();
int glStop(GLFWwindow* window);


/**
* Flat surface
**/

// Mesh vertices: coordinates/normals/texturePos
Vertex verticeFlat[] = {
	Vertex{glm::vec3(-1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(1.0f, 0.0f, -1.0f),  glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3(1.0f, 0.0f,  1.0f),  glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)}
};
// Mesh indices
GLuint indiceFlat[] = {
	0, 1, 2,
	0, 2, 3
};

/**
* Cube
**/

Vertex verticeCube[] = {
	Vertex{glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},

	Vertex{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},

	Vertex{glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)},

	Vertex{glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},

	Vertex{glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 0.0f)},

	Vertex{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)}
};

GLuint indiceCube[] = {
	0, 1, 2,
	0, 2, 3,

	4, 5, 6,
	4, 6, 7,

	8, 9, 10,
	8, 10, 11,

	12, 13, 14, 
	12, 14, 15,

	16, 17, 18,
	16, 18, 19,

	20, 21, 22,
	20, 22, 23
};

int main() {
	// First initialize glFW and create scene
	GLFWwindow* window = glInitialize();

	const glm::vec3 camPos(-7.0f, 8.0f, -7.0f);
	const glm::vec3 camOrient(0.75f, -0.75f, 0.75f);
	Camera camera(DEFAULT_MONITOR_WIDTH, DEFAULT_MONITOR_HEIGHT, camPos, camOrient);

	Shader basicShader((shaderPath + "default.vert").c_str(), (shaderPath + "default.frag").c_str());
	Shader depthMapShader((shaderPath + "depthMapShader.vert").c_str(), (shaderPath + "depthMapShader.frag").c_str());

	Scene scene(camera, window, basicShader, depthMapShader);

	// Brick texture
	// 1024 x 1024, 5.5 MB, 72 dpi, 64 bit
	Texture brickTextures[]{
		Texture((texturePath + "brick.png").c_str(), "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture((texturePath + "brick.png").c_str(), "specular", 1, GL_RGBA, GL_UNSIGNED_BYTE)
	};
	scene.addTexture(brickTextures);
	
	std::vector <Vertex> verts(verticeCube, verticeCube + sizeof(verticeCube) / sizeof(Vertex));
	std::vector <GLuint> ind(indiceCube, indiceCube + sizeof(indiceCube) / sizeof(GLuint));
	std::vector <Texture> tex(brickTextures, brickTextures + sizeof(brickTextures) / sizeof(Texture));
	Mesh cubeMesh(verts, ind, tex);
	scene.addMesh(cubeMesh);
	
	glm::vec3 pos(0.0f, 0.5f, 0.0f);
	glm::vec3 scale(1.0f, 1.0f, 2.0f);
	glm::vec3 rot(0.0f, 0.0f, 0.0f);
	scene.createObject(0, pos, scale, rot);

	GameObject floor = GameObject(cubeMesh);
	floor.setPosition(glm::vec3(0.0f, -0.5f, 0.0f));
	floor.setScale(glm::vec3(10.0f, 0.5f, 10.0f));
	floor.setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	scene.addObject(floor);

	LightFactory& lightFactory = scene.getLightFactory();
	
	// Spot light
	glm::vec3 lightpos5 = glm::vec3(0.0f, 10.0f, 0.0f);
	glm::vec4 lightcolor5 = glm::vec4(0.3f, 0.8f, 0.9f, 1.0f);
	glm::vec3 lightdirection5 = glm::vec3(0.0f, -1.0f, 0.0f);
	float innercone5 = 0.95f;
	float outercone5 = 0.80f;
	SpotLight* spotLight5 = lightFactory.generateSpotLight(lightpos5, lightcolor5, lightdirection5, innercone5, outercone5);

	// Directinal light
	glm::vec3 lightPos0 = glm::vec3(0.0f, 10.0f, 0.0f);
	glm::vec4 lightColor0 = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	glm::vec3 lightDirection0 = glm::vec3(0.0f, -1.0f, 0.5f);
	DirectionalLight* dirLight = lightFactory.generateDirectionalLight(lightPos0, lightColor0, lightDirection0);

	/*
		Showcases and testing
	*/

	



	while (!glfwWindowShouldClose(window)) {
		scene.iterate();
	}

	return glStop(window);
}

GLFWwindow* glInitialize() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window with the game scene
	GLFWwindow* window = glfwCreateWindow(DEFAULT_MONITOR_WIDTH, DEFAULT_MONITOR_HEIGHT, "Default window", NULL, NULL);
	// Create full screen window with the game scene
	// GLFWwindow* window = glfwCreateWindow(DEFAULT_MONITOR_WIDTH, DEFAULT_MONITOR_HEIGHT, "Test window", glfwGetPrimaryMonitor(), NULL);

	// Adding icon
	GLFWimage windowIcon[1]{ FileManager::getImageContent((iconPath + "Fox_icon.png").c_str()) };
	glfwSetWindowIcon(window, 1, windowIcon);

	// Error checker
	if (window == NULL)
	{
		glfwTerminate();
	}

	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Initialize glad
	gladLoadGL();

	// Map the NDC coordinates to the framebuffer coordinates and enable depth testing
	glEnable(GL_DEPTH_TEST);
	// Enable gamma correction
	// glEnable(GL_FRAMEBUFFER_SRGB);
	
	return window;
}

int glStop(GLFWwindow* window) {
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}