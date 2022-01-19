#ifndef DIRECTIONAL_LIGHT_CLASS_HEADER
#define DIRECTIONAL_LIGHT_CLASS_HEADER

#include <glm/gtx/rotate_vector.hpp>

#include "Light.h"
#include "Shadow.h"

class DirectionalLight: public Light {
private:
	glm::vec3 direction = glm::vec3(0.0f);

	// Shadow implementation
	bool shadowActive = false;
	Shadow shadow = Shadow();

public:
	DirectionalLight();
	DirectionalLight(glm::vec3 position, glm::vec4 color, glm::vec3 direction);

	glm::vec3 getDirection();
	bool getShadowActive();

	void setDirection(glm::vec3 dir);
	void setShadowActive(bool isActive);

	void changeDirection(glm::vec3 dirChange);

	// Fills the following shader data
	void setShaderData(Shader shader, std::string path);
	// Fills shader with shadow data (applicable for the array lists in the shader)
	void setShadowShaderData(Shader shader, std::string path, int textureLocation);

	void updateLightMatrix();
	void updateDepthMap(Shader shader, std::vector<GameObject*> objects);

	Shadow getShadow();
};

#endif