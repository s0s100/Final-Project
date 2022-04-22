#include <glad/glad.h>
#include <glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Shadow.h"

Shadow::Shadow() {
	// Generate buffer to store the depth
	glGenFramebuffers(1, &bufferId);
	// Generate texture to save the depth data
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowWidth, shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);*/

	// To prevent shadows outside of the depth map set those values to white
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	// Attach depth texture as FBO's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, bufferId);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, textureId, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Shadow::calculateMatrix(glm::vec3 lightPos, glm::vec3 lightDir) {
	glm::mat4 lightProjection = glm::ortho(-planeSize, planeSize, -planeSize, planeSize, nearPlane, farPlane);
	glm::mat4 lightView;

	// Also check if th direction of the light is not the same as Y_Vector
	glm::vec3 normDir = glm::normalize(lightDir);
	if ((normDir == Y_VECTOR) || (normDir == -Y_VECTOR)) {
		lightView = glm::lookAt(lightPos, lightPos + lightDir, X_VECTOR);
	}
	else {
		lightView = glm::lookAt(lightPos, lightPos + lightDir, Y_VECTOR);
	}

	glm::mat4 result = lightProjection * lightView;
	this->lightMatrix = result;
}

void Shadow::calculateSpotMatrix(glm::vec3 lightPos, glm::vec3 lightDir) {
	// glm::mat4 lightProjection = glm::ortho(-planeSize, planeSize, -planeSize, planeSize, nearPlane, farPlane);
	glm::mat4 lightProjection = glm::ortho(-2.0f, 2.0f, -10.0f, 10.0f, nearPlane, farPlane);
	glm::mat4 lightView;

	// Also check if th direction of the light is not the same as Y_Vector
	glm::vec3 normDir = glm::normalize(lightDir);
	if ((normDir == Y_VECTOR) || (normDir == -Y_VECTOR)) {
		lightView = glm::lookAt(lightPos, lightPos + lightDir, X_VECTOR);
	}
	else {
		lightView = glm::lookAt(lightPos, lightPos + lightDir, Y_VECTOR);
	}

	glm::mat4 result = lightProjection * lightView;
	this->lightMatrix = result;
}

void Shadow::generateDepthMap(Shader shader, std::vector<GameObject*> objects) {
	// Assign the light matrix value
	assignLightMatrix(shader, "lightSpaceMatrix");

	// To generate more proper shadows, works for solid objects
	glCullFace(GL_FRONT);
	// Define buffer area
	glViewport(0, 0, shadowWidth, shadowHeight);
	// Bind framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, bufferId);
	glClear(GL_DEPTH_BUFFER_BIT);

	// Render the scene
	for (const auto& object : objects) {
		object->draw(shader);
	}

	// Return culling to normal
	glCullFace(GL_BACK);
	// Unbind framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Shadow::generateDepthMap(Shader shader, std::vector<GameObject>& objects) {
	// Assign the light matrix value
	assignLightMatrix(shader, "lightSpaceMatrix");

	// To generate more proper shadows, works for solid objects
	glCullFace(GL_FRONT);
	// Define buffer area
	glViewport(0, 0, shadowWidth, shadowHeight);
	// Bind framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, bufferId);
	glClear(GL_DEPTH_BUFFER_BIT);

	// Render the scene
	for (auto &object : objects) {
		object.draw(shader);
	}

	// Return culling to normal
	glCullFace(GL_BACK);
	// Unbind framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Shadow::assignTexture(Shader shader, unsigned int textureNumber, std::string name) {
	shader.setInt(name, textureNumber);
	glActiveTexture(GL_TEXTURE0 + textureNumber);
	glBindTexture(GL_TEXTURE_2D, textureId);
}

void Shadow::assignLightMatrix(Shader shader, std::string name) {
	// std::cout << glm::to_string(this->lightMatrix) << std::endl;
	shader.setMat4(name, this->lightMatrix);
}