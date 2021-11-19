#include "SpotLight.h"

SpotLight::SpotLight(){}

SpotLight::SpotLight(glm::vec3 position, glm::vec4 color, glm::vec3 direction, float innecCone, float outerCone): Light(position, color)
{
	SpotLight::direction = direction;
	SpotLight::innerCone = innecCone;
	SpotLight::outerCone = outerCone;
}

glm::vec3 SpotLight::getDirection()
{
	return direction;
}

float SpotLight::getInnerCone()
{
	return innerCone;
}

float SpotLight::getOuterCone()
{
	return outerCone;
}

void SpotLight::setDirection(glm::vec3 dir)
{
	this->direction = dir;
}

