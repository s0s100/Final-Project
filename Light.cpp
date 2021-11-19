#include "Light.h"

Light::Light(){}

Light::Light(glm::vec3 position, glm::vec4 color)
{
	Light::position = position;
	Light::color = color;
}

glm::vec3 Light::getPosition()
{
	return Light::position;
}

glm::vec4 Light::getColor()
{
	return Light::color;
}