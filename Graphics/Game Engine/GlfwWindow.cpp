#include "GlfwWindow.h"
#include <iostream>

GlfwWindow::GlfwWindow(int windowWidth, int windowHeight, std::string title)
{
	initWindow(windowWidth, windowHeight, title);
}

void GlfwWindow::getMousePos(double* mouseX, double* mouseY)
{
    glfwGetCursorPos(_window, mouseX, mouseY);
}

bool GlfwWindow::getFrameBufferResized()
{
    return _frameBufferResized;
}

void GlfwWindow::getFrameBufferSize(int* width, int* height)
{
    glfwGetFramebufferSize(_window, width, height);
}

void GlfwWindow::setFrameBufferResized(bool isResized)
{
    _frameBufferResized = isResized;
}

bool GlfwWindow::isWindowOpen()
{
    return !glfwWindowShouldClose(_window);
}

VkSurfaceKHR GlfwWindow::createWindowSurface(VkInstance instance)
{
    VkSurfaceKHR surface;
    if (glfwCreateWindowSurface(instance, _window, nullptr, &surface) != VK_SUCCESS) {
        throw std::runtime_error("échec de la création de la window surface!");
    }
    return surface;
}

void GlfwWindow::pollEvents()
{
    glfwPollEvents();
}

bool GlfwWindow::isKeyPressed(int key)
{
    return (glfwGetKey(_window, key) == GLFW_PRESS);
}

void GlfwWindow::close()
{
    glfwSetWindowShouldClose(_window, GLFW_TRUE);
}

// Private

void GlfwWindow::initWindow(int windowWidth, int windowHeight, std::string title)
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    _window = glfwCreateWindow(windowWidth, windowHeight, title.c_str(), nullptr, nullptr);
    glfwSetWindowUserPointer(_window, this);
    glfwSetFramebufferSizeCallback(_window, framebufferResizeCallback);
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void GlfwWindow::destroyWindow()
{
    glfwDestroyWindow(_window);
}

static void framebufferResizeCallback(GLFWwindow* window, int width, int height)
{
    std::cout << "Resize callback !" << std::endl;
    auto win = reinterpret_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
    win->setFrameBufferResized(true);
}
