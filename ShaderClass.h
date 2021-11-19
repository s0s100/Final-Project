#ifndef SHADER_CLASS_HEADER
#define SHADER_CLASS_HEADER

#include <glad/glad.h>

class Shader 
{
private:
	// Reference ID of the Shader Program
	GLuint ID;

	// Checks if the different Shaders have compiled properly
	void compileErrors(unsigned int shader, const char* type);

public:
	// Empty constructor
	Shader();
	// Constructor that build the Shader Program from 2 different shaders
	Shader(const char* vertexFile, const char* fragmentFile);

	// Activates the Shader Program
	void activateShader();
	// Deletes the Shader Program
	void deleteShader();

	GLuint getID();
};
#endif