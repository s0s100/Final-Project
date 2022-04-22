#ifndef LIGHT_FACTORY_CLASS_HEADER
#define LIGHT_FACTORY_CLASS_HEADER

#include <vector>
#include <map>

#include "ShaderClass.h"
#include "Shadow.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

class LightFactory {
private:
	std::vector<DirectionalLight*> directionalLights;
	std::vector<PointLight*> pointLights;
	std::vector<SpotLight*> spotLights;

	// Texture shift in the shader slot
	inline static const int texFrom = 16;
public:
	LightFactory();

	// Generate and return object, save it to one of the pointer vectors
	DirectionalLight* generateDirectionalLight(glm::vec3 position, glm::vec4 color, glm::vec3 direction);
	SpotLight* generateSpotLight(glm::vec3 position, glm::vec4 color, glm::vec3 direction, float innecCone, float outerCone);
	PointLight* generatePointLight(glm::vec3 position, glm::vec4 color, float constant, float linear, float quadratic);

	// Simply return number of elements in the vector
	size_t getDirectionalLightSize();
	size_t getSpotLightSize();
	size_t getPointLightSize();

	// Get specific light source
	DirectionalLight* getDirectionalLight(int index);
	SpotLight* getSpotLight(int index);
	PointLight* getPointLight(int index);


	// Update funtion for the shader
	void update(Shader shader);
	// Update depth maps and light matrices
	void updateShadowMaps(Shader shader, std::vector<GameObject*> objects);
	void updateShadowMaps(Shader shader, std::vector<GameObject>& objects);
};

#endif
