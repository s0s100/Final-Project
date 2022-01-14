#include "Light.h"

#include <glm/glm.hpp>
#include <iostream>
#include <glm/gtx/string_cast.hpp>

Light::Light(){
	shadow = ShadowClass();
}

Light::Light(glm::vec3 position, glm::vec4 color)
{
	Light::position = position;
	Light::color = color;
	shadow = ShadowClass();
}

Light::Light(glm::vec3 position, glm::vec4 color, glm::vec3 direction)
{
	Light::position = position;
	Light::color = color;
	Light::direction = direction;
	shadow = ShadowClass();
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

ShadowClass Light::getShadowClass() 
{
	return shadow;
}

glm::vec3 Light::getDirection()
{
	return direction;
}

void Light::setDirection(glm::vec3 direction)
{
	this->direction = direction;
}

glm::mat4 Light::getLightMatrix()
{
	return lightSpaceMatrix;
}

void Light::generateLightMatrix()
{
	glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, NEAR_PLANE, FAR_PLANE);

	//std::cout << "LightProj light: " << glm::to_string(lightProjection) << std::endl;

	// Dot product to prevent nan values in the matrix
	float dotProduct = glm::dot(glm::normalize(getDirection()), Y_VECTOR);
	//std::cout << "Dot product" << dotProduct << std::endl;

	glm::mat4 lightView;
	if (dotProduct == -1 || dotProduct == 1) {
		// The other vector
		lightView = glm::lookAt(getPosition(), getPosition() + getDirection(), X_VECTOR);
	}
	else {
		lightView = glm::lookAt(getPosition(), getPosition() + getDirection(), Y_VECTOR);
	}
	
	// glm::mat4 lightView = glm::lookAt(getPosition(), glm::vec3(0.0f), Y_VECTOR);

	//std::cout << "LightView light: " << glm::to_string(lightView) << std::endl;

	glm::mat4 lightSpaceMatrix = lightProjection * lightView;

	//std::cout << "LightMatrix light: " << glm::to_string(lightSpaceMatrix) << std::endl;

	this->lightSpaceMatrix = lightSpaceMatrix;
}

void Light::generateDepthMap(GameObject object, Shader &depthShader)
{
	this->shadow.renderDepthMap(object, depthShader, this->lightSpaceMatrix);
}

void Light::generateDepthMap2(std::vector<GameObject> objects, Shader& shader)
{
	shader.setMat4("lightSpaceMatrix", this->lightSpaceMatrix);
	this->shadow.renderDepthMap2(objects, shader);
}