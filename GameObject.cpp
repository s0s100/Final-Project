#include <iostream>
#include <glm/gtx/string_cast.hpp>

#include "GameObject.h"

GameObject::GameObject(Mesh mesh)
{
	GameObject::mesh = mesh;
}

//void GameObject::matrixSetup(Shader shader)
//{
//	shader.activateShader();
//	glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "model"), 1, GL_FALSE, glm::value_ptr(model));
//}

void GameObject::draw(Shader& shader, Camera camera)
{
	shader.activateShader();
	glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "model"), 1, GL_FALSE, glm::value_ptr(model));
	GameObject::mesh.draw(shader, camera);
}

// Upload matrix 
void GameObject::shadowDraw(Shader& shadowShader)
{
	shadowShader.activateShader();
	glUniformMatrix4fv(glGetUniformLocation(shadowShader.getID(), "model"), 1, GL_FALSE, glm::value_ptr(model));
	GameObject::mesh.shadowDraw(shadowShader);
}


/*void GameObject::generateDepthMap(Shader depthMapShader, ShadowClass shadow, Camera camera)
{
	// Before generating depth map create light space matrix
	glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, NEAR_PLANE, FAR_PLANE);
	glm::mat4 lightView = glm::lookAt(glm::vec3(0.1f, 0.5f, 0.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, -1.0f, 0.0f));

	glm::mat4 lightSpaceMatrix = lightProjection * lightView;

	depthMapShader.activateShader();
	// Testing shadow with a point light
	glUniformMatrix4fv(glGetUniformLocation(depthMapShader.getID(), "lightSpaceMatrix"), 1, GL_FALSE,
		glm::value_ptr(lightSpaceMatrix));


	glViewport(0, 0, shadow.getShadowWidth(), shadow.getShadowHeight());
	shadow.bindFBO();
	glClear(GL_DEPTH_BUFFER_BIT);
	draw(depthMapShader, camera);// Render scene, maybe the other option, time consuming
	shadow.unbindFBO();
}*/

/**
* Getter/changer time
* Also changes model matrix
**/

void GameObject::setPosition(glm::vec3 position)
{
	GameObject::position = position;
	GameObject::model[3][0] = position[0];
	GameObject::model[3][1] = position[1];
	GameObject::model[3][2] = position[2];
}

void GameObject::setScale(glm::vec3 scale)
{
	GameObject::scale = scale;
	// std::cout << "Before" << glm::to_string(model);
	GameObject::model = glm::scale(model, GameObject::scale);
	// std::cout << "After" << glm::to_string(model);
}

void GameObject::setRotation(glm::vec3 rotation)
{	
	glm::vec3 oldRotation = GameObject::rotation;
	GameObject::rotation = rotation;

	// Testing
	// std::cout << rotation.x << " " << rotation.y << " " << rotation.z << std::endl;

	GameObject::model = glm::rotate(model, glm::radians(rotation[0] - oldRotation[0]), X_VECTOR);
	GameObject::model = glm::rotate(model, glm::radians(rotation[1] - oldRotation[1]), Y_VECTOR);
	GameObject::model = glm::rotate(model, glm::radians(rotation[2] - oldRotation[2]), Z_VECTOR);
}

void GameObject::changePosition(glm::vec3 positionChange)
{
	setPosition(position + positionChange);
}

void GameObject::changeScale(glm::vec3 scaleChange)
{
	setScale(scale + scaleChange);
}

void GameObject::changeRotation(glm::vec3 rotationChange)
{
	setRotation(rotation + rotationChange);
}