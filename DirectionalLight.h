#ifndef DIRECTIONAL_LIGHT_CLASS_HEADER
#define DIRECTIONAL_LIGHT_CLASS_HEADER

#include "Light.h"
#include "Shadow.h"

class DirectionalLight: public Light {
private:
	glm::vec3 direction = glm::vec3(0.0f);
	// Also shadow implementation
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
};

#endif