#include "Light.h"

#include <glm/glm.hpp>
#include <iostream>
#include <glm/gtx/string_cast.hpp>

Light::Light() {}

Light::Light(glm::vec3 position, glm::vec4 color)
{
	Light::position = position;
	Light::color = color;
}

Light::Light(glm::vec3 position, glm::vec4 color, glm::vec3 direction)
{
	Light::position = position;
	Light::color = color;
	Light::direction = direction;
}

glm::vec3 Light::getPosition()
{
	return Light::position;
}

glm::vec4 Light::getColor()
{
	return Light::color;
}

void Light::setPosition(glm::vec3 pos)
{
	this->position = pos;
}

void Light::setColor(glm::vec4 col)
{
	this->color = col;
}

void Light::addPosition(glm::vec3 addedPos)
{
	this->position += addedPos;
}

glm::vec3 Light::getDirection()
{
	return direction;
}

void Light::setDirection(glm::vec3 direction)
{
	this->direction = direction;
}