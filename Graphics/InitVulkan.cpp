#include "InitVulkan.h"
#include "CheckError.h"

#include <cstdlib>
#include <assert.h>
#include <vector>

#include <iostream>
#include <sstream>

#if defined( _WIN32 )
#include <windows.h>
#endif

InitVulkan::InitVulkan()
{
	_SetupDebug();
	_InitInstance();
	_InitDebug();
	_InitDevice();
}

InitVulkan::~InitVulkan()
{
	_DestroyDevice();
	_DestroyDebug();
	_DestroyInstance();
}

void InitVulkan::_InitInstance()
{
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "3DGameEngine";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo instance_create_info{};
	instance_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instance_create_info.pApplicationInfo = &appInfo;
	instance_create_info.enabledLayerCount = _instanceLayers.size();
	instance_create_info.ppEnabledLayerNames = _instanceLayers.data();
	instance_create_info.enabledExtensionCount = _instanceExtensions.size();
	instance_create_info.ppEnabledExtensionNames = _instanceExtensions.data();
	instance_create_info.pNext = &debugCallbackCreateInfo;

	CheckError(vkCreateInstance(&instance_create_info, nullptr, &_instance));
}

void InitVulkan::_DestroyInstance()
{
	vkDestroyInstance(_instance, nullptr);
	_instance = nullptr;
}

void InitVulkan::_InitDevice()
{
	{
		uint32_t gpu_count = 0;
		vkEnumeratePhysicalDevices(_instance, &gpu_count, nullptr);
		std::vector<VkPhysicalDevice> gpu_list(gpu_count);
		vkEnumeratePhysicalDevices(_instance, &gpu_count, gpu_list.data());
		_gpu = gpu_list[0];
		vkGetPhysicalDeviceProperties(_gpu, &_gpuProperties);
	}
	{
		uint32_t family_count = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(_gpu, &family_count, nullptr);
		std::vector<VkQueueFamilyProperties> family_property_list(family_count);
		vkGetPhysicalDeviceQueueFamilyProperties(_gpu, &family_count, family_property_list.data());

		bool found = false;
		for (uint32_t i = 0; i < family_count; ++i) {
			if (family_property_list[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
				found = true;
				_graphicsFamilyIndex = i;
			}
		}
		if (!found) {
			assert(0 && "Vulkan ERROR: Queue family supporting graphics not found.");
			std::exit(-1);
		}
	}
	{
		uint32_t layer_count = 0;
		vkEnumerateInstanceLayerProperties(&layer_count, nullptr);
		std::vector<VkLayerProperties> layer_property_list(layer_count);
		vkEnumerateInstanceLayerProperties(&layer_count, layer_property_list.data());
		std::cout << "Instance Layers: \n";
		for (auto& i : layer_property_list) {
			std::cout << "  " << i.layerName << "\t\t | " << i.description << std::endl;
		}
		std::cout << std::endl;
	}
	{
		uint32_t layer_count = 0;
		vkEnumerateDeviceLayerProperties(_gpu, &layer_count, nullptr);
		std::vector<VkLayerProperties> layer_property_list(layer_count);
		vkEnumerateDeviceLayerProperties(_gpu, &layer_count, layer_property_list.data());
		std::cout << "Device Layers: \n";
		for (auto& i : layer_property_list) {
			std::cout << "  " << i.layerName << "\t\t | " << i.description << std::endl;
		}
		std::cout << std::endl;
	}

	float queue_priorities[]{ 1.0f };
	VkDeviceQueueCreateInfo device_queue_create_info{};
	device_queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	device_queue_create_info.queueFamilyIndex = _graphicsFamilyIndex;
	device_queue_create_info.queueCount = 1;
	device_queue_create_info.pQueuePriorities = queue_priorities;

	VkDeviceCreateInfo device_create_info{};
	device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	device_create_info.queueCreateInfoCount = 1;
	device_create_info.pQueueCreateInfos = &device_queue_create_info;
	device_create_info.enabledExtensionCount = _deviceExtensions.size();
	device_create_info.ppEnabledExtensionNames = _deviceExtensions.data();

	CheckError(vkCreateDevice(_gpu, &device_create_info, nullptr, &_device));
}

void InitVulkan::_DestroyDevice()
{
	vkDestroyDevice(_device, nullptr);
	_device = nullptr;
}

VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT obj_type, uint64_t src_obj, size_t location,int32_t msg_code, const char* layer_prefix, const char* msg, void* user_data)
{
	std::ostringstream stream;
	stream << "VKDBG: ";
	if (flags & VK_DEBUG_REPORT_INFORMATION_BIT_EXT) {
		stream << "INFO: ";
	}
	if (flags & VK_DEBUG_REPORT_WARNING_BIT_EXT) {
		stream << "WARNING: ";
	}
	if (flags & VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT) {
		stream << "PERFORMANCE: ";
	}
	if (flags & VK_DEBUG_REPORT_ERROR_BIT_EXT) {
		stream << "ERROR: ";
	}
	if (flags & VK_DEBUG_REPORT_DEBUG_BIT_EXT) {
		stream << "DEBUG: ";
	}
	stream << "@[" << layer_prefix << "]: ";
	stream << msg << std::endl;
	std::cout << stream.str();
	
	#if defined( _WIN32 )
		if (flags & VK_DEBUG_REPORT_ERROR_BIT_EXT) {
			stream << "Vulkan Error!";
		}
	#endif

	return false;
}

void InitVulkan::_SetupDebug()
{
	debugCallbackCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
	debugCallbackCreateInfo.pfnCallback = VulkanDebugCallback;
	debugCallbackCreateInfo.flags = VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT | VK_DEBUG_REPORT_ERROR_BIT_EXT | 0;

	_GetRequiredExtensions();
	_GetRequiredLayers();
}

void InitVulkan::_GetRequiredExtensions() {
	_instanceExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	_instanceExtensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
}

void InitVulkan::_GetRequiredLayers() {
	_instanceLayers.push_back("VK_LAYER_LUNARG_standard_validation");
	_instanceLayers.push_back("VK_LAYER_KHRONOS_validation");
}

PFN_vkCreateDebugReportCallbackEXT fvkCreateDebugReportCallbackEXT = nullptr;
PFN_vkDestroyDebugReportCallbackEXT fvkDestroyDebugReportCallbackEXT = nullptr;

void InitVulkan::_InitDebug()
{
	fvkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(_instance, "vkCreateDebugReportCallbackEXT");
	fvkDestroyDebugReportCallbackEXT = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(_instance, "vkDestroyDebugReportCallbackEXT");
	if (nullptr == fvkCreateDebugReportCallbackEXT || nullptr == fvkDestroyDebugReportCallbackEXT) {
		assert(0 && "Vulkan ERROR: Can't fetch debug function pointers.");
		std::exit(-1);
	}

	fvkCreateDebugReportCallbackEXT(_instance, &debugCallbackCreateInfo, nullptr, &_debugReport);
}

void InitVulkan::_DestroyDebug()
{
	fvkDestroyDebugReportCallbackEXT(_instance, _debugReport, nullptr);
	_debugReport = nullptr;
}