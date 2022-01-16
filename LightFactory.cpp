#include <string>
#include <glm/glm.hpp>
#include <iostream>
#include <glm/gtx/string_cast.hpp>

#include "LightFactory.h"

LightFactory::LightFactory(){}

DirectionalLight* LightFactory::getDirectionalLight(glm::vec3 position, glm::vec4 color, glm::vec3 direction) {
	DirectionalLight* result = new DirectionalLight(position, color, direction);
	directionalLights.push_back(result);

	return result;
}

SpotLight* LightFactory::getSpotLight(glm::vec3 position, glm::vec4 color, glm::vec3 direction, float innecCone, float outerCone) {
	SpotLight* result = new SpotLight(position, color, direction, innecCone, outerCone);
	spotLights.push_back(result);

	return result;
}

PointLight* LightFactory::getPointLight(glm::vec3 position, glm::vec4 color, float constant, float linear, float quadratic) {
	PointLight* result = new PointLight(position, color, constant, linear, quadratic);
	pointLights.push_back(result);

	return result;
}

size_t LightFactory::getDirectionalLightSize() {
	return directionalLights.size();
}

size_t LightFactory::getSpotLightSize() {
	return spotLights.size();
}

size_t LightFactory::getPointLightSize() {
	return pointLights.size();
}

// Weird option to create this one, optimize
void LightFactory::update(Shader shader) {
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

	// Depth map locations in the GL texture buffer, in range [16,31]
	int currentTexturePointer = 0;
	int textureShift = 16;

	// Update point lights
	glUniform1i(glGetUniformLocation(shader.getID(), "pointLightNum"), (GLint)getPointLightSize());
	for (int i = 0; i < getPointLightSize(); i++) {
		path1 = "pointLights[" + std::to_string(i) + "].";

		path2 = path1 + "position";
		//ePosition = pointLights[i].getPosition();
		ePosition = pointLights.at(i)->getPosition();
		glUniform3f(glGetUniformLocation(shader.getID(), path2.c_str()), ePosition.x, ePosition.y, ePosition.z);

		path2 = path1 + "color";
		eColor = pointLights.at(i)->getColor();
		glUniform4f(glGetUniformLocation(shader.getID(), path2.c_str()), eColor.r, eColor.g, eColor.b, eColor.a);

		path2 = path1 + "constant";
		constant = pointLights.at(i)->getC();
		glUniform1f(glGetUniformLocation(shader.getID(), path2.c_str()), constant);

		path2 = path1 + "linear";
		linear = pointLights.at(i)->getL();
		glUniform1f(glGetUniformLocation(shader.getID(), path2.c_str()), linear);

		path2 = path1 + "quadratic";
		quadratic = pointLights.at(i)->getQ();
		glUniform1f(glGetUniformLocation(shader.getID(), path2.c_str()), quadratic);
	}

	// Update direction lights
	glUniform1i(glGetUniformLocation(shader.getID(), "directionalLightNum"), (GLint)getDirectionalLightSize());
	for (int i = 0; i < getDirectionalLightSize(); i++) {
		path1 = "directionalLights[" + std::to_string(i) + "].";

		path2 = path1 + "position";
		ePosition = directionalLights.at(i)->getPosition();
		glUniform3f(glGetUniformLocation(shader.getID(), path2.c_str()), ePosition.x, ePosition.y, ePosition.z);

		// Testing
		// std::cout << ePosition.x << " " << ePosition.y << " " << ePosition.z << std::endl;

		path2 = path1 + "color";
		eColor = directionalLights.at(i)->getColor();
		glUniform4f(glGetUniformLocation(shader.getID(), path2.c_str()), eColor.r, eColor.g, eColor.b, eColor.a);

		// Debug
		//std::cout << path2 << " " << eColor.r << " " << eColor.g << " " << eColor.b << " " << eColor.a << std::endl;

		path2 = path1 + "direction";
		eDirection = directionalLights.at(i)->getDirection();
		glUniform3f(glGetUniformLocation(shader.getID(), path2.c_str()), eDirection.x, eDirection.y, eDirection.z);

		// Shadows
		/*if (directionalLights.at(i)->isShadowActive()) {
			path2 = path1 + "isShadowing";
			shader.setBool(path2, true);

			path2 = path1 + "lightMatrix";
			directionalLights.at(i)->getShadow().setLightMatrix(shader, path2);

			path2 = path1 + "mapPosition";
			shader.setInt(path2, currentTexturePointer);
			currentTexturePointer++;

			std::string location = "shadowMap[" + currentTexturePointer + ']';
			directionalLights.at(i)->getShadow().assignTexture(shader, currentTexturePointer + textureShift, location);

		}
		else {
			path2 = path1 + "isShadowing";
			shader.setBool(path2, false);
		}*/
	}

	// Update spot lights
	SpotLight* spotLight;
	glUniform1i(glGetUniformLocation(shader.getID(), "spotLightNum"), (GLint)getSpotLightSize());
	for (int i = 0; i < getSpotLightSize(); i++) {
		spotLight = spotLights.at(i);
		path1 = "spotLights[" + std::to_string(i) + "].";
		i++;

		path2 = path1 + "position";
		ePosition = spotLight->getPosition();
		glUniform3f(glGetUniformLocation(shader.getID(), path2.c_str()), ePosition.x, ePosition.y, ePosition.z);

		path2 = path1 + "color";
		eColor = spotLight->getColor();
		glUniform4f(glGetUniformLocation(shader.getID(), path2.c_str()), eColor.r, eColor.g, eColor.b, eColor.a);
		
		path2 = path1 + "direction";
		eDirection = spotLight->getDirection();
		glUniform3f(glGetUniformLocation(shader.getID(), path2.c_str()), eDirection.x, eDirection.y, eDirection.z);

		path2 = path1 + "innerCone";
		eInnerCone = spotLight->getInnerCone();
		glUniform1f(glGetUniformLocation(shader.getID(), path2.c_str()), eInnerCone);

		path2 = path1 + "outerCone";
		eOuterCone = spotLight->getOuterCone();
		glUniform1f(glGetUniformLocation(shader.getID(), path2.c_str()), eOuterCone);

		// Shadows
		if (spotLight->isShadowActive()) {
			Shadow shadow = spotLight->getShadow();

			path2 = path1 + "isShadowing";
			std::cout << path2 << std::endl;
			shader.setBool(path2, true);

			path2 = path1 + "mapPosition";
			std::cout << path2 << std::endl;
			shader.setInt(path2, currentTexturePointer);

			std::string location = "shadowMap[" + std::to_string(currentTexturePointer) + "]";
			std::cout << location << std::endl;
			shadow.calculateMatrix(spotLight->getPosition(), spotLight->getDirection());
			shadow.assignTexture(shader, currentTexturePointer + textureShift, location);

			path2 = path1 + "lightMatrix";
			std::cout << path2 << std::endl;
			shadow.setLightMatrix(shader, path2);

			currentTexturePointer++;
		}
		else {
			path2 = path1 + "isShadowing";
			shader.setBool(path2, false);
		}
	}
}

void LightFactory::updateShadowMaps(Shader shader, std::vector<GameObject*> objects) {
	// Check directional and spot light vectors
	Shadow shadow;
	/*for (DirectionalLight* light : directionalLights) {
		if (light->isShadowActive()) {
			shadow = light->getShadow();
			shadow.calculateMatrix(light->getPosition(), light->getDirection());
			shadow.generateDepthMap(shader, objects);
		}
	}*/
	for (SpotLight* light : spotLights) {
		if (light->isShadowActive()) {
			shadow = light->getShadow();
			shadow.calculateMatrix(light->getPosition(), light->getDirection());
			shadow.generateDepthMap(shader, objects);
		}
	}
}