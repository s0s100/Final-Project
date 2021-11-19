#include <string>
#include <glm/glm.hpp>
#include <iostream>
#include <glm/gtx/string_cast.hpp>

#include "LightFactory.h"

LightFactory::LightFactory(){}

DirectionalLight& LightFactory::getDirectionalLight(glm::vec3 position, glm::vec4 color, glm::vec3 direction)
{
	DirectionalLight result = DirectionalLight(position, color, direction);
	directionalLights.push_back(&result);

	return result;
}

SpotLight& LightFactory::getSpotLight(glm::vec3 position, glm::vec4 color, glm::vec3 direction, float innecCone, float outerCone)
{
	SpotLight result = SpotLight(position, color, direction, innecCone, outerCone);
	spotLights.push_back(&result);

	return result;
}

PointLight& LightFactory::getPointLight(glm::vec3 position, glm::vec4 color, float constant, float linear, float quadratic)
{
	PointLight result = PointLight(position, color, constant, linear, quadratic);
	pointLights.push_back(&result);

	return result;
}

int LightFactory::getDirectionalLightSize()
{
	return directionalLights.size();
}

int LightFactory::getSpotLightSize()
{
	return spotLights.size();
}

int LightFactory::getPointLightSize()
{
	return pointLights.size();
}

// Weird option to create this one, optimize
void LightFactory::update(Shader shader)
{
	shader.activateShader();

	// After activating shader
	// First path with ref. to the lightPos array element
	// Second for the variable inside of it
	std::string path1;
	std::string path2;
	// Elements for the shader
	glm::vec3 ePosition;
	glm::vec4 eColor;
	glm::vec3 eDirection;
	float eInnerCone;
	float eOuterCone;
	float constant;
	float linear;
	float quadratic;

	// Transform references into


	// Update point lights
	glUniform1i(glGetUniformLocation(shader.getID(), "pointLightNum"), getPointLightSize());
	for (int i = 0; i < getPointLightSize(); i++) {
		path1 = "pointLights[" + std::to_string(i) + "].";

		path2 = path1 + "position";
		ePosition = pointLights[i].getPosition();
		// ePosition = pointLights.at(i)->getPosition();
		glUniform3f(glGetUniformLocation(shader.getID(), path2.c_str()), ePosition.x, ePosition.y, ePosition.z);

		path2 = path1 + "color";
		eColor = pointLights[i].getColor();
		glUniform4f(glGetUniformLocation(shader.getID(), path2.c_str()), eColor.r, eColor.g, eColor.b, eColor.a);

		path2 = path1 + "constant";
		constant = pointLights[i].getC();
		glUniform1f(glGetUniformLocation(shader.getID(), path2.c_str()), constant);

		path2 = path1 + "linear";
		linear = pointLights[i].getL();
		glUniform1f(glGetUniformLocation(shader.getID(), path2.c_str()), linear);

		path2 = path1 + "quadratic";
		quadratic = pointLights[i].getQ();
		glUniform1f(glGetUniformLocation(shader.getID(), path2.c_str()), quadratic);
	}

	// Update direction lights
	glUniform1i(glGetUniformLocation(shader.getID(), "directionalLightNum"), getDirectionalLightSize());
	for (int i = 0; i < getDirectionalLightSize(); i++) {
		path1 = "directionalLights[" + std::to_string(i) + "].";

		path2 = path1 + "position";
		ePosition = directionalLights[i].getPosition();
		glUniform3f(glGetUniformLocation(shader.getID(), path2.c_str()), ePosition.x, ePosition.y, ePosition.z);

		// Testing
		// std::cout << ePosition.x << " " << ePosition.y << " " << ePosition.z << std::endl;

		path2 = path1 + "color";
		eColor = directionalLights[i].getColor();
		glUniform4f(glGetUniformLocation(shader.getID(), path2.c_str()), eColor.r, eColor.g, eColor.b, eColor.a);

		// Debug
		//std::cout << path2 << " " << eColor.r << " " << eColor.g << " " << eColor.b << " " << eColor.a << std::endl;

		path2 = path1 + "direction";
		eDirection = directionalLights[i].getDirection();
		glUniform3f(glGetUniformLocation(shader.getID(), path2.c_str()), eDirection.x, eDirection.y, eDirection.z);
	}

	// Update spot lights
	glUniform1i(glGetUniformLocation(shader.getID(), "spotLightNum"), getSpotLightSize());
	for (int i = 0; i < getSpotLightSize(); i++) {
		path1 = "spotLights[" + std::to_string(i) + "].";

		path2 = path1 + "position";
		ePosition = spotLights[i].getPosition();
		glUniform3f(glGetUniformLocation(shader.getID(), path2.c_str()), ePosition.x, ePosition.y, ePosition.z);

		path2 = path1 + "color";
		eColor = spotLights[i].getColor();
		glUniform4f(glGetUniformLocation(shader.getID(), path2.c_str()), eColor.r, eColor.g, eColor.b, eColor.a);
		
		path2 = path1 + "direction";
		eDirection = spotLights[i].getDirection();
		glUniform3f(glGetUniformLocation(shader.getID(), path2.c_str()), eDirection.x, eDirection.y, eDirection.z);

		path2 = path1 + "innerCone";
		eInnerCone = spotLights[i].getInnerCone();
		glUniform1f(glGetUniformLocation(shader.getID(), path2.c_str()), eInnerCone);

		path2 = path1 + "outerCone";
		eOuterCone = spotLights[i].getOuterCone();
		glUniform1f(glGetUniformLocation(shader.getID(), path2.c_str()), eOuterCone);

		std::cout << "LF " << glm::to_string(ePosition) << std::endl;
	}

	// Update point lights
}