#version 330 core

#define NR_DIR_LIGHT 10
#define NR_POINT_LIGHT 10
#define NR_SPOT_LIGHT 10

#define AMBIENT 0.2f
#define DIFFUSE 0.4f
#define SPECULAR 0.7f

struct DirectionalLight
{
	vec3 position;
	vec4 color;

	vec3 direction;
};

struct PointLight
{
	vec3 position;
	vec4 color;

	float constant;
	float linear;
	float quadratic;
};

struct SpotLight
{
	vec3 position;
	vec4 color;

	vec3 direction;
	float innerCone;
	float outerCone;
};

// Outputs colors in RGBA
out vec4 FragColor;

// Input fragment position
in vec3 crntPos;
// Input fragment normal
in vec3 normal;
// Inputs the texture coordinates from the Vertex Shader
in vec2 texCoord;
// Test frag pos light space
in vec4 fragPosLightSpace;

// Standart diffuse unit texture
uniform sampler2D diffuse0;
// Specular light map unit
uniform sampler2D specular0;
// Shadow map texture
uniform sampler2D shadowMap;
// Camera position
uniform vec3 camPos;

// Light arrays
uniform DirectionalLight directionalLights[NR_DIR_LIGHT];
uniform PointLight pointLights[NR_POINT_LIGHT];
uniform SpotLight spotLights[NR_SPOT_LIGHT];

// Number of the lights on the scene
uniform int directionalLightNum;
uniform int pointLightNum;
uniform int spotLightNum;

vec4 calculateDirectionalLight(DirectionalLight directionalLight)
{
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

	vec4 result = (texture(diffuse0, texCoord) * (diffuse + ambient) + texture(specular0, texCoord).r * specular) * lightClr;
	// return directionalLight.color;
	return result;
}

vec4 calculatePointLight(PointLight pointLight)
{
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

	return (texture(diffuse0, texCoord) * (diffuse * inten + ambient) + texture(specular0, texCoord).r * specular * inten) * lightClr;
}

float ShadowCalculation(vec4 fragPosLightSpace)
{
	// Prospective divide (useless for orthographic projection)
	// [-1, 1]
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	// [ 0, 1]
	projCoords = projCoords * 0.5f + 0.5f;
	// Finding closest depth
	float closestDepth = texture(shadowMap, projCoords.xy).r;
	float currentDepth = projCoords.z; // Problem with value
	// float bias = 0.05f;
	// float shadow = currentDepth - bias > closestDepth ? 1.0f : 0.0f;
	// float shadow = currentDepth > closestDepth ? 1.0f : 0.0f;

	// return 0;
	// return currentDepth; // Makes it black (even ambient value goes to 0)
	return closestDepth; // Value between 0 and 1
	// return shadow; // Always return zero
}

vec4 calculateSpotLight(SpotLight spotLight)
{
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

	float shadow = ShadowCalculation(fragPosLightSpace);

	//vec4 result = vec4(0.0f);
	// vec4 result = (texture(diffuse0, texCoord) * (diffuse * inten + ambient) + texture(specular0, texCoord).r * specular * inten) * lightClr;
	vec4 result = (texture(diffuse0, texCoord) * (diffuse * inten * (1.0 - shadow) + ambient) + 
	texture(specular0, texCoord).r * specular * inten * (1.0 - shadow)) * lightClr;
	return result;
}

void main()
{	
	vec4 finalColor = vec4(0.0f);

	// Directional lights
	for (int i = 0; i < directionalLightNum; i++){
		finalColor += calculateDirectionalLight(directionalLights[i]);
	}

	// Point lights
	for (int i = 0; i < pointLightNum; i++){
		finalColor += calculatePointLight(pointLights[i]);
	}

	// Spot lights
	for (int i = 0; i < spotLightNum; i++){
		finalColor += calculateSpotLight(spotLights[i]);
	}

	// Checking texture
	// FragColor = texture(shadowMap, texCoord);
	FragColor = finalColor;
	// FragColor = texture(shadowMap, crntPos.xy);
	// Create projection for the texture
	
}