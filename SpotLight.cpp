#include "SpotLight.h"

SpotLight::SpotLight(){}

SpotLight::SpotLight(glm::vec3 position, glm::vec4 color, glm::vec3 direction, float innecCone, float outerCone): DirectionalLight(position, color, direction) {
	SpotLight::innerCone = innecCone;
	SpotLight::outerCone = outerCone;
}

float SpotLight::getInnerCone() {
	return innerCone;
}

float SpotLight::getOuterCone() {
	return outerCone;
}

