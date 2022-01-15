#include <iostream>
#include <glm/gtx/string_cast.hpp>

#include "GameObject.h"
#include "Camera.h"

GameObject::GameObject(Mesh mesh) {
	GameObject::mesh = mesh;
}

void GameObject::draw(Shader& shader) {
	shader.setMat4("modelMatrix", model);
	GameObject::mesh.draw(shader);
}


void GameObject::setPosition(glm::vec3 position) {
	GameObject::position = position;
	GameObject::model[3][0] = position[0];
	GameObject::model[3][1] = position[1];
	GameObject::model[3][2] = position[2];
}

void GameObject::setScale(glm::vec3 scale) {
	GameObject::scale = scale;
	GameObject::model = glm::scale(model, GameObject::scale);
}

void GameObject::setRotation(glm::vec3 rotation) {	
	glm::vec3 oldRotation = GameObject::rotation;
	GameObject::rotation = rotation;
	GameObject::model = glm::rotate(model, glm::radians(rotation[0] - oldRotation[0]), X_VECTOR);
	GameObject::model = glm::rotate(model, glm::radians(rotation[1] - oldRotation[1]), Y_VECTOR);
	GameObject::model = glm::rotate(model, glm::radians(rotation[2] - oldRotation[2]), Z_VECTOR);
}

void GameObject::changePosition(glm::vec3 positionChange) {
	setPosition(position + positionChange);
}

void GameObject::changeScale(glm::vec3 scaleChange) {
	setScale(scale + scaleChange);
}

void GameObject::changeRotation(glm::vec3 rotationChange) {
	setRotation(rotation + rotationChange);
}