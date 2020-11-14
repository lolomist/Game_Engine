#include "Win32.h"
#include <stdexcept>
#include <iostream>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

Win32::Win32()
{
}

void Win32::getMousePos(double* mouseX, double* mouseY)
{
}

bool Win32::init()
{
	_win_instance = GetModuleHandle(nullptr);

	//Setting up WNDCLASSEX object
	WNDCLASSEX wc{}; // Using {} to initialize a struct sets all fields to 0 in C++
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = _win_instance;
	wc.lpszClassName = _windowClassName;
	wc.lpfnWndProc = &WndProc;

	// If the registration of class will fail, the function will return false
	if (!RegisterClassEx(&wc))
		throw std::runtime_error("Filed to register WNDCLASSEX.");

	// When you create a window the dimensions include the non-client area such as the 
	// border and title bar, I'd use the AdjustWindowRectEx API
	RECT rect = { 0,0,1024,768 };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_OVERLAPPEDWINDOW);

	const auto width = rect.right - rect.left;
	const auto height = rect.bottom - rect.top;

	//Creation of the window
	m_hwnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		_windowClassName,
		_windowName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		nullptr,
		nullptr,
		nullptr,
		this);

	//if the creation fail return false
	if (!m_hwnd)
		throw std::runtime_error("Filed to initialize Window.");

	//show up the window
	ShowWindow(m_hwnd, SW_SHOW);
	return true;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		// Event fired when the window is created
		// collected here..
		auto* const params = reinterpret_cast<LPCREATESTRUCT>(lparam);
		auto* const window =
			reinterpret_cast<Win32* const>(params->lpCreateParams);

		// .. and then stored for later lookup
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
		window->onCreate();
		break;
	}

	case WM_DESTROY:
	{
		// Event fired when the window is destroyed
		auto* const window =
			reinterpret_cast<Win32* const>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		window->destroyWindow();
		PostQuitMessage(0);
		break;
	}


	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return 0;
}

void Win32::broadcast()
{
	MSG msg{};
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	onUpdate();

	Sleep(1);
}

bool Win32::isWindowOpen()
{
	return m_is_run;
}

void Win32::onCreate()
{
}

void Win32::onUpdate()
{
}

bool Win32::isKeyPressed(UINT uMsg)
{
	return (GetKeyState(uMsg) & 0x8000);
}

VkSurfaceKHR Win32::createWindowSurface(VkInstance instance)
{
	VkSurfaceKHR surface;

	VkWin32SurfaceCreateInfoKHR create_info{};
	create_info.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	create_info.hinstance = _win_instance;
	create_info.hwnd = m_hwnd;

	if (vkCreateWin32SurfaceKHR(instance, &create_info, nullptr, &surface) != VK_SUCCESS) {
		throw std::runtime_error("Fail to create window surface!");
	}

	return surface;
}

void Win32::destroyWindow()
{
	m_is_run = false;
	DestroyWindow(m_hwnd);
}

Win32::~Win32()
{
	DestroyWindow(m_hwnd);
}