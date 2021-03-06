#pragma once
#include "../Vertex.h"
#include "Shader.h"
#include <string>
#include <vulkan/vulkan.h>
#include <fstream>
#include <vector>

class ColorShader : public Shader
{
public:
	ColorShader(VkExtent2D swapChainExtent, VkDevice device, VkRenderPass renderPass, VkSampleCountFlagBits msaaSamples);
	VkDescriptorSetLayout getDescriptorSetLayout();
	VkPipelineLayout getPipelineLayout();
	VkPipeline getGraphicsPipeline();

	virtual void createGraphicsPipeline(VkExtent2D swapChainExtent, VkDevice device, VkRenderPass renderPass, VkSampleCountFlagBits msaaSamples);
	void destroyPipeline();
	void destroyDescriptorSetLayout();

private:
	std::string _vertShaderPath;
	std::string _fragShaderPath;

	VkExtent2D _swapChainExtent;
	VkDescriptorSetLayout _descriptorSetLayout;
	VkDevice _device;
	VkPipelineLayout _pipelineLayout;
	VkRenderPass _renderPass;
	VkPipeline _graphicsPipeline;

	void createDescriptorSetLayout();
	VkShaderModule createShaderModule(const std::vector<char>& code);
	std::vector<char> readFile(const std::string& filename);
};

