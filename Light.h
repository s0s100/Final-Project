#ifndef LIGHT_CLASS_HEADER
#define LIGHT_CLASS_HEADER

#include <glm/glm.hpp>

class Light
{
private:
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec4 color = glm::vec4(1.0f);

public:
	Light();

	Light(glm::vec3 position, glm::vec4 color);

	glm::vec3 getPosition();
	glm::vec4 getColor();
};

#endif