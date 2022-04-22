#include <string>
#include <iostream>
#include <glm/gtx/string_cast.hpp>

#include "LightFactory.h"
#include "FileManager.h"
#include "GameObject.h"
#include "Camera.h"
#include "Shadow.h"

// Default paths
const std::string texturePath = "Resources\\Textures\\";
const std::string shaderPath = "Shaders\\";
const std::string iconPath = "Resources\\Other\\";

// Defined functions
void renderQuad();

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
	// GLFWwindow* window = glfwCreateWindow(DEFAULT_MONITOR_WIDTH, DEFAULT_MONITOR_HEIGHT, "Test window", glfwGetPrimaryMonitor(), NULL);

	// Adding icon
	GLFWimage windowIcon[1]{FileManager::getImageContent((iconPath + "Fox_icon.png").c_str())};
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
	glEnable(GL_DEPTH_TEST);
	// Enable gamma correction
	// glEnable(GL_FRAMEBUFFER_SRGB);

	/**
	* Main body
	* --------------------------------------------------
	**/

	// Shader creation
	Shader shader((shaderPath + "default.vert").c_str(), (shaderPath + "default.frag").c_str());
	Shader depthMapShader((shaderPath + "depthMapShader.vert").c_str(), (shaderPath + "depthMapShader.frag").c_str());
	Shader depthMapShaderDebug((shaderPath + "depthMapShaderDebug.vert").c_str(), (shaderPath + "depthMapShaderDebug.frag").c_str());

	// Main camera
	glm::vec3 camPosition(-7.0f, 8.0f, -7.0f);
	glm::vec3 camOrientation = glm::vec3(0.75f, -0.75f, 0.75f);
	Camera camera(DEFAULT_MONITOR_WIDTH, DEFAULT_MONITOR_HEIGHT, camPosition, camOrientation);

	// Plank textures
	// 1024 x 1023, 5.5 MB, 72 dpi, 64 bit
	// 1024 x 1023, 1.7 MB, 72 dpi, 16 bit
	Texture plankTextures[] {
		Texture((texturePath + "planks.png").c_str(), "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture((texturePath + "planksSpec.png").c_str(), "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
	};

	// Brick texture
	// 1024 x 1024, 5.5 MB, 72 dpi, 64 bit
	Texture brickTextures[] {
		Texture((texturePath + "brick.png").c_str(), "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture((texturePath + "brick.png").c_str(), "specular", 1, GL_RGBA, GL_UNSIGNED_BYTE)
	};

	//Grey brick texture
	// 72 dpi, 24 bit (96, 24)
	/*Texture newTextures[]{
		Texture((texturePath + "Texture2.jpg").c_str(), "diffuse", 0, GL_RGB8, GL_UNSIGNED_BYTE)
	};*/
	// std::vector <Texture> tex(newTextures, newTextures + sizeof(newTextures) / sizeof(Texture));

	// Plank cube mesh
	std::vector <Vertex> verts(verticeCube, verticeCube + sizeof(verticeCube) / sizeof(Vertex));
	std::vector <GLuint> ind(indiceCube, indiceCube + sizeof(indiceCube) / sizeof(GLuint));
	std::vector <Texture> tex(plankTextures, plankTextures + sizeof(plankTextures) / sizeof(Texture));
	Mesh cubeMesh(verts, ind, tex);

	// Brick cube meshw 
	std::vector <Texture> tex2(brickTextures, brickTextures + sizeof(brickTextures) / sizeof(Texture));
	Mesh cubeBrickMesh(verts, ind, tex2);

	// Game objects
	std::vector<GameObject*> gameObjects;

	GameObject floor = GameObject(cubeMesh);
	floor.setPosition(glm::vec3(0.0f, -0.5f, 0.0f));
	floor.setScale(glm::vec3(10.0f, 0.5f, 10.0f));
	floor.setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	gameObjects.push_back(&floor);

	GameObject leftWall = GameObject(cubeMesh);
	leftWall.setPosition(glm::vec3(-7.5f, 5.0f, 0.0f));
	leftWall.setScale(glm::vec3(0.5f, 5.0f, 10.0f));
	leftWall.setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	gameObjects.push_back(&leftWall);

	GameObject rightWall = GameObject(cubeMesh);
	rightWall.setPosition(glm::vec3(7.5f, 5.0f, 0.0f));
	rightWall.setScale(glm::vec3(0.5f, 5.0f, 10.0f));
	rightWall.setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	gameObjects.push_back(&rightWall);

	GameObject backWall = GameObject(cubeMesh);
	backWall.setPosition(glm::vec3(0.0f, 5.0f, -7.5f));
	backWall.setScale(glm::vec3(10.0f, 5.0f, 0.5f));
	backWall.setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	gameObjects.push_back(&backWall);

	GameObject frontWall = GameObject(cubeMesh);
	frontWall.setPosition(glm::vec3(0.0f, 5.0f, 7.5f));
	frontWall.setScale(glm::vec3(10.0f, 5.0f, 0.5f));
	frontWall.setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	gameObjects.push_back(&frontWall);

	GameObject leftWall2 = GameObject(cubeBrickMesh);
	leftWall2.setPosition(glm::vec3(-3.5f, 1.0f, 0.0f));
	leftWall2.setScale(glm::vec3(0.5f, 2.0f, 1.5f));
	leftWall2.setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	gameObjects.push_back(&leftWall2);

	GameObject rightWall2 = GameObject(cubeBrickMesh);
	rightWall2.setPosition(glm::vec3(3.5f, 1.0f, 0.0f));
	rightWall2.setScale(glm::vec3(0.5f, 2.0f, 1.5f));
	rightWall2.setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	gameObjects.push_back(&rightWall2);

	GameObject backWall2 = GameObject(cubeBrickMesh);
	backWall2.setPosition(glm::vec3(0.0f, 1.0f, -3.5f));
	backWall2.setScale(glm::vec3(1.5f, 2.0f, 0.5f));
	backWall2.setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	gameObjects.push_back(&backWall2);

	GameObject frontWall2 = GameObject(cubeBrickMesh);
	frontWall2.setPosition(glm::vec3(0.0f, 1.0f, 3.5f));
	frontWall2.setScale(glm::vec3(1.5f, 2.0f, 0.5f));
	frontWall2.setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	gameObjects.push_back(&frontWall2);

	/*
	* Middle object
	*/

	GameObject objectTop = GameObject(cubeMesh);
	objectTop.setPosition(glm::vec3(0.0f, 1.5f, 0.0f));
	objectTop.setScale(glm::vec3(0.5f, 0.2f, 0.5f));
	objectTop.setRotation(glm::vec3(0.0f, 45.0f, 0.0f));
	gameObjects.push_back(&objectTop);

	GameObject objectMiddle = GameObject(cubeMesh);
	objectMiddle.setPosition(glm::vec3(0.0f, 1.0f, 0.0f));
	objectMiddle.setScale(glm::vec3(0.2f, 0.5f, 0.2f));
	objectMiddle.setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	gameObjects.push_back(&objectMiddle);

	GameObject objectBottom = GameObject(cubeMesh);
	objectBottom.setPosition(glm::vec3(0.0f, 0.5f, 0.0f));
	objectBottom.setScale(glm::vec3(0.5f, 0.2f, 0.5f));
	objectBottom.setRotation(glm::vec3(0.0f, 45.0f, 0.0f));
	gameObjects.push_back(&objectBottom);

	// Light factory
	LightFactory lightFactory;

	// Directinal light
	glm::vec3 lightPos0 = glm::vec3(0.0f, 10.0f, 0.0f);
	glm::vec4 lightColor0 = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	glm::vec3 lightDirection0 = glm::vec3(0.0f, -1.0f, 0.5f);
	DirectionalLight* dirLight = lightFactory.generateDirectionalLight(lightPos0, lightColor0, lightDirection0);
	dirLight->setShadowActive(true);

	// Spot lights
	glm::vec3 lightpos1 = glm::vec3(0.0f, 0.5f, 0.0f);
	glm::vec4 lightcolor1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightdirection1 = glm::vec3(0.0f, -1.0f, 0.0f);
	float innercone1 = 0.95f;
	float outercone1 = 0.80f;
	SpotLight* spotLight1 = lightFactory.generateSpotLight(lightpos1, lightcolor1, lightdirection1, innercone1, outercone1);

	glm::vec3 lightpos2 = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec4 lightcolor2 = glm::vec4(0.4f, 1.0f, 0.4f, 1.0f);
	glm::vec3 lightdirection2 = glm::vec3(1.0f, 0.0f, 0.0f);
	float innercone2 = 0.95f;
	float outercone2 = 0.80f;
	SpotLight* spotLight2 = lightFactory.generateSpotLight(lightpos2, lightcolor2, lightdirection2, innercone2, outercone2);
	spotLight2->setShadowActive(true);

	glm::vec3 lightpos3 = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec4 lightcolor3 = glm::vec4(1.0f, 0.4f, 0.4f, 1.0f);
	glm::vec3 lightdirection3 = glm::vec3(-1.0f, 0.0f, 0.0f);
	float innercone3 = 0.95f;
	float outercone3 = 0.80f;
	SpotLight* spotLight3 = lightFactory.generateSpotLight(lightpos3, lightcolor3, lightdirection3, innercone3, outercone3);
	spotLight3->setShadowActive(true);

	glm::vec3 lightpos4 = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec4 lightcolor4 = glm::vec4(0.4f, 0.4f, 1.0f, 1.0f);
	glm::vec3 lightdirection4 = glm::vec3(0.0f, 0.0f, -1.0f);
	float innercone4 = 0.95f;
	float outercone4 = 0.80f;
	SpotLight* spotLight4 = lightFactory.generateSpotLight(lightpos4, lightcolor4, lightdirection4, innercone4, outercone4);
	spotLight4->setShadowActive(true);

	glm::vec3 lightpos5 = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec4 lightcolor5 = glm::vec4(0.3f, 0.8f, 0.9f, 1.0f);
	glm::vec3 lightdirection5 = glm::vec3(0.0f, 0.0f, 1.0f);
	float innercone5 = 0.95f;
	float outercone5 = 0.80f;
	SpotLight* spotLight5 = lightFactory.generateSpotLight(lightpos5, lightcolor5, lightdirection5, innercone5, outercone5);
	spotLight5->setShadowActive(true);

	// Point light
	/*glm::vec3 lightPos6 = glm::vec3(5.0f, 2.0f, 0.0f);
	glm::vec4 lightColor6 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	float constant6 = 0.5f;
	float linear6 = 0.5f;
	float quadratic6 = 1.0f;
	PointLight* pointLight = lightFactory.getPointLight(lightPos6, lightColor6, constant6, linear6, quadratic6);*/


	/**
	* Main loop
	* --------------------------------------------------
	**/

	float prevTime = 0;
	float timeDiff = 0;
	float fps = 0;
	while (!glfwWindowShouldClose(window)) {
		// FPS calculator
		timeDiff = (float)glfwGetTime() - prevTime;
		prevTime = (float)glfwGetTime();
		fps = 1 / timeDiff;
		std::cout <<  "FPS: " << static_cast<int>(fps) << std::endl;
		
		// Set up camera inputs and update it after it was changed by the input
		camera.inputs2(window);
		camera.updateMatrix();

		float rotationSp = 10.0f; // 10 degrees/sec
		float upSp = 0.1f; // 0.1 m/sec

		objectTop.changeRotation(glm::vec3(0.0f, rotationSp, 0.0f) * timeDiff);
		objectMiddle.changeRotation(glm::vec3(0.0f, rotationSp, 0.0f) * timeDiff);
		objectBottom.changeRotation(glm::vec3(0.0f, rotationSp, 0.0f) * timeDiff);

		objectTop.changePosition(glm::vec3(0.0f, upSp, 0.0f) * timeDiff);
		objectMiddle.changePosition(glm::vec3(0.0f, upSp, 0.0f) * timeDiff);
		objectBottom.changePosition(glm::vec3(0.0f, upSp, 0.0f) * timeDiff);

		spotLight2->changeDirection(glm::vec3(0.0f, rotationSp, 0.0f) * timeDiff);
		spotLight3->changeDirection(glm::vec3(0.0f, rotationSp, 0.0f) * timeDiff);
		spotLight4->changeDirection(glm::vec3(0.0f, rotationSp, 0.0f) * timeDiff);
		spotLight5->changeDirection(glm::vec3(0.0f, rotationSp, 0.0f) * timeDiff);

		spotLight1->changePosition(glm::vec3(0.0f, upSp, 0.0f) * timeDiff);
		spotLight2->changePosition(glm::vec3(0.0f, upSp, 0.0f) * timeDiff);
		spotLight3->changePosition(glm::vec3(0.0f, upSp, 0.0f) * timeDiff);
		spotLight4->changePosition(glm::vec3(0.0f, upSp, 0.0f) * timeDiff);
		spotLight5->changePosition(glm::vec3(0.0f, upSp, 0.0f) * timeDiff);

		/**
		 * Rendering
		 * --------------------------------------------------
		**/

		// Calculate shadows
		depthMapShader.activateShader();
		lightFactory.updateShadowMaps(depthMapShader, gameObjects);

		// Rendering
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glViewport(0, 0, DEFAULT_MONITOR_WIDTH, DEFAULT_MONITOR_HEIGHT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.activateShader();
		camera.setCameraPosition(shader, "camPos");
		camera.setCameraMatrix(shader, "camMatrix");
		lightFactory.update(shader);
		for (const auto& object : gameObjects) {
			object->draw(shader);
		}

		// Depth map testing
		// depthMapShaderDebug.activateShader();
		// light->getShadow().assignTexture(depthMapShaderDebug, 0, "shadowMap");
		// renderQuad();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Program termination
	/*glfwDestroyWindow(window);
	glfwTerminate();
	return 0;*/
}

// Renders flat block to display data (for depth map testing)
// -----------------------------------------
unsigned int quadVAO = 0;
unsigned int quadVBO;
void renderQuad() {
	if (quadVAO == 0) {
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