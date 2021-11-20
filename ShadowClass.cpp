#include "ShadowClass.h"

#include <glad/glad.h>
#include <cstddef>

ShadowClass::ShadowClass()
{
	// Initialize framebuffer
	glGenFramebuffers(1, &this->fboID);

	// Create and bind depth map texture
	glGenTextures(1, &this->depthMap);
	glBindTexture(GL_TEXTURE_2D, this->depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 
		SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	// Now framebuffer and texture should be connected
	bindFBO();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE, this->depthMap, 0);
	// Hope I won't use it in the main/scene class
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	unbindFBO();
}

void ShadowClass::renderDepthMap()
{
	//
}

/*
*	Binding/deleting functions
*/

void ShadowClass::bindFBO()
{
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

void ShadowClass::bindDepthMap()
{
	glBindTexture(GL_TEXTURE_2D, this->depthMap);
}

void ShadowClass::unbindDepthMap()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void ShadowClass::deleteDepthMap()
{
	glDeleteTextures(1, &this->depthMap);
}

