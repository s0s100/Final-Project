#ifndef POINT_LIGHT_CLASS_HEADER
#define POINT_LIGHT_CLASS_HEADER

#include "Light.h"

class PointLight: public Light {
private:
	// Defines distance of the light
	float constant;
	float linear;
	float quadratic;

public:
	PointLight();
	PointLight(glm::vec3 position, glm::vec4 color);
	PointLight(glm::vec3 position, glm::vec4 color, float constant, float linear, float quadratic);

	float getC();
	float getL();
	float getQ();

	// Fills the following shader data
	void setShaderData(Shader shader, std::string path);
};

#endif
