#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() :shadowActive(true),
	direction(glm::vec3(0.0f)){}

DirectionalLight::DirectionalLight(glm::vec3 position, 
	glm::vec4 color, glm::vec3 direction) 
	: Light(position, color), shadowActive(true) {

	this->direction = direction;
}

glm::vec3 DirectionalLight::getDirection() {
	return direction;
}

bool DirectionalLight::getShadowActive() {
	return shadowActive;
}

void DirectionalLight::setDirection(glm::vec3 dir) {
	this->direction = dir;
}

void DirectionalLight::setShadowActive(bool isActive) {
	this->shadowActive = isActive;
}

void DirectionalLight::setShaderData(Shader shader, std::string path) {
	Light::setShaderData(shader, path);
	
	std::string resultPath;
	resultPath = path + "direction";
	shader.setVec3(resultPath, this->direction);

	// std::cout << resultPath << ": " << glm::to_string(direction) << std::endl;

	resultPath = path + "isShadowing";
	shader.setBool(resultPath, this->shadowActive);

	// std::cout << resultPath << ": " << shadowActive << std::endl;
}

void DirectionalLight::setShadowShaderData(Shader shader, std::string path, int textureLocation) {
	// std::cout << "---Shadow shader data---" << std::endl;

	std::string resultPath;
	std::string mapLocation = "shadowMap[" + std::to_string(textureLocation) + "]";

	// std::cout << "Map location: " << mapLocation << std::endl;

	this->shadow.assignTexture(shader, textureLocation + TEXTURE_SHIFT, mapLocation);

	resultPath = path + "lightMatrix";
	this->shadow.assignLightMatrix(shader, resultPath);

	// std::cout << resultPath << std::endl;

	// Connects depth map and light object
	resultPath = path + "mapPosition";
	shader.setInt(resultPath, textureLocation);

	// std::cout << resultPath << ": " << textureLocation << std::endl;
}

void DirectionalLight::updateLightMatrix() {
	this->shadow.calculateMatrix(this->getPosition(), this->getDirection());
}

void DirectionalLight::updateDepthMap(Shader shader, std::vector<GameObject*> objects) {
	this->shadow.generateDepthMap(shader, objects);
}

void DirectionalLight::updateDepthMap(Shader shader, std::vector<GameObject>& objects) {
	this->shadow.generateDepthMap(shader, objects);
}

Shadow DirectionalLight::getShadow() {
	return this->shadow;
}

void DirectionalLight::changeDirection(glm::vec3 dirChange) {
	direction = glm::rotateX(direction, glm::radians(dirChange.x));
	direction = glm::rotateY(direction, glm::radians(dirChange.y));
	direction = glm::rotateZ(direction, glm::radians(dirChange.z));
}