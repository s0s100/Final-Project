#ifndef CAMERA_CLASS_HEADER
#define CAMERA_CLASS_HEADER

#include <glad/glad.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "ShaderClass.h"

// Screen size
 /*#define DEFAULT_MONITOR_WIDTH 720
 #define DEFAULT_MONITOR_HEIGHT 480*/



#define DEFAULT_MONITOR_WIDTH 1920
#define DEFAULT_MONITOR_HEIGHT 1080

// Basis vectors
#define X_VECTOR glm::vec3(1.0f, 0.0f, 0.0f)
#define Y_VECTOR glm::vec3(0.0f, 1.0f, 0.0f)
#define Z_VECTOR glm::vec3(0.0f, 0.0f, 1.0f)
// Near/far planes
constexpr float NEAR_PLANE = 0.1f;
constexpr float FAR_PLANE = 100.0f;
constexpr float FOV = 45.0f;

class Camera  {
private:
	// Camera position, orientation and it's result  cameraMatrix
	glm::vec3 position;
	glm::vec3 orientation;
	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	// Size of the camera
	int width;
	int height;

	// Zoom changer variable for gradual zoom
	inline static float zoom = 0.0f;
	// Screen move speed
	inline static const float screenSpeed = 0.05f;

	// Zoom settings for the wheel zoom
	inline static const float zoomValue = 0.3f;
	inline static const float zoomSpeed = 0.04f;
	inline static const float minHeight = 1.0f; // Min height of the camera on the scene
	inline static const float maxHeight = 5.0f; // Max height of the camera on the scene

	// Function to interact with camera using mouse wheel
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	// Function to be called if the size of the screen has changed
	// static void window_size_callback(GLFWwindow* window, int width, int height);

public:
	// Empty constructor
	Camera();
	// Basic constructor for the camera
	Camera(int width, int height, glm::vec3 position, glm::vec3 orientation);
	// Updates camera matrix
	void updateMatrix();
	// Set camera matrix for the shader
	void setCameraMatrix(Shader& shader, const char* uniform);
	// Set camera position for the shader
	void setCameraPosition(Shader& shader, const char* uniform);
	// Strategy camera
	void inputs(GLFWwindow* window);
	// Function to control camera using input mouse and keyboard 
	void inputs2(GLFWwindow* window);
};

#endif 


