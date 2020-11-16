#pragma once

#include "Utils.h"

#include <string>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <vulkan/vulkan.h>

#include <stb_image.h>

class TextureImage
{
public:
	TextureImage(Utils*);

	VkImage getTextureImage();
	uint32_t getMipLevels();
	VkDeviceMemory getTextureImageMemory();
	VkImageView getTextureImageView();
	VkSampler getTextureSampler();

	//permet de load une texture
	void createTexture(std::string texturePath);
	void createTextureImageView();
	void createTextureSampler();

	void destroyTextureImage();

	// Utils
	/*void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	VkCommandBuffer beginSingleTimeCommands();
	void endSingleTimeCommands(VkCommandBuffer commandBuffer);
	VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);*/

private:
	Utils* _utils;

	/*VkDevice _device;
	VkPhysicalDevice _physicalDevice;
	VkCommandPool _commandPool;
	VkQueue _graphicsQueue;*/
	uint32_t _mipLevels;
	VkImage _textureImage;
	VkDeviceMemory _textureImageMemory;
	VkImageView _textureImageView;
	VkSampler _textureSampler;

	void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
	void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);
	void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);
};

