#pragma once

#include <vulkan/vulkan.h>

#include "InitVulkan.h"

class CommandBuffers
{
public:
	CommandBuffers(InitVulkan, VkDevice, VkQueue);
	~CommandBuffers();

private:
	void createFence();
	void createSemaphore();

	void createCommandPool();

	void createCommandBuffers();
	void submitInfo();

	void DestroyCommandBuffers();

	uint32_t _graphicsFamilyIndex = 0;
	VkDevice _device = VK_NULL_HANDLE;
	VkQueue _queue = VK_NULL_HANDLE;

	VkFence _fence;
	VkSemaphore _semaphore;

	VkCommandPool _commandPool;

	VkCommandBuffer _commandBuffer[2];
};