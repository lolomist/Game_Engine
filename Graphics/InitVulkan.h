#pragma once

#include <vulkan/vulkan.h>

#include <vector>

class InitVulkan
{
	public:
		InitVulkan();
		~InitVulkan();

	private:
		void InitInstance();
		void DestroyInstance();

		void SetupDebug();
		
		void InitDevice();
		void DestroyDevice();
		
		void InitDebug();
		void DestroyDebug();
		void GetRequiredExtensions();
		void GetRequiredLayers();

		VkInstance _instance = VK_NULL_HANDLE;
		VkPhysicalDevice _gpu = VK_NULL_HANDLE;
		VkDevice _device = VK_NULL_HANDLE;
		VkQueue _queue = VK_NULL_HANDLE;
		VkPhysicalDeviceProperties _gpuProperties = {};

		uint32_t _graphicsFamilyIndex = 0;

		std::vector<const char*> _instanceLayers;
		std::vector<const char*> _instanceExtensions;
		std::vector<const char*> _deviceExtensions;

		VkDebugReportCallbackEXT _debugReport = VK_NULL_HANDLE;
		VkDebugReportCallbackCreateInfoEXT _debugCallbackCreateInfo = {};
};