#pragma once

#include "TextureImage.h"
#include "Vertex.h"
#include "Camera.h"
#include <glm/gtx/hash.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <string>
//#include <tiny_obj_loader.h>
#include <unordered_map>


//namespace std {
//	template<> struct hash<Vertex> {
//		size_t operator()(Vertex const& vertex) const {
//			return ((hash<glm::vec3>()(vertex.pos) ^ (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^ (hash<glm::vec2>()(vertex.texCoord) << 1);
//		}
//	};
//}

#include "OBJLoader.h"


class SceneObject
{
public:
	SceneObject(std::string objPath, std::string texturePath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Utils*);
	SceneObject(std::string objPath, std::string texturePath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Camera *camera, Utils*);

	glm::vec3 getRotation();
	glm::vec3 getPosition();
	glm::vec3 getScale();

	void setPosition(glm::vec3);
	void setRotation(glm::vec3);

	VkImage getTextureImage();
	VkDeviceMemory getTextureImageMemory();
	VkImageView getTextureImageView();
	VkSampler getTextureSampler();
	void destroyTextureImage();

	std::vector<VkBuffer> getUniformBuffers();
	std::vector<VkDeviceMemory> getUniformBuffersMemory();
	std::vector<Vertex> getVertices();
	std::vector<uint32_t> getIndices();
	VkBuffer getVertexBuffer();
	VkDeviceMemory getVertexBufferMemory();
	VkBuffer getIndexBuffer();
	VkDeviceMemory getIndexBufferMemory();
	std::vector<VkDescriptorSet> getDescriptorSets();

	bool hasCamera();
	Camera *getCamera();

	glm::mat4 getModelMatrix();

	void createUniformBuffer(size_t swapChainImageSize);
	void createDescriptorSets(size_t swapChainSize, VkDescriptorSetLayout descriptorSetLayout, VkDescriptorPool descriptorPool);
	void bindCommandBuffer(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, size_t index);

	void move(float speed, const int direction);
	void rotate(const glm::vec3 rotation, float dt);

	void destroyVertexBuffer();
	void destroyIndexBuffer();
	void destroyUniformBuffers(size_t swapChainImageSize);

private:
	Utils* _utils;

	//Position data
	glm::vec3 _rotation;
	glm::vec3 _position;
	glm::vec3 _scale;

	glm::mat4 _modelMatrix;

	//Texture data for obj
	TextureImage* _textureImage;

	//Vertex data for obj
	std::vector<Vertex> _vertices;
	VkBuffer _vertexBuffer;
	VkDeviceMemory _vertexBufferMemory;

	//Index data for obj
	std::vector<uint32_t> _indices;
	VkBuffer _indexBuffer;
	VkDeviceMemory _indexBufferMemory;

	std::vector<VkBuffer> _uniformBuffers;
	std::vector<VkDeviceMemory> _uniformBuffersMemory;

	std::vector<VkDescriptorSet> _descriptorSets;

	bool _hasCamera;
	//Camera *_initialCamera = new Camera(glm::vec3(0.f, 0.f, 2.0f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f));
	glm::vec3 _initialPosition;
	Camera* _camera;

	//void loadModelLIB(std::string objPath);
	void loadModel(std::string);
	void createVertexBuffer();
	void createIndexBuffer();

	// Utils
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
};