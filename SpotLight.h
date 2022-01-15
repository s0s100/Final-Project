#ifndef SPOT_LIGHT_CLASS_HEADER
#define SPOT_LIGHT_CLASS_HEADER

#include "DirectionalLight.h"

class SpotLight: public DirectionalLight {
private:
	// Light cone parameters to make the light more realistic (light range) 
	float innerCone = 1.0f;
	float outerCone = 0.0f;
public:
	SpotLight();
	SpotLight(glm::vec3 position, glm::vec4 color, glm::vec3 direction, float innecCone, float outerCone);

	float getInnerCone();
	float getOuterCone();
};

#endif