#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(){}

DirectionalLight::DirectionalLight(glm::vec3 position, glm::vec4 color, glm::vec3 direction) : Light(position, color)
{
	Light(position, color);
	DirectionalLight::direction = direction;
}

glm::vec3 DirectionalLight::getDirection()
{
	return direction;
}