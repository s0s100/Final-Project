#include <iostream>
#include <math.h> 
#include <glm/gtx/string_cast.hpp>

#include "Camera.h"

// Empty constructor
Camera::Camera() {
	Camera::width = DEFAULT_MONITOR_WIDTH;
	Camera::height = DEFAULT_MONITOR_HEIGHT;
	Camera::orientation = glm::vec3(0.0f);
	Camera::position = glm::vec3(0.0f);
}

// Basic constructor for the camera
Camera::Camera(int width, int height, glm::vec3 position, glm::vec3 orientation) {
	// Get input values and set camera values to it
	Camera::width = width;
	Camera::height = height;
	Camera::position = position;
	Camera::orientation = orientation;
}

// Update model matrix to use in the shader
void Camera::updateMatrix() {
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);

	// View matrix
	view = glm::lookAt(position, position + orientation, Y_VECTOR);
	// Projection matrix
	proj = glm::perspective(glm::radians(FOV), float(width / height), NEAR_PLANE, FAR_PLANE);
	// Multiplication of those matrices is camera matrix
	cameraMatrix = proj * view;

	// Debug
	// std::cout << glm::to_string(cameraMatrix) << std::endl;
}

// Creates camera matrix in the selected shader so its location could be changed
void Camera::setCameraMatrix(Shader& shader, const char* location) {
	shader.setMat4(location, cameraMatrix);
}


void Camera::setCameraPosition(Shader& shader, const char* location) {
	shader.setVec3(location, this->position);
}

// Inputs I've taken from tutorial
void Camera::inputs2(GLFWwindow* window) {
	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		position += screenSpeed * orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		position += screenSpeed * -glm::normalize(glm::cross(orientation, Y_VECTOR));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		position += screenSpeed * -orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		position += screenSpeed * glm::normalize(glm::cross(orientation, Y_VECTOR));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		position += screenSpeed * Y_VECTOR;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		position += screenSpeed * -Y_VECTOR;
	}

	float sensitivity = 45.0f;
	// Handles mouse inputs
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		// Hides mouse cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Stores the coordinates of the cursor
		double mouseX;
		double mouseY;
		// Fetches the coordinates of the cursor
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
		// and then "transforms" them into degrees 
		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

		// Calculates upcoming vertical change in the Orientation
		glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotX), glm::normalize(glm::cross(orientation, Y_VECTOR)));

		// Decides whether or not the next vertical Orientation is legal or not
		if (abs(glm::angle(newOrientation, Y_VECTOR) - glm::radians(90.0f)) <= glm::radians(85.0f)) {
			orientation = newOrientation;
		}

		// Rotates the Orientation left and right
		orientation = glm::rotate(orientation, glm::radians(-rotY), Y_VECTOR);

		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
	}
}

// Strategy control version
// Function to control camera using input mouse and keyboard
void Camera::inputs(GLFWwindow* window) {
	// Keys to change location of the window in X, Z axises
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		position -= screenSpeed * Z_VECTOR;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		position += screenSpeed * Z_VECTOR;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		position += screenSpeed * X_VECTOR;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		position -= screenSpeed * X_VECTOR;
	}

	// Debug
	// std::cout << zoom << " " << position[1] << std::endl;

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	// Controls mouse wheel input
	glfwSetScrollCallback(window, scroll_callback);
	// Controls window resize
	//glfwSetWindowSizeCallback(window, window_size_callback);

	// Change position values after scroll callback (also check height bounds)
	if (zoom > 0 && position[1] <= maxHeight) {
		//Change position
		position -= zoomSpeed * orientation;
		// Change zoom value
		if (zoom > zoomSpeed) {
			zoom -= zoomSpeed;
		}
		else {
			zoom = 0;
		}
	}
	else if (zoom < 0 && position[1] >= minHeight) {
		//Change position
		position += zoomSpeed * orientation;
		// Change zoom value
		if (zoom < zoomSpeed) {
			zoom += zoomSpeed;
		}
		else {
			zoom = 0;
		}
	}
	else {
		zoom = 0;
	}
}

// Function for the mouse wheel to zoom in/out camera
void Camera::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	if (yoffset > 0) {
		zoom -= zoomValue;
	}
	else if (yoffset < 0) {
		zoom += zoomValue;
	}
}

/*void Camera::window_size_callback(GLFWwindow* window, int width, int height) {
	// Debug
	std::cout << "Size of the screen has changed: " << width << "," << height << std::endl;
	newWidth = width;
	newHeight = height;
}*/
