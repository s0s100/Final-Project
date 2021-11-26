#include "Light.h"

#include <glm/glm.hpp>

Light::Light(){}

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

//ShadowClass Light::getShadowClass() 
//{
//	return shadow;
//}

glm::vec3 Light::getDirection()
{
	return direction;
}

void Light::setDirection(glm::vec3 direction)
{
	this->direction = direction;
}

void Light::generateLightMatrix()
{
	float near_plane = NEAR_PLANE;
	float far_plane = FAR_PLANE;

	glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, NEAR_PLANE, FAR_PLANE);
	glm::mat4 lightView = glm::lookAt(getPosition(), getPosition() + getDirection(), Y_VECTOR);

	glm::mat4 lightSpaceMatrix = lightProjection * lightView;
	this->lightSpaceMatrix = lightSpaceMatrix;
}

void Light::generateDepthMap(GameObject object, Shader depthShader)
{
	this->shadow.renderDepthMap(object, depthShader, this->lightSpaceMatrix);
}