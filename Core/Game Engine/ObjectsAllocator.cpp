#include "ObjectsAllocator.h"

ObjectsAllocator::ObjectsAllocator(std::vector<Model*> models, std::vector<PointLight*> pointLights, VkDevice device, VkPhysicalDevice physicalDevice)
{
	_models = models;
	_pointLights = pointLights;
    _device = device;
    _physicalDevice = physicalDevice;
}

void ObjectsAllocator::createUniformBuffer(size_t swapChainImageSize)
{
	for (size_t objIndex = 0; objIndex < _models.size(); objIndex++) {
		VkDeviceSize ubobufferSize = sizeof(UniformBufferObject);

		_uniformBuffers.resize(swapChainImageSize);
		_uniformBuffersMemory.resize(swapChainImageSize);
		for (size_t i = 0; i < swapChainImageSize; i++) {
            createBuffer(ubobufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, _uniformBuffers[i], _uniformBuffersMemory[i]);
		}

	}

    for (size_t LightIndex = 0; LightIndex < _pointLights.size(); LightIndex++) {
        VkDeviceSize ubobufferSize = sizeof(UniformBufferObject);

        _pointLightBuffers.resize(swapChainImageSize);
        _pointLightBuffersMemory.resize(swapChainImageSize);
        for (size_t i = 0; i < swapChainImageSize; i++) {
            createBuffer(ubobufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, _pointLightBuffers[i], _pointLightBuffersMemory[i]);
        }
    }
}

void ObjectsAllocator::allocateDescriptorSets(size_t swapChainSize, VkDescriptorPool descriptorPool, VkDescriptorSetLayout descriptorSetLayout)
{
    std::vector<VkDescriptorSetLayout> layouts(swapChainSize, descriptorSetLayout);
    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = descriptorPool;
    allocInfo.descriptorSetCount = static_cast<uint32_t>(swapChainSize);
    allocInfo.pSetLayouts = layouts.data();

    _descriptorSets.resize(swapChainSize);

    if (vkAllocateDescriptorSets(_device, &allocInfo, _descriptorSets.data()) != VK_SUCCESS) {
        throw std::runtime_error("echec de l'allocation d'un set de descripteurs!");
    }
}

void ObjectsAllocator::createDescriptorSets(size_t swapChainImageSize)
{
    for (size_t objIndex = 0; objIndex < _models.size(); objIndex++) {
        for (size_t i = 0; i < swapChainImageSize; i++) {

        }
    }
}

void ObjectsAllocator::createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory) {
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(_device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
        throw std::runtime_error("echec de la creation d'un buffer!");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(_device, buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);

    // l'appel de cette fonction est limité 
    // Meilleure solution : allouer une grande zone mémoire et utiliser un gestionnaire ( + d'infos chapitre buffer intermédiaire (Vertex buffers))
    if (vkAllocateMemory(_device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
        throw std::runtime_error("echec de l'allocation de memoire!");
    }

    vkBindBufferMemory(_device, buffer, bufferMemory, 0);
}

uint32_t ObjectsAllocator::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(_physicalDevice, &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    throw std::runtime_error("aucun type de memoire ne satisfait le buffer!");
}