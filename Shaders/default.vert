#version 330 core

// Position, normal and texture coordinate
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;

// Position, normal and texuture coordinate after matrix transformation
out vec3 pos;
out vec3 normal;
out vec2 texCoord;

// Camera and object mmatrices + Test light matrix
uniform mat4 camMatrix; 
uniform mat4 modelMatrix;

void main() {
	// Calculate shader positon using models matrix and input position
	pos = vec3(modelMatrix * vec4(aPos, 1.0f));
	// Normalize aNormal to prevent errors
	normal = normalize(aNormal);
	// Assigns the texture coordinates from the Vertex Data
	texCoord = aTex;
	// Outputs the positions of all vertices
	gl_Position = camMatrix * vec4(pos, 1.0f);
}