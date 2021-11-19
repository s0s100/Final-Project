#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <string>
#include <stb/stb_image.h>

#include "FileManager.h"

std::string FileManager::get_file_contents(const char* fileName)
{
	// Create stream and read all of the information from there
	std::ifstream in(fileName, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

GLFWimage FileManager::get_image_content(const char* imageName) {
	int imageWidth, imageHeight;
	unsigned char* bytes = stbi_load(imageName, &imageWidth, &imageHeight, NULL, 0);

	GLFWimage result{ imageWidth, imageHeight, bytes };
	return result;
}