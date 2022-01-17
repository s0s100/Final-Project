#include "Light.h"

Light::Light() {}

Light::Light(glm::vec3 position, glm::vec4 color) {
	Light::position = position;
	Light::color = color;
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

void Light::setShaderData(Shader shader, std::string path) {
	// Path variable is a reference to the array object with a dot in the end
	std::string resultPath;

	// std::cout << "---Shader data---" << std::endl;

	resultPath = path + "position";
	shader.setVec3(resultPath, this->position);

	// std::cout << resultPath << ": " << glm::to_string(this->position) << std::endl;

	resultPath = path + "color";
	shader.setVec4(resultPath, this->color);

	// std::cout << resultPath << ": " << glm::to_string(this->color) << std::endl;
}