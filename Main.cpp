#include <string>
#include <iostream>
#include <glm/gtx/string_cast.hpp>

#include "LightFactory.h"
#include "FileManager.h"
#include "GameObject.h"

// Adding functions
void renderQuad();

// Default paths
const std::string texturePath = "Resources\\Textures\\";
const std::string shaderPath = "Shaders\\";
const std::string iconPath = "Resources\\Other\\";

// Planks
// Mesh vertices: coordinates/normals/texturePos
Vertex vertices[] =
{
	Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(1.0f, 0.0f, -1.0f),  glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3(1.0f, 0.0f,  1.0f),  glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)}
};

// Mesh indices
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
};

int main()
{
	/**
	* Basic initialization 
	* --------------------------------------------------
	**/

	// Initialize GLFW with glfw know the version of OpenGL and that we are using Core profile
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window with the game scene
	GLFWwindow* window = glfwCreateWindow(DEFAULT_MONITOR_WIDTH, DEFAULT_MONITOR_HEIGHT, "Test window", NULL, NULL);
	// Create full screen window with the game scene
	// GLFWwindow* window = glfwCreateWindow(width, height, "Test window", glfwGetPrimaryMonitor(), NULL);

	// Adding icon
	GLFWimage windowIcon[1]{FileManager::get_image_content((iconPath + "Fox_icon.png").c_str())};
	glfwSetWindowIcon(window, 1, windowIcon);

	// Error checker
	if (window == NULL)
	{
		glfwTerminate();
		return -1;
	}

	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Initialize glad
	gladLoadGL();

	// Map the NDC coordinates to the framebuffer coordinates and enable depth testing
	glViewport(0, 0, DEFAULT_MONITOR_WIDTH, DEFAULT_MONITOR_HEIGHT);
	glEnable(GL_DEPTH_TEST);

	/**
	* Main body
	* --------------------------------------------------
	**/

	// Shader creation
	Shader shader((shaderPath + "default.vert").c_str(), (shaderPath + "default.frag").c_str());
	Shader depthShader((shaderPath + "depthShader.vert").c_str(), (shaderPath + "depthShader.frag").c_str());
	Shader depthDebug((shaderPath + "depthDebug.vert").c_str(), (shaderPath + "depthDebug.frag").c_str());

	// Main camera
	glm::vec3 camPosition(0.0f, 2.0f, 3.0f);
	glm::vec3 camOrientation = glm::vec3(0.0f, -0.75f, -1.0f);
	Camera camera(DEFAULT_MONITOR_WIDTH, DEFAULT_MONITOR_HEIGHT, camPosition, camOrientation);

	// Plank textures
	Texture plankTextures[]
	{
		Texture((texturePath + "planks.png").c_str(), "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture((texturePath + "planksSpec.png").c_str(), "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
	};

	Texture brickTextures[]
	{
		Texture((texturePath + "brick.png").c_str(), "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};

	// Create mesh of the planks
	std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector <Texture> tex(plankTextures, plankTextures + sizeof(plankTextures) / sizeof(Texture));
	Mesh planksMesh(verts, ind, tex);
	
	// Game objects
	std::vector<GameObject> objectVector;

	GameObject planks = GameObject(planksMesh);
	planks.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	planks.setRotation(glm::vec3(30.0f, 0.0f, 0.0f));

	GameObject planks2 = GameObject(planksMesh);
	planks2.setPosition(glm::vec3(0.0f, 0.5f, 0.0f));
	planks2.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	planks2.setRotation(glm::vec3(0.0f, 0.0f, 0.0f));

	objectVector.push_back(planks);
	objectVector.push_back(planks2);

	// Light factory
	LightFactory lightFactory;

	// Directinal light
	/*glm::vec3 lightPos0 = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec4 lightColor0 = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
	glm::vec3 lightDirection0 = glm::vec3(1.0f, 1.0f, 1.0f);
	lightFactory.getDirectionalLight(lightPos0, lightColor0, lightDirection0);*/

	// Point light
	/*glm::vec3 lightPosP1 = glm::vec3(0.1f, 0.5f, 0.0f);
	glm::vec4 lightColorP1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	float constant1 = 0.5f;
	float linear1 = 0.5f;
	float quadratic1 = 1.0f;
	lightFactory.getPointLight(lightPosP1, lightColorP1, constant1, linear1, quadratic1);*/

	/*glm::vec3 lightPosP2 = glm::vec3(1.0f, 1.0f, 0.0f);
	glm::vec4 lightColorP2 = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
	float constant2 = 3.0f;
	float linear2 = 0.7f;
	float quadratic2 = 1.0f;
	lightFactory.getPointLight(lightPosP2, lightColorP2, constant2, linear2, quadratic2);*/

	// Spot lights
	/*glm::vec3 lightpos = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec4 lightcolor = glm::vec4(0.5f, 0.5f, 1.0f, 1.0f);
	glm::vec3 lightdirection = glm::vec3(0.0f, 1.0f, 0.0f);
	float innercone = 0.95f;
	float outercone = 0.80f;
	lightFactory.getSpotLight(lightpos, lightcolor, lightdirection, innercone, outercone);*/

	glm::vec3 lightPos2 = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec4 lightColor2 = glm::vec4(0.8f, 1.0f, 0.5f, 1.0f);
	glm::vec3 lightDirection2 = glm::vec3(0.0f, -1.0f, 0.0f);
	float innerCone2 = 0.4f;
	float outerCone2 = 0.1f;
	lightFactory.getSpotLight(lightPos2, lightColor2, lightDirection2, innerCone2, outerCone2);

	/**
	* Main loop
	* --------------------------------------------------
	**/

	float prevTime = 0;
	float timeDiff = 0;
	float fps = 0;
	while (!glfwWindowShouldClose(window))
	{
		// FPS calculator
		timeDiff = (float)glfwGetTime() - prevTime;
		prevTime = (float)glfwGetTime();
		fps = 1 / timeDiff;
		// std::cout <<  "FPS: " << static_cast<int>(fps) << std::endl;
		
		// Set up camera inputs and update it after it was changed by the input
		camera.inputs2(window);
		camera.updateMatrix();

		// Specify the color of the background, clean the back buffer and depth buffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

		// Change object locations
		planks2.changePosition(glm::vec3(-0.1f, 0.0f, 0.0f) * timeDiff);
		planks2.changeRotation(glm::vec3(12.0f, 0.0f, 0.0f) * timeDiff);
		planks.changeRotation(glm::vec3(0.0f, 2.5f, 0.0f) * timeDiff);

		/*
			Generate image
		*/

		// Main rendering
		glViewport(0, 0, DEFAULT_MONITOR_WIDTH, DEFAULT_MONITOR_HEIGHT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader.activateShader();

		lightFactory.update(shader);

		planks.draw(shader, camera);
		planks2.draw(shader, camera);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Program termination
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

// renderQuad() renders a 1x1 XY quad in NDC
// -----------------------------------------
unsigned int quadVAO = 0;
unsigned int quadVBO;
void renderQuad()
{
	if (quadVAO == 0)
	{
		float quadVertices[] = {
			// positions        // texture Coords
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};
		// setup plane VAO
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	}
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}