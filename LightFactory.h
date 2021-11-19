#ifndef LIGHT_FACTORY_CLASS_HEADER
#define LIGHT_FACTORY_CLASS_HEADER

#include <vector>

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "ShaderClass.h"

class LightFactory
{
private:
	std::vector<DirectionalLight*> directionalLights;
	std::vector<PointLight*> pointLights;
	std::vector<SpotLight*> spotLights;

public:
	LightFactory();

	// Generate and return object, save them to the vector
	// Also change it's value

	// Only the direction of the light
	DirectionalLight getDirectionalLight(glm::vec3 position, glm::vec4 color, glm::vec3 direction);
	// Constant is mostly 1 equal to 1. Linear and quadratic value decreases as we increase light distance
	SpotLight* getSpotLight(glm::vec3 position, glm::vec4 color, glm::vec3 direction, float innecCone, float outerCone);
	// Direction of the light as well as light cone parameters
	PointLight getPointLight(glm::vec3 position, glm::vec4 color, float constant, float linear, float quadratic);

	// Simply return number of elements in the vector
	int getDirectionalLightSize();
	int getSpotLightSize();
	int getPointLightSize();

	// Update funtion for the shader
	void update(Shader shader);
};

#endif
