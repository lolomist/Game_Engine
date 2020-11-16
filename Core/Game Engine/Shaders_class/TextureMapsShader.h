#include "../Vertex.h"
#include "Shader.h"
#include <string>
#include <vulkan/vulkan.h>
#include <fstream>
#include <vector>

class TextureMapsShader : public Shader
{
public:
	TextureMapsShader(VkExtent2D swapChainExtent, VkDevice device, VkRenderPass renderPass, VkSampleCountFlagBits msaaSamples, bool isSpecular);
	TextureMapsShader(VkExtent2D swapChainExtent, VkDevice device, VkRenderPass renderPass, VkSampleCountFlagBits msaaSamples, bool isSpecular, bool isEffuse);
	virtual VkDescriptorSetLayout getDescriptorSetLayout() override;
	virtual VkPipelineLayout getPipelineLayout() override;
	virtual VkPipeline getGraphicsPipeline() override;
	virtual void createGraphicsPipeline(VkExtent2D swapChainExtent, VkDevice device, VkRenderPass renderPass, VkSampleCountFlagBits msaaSamples) override;
	virtual void createDescriptorSetLayout() override;
	void createDescriptorSetLayoutObject();

	void destroyPipeline();
	void destroyDescriptorSetLayout();

private:
	bool _isEffuseAndSpecular = false;
	std::string _vertShaderPath;
	std::string _fragShaderPath;

	VkExtent2D _swapChainExtent;
	
	VkDescriptorSetLayout _descriptorSetLayoutObjects;
	
	VkDevice _device;
	VkPipelineLayout _pipelineLayout;
	VkRenderPass _renderPass;
	VkPipeline _graphicsPipeline;
	VkSampleCountFlagBits _msaaSamples;
	VkShaderModule createShaderModule(const std::vector<char>& code);
	std::vector<char> readFile(const std::string& filename);
};

