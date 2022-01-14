#ifndef DIRECTIONAL_LIGHT_CLASS_HEADER
#define DIRECTIONAL_LIGHT_CLASS_HEADER

#include "Light.h"

class DirectionalLight: public Light
{
public:
	DirectionalLight();
	DirectionalLight(glm::vec3 position, glm::vec4 color, glm::vec3 direction);
};

#endif