#pragma once
#include "../Vertex.h"
#include "Shader.h"
#include <string>
#include <vulkan/vulkan.h>
#include <fstream>
#include <vector>

class TextureShader : public Shader
{
public:
	TextureShader(VkExtent2D swapChainExtent, VkDevice device, VkRenderPass renderPass);
	VkDescriptorSetLayout getDescriptorSetLayout();
	VkPipelineLayout getPipelineLayout();
	VkPipeline getGraphicsPipeline();

	void createGraphicsPipeline(VkExtent2D swapChainExtent, VkDevice device, VkRenderPass renderPass);
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

