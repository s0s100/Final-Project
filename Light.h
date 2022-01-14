#ifndef LIGHT_CLASS_HEADER
#define LIGHT_CLASS_HEADER

#include <glm/glm.hpp>

class Light
{
private:
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 direction = glm::vec3(0.0f);
	glm::vec4 color = glm::vec4(1.0f);
	glm::mat4 lightSpaceMatrix = glm::mat4(0.0f);

public:
	Light();

	Light(glm::vec3 position, glm::vec4 color);

	Light(glm::vec3 position, glm::vec4 color, glm::vec3 direction);

	void addPosition(glm::vec3 addedPos);
	/*
		Getters/setters
	*/

	glm::vec3 getPosition();
	glm::vec4 getColor();
	glm::vec3 getDirection();
	
	void setPosition(glm::vec3 pos);
	void setColor(glm::vec4 col);
	void setDirection(glm::vec3 dir);
};

#endif