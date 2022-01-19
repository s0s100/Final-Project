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
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec4 color = glm::vec4(1.0f);
	glm::mat4 lightSpaceMatrix = glm::mat4(0.0f);


public:
	Light();
	Light(glm::vec3 position, glm::vec4 color);

	void addPosition(glm::vec3 addedPos);

	glm::vec3 getPosition();
	glm::vec4 getColor();
	
	void setPosition(glm::vec3 pos);
	void setColor(glm::vec4 col);

	void changePosition(glm::vec3 pos);

	// Fills the following shader data
	void setShaderData(Shader shader, std::string path);
};

#endif