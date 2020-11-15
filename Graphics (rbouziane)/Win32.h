#pragma once

#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>

class Win32
{
public:
	//Initialize the window
	Win32();
	bool init();
	void broadcast();
	bool isWindowOpen();

	VkSurfaceKHR createWindowSurface(VkInstance instance);

	//EVENTS
	virtual void onCreate();
	virtual void onUpdate();
	virtual void destroyWindow();

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	bool getFrameBufferResized();
	void setFrameBufferResized(bool isResized);

	bool isKeyPressed(UINT uMsg);
	void getMousePos(double* mouseX, double* mouseY);

	//Release the window
	~Win32();
private:
	HWND m_hwnd = nullptr;
	//set this flag to true to indicate that the window is initialized and running
	bool m_is_run = true;

	HINSTANCE _win_instance = NULL;

	bool _frameBufferResized = false;

	LPCWSTR _windowClassName = L"WindowClassName";
	LPCWSTR _windowName = L"Game Engine";
};