#pragma once
#include <string>
#include <vulkan/vulkan.h>

class Window
{
public:
	virtual bool getFrameBufferResized() { return false; };
	virtual void getFrameBufferSize(int* width, int* height) = 0;
	virtual void setFrameBufferResized(bool isResize) { return ; }
	virtual bool isWindowOpen() = 0;
	virtual void pollEvents() = 0;
	virtual bool isKeyPressed(int key) = 0;
	virtual VkSurfaceKHR createWindowSurface(VkInstance instance) = 0;
	virtual void destroyWindow() = 0;
	virtual void close() = 0;

private:
	int _width;
	int _height;
	std::string _title;
};

