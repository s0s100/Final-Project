#ifndef SHADOW_CLASS_HEADER
#define SHADOW_CLASS_HEADER

#include <glm/glm.hpp>

#include "GameObject.h"
#include "ShaderClass.h"

class ShadowClass
{
private:
	// Depth map framebuffer object id
	unsigned int fboID;
	// Depth map texture which contains map
	unsigned int depthMap;

	// By the default it will be 800x800, might want to 
	// change it according to the screen size or smth
	inline static const int SHADOW_WIDTH = 800;
	inline static const int SHADOW_HEIGHT = 800;

public:
	// Basic constructor
	ShadowClass();

	// Depth map rendering for the object
	void renderDepthMap(GameObject object, Shader depthShader, 
		glm::mat4 lightSpaceMatrix);

	// Calculate light matrix to generate depth map
	//void generateLightMatrix(DirectionalLight light);
	// void generateLightMatrix(SpotLight light);

	// Get shadow width/height
	int getShadowWidth();
	int getShadowHeight();

	// Bind, unbind and delete operation for the depth map and framebuffer
	void bindFBO();
	void bindDepthMap(Shader shader);
	void unbindFBO();
	void unbindDepthMap();
	void deleteFBO();
	void deleteDepthMap();
};

#endif