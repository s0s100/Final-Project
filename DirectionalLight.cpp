#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(){}

DirectionalLight::DirectionalLight(glm::vec3 position, glm::vec4 color, glm::vec3 direction) : Light(position, color) {
	this->direction = direction;
}

glm::vec3 DirectionalLight::getDirection() {
	return direction;
}

Shadow DirectionalLight::getShadow() {
	return shadow;
}

bool DirectionalLight::isShadowActive() {
	return shadowActive;
}

void DirectionalLight::setDirection(glm::vec3 dir) {
	this->direction = dir;
}

void DirectionalLight::setShadovActive(bool isActive) {
	this->shadowActive = isActive;
}

void DirectionalLight::setShaderData(Shader shader, std::string path) {
	Light::setShaderData(shader, path);
	
	std::string resultPath;
	resultPath = path + "direction";
	shader.setVec3(resultPath, this->direction);

	std::cout << resultPath << ": " << glm::to_string(direction) << std::endl;

	resultPath = path + "isShadowing";
	shader.setBool(resultPath, this->shadowActive);

	std::cout << resultPath << ": " << shadowActive << std::endl;
}

void DirectionalLight::setShadowShaderData(Shader shader, std::string path, int textureLocation) {
	Shadow shadow = this->shadow;

	std::cout << "---Shadow shader data---" << std::endl;

	std::string resultPath;
	std::string mapLocation = "shadowMap[" + std::to_string(textureLocation) + "]";;
	std::cout << "Map location: " << mapLocation << std::endl;

	shadow.calculateMatrix(this->getPosition(), this->getDirection());
	shadow.assignTexture(shader, textureLocation + TEXTURE_SHIFT, mapLocation);

	resultPath = path + "lightMatrix";
	shadow.assignLightMatrix(shader, resultPath);

	std::cout << resultPath << std::endl;

	// Connects depth map and light object
	resultPath = path + "mapPosition";
	shader.setInt(resultPath, textureLocation);

	std::cout << resultPath << ": " << textureLocation << std::endl;
}