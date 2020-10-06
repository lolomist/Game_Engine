#pragma once

#include <vulkan/vulkan.h>

#include <vector>

class InitVulkan
{
	public:
		InitVulkan();
		~InitVulkan();

	private:
		void _InitInstance();
		void _DestroyInstance();

		void _SetupDebug();
		
		void _InitDevice();
		void _DestroyDevice();
		
		void _InitDebug();
		void _DestroyDebug();
		void _GetRequiredExtensions();
		void _GetRequiredLayers();

		VkInstance _instance = nullptr;
		VkPhysicalDevice _gpu = nullptr;
		VkDevice _device = nullptr;
		VkPhysicalDeviceProperties _gpuProperties = {};

		uint32_t _graphicsFamilyIndex = 0;

		std::vector<const char*> _instanceLayers;
		std::vector<const char*> _instanceExtensions;
		std::vector<const char*> _deviceExtensions;

		VkDebugReportCallbackEXT _debugReport = nullptr;
		VkDebugReportCallbackCreateInfoEXT debugCallbackCreateInfo = {};
};