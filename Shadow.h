#ifndef SHADOW_CLASS_HEADER
#define SHADOW_CLASS_HEADER

#include <glm/glm.hpp>
#include <vector>

#include "ShaderClass.h"
#include "GameObject.h"

// Basis vectors
#define X_VECTOR glm::vec3(1.0f, 0.0f, 0.0f)
#define Y_VECTOR glm::vec3(0.0f, 1.0f, 0.0f)
#define Z_VECTOR glm::vec3(0.0f, 0.0f, 1.0f)

class Shadow {
private:
	// Id for the generated framebuffer and depth map texture
	unsigned int bufferId;
	unsigned int textureId;
	// Matrix which represents light path
	glm::mat4 lightMatrix;

	// Shadow width/height for the texture
	inline static const int shadowWidth = 2000;
	inline static const int shadowHeight = 2000;

	// Light matrix data
	inline static const float nearPlane = 0.1f;
	inline static const float farPlane = 30.0f;
	inline static const float planeSize = 50.0f;
public:
	// Constructor which initializes buffer and texture
	Shadow();
	// Light matrix calculation using light position and direction
	void calculateMatrix(glm::vec3 lightPos, glm::vec3 lightDir);
	// Light matrix calculation for the spot lights
	void calculateSpotMatrix(glm::vec3 lightPos, glm::vec3 lightDir);
	// Generate depth map texture using shader to use the buffer
	void generateDepthMap(Shader shader, std::vector<GameObject*> objects);
	void generateDepthMap(Shader shader, std::vector<GameObject>& objects);
	// Assign depth map texture from the buffer
	void assignTexture(Shader shader, unsigned int textureNumber, std::string name);
	// Assign matrix to the shader
	void assignLightMatrix(Shader shader, std::string name);
};

#endif

