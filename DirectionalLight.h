#ifndef DIRECTIONAL_LIGHT_CLASS_HEADER
#define DIRECTIONAL_LIGHT_CLASS_HEADER

#include "Light.h"

class DirectionalLight: public Light
{
private:
	// Direction in which light shines
	glm::vec3 direction = glm::vec3(1.0f);

public:
	DirectionalLight();
	DirectionalLight(glm::vec3 position, glm::vec4 color, glm::vec3 direction);

	/*
	* Getters/setters
	*/
	glm::vec3 getDirection();

	void setDirection(glm::vec3 dir);
};

#endif