#ifndef LIGHT_CLASS_HEADER
#define LIGHT_CLASS_HEADER

#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "ShaderClass.h"

// The location from which textures are stored
constexpr int TEXTURE_SHIFT = 16;

class Light {
private:
	glm::vec3 position;
	glm::vec4 color;
	glm::mat4 lightSpaceMatrix;


public:
	Light();
	Light(glm::vec3 position, glm::vec4 color);

	void addPosition(glm::vec3 addedPos);

	glm::vec3 getPosition();
	glm::vec4 getColor();
	
	void setPosition(glm::vec3 pos);
	void setColor(glm::vec4 col);

	void changePosition(glm::vec3 posChange);

	// Fills the following shader data
	void setShaderData(Shader shader, std::string path);
};

#endif