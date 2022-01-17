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
	std::string path;

	// Texture pointer in the GL texture buffer
	int currentTexturePointer = 0;

	PointLight* pointLight;
	shader.setInt("pointLightNum", (GLint)getPointLightSize());
	for (int i = 0; i < getPointLightSize(); i++) {
		pointLight = pointLights.at(i);
		path = "pointLights[" + std::to_string(i) + "].";
		pointLight->setShaderData(shader, path);
	}

	DirectionalLight* directionalLight;
	shader.setInt("directionalLightNum", (GLint)getDirectionalLightSize());
	for (int i = 0; i < getDirectionalLightSize(); i++) {
		directionalLight = directionalLights.at(i);
		path = "directionalLights[" + std::to_string(i) + "].";
		directionalLight->setShaderData(shader, path);

		if (directionalLight->isShadowActive()) {
			directionalLight->setShadowShaderData(shader, path, currentTexturePointer);
			currentTexturePointer++;
		}
	}

	SpotLight* spotLight;
	shader.setInt("spotLightNum", (GLint)getSpotLightSize());
	for (int i = 0; i < getSpotLightSize(); i++) {
		spotLight = spotLights.at(i);
		path = "spotLights[" + std::to_string(i) + "].";
		spotLight->setShaderData(shader, path);

		if (spotLight->isShadowActive()) {
			spotLight->setShadowShaderData(shader, path, currentTexturePointer);
			currentTexturePointer++;
		}
	}
}

void LightFactory::updateShadowMaps(Shader shader, std::vector<GameObject*> objects) {
	// Check directional and spot light vectors
	Shadow shadow;
	for (DirectionalLight* light : directionalLights) {
		if (light->isShadowActive()) {
			shadow = light->getShadow();
			shadow.calculateMatrix(light->getPosition(), light->getDirection());
			shadow.generateDepthMap(shader, objects);
		}
	}

	for (SpotLight* light : spotLights) {
		if (light->isShadowActive()) {
			shadow = light->getShadow();
			shadow.calculateMatrix(light->getPosition(), light->getDirection());
			shadow.generateDepthMap(shader, objects);
		}
	}
}

