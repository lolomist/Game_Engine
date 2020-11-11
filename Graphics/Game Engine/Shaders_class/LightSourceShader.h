#pragma once
#include "Shader.h"
#include "../Vertex.h"
#include <string>
#include <vulkan/vulkan.h>
#include <fstream>
#include <vector>

class LightSourceShader : public Shader
{
public:
	LightSourceShader(VkExtent2D swapChainExtent, VkDevice device, VkRenderPass renderPass);
	
	virtual VkDescriptorSetLayout getDescriptorSetLayout() override;
	virtual VkPipelineLayout getPipelineLayout() override;
	virtual VkPipeline getGraphicsPipeline() override;
	virtual void createGraphicsPipeline(VkExtent2D swapChainExtent, VkDevice device, VkRenderPass renderPass) override;
	virtual void createDescriptorSetLayout() override;

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

	VkShaderModule createShaderModule(const std::vector<char>& code);
	std::vector<char> readFile(const std::string& filename);
};

