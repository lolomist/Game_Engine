#pragma once
#include "Window.h"
#include <string>
#include <GLFW/glfw3.h>

static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

class GlfwWindow : public Window
{
public:
	GlfwWindow(int windowWidth, int windowHeight, std::string title);

	bool getFrameBufferResized() override;
	void getFrameBufferSize(int *width, int *height) override;
	void setFrameBufferResized(bool isResized) override;
	bool isWindowOpen() override;
	VkSurfaceKHR createWindowSurface(VkInstance instance) override;
	void pollEvents() override;
	bool isKeyPressed(int key) override;
	void close() override;
private:
	void initWindow(int windowWidth, int windowHeight, std::string title);
	GLFWwindow* _window;

	void destroyWindow() override;

	bool _frameBufferResized = false;
};

