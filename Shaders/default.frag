#version 330 core

#define NR_DIR_LIGHT 1
#define NR_POINT_LIGHT 1
#define NR_SPOT_LIGHT 25

#define AMBIENT 0.05f
#define DIFFUSE 0.6f
#define SPECULAR 0.8f

// Defines how strong is the shininess using specular lighting
#define SHININESS_COEFFICIENT 32.0f
#define ACNE_COEFFICIENT 0.01f
#define GAMMA_COEFFICIENT 1.3f

struct DirectionalLight {
	vec3 position;
	vec4 color;
	vec3 direction;

	bool isShadowing;
	mat4 lightMatrix;
	int mapPosition; 
};

struct SpotLight {
	vec3 position;
	vec4 color;
	vec3 direction;

	float innerCone;
	float outerCone;

	bool isShadowing;
	mat4 lightMatrix;
	int mapPosition;
};

struct PointLight {
	vec3 position;
	vec4 color;

	float constant;
	float linear;
	float quadratic;
};

// Outputs colors in RGBA
out vec4 FragColor;

// Input fragment current position
in vec3 pos;
// Input fragment normal
in vec3 normal;
// Inputs the texture coordinates from the Vertex Shader
in vec2 texCoord;

// Camera position
uniform vec3 camPos;

// Diffuse texture
uniform sampler2D diffuse0;
// Specular texture
uniform sampler2D specular0;
// Shadow depth maps, up to 16 fragment textures
uniform sampler2D shadowMap[16];

// Number of the lights on the scene
uniform int directionalLightNum;
uniform int pointLightNum;
uniform int spotLightNum;

// Light arrays
uniform DirectionalLight directionalLights[NR_DIR_LIGHT];
uniform PointLight pointLights[NR_POINT_LIGHT];
uniform SpotLight spotLights[NR_SPOT_LIGHT];

// Directional light shadow calculation
float shadowCalculation(vec4 lightProj, vec3 lightDir, int mapPos) {
	// Get projection of the fragment in the light from the top
	vec3 projCoords = lightProj.xyz / lightProj.w;
	// Make it to be in range [0,1]
	projCoords = projCoords * 0.5 + 0.5;

	// Depth map depth and current depth
	float closestDepth = texture(shadowMap[mapPos], projCoords.xy).r; 
	float currentDepth = projCoords.z;

	// Shadow acne remove using bias
	float bias = max(ACNE_COEFFICIENT * (1.0 - dot(normal, lightDir)), ACNE_COEFFICIENT * 0.1f);

	// Shadow distribution to improve quality of the shadow
	float shadow = 0.0f;
	// Texel - pixel in the texture
	vec2 texelSize = 1.0 / textureSize(shadowMap[mapPos], 0);
	// Parse the texture and for each of the points calculate the value
	for(int x = -1; x <= 1; ++x) {
		for(int y = -1; y <= 1; ++y) {
			float textureDepth = texture(shadowMap[mapPos], projCoords.xy + vec2(x, y) * texelSize).r; 
			shadow += currentDepth - bias > textureDepth  ? 1.0 : 0.0;        
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

// Spot light shadow calculation
/*float shadowSpotCalculation(vec4 lightProj, vec3 lightDir, int mapPos) {
	// Get projection of the fragment in the light from the top
	vec3 projCoords = lightProj.xyz / lightProj.w;
	// Make it to be in range [0,1]
	projCoords = projCoords * 0.5 + 0.5;

	// Depth map depth and current depth
	float closestDepth = texture(shadowMap[mapPos], projCoords.xy).r; 
	float currentDepth = projCoords.z;

	// Shadow acne remove using bias
	float bias = max(ACNE_COEFFICIENT * (1.0 - dot(normal, lightDir)), ACNE_COEFFICIENT * 0.1f);

	// Shadow distribution to improve quality of the shadow
	float shadow = 0.0f;
	// Texel - pixel in the texture
	vec2 texelSize = 1.0 / textureSize(shadowMap[mapPos], 0);
	// Parse the texture and for each of the points calculate the value
	//if ( texture( shadowMap, (ShadowCoord.xy/ShadowCoord.w) ).z  <  (ShadowCoord.z-bias)/ShadowCoord.w )
	//if ( textureProj( shadowMap, ShadowCoord.xyw ).z  <  (ShadowCoord.z-bias)/ShadowCoord.w )
	//if ( texture( shadowMap, ShadowCoord.xy ).z  <  ShadowCoord.z){ // Before
	for(int x = -1; x <= 1; ++x) {
		for(int y = -1; y <= 1; ++y) {
			float textureDepth = texture(shadowMap[mapPos], projCoords.xy + vec2(x, y) * texelSize).r; 
			shadow += currentDepth - bias > textureDepth  ? 1.0 : 0.0;        
			//float textureDepth = texture(shadowMap[mapPos], (projCoords.xy / projCoords.w) + vec2(x, y) * texelSize).r; 
			
		}    
	}
	// Shadow now is [0,9], normalize it
	shadow /= 9.0; 
	
	// If outside of the bounds, set to 0
	if(projCoords.z > 1.0) {
		shadow = 0.0;
	}

	return shadow;
}*/

vec4 calculatePointLight(PointLight pointLight) {
	// Define variables
	vec3 lightPos = pointLight.position;
	vec4 lightCol = pointLight.color;
	float constant = pointLight.constant;
	float linear = pointLight.linear;
	float quadratic = pointLight.quadratic;

	vec3 lightVec = lightPos - pos;
	vec3 lightVector = normalize(lightVec);
	vec3 viewVector = normalize(camPos - pos);
	vec3 reflectionVector = reflect(-lightVector, normal);

	// Calculate distance between fragment and the light source
	float dist = length(lightVec);
	float intensity = 1.0f / (quadratic * pow(dist, 2) + linear * dist + constant);

	// Ambient
	float ambient = AMBIENT;

	// Diffuse
	float diffuse = max(dot(normal, lightVector), 0.0f);
	diffuse = diffuse * intensity * DIFFUSE;

	// Specular
	float specular = pow(max(dot(viewVector, reflectionVector), 0.0f), SHININESS_COEFFICIENT);
	specular = specular * intensity * SPECULAR; 

	// Calculating result
	vec4 diffuseVector = diffuse * texture(diffuse0, texCoord);
	vec4 specularValue = specular * texture(specular0, texCoord);
	vec4 result = (ambient + diffuseVector + specularValue) * lightCol;

	return result;
}

vec4 calculateDirectionalLight(DirectionalLight directionalLight) {
	// Define variables
	vec3 lightPos = directionalLight.position;
	vec4 lightCol = directionalLight.color;
	vec3 lightDir = directionalLight.direction;
	bool isShadowing = directionalLight.isShadowing;

	// vec3 lightVector = normalize(lightDir);
	vec3 lightVector = normalize(lightPos - pos);
	vec3 viewVector = normalize(camPos - pos);
	vec3 reflectionVector = reflect(-lightVector, normal);

	// Ambient
	float ambient = AMBIENT;

	// Diffuse
	float diffuse = max(dot(normal, lightVector), 0.0f);
	diffuse *= DIFFUSE;

	// Specular
	float specular = pow(max(dot(viewVector, reflectionVector), 0.0f), SHININESS_COEFFICIENT);
	specular *=  SPECULAR;

	// Calculation shadows
	float shadow = 0.0f;
	if (isShadowing) {
		// Define position of the fragment in the light
		mat4 lightMatrix = directionalLight.lightMatrix;
		vec4 lightProj = lightMatrix * vec4(pos, 1.0f);
		// Depth map location
		int mapPos = directionalLight.mapPosition;

		shadow = shadowCalculation(lightProj, lightDir, mapPos); 
	}

	// Calculating result
	vec4 diffuseVector = diffuse * texture(diffuse0, texCoord) * (1 - shadow);
	float specularValue = specular * texture(specular0, texCoord).r * (1 - shadow);
	vec4 result = (ambient + diffuseVector + specularValue) * lightCol;

	return result;
}

vec4 calculateSpotLight(SpotLight spotLight) {
	// Defining light values
	vec3 lightPos = spotLight.position;
	vec4 lightCol = spotLight.color;
	vec3 lightDir = spotLight.direction;
	float innerCone = spotLight.innerCone;
	float outerCone = spotLight.outerCone;
	bool isShadowing = spotLight.isShadowing;

	vec3 lightVector = normalize(lightPos - pos);
	vec3 viewVector = normalize(camPos - pos);
	vec3 reflectionVector = reflect(-lightVector, normal);

	// Ambient
	float ambient = AMBIENT;

	// Diffuse
	float diffuse = max(dot(normal, lightVector), 0.0f);
	diffuse *= DIFFUSE;

	// Specular
	float specular = pow(max(dot(viewVector, reflectionVector), 0.0f), SHININESS_COEFFICIENT);
	specular *=  SPECULAR;

	// Dot product between light source and the direction to the fragment
	float lightDot = dot(lightDir, -lightVector);
	// Intencity coefficient which lays between [0,1]
	float intenCoef = clamp((lightDot - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	// Calculation shadows
	float shadow = 0.0f;
	if (isShadowing) {
		// Define position of the fragment in the light
		mat4 lightMatrix = spotLight.lightMatrix;
		vec4 lightProj = lightMatrix * vec4(pos, 1.0f);
		// Depth map location
		int mapPos = spotLight.mapPosition;

		//shadow = shadowSpotCalculation(lightProj, lightDir, mapPos); 
		shadow = shadowCalculation(lightProj, lightDir, mapPos); 
	}
	
	// Calculating result
	vec4 diffuseVector = diffuse * texture(diffuse0, texCoord) * intenCoef * (1 - shadow);
	float specularValue = specular * texture(specular0, texCoord).r * intenCoef * (1 - shadow);
	vec4 result = (ambient + diffuseVector + specularValue) * lightCol;

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
	//finalColor.rgb = pow(finalColor.rgb, vec3(1.0f/GAMMA_COEFFICIENT));
	FragColor = finalColor;
}