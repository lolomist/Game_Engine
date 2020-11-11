#pragma once
#include <vulkan/vulkan.h>
#include <fstream>
#include <vector>

class Shader {
public: 
	virtual VkDescriptorSetLayout getDescriptorSetLayout() = 0;
	virtual VkPipelineLayout getPipelineLayout() = 0;
	virtual VkPipeline getGraphicsPipeline() = 0;
	virtual void createGraphicsPipeline(VkExtent2D swapChainExtent, VkDevice device, VkRenderPass renderPass) = 0;
	virtual void createDescriptorSetLayout() = 0;
private:
};