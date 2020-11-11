#pragma once
#include <vector>
#include "Model.h"
#include "Lights/PointLight.h"

class ObjectsAllocator
{
public:
	ObjectsAllocator(std::vector<Model*> models, std::vector<PointLight*> pointLights, VkDevice device, VkPhysicalDevice physicalDevice);

	void createUniformBuffer(size_t swapChainImageSize);
	void allocateDescriptorSets(size_t swapChainSize, VkDescriptorPool descriptorPool, VkDescriptorSetLayout descriptorSetLayout);
	void createDescriptorSets(size_t swapChainImageSize);
private:

	std::vector<Model*> _models;
	std::vector<PointLight*> _pointLights;

	std::vector<VkBuffer> _uniformBuffers;
	std::vector<VkDeviceMemory> _uniformBuffersMemory;

	std::vector<VkBuffer> _pointLightBuffers;
	std::vector<VkDeviceMemory> _pointLightBuffersMemory;

	VkDevice _device;
	VkPhysicalDevice _physicalDevice;

	std::vector<VkDescriptorSet> _descriptorSets;

	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
};

