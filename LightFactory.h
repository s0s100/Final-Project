#ifndef LIGHT_FACTORY_CLASS_HEADER
#define LIGHT_FACTORY_CLASS_HEADER

#include <vector>

#include "ShaderClass.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

class LightFactory {
private:
	std::vector<DirectionalLight*> directionalLights;
	std::vector<PointLight*> pointLights;
	std::vector<SpotLight*> spotLights;

public:
	LightFactory();

	// Generate and return object, save it to one of the pointer vectors
	DirectionalLight* getDirectionalLight(glm::vec3 position, glm::vec4 color, glm::vec3 direction);
	SpotLight* getSpotLight(glm::vec3 position, glm::vec4 color, glm::vec3 direction, float innecCone, float outerCone);
	PointLight* getPointLight(glm::vec3 position, glm::vec4 color, float constant, float linear, float quadratic);

	// Simply return number of elements in the vector
	size_t getDirectionalLightSize();
	size_t getSpotLightSize();
	size_t getPointLightSize();

	// Update funtion for the shader
	void update(Shader shader);
};

#endif
