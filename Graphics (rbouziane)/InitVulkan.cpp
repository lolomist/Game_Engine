#include "BUILD_OPTIONS.h"

#include "InitVulkan.h"
#include "CheckError.h"

#include <cstdlib>
#include <assert.h>
#include <vector>

#include <iostream>
#include <sstream>

//#if defined( _WIN32 )
//#include <windows.h>
//#endif

InitVulkan::InitVulkan()
{
	//Call debug function only when it's enable
	if (BUILD_ENABLE_VULKAN_DEBUG)
		SetupDebug();
	InitInstance();
	//Call debug function only when it's enable
	if (BUILD_ENABLE_VULKAN_DEBUG)
		InitDebug();
	InitDevice();
}

InitVulkan::~InitVulkan()
{
	DestroyDevice();
	//Call debug function only when it's enable
	if (BUILD_ENABLE_VULKAN_DEBUG)
		DestroyDebug();
	DestroyInstance();
}

void InitVulkan::InitInstance()
{
	//Application information
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "3DGameEngine";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	//Information to create instance
	VkInstanceCreateInfo instance_create_info{};
	instance_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instance_create_info.pApplicationInfo = &appInfo;
	instance_create_info.enabledLayerCount = static_cast<uint32_t>(_instanceLayers.size());
	instance_create_info.ppEnabledLayerNames = _instanceLayers.data();
	instance_create_info.enabledExtensionCount = static_cast<uint32_t>(_instanceExtensions.size());
	instance_create_info.ppEnabledExtensionNames = _instanceExtensions.data();
	instance_create_info.pNext = &_debugCallbackCreateInfo;

	CheckError(vkCreateInstance(&instance_create_info, nullptr, &_instance));
}

//Cleanup instance
void InitVulkan::DestroyInstance()
{
	vkDestroyInstance(_instance, nullptr);
	_instance = nullptr;
}

void InitVulkan::InitDevice()
{
	{
		//Get count of physical device
		uint32_t gpu_count = 0;
		vkEnumeratePhysicalDevices(_instance, &gpu_count, nullptr);
		std::vector<VkPhysicalDevice> gpu_list(gpu_count);
		vkEnumeratePhysicalDevices(_instance, &gpu_count, gpu_list.data());
		_gpu = gpu_list[0];
		vkGetPhysicalDeviceProperties(_gpu, &_gpuProperties);
	}
	{
		//Get count of device queue families
		uint32_t family_count = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(_gpu, &family_count, nullptr);
		std::vector<VkQueueFamilyProperties> family_property_list(family_count);
		vkGetPhysicalDeviceQueueFamilyProperties(_gpu, &family_count, family_property_list.data());

		//Check if queue family is supporting graphics
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
		//print instance layers name
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
		//print device layers name
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

	//Specify the queues to create
	float queue_priorities[]{ 1.0f };
	VkDeviceQueueCreateInfo device_queue_create_info{};
	device_queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	device_queue_create_info.queueFamilyIndex = _graphicsFamilyIndex;
	device_queue_create_info.queueCount = 1;
	device_queue_create_info.pQueuePriorities = queue_priorities;

	//Create logical device
	VkPhysicalDeviceFeatures deviceFeatures{};
	VkDeviceCreateInfo device_create_info{};
	device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	device_create_info.queueCreateInfoCount = 1;
	device_create_info.pEnabledFeatures = &deviceFeatures;
	device_create_info.pQueueCreateInfos = &device_queue_create_info;
	//device_create_info.enabledLayerCount = _instanceLayers.size();				// it looks like it's deprecated, need more information about it
	//device_create_info.ppEnabledLayerNames = _instanceLayers.data();				// it looks like it's deprecated, need more information about it
	device_create_info.enabledExtensionCount = static_cast<uint32_t>(_deviceExtensions.size());
	device_create_info.ppEnabledExtensionNames = _deviceExtensions.data();

	CheckError(vkCreateDevice(_gpu, &device_create_info, nullptr, &_device));

	vkGetDeviceQueue(_device, _graphicsFamilyIndex, 0, &_queue);
}

//Cleanup device
void InitVulkan::DestroyDevice()
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

void InitVulkan::SetupDebug()
{
	_debugCallbackCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
	_debugCallbackCreateInfo.pfnCallback = VulkanDebugCallback;
	_debugCallbackCreateInfo.flags = VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT | VK_DEBUG_REPORT_ERROR_BIT_EXT | 0;

	GetRequiredExtensions();
	GetRequiredLayers();
}

//Add required extensions
void InitVulkan::GetRequiredExtensions() {
	_instanceExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	_instanceExtensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
}

//Add required Layers
void InitVulkan::GetRequiredLayers() {
	//_instanceLayers.push_back("VK_LAYER_LUNARG_standard_validation");
	_instanceLayers.push_back("VK_LAYER_KHRONOS_validation");
}

PFN_vkCreateDebugReportCallbackEXT fvkCreateDebugReportCallbackEXT = nullptr;
PFN_vkDestroyDebugReportCallbackEXT fvkDestroyDebugReportCallbackEXT = nullptr;

//Initialisation of debug report
void InitVulkan::InitDebug()
{
	fvkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(_instance, "vkCreateDebugReportCallbackEXT");
	fvkDestroyDebugReportCallbackEXT = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(_instance, "vkDestroyDebugReportCallbackEXT");
	if (nullptr == fvkCreateDebugReportCallbackEXT || nullptr == fvkDestroyDebugReportCallbackEXT) {
		assert(0 && "Vulkan ERROR: Can't fetch debug function pointers.");
		std::exit(-1);
	}

	fvkCreateDebugReportCallbackEXT(_instance, &_debugCallbackCreateInfo, nullptr, &_debugReport);
}

//Cleanup debug report
void InitVulkan::DestroyDebug()
{
	fvkDestroyDebugReportCallbackEXT(_instance, _debugReport, nullptr);
	_debugReport = VK_NULL_HANDLE;
}