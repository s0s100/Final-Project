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
void firstDemonstation(GLFWwindow* window);


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

/*
	Functions
*/

int main() {
	GLFWwindow* window = glInitialize();

	firstDemonstation(window);

	return glStop(window);
}

GLFWwindow* glInitialize() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window with the game scene
	// GLFWwindow* window = glfwCreateWindow(DEFAULT_MONITOR_WIDTH, DEFAULT_MONITOR_HEIGHT, "Default window", NULL, NULL);
	// Create full screen window with the game scene
	 GLFWwindow* window = glfwCreateWindow(DEFAULT_MONITOR_WIDTH, DEFAULT_MONITOR_HEIGHT, "Test window", glfwGetPrimaryMonitor(), NULL);

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

void firstDemonstation(GLFWwindow* window) {
	// Put pos according to the cubes
	const glm::vec3 camPos(2.5, 5.0f, -5.0f);
	const glm::vec3 camOrient(0.0f, -0.5f, 1.0f);
	Camera camera(DEFAULT_MONITOR_WIDTH, DEFAULT_MONITOR_HEIGHT, camPos, camOrient);

	Shader basicShader((shaderPath + "default.vert").c_str(), (shaderPath + "default.frag").c_str());
	Shader depthMapShader((shaderPath + "depthMapShader.vert").c_str(), (shaderPath + "depthMapShader.frag").c_str());

	Scene scene(camera, window, basicShader, depthMapShader);

	// Brick texture
	// 1024 x 1024, 5.5 MB, 72 dpi, 64 bit
	/*Texture brickTextures[]{
		Texture((texturePath + "brick.png").c_str(), "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture((texturePath + "brick.png").c_str(), "specular", 1, GL_RGBA, GL_UNSIGNED_BYTE)
	};*/

	// Brick textures
	// Taken from: https://learnopengl.com/img/textures/container2.png
	//			   https://learnopengl.com/img/textures/container2_specular.png
	Texture brickTextures[]{
		Texture((texturePath + "container.png").c_str(), "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture((texturePath + "container_specular.png").c_str(), "specular", 1, GL_RGBA, GL_UNSIGNED_BYTE)
	};
	scene.addTexture(brickTextures);

	// Add cube mesh
	std::vector <Vertex> verts(verticeCube, verticeCube + sizeof(verticeCube) / sizeof(Vertex));
	std::vector <GLuint> ind(indiceCube, indiceCube + sizeof(indiceCube) / sizeof(GLuint));
	std::vector <Texture> tex(brickTextures, brickTextures + sizeof(brickTextures) / sizeof(Texture));
	Mesh cubeMesh(verts, ind, tex);
	scene.addMesh(cubeMesh);

	// Factory pointer
	LightFactory& lightFactory = scene.getLightFactory();

	/*
	* Populating with objects and light
	*/

	// Directinal light for now
	/*glm::vec3 lightPos0 = glm::vec3(0.0f, 10.0f, 0.0f);
	glm::vec4 lightColor0 = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	glm::vec3 lightDirection0 = glm::vec3(-0.3f, -1.0f, -0.1f);
	DirectionalLight* dirLight = lightFactory.generateDirectionalLight(lightPos0, lightColor0, lightDirection0);*/

	// Populate scene with objects
	const float sceneSize = 10;
	const int xParam = 75;
	const int zParam = 75;
	float boxSize = 0.060;
	GameObject* objects[xParam][zParam];

	glm::vec3 pos(0.0f, 0.0f, 0.0f);
	glm::vec3 scale(boxSize, boxSize * 2, boxSize);
	glm::vec3 rotation(0.0f, 0.0f, 0.0f);
	for (int curH = 0; curH < zParam; curH++) {
		for (int curW = 0; curW < xParam; curW++) {
			objects[curH][curW] = scene.createObject(0, pos, scale, rotation);

			pos.x += sceneSize / xParam;
		}
		pos.x = 0.0f;
		pos.z += sceneSize / xParam;
	}

	// 
	/*scene.createObject(0, glm::vec3(sceneSize / 2, -2, sceneSize / 2),
		glm::vec3(sceneSize, 0.1, sceneSize), glm::vec3(0, 0, 0));*/

	// Create 2 light sources
	glm::vec3 lightTo = glm::vec3(sceneSize / 2, 0.0f, sceneSize / 2);

	glm::vec3 sunPos = glm::vec3(sceneSize / 2, 10.0f, sceneSize / 2);
	glm::vec3 moonPos = glm::vec3(sceneSize / 2, -10.0f, sceneSize / 2);

	glm::vec4 sunColor = glm::vec4(0.97265625f, 0.83984375f, 0.109375f, 1.0f);
	glm::vec4 moonColor = glm::vec4(0.7578125f, 0.76953125f, 0.796875f, 1.0f);

	glm::vec3 sunDirection = glm::vec3(0.0f, -1.0f, 0.0f);
	glm::vec3 moonDirection = glm::vec3(0.0f, 1.0f, 0.0f);

	float innercone = 0.98f;
	float outercone = 0.75f;

	SpotLight* sun = lightFactory.generateSpotLight(sunPos, sunColor, sunDirection, innercone, outercone);
	/*SpotLight* moon = lightFactory.generateSpotLight(moonPos, moonColor, moonDirection, innercone, outercone);*/
	sun->setShadowActive(false);
	/*moon->setShadowActive(false);*/

	// Run the loop
	double yPos;
	double param;

	// FPS counter
	double curTime;
	float prevTime = 0;
	float timeDiff = 0;
	float fps = 0;

	// Extra info
	double pi = 3.1415926535;
	while (!glfwWindowShouldClose(window)) {
		curTime = glfwGetTime();
		timeDiff = curTime - prevTime;
		prevTime = curTime;
		fps = 1 / timeDiff;
		std::cout << "FPS: " << static_cast<int>(fps) << std::endl;

		for (int i = 0; i < zParam; i++) {
			for (int j = 0; j < xParam; j++) {
				param = (double)i + (double)j + curTime;
				if (param > 263 || param < -263) {
					param -= 360;
				}
				yPos = 0.1 * sin(param);
				objects[i][j]->setPosition(glm::vec3(sceneSize / xParam * j, yPos, sceneSize / zParam * i));
			}
		}

		// Also change the location of the light
		

		scene.iterate();
	}	
}