#version 330 core

#define NR_DIR_LIGHT 10
#define NR_POINT_LIGHT 10
#define NR_SPOT_LIGHT 10

#define AMBIENT 0.1f
#define DIFFUSE 0.4f
#define SPECULAR 0.7f

struct DirectionalLight {
	vec3 position;
	vec4 color;

	vec3 direction;
};

struct PointLight {
	vec3 position;
	vec4 color;

	float constant;
	float linear;
	float quadratic;
};

struct SpotLight {
	vec3 position;
	vec4 color;

	vec3 direction;
	float innerCone;
	float outerCone;
};

// Outputs colors in RGBA
out vec4 FragColor;

// Input fragment current position
in vec3 crntPos;
// Input fragment normal
in vec3 normal;
// Inputs the texture coordinates from the Vertex Shader
in vec2 texCoord;
// Test frag pos light space
in vec4 fragPosLightSpace;

// Camera position
uniform vec3 camPos;
// Standart diffuse unit texture
uniform sampler2D diffuse0;
// Specular light map unit
uniform sampler2D specular0;
// Shadow map texture
uniform sampler2D shadowMap;

// Light arrays
uniform DirectionalLight directionalLights[NR_DIR_LIGHT];
uniform PointLight pointLights[NR_POINT_LIGHT];
uniform SpotLight spotLights[NR_SPOT_LIGHT];

// Number of the lights on the scene
uniform int directionalLightNum;
uniform int pointLightNum;
uniform int spotLightNum;

vec4 calculateDirectionalLight(DirectionalLight directionalLight) {
	// Define variables
	vec4 lightClr = directionalLight.color;
	vec3 lightDirection = normalize(directionalLight.direction);
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);

	// Ambient
	float ambient = AMBIENT;

	// Diffuse
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// Specular
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 32);
	float specular = specAmount * SPECULAR;

	vec4 result = (texture(diffuse0, texCoord) * (diffuse + ambient)
	+ texture(specular0, texCoord).r * specular) * lightClr;
	return result;
}

vec4 calculatePointLight(PointLight pointLight) {
	vec4 lightClr = pointLight.color;
	vec3 lightPos = pointLight.position;
	float constant = pointLight.constant; // c
	float linear = pointLight.linear; // b
	float quadratic = pointLight.quadratic; // a

	vec3 lightVec = lightPos - crntPos;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 lightDirection = normalize(lightVec);
	vec3 reflectionDirection = reflect(-lightDirection, normal);

	float dist = length(lightVec);
	float inten = 1.0f / (quadratic * dist * dist + linear * dist + constant);

	// Ambient
	float ambient = AMBIENT;

	// Diffuse
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// Specular
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 32);
	float specular = specAmount * SPECULAR; 

	vec4 result = (texture(diffuse0, texCoord) * (diffuse * inten + ambient)
	+ texture(specular0, texCoord).r * specular * inten) * lightClr;
	return result;
}

// This works fine for spot light
float shadowCalculation(vec4 fragPosLightSpace, vec3 lightDir) {
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // Removes shadow acne
	float bias = max(0.01 * (1.0 - dot(normal, lightDir)), 0.001);
	// check whether current frag pos is in shadow
    float shadow = 0.0f;
	vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
	// Parse the texture and for each of the points calculate the value
    for(int x = -1; x <= 1; ++x) {
        for(int y = -1; y <= 1; ++y) {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
	// Shadow now is [0,9], normalize it
    shadow /= 9.0; 
    
    // If outside of the bounds, set to 0
    if(projCoords.z > 1.0) {
		shadow = 0.0;
	}

    return shadow;
}

vec4 calculateSpotLight(SpotLight spotLight) {
	// Define values
	float innerCone = 0.95f;
	float outerCone = 0.80f;
	vec4 lightClr = spotLight.color;
	vec3 lightPs = spotLight.position;

	vec3 lightDirection = normalize(lightPs - crntPos);
	// vec3 lightDirection = normalize(spotLight.direction);
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);

	// Ambient
	float ambient = AMBIENT;

	// Diffuse
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// Specular
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 32);
	float specular = specAmount * SPECULAR;

	// Spot light params
	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	// vec4 result = (texture(diffuse0, texCoord) * (diffuse * inten + ambient) + texture(specular0, texCoord).r * specular * inten) * lightClr;
	float shadow = shadowCalculation(fragPosLightSpace, spotLight.direction); 
	
	vec4 result = (texture(diffuse0, texCoord) * (diffuse * inten * (1 - shadow)  + ambient)
	+ texture(specular0, texCoord).r * specular * inten * (1 - shadow)) * lightClr;
	return result;
}

void main() {	
	vec4 finalColor = vec4(0.0f);

	// Directional lights
	for (int i = 0; i < directionalLightNum; i++) {
		finalColor += calculateDirectionalLight(directionalLights[i]);
	}

	// Point lights
	for (int i = 0; i < pointLightNum; i++) {
		finalColor += calculatePointLight(pointLights[i]);
	}

	// Spot lights
	for (int i = 0; i < spotLightNum; i++) {
		finalColor += calculateSpotLight(spotLights[i]);
	}

	FragColor = finalColor;	
}