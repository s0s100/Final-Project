#ifndef DIRECTIONAL_LIGHT_CLASS_HEADER
#define DIRECTIONAL_LIGHT_CLASS_HEADER

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
	Shadow getShadow();
	bool isShadowActive();
	void setDirection(glm::vec3 dir);
	void setShadovActive(bool isActive);

	// Fills the following shader data
	void setShaderData(Shader shader, std::string path);
	// Fills shader with shadow data
	void setShadowShaderData(Shader shader, std::string path, int textureLocation);
};

#endif