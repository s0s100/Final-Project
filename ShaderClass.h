#ifndef SHADER_CLASS_HEADER
#define SHADER_CLASS_HEADER

#include <glad/glad.h>
#include <iostream>
#include <glm/glm.hpp>

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
	// Get shader ID
	GLuint getID();
	// Shader setters
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec2(const std::string& name, const glm::vec2& value) const;
	void setVec3(const std::string& name, const glm::vec3& value) const;
	void setVec4(const std::string& name, const glm::vec4& value) const;
	void setMat2(const std::string& name, const glm::mat2& mat) const;
	void setMat3(const std::string& name, const glm::mat3& mat) const;
	void setMat4(const std::string& name, const glm::mat4& mat) const;
};
#endif