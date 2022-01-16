#version 330 core

// Position, normal and texture coordinate
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;

// Position, normal and texuture coordinate after matrix transformation
out vec3 crntPos;
out vec3 normal;
out vec2 texCoord;

// Camera and object mmatrices + Test light matrix
uniform mat4 camMatrix; 
uniform mat4 modelMatrix;

void main() {
	// Calculate shader positon using models matrix and input position
	crntPos = vec3(modelMatrix * vec4(aPos, 1.0f));
	// Also normal calculations
	normal = normalize(aNormal);
	// Assigns the texture coordinates from the Vertex Data to "texCoord"
	texCoord = aTex;
	// Outputs the positions/coordinates of all vertices
	gl_Position = camMatrix * vec4(crntPos, 1.0f);
}