#include <glad/glad.h>
#include <cstddef>
#include <glm/glm.hpp>

#include "ShadowClass.h"
#include "GameObject.h"
#include <iostream>
#include "Light.h"
#include <glm/gtx/string_cast.hpp>

ShadowClass::ShadowClass()
{
	// Initialize framebuffer
	glGenFramebuffers(1, &this->fboID);

	std::cout << "FBO ID: " << fboID << std::endl;

	// Create and bind depth map texture
	glGenTextures(1, &this->depthMap);

	std::cout << "Depth map: " << depthMap << std::endl;

	glBindTexture(GL_TEXTURE_2D, this->depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 
		SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Now framebuffer and texture should be connected
	bindFBO();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->depthMap, 0);
	// To prevent usage of it in the main/scene class
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	unbindFBO();
}

void ShadowClass::renderDepthMap(GameObject object, Shader &depthShader,
	glm::mat4 lightSpaceMatrix)
{
	depthShader.activateShader();

	// Pushing parameters into the shader (object vertices, indices, textures, etc)
	glUniformMatrix4fv(glGetUniformLocation(depthShader.getID(), "lightSpaceMatrix"),
		1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));

	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	bindFBO();
	glClear(GL_DEPTH_BUFFER_BIT);	
	object.shadowDraw(depthShader);// Rendering using depth shader
	unbindFBO();
}

void ShadowClass::renderDepthMap2(std::vector<GameObject> objects, Shader& depthShader,
	glm::mat4 lightSpaceMatrix)
{
	depthShader.activateShader();

	// Pushing parameters into the shader (object vertices, indices, textures, etc)
	glUniformMatrix4fv(glGetUniformLocation(depthShader.getID(), "lightSpaceMatrix"),
		1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));

	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	bindFBO();
	glClear(GL_DEPTH_BUFFER_BIT);
	
	// After the set up render each of the objects
	for (GameObject object : objects) {
		object.shadowDraw(depthShader);// Rendering using depth shader
	}

	unbindFBO();
}

int ShadowClass::getShadowHeight()
{
	return SHADOW_HEIGHT;
}

int ShadowClass::getShadowWidth()
{
	return SHADOW_WIDTH;
}

/*
*	Binding/deleting functions
*/

void ShadowClass::bindFBO()
{
	// std::cout << "Binding fbo: " << fboID << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, this->fboID);
}

void ShadowClass::unbindFBO()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ShadowClass::deleteFBO()
{
	glDeleteFramebuffers(1, &this->fboID);
}

void ShadowClass::bindDepthMap(Shader shader)
{
	// std::cout << "Binding depth map: " << depthMap << std::endl;
	// Shader needs to be activated before changing the value of a uniform
	shader.activateShader();
	// Sets the value of the uniform
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, this->depthMap);
	glUniform1i(glGetUniformLocation(shader.getID(), "shadowMap"), fboID);
}

void ShadowClass::unbindDepthMap()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void ShadowClass::deleteDepthMap()
{
	glDeleteTextures(1, &this->depthMap);
}

