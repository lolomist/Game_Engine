#pragma once
#include "Entity.h"
#include <vector>
#include <vulkan/vulkan.h>
#include "Lights/PointLight.h"
#include "Vertex.h"
class Model : public Entity
{
public:
	virtual glm::vec3 getEmissionColor() = 0;
	virtual float getEmissionRate() = 0;
	virtual glm::mat4 getModelMatrix() = 0;
	virtual void setEmissionRate(float) = 0;
	virtual void setEmissionColor(glm::vec3) = 0;
	virtual std::vector<VkDeviceMemory> getUniformBuffersMemory() = 0;

	virtual void allocateDescriptorSets(size_t swapChainSize, VkDescriptorPool descriptorPool) = 0;
	virtual void createUniformBuffer(size_t swapChainImageSize) = 0;
	virtual void bindPipeline(VkCommandBuffer commandBuffer) = 0;
	virtual void bindCommandBuffer(VkCommandBuffer commandBuffer, size_t index, std::vector<PointLight*> pointLights) = 0;
	virtual void createDescriptorSets(size_t imageIndex) = 0;
	virtual int hasSpecularTexture() = 0;
	virtual std::vector<Vertex> getVertices() = 0;
	virtual std::vector<glm::vec3> getVerticesPos() = 0;
	virtual void printVertices() = 0;
	virtual void printVerticesFloat() = 0;
	virtual float* getVerticesFloat() = 0;

	//Destroy
	virtual void destroyTextureImage() = 0;
	virtual void destroyVertexBuffer() = 0;
	virtual void destroyIndexBuffer() = 0;
	virtual void destroyUniformBuffers(size_t swapChainImageSize) = 0;
};
