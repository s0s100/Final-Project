#include "SpotLight.h"

SpotLight::SpotLight(){}

SpotLight::SpotLight(glm::vec3 position, glm::vec4 color, glm::vec3 direction, float innecCone, float outerCone): DirectionalLight(position, color, direction) {
	SpotLight::innerCone = innecCone;
	SpotLight::outerCone = outerCone;
}

float SpotLight::getInnerCone() {
	return innerCone;
}

float SpotLight::getOuterCone() {
	return outerCone;
}

void SpotLight::setShaderData(Shader shader, std::string path) {
	DirectionalLight::setShaderData(shader, path);
	
	std::string resultPath;
	resultPath = path + "innerCone";
	shader.setFloat(resultPath, this->innerCone);

	// std::cout << resultPath << ": " << this->innerCone << std::endl;

	resultPath = path + "outerCone";
	shader.setFloat(resultPath, this->outerCone);

	// std::cout << resultPath << ": " << this->outerCone << std::endl;
}

void SpotLight::updateLightMatrix() {
	this->shadow.calculateSpotMatrix(this->getPosition(), this->getDirection());
	// this->shadow.calculateMatrix(this->getPosition(), this->getDirection());
}