#include "PointLight.h"

PointLight::PointLight(){}

PointLight::PointLight(glm::vec3 position, glm::vec4 color, float constant, float linear, float quadratic) : Light(position, color)
{
	Light(position, color);
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
}

float PointLight::getC()
{
	return constant;
}

float PointLight::getL()
{
	return linear;
}

float PointLight::getQ()
{
	return quadratic;
}