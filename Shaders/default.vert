#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Normals
layout (location = 1) in vec3 aNormal;
// Texture Coordinates
layout (location = 2) in vec2 aTex;

// Outputs current position for the fragment shader
out vec3 crntPos;
// Outputs calculated object normal
out vec3 normal;
// Outputs the texture coordinates to the fragment shader
out vec2 texCoord;

// Camera matrix
uniform mat4 camMatrix; 
// Model matrix
uniform mat4 model;

void main()
{
	// Calculate shader positon using models matrix and input position
	crntPos = vec3(model * vec4(aPos, 1.0f));
	// Also normal calculations
	normal = normalize(aNormal);
	// Assigns the texture coordinates from the Vertex Data to "texCoord"
	texCoord = aTex;
	// Outputs the positions/coordinates of all vertices
	gl_Position = camMatrix * vec4(crntPos, 1.0f);

}