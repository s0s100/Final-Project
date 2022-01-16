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