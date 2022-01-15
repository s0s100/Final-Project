#ifndef FILE_MANAGER_NAMESPACE
#define FILE_MANAGER_NAMESPACE

#include <string>
#include <glfw3.h>

namespace FileManager {
	// Reads a text file and outputs a string with everything in the text file
	// Used to read textures from the images
	std::string getFileContent(const char* fileName);

	// Gets a path to the image and returns an Image data object
	GLFWimage getImageContent(const char* imageName);
};

#endif