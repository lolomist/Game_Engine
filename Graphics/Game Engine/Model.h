#pragma once
#include "Entity.h"
#include <vector>
#include <vulkan/vulkan.h>
#include "Lights/PointLight.h"
class Model : public Entity
{
public:
	virtual glm::mat4 getModelMatrix() = 0;
	virtual std::vector<VkDeviceMemory> getUniformBuffersMemory() = 0;

	virtual void allocateDescriptorSets(size_t swapChainSize, VkDescriptorPool descriptorPool) = 0;
	virtual void createUniformBuffer(size_t swapChainImageSize) = 0;
	virtual void bindPipeline(VkCommandBuffer commandBuffer) = 0;
	virtual void bindCommandBuffer(VkCommandBuffer commandBuffer, size_t index, std::vector<PointLight*> pointLights) = 0;
	virtual void createDescriptorSets(size_t imageIndex) = 0;
	virtual int hasSpecularTexture() = 0;

	//Destroy
	virtual void destroyTextureImage() = 0;
	virtual void destroyVertexBuffer() = 0;
	virtual void destroyIndexBuffer() = 0;
	virtual void destroyUniformBuffers(size_t swapChainImageSize) = 0;
};
