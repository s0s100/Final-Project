#include "Texture.h"
#include "FileManager.h"

Texture::Texture(const char* image, const char* texType, GLuint slot, GLenum format, GLenum pixelType) {
	// Type of the texture
	type = texType;
	// Image data
	int widthImg, heightImg, numColCh;
	unsigned char* pixels;

	// Flips the image so it appears right side up
	stbi_set_flip_vertically_on_load(true);
	// Reads the image from a file and stores it in bytes
	pixels = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	// Generates an OpenGL texture object and save its ID
	glGenTextures(1, &ID);
	// Assigns the texture to a Texture Unit
	glActiveTexture(GL_TEXTURE0 + slot);
	unit = slot;
	glBindTexture(GL_TEXTURE_2D, ID);

	// Configures the type of algorithm that is used to make the image smaller or bigger
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Configures the way the texture repeats (if it does at all)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	std::cout << "Assigning image: " << widthImg << " " 
		<< heightImg << " " << numColCh << std::endl;

	// Assigns the image to the OpenGL Texture object
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, pixels);
	// Generates MipMaps
	glGenerateMipmap(GL_TEXTURE_2D);

	// Testing
	// std::cout << "Texture.cpp, constructor, created texture, id = " << ID << ", assigned to " << unit << std::endl;

	// Deletes the image data as it is already in the OpenGL Texture object
	stbi_image_free(pixels);

	// Unbinds the OpenGL Texture object so that it can't accidentally be modified
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit) {
	// Testing
	// std::cout << "Texture.cpp, texUnit, set shader value " << uniform << ", value " << unit << std::endl;
	shader.setInt(uniform, unit);
}

void Texture::bind() {
	// Testing
	// std::cout << "Texture.cpp, bind, activate texture" << unit << std::endl;
	glActiveTexture(GL_TEXTURE0 + unit);

	// Testing
	// std::cout << "Texture.cpp, bind, bind texture_2D " << ID << std::endl;
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::deleteTexture() {
	glDeleteTextures(1, &ID);
}

const char* Texture::getType() {
	return Texture::type;
}