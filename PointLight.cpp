#include "PointLight.h"

PointLight::PointLight(){}

PointLight::PointLight(glm::vec3 position, glm::vec4 color) : Light(position, color) {}

PointLight::PointLight(glm::vec3 position, glm::vec4 color, float constant, float linear, float quadratic) : Light(position, color) {
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
}

float PointLight::getC() {
	return constant;
}

float PointLight::getL() {
	return linear;
}

float PointLight::getQ() {
	return quadratic;
}

void PointLight::setShaderData(Shader shader, std::string path) {
	Light::setShaderData(shader, path);

	std::string resultPath;
	resultPath = path + "constant";
	shader.setFloat(resultPath, this->constant);

	resultPath = path + "linear";
	shader.setFloat(resultPath, this->linear);

	resultPath = path + "quadratic";
	shader.setFloat(resultPath, this->quadratic);
}