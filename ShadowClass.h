#ifndef SHADOW_CLASS_HEADER
#define SHADOW_CLASS_HEADER

class ShadowClass
{
private:
	// Depth map framebuffer object id
	unsigned int fboID;
	// Depth map texture which contains map
	unsigned int depthMap;

	// By the default it will be 800x800, might want to 
	// change it according to the screen size or smth
	inline static const int SHADOW_WIDTH = 800;
	inline static const int SHADOW_HEIGHT = 800;

public:
	// Basic constructor
	ShadowClass();

	// Depth map rendering
	void renderDepthMap();

	// Get shadow width/height
	int getShadowWidth();
	int getShadowHeight();

	// Bind, unbind and delete operation for the depth map and framebuffer
	void bindFBO();
	void bindDepthMap();
	void unbindFBO();
	void unbindDepthMap();
	void deleteFBO();
	void deleteDepthMap();
};

#endif