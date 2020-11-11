#pragma once
#include "Model.h"
#include "Utils.h"
#include "Shaders_class/Shader.h"
#include "Vertex.h"
#include "enum.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "UBO.h"
#include "OBJLoader.h"
#include "TextureImage.h"

class Cube : public Model
{
public:
	Cube(glm::vec3 color, Shader* shader, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Utils *utils);
	Cube(std::string texturePath, Shader* shader, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Utils* utils);
	Cube(std::string texturePath, std::string specularTexturePath, Shader* shader, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Utils* utils);
	Cube(std::string texturePath, std::string specularTexturePath, std::string specularAndEffuseTexturePath, Shader* shader, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Utils* utils);
	
	virtual const glm::vec3 getPosition() const override;
	virtual glm::vec3 getRotation() override;
	virtual glm::vec3 getScale() override;
	virtual glm::vec3 getColor() override;
	virtual glm::mat4 getModelMatrix() override;
	void loadModel(std::string objPath);
	virtual std::vector<VkDeviceMemory> getUniformBuffersMemory() override;

	virtual void setPosition(glm::vec3 position) override;
	virtual void setRotation(glm::vec3 rotation) override;
	virtual void setScale(glm::vec3 scale) override;
	virtual void setColor(glm::vec3 color) override;

	virtual void createUniformBuffer(size_t swapChainImageSize) override;
	virtual void bindPipeline(VkCommandBuffer commandBuffer) override;
	virtual void bindCommandBuffer(VkCommandBuffer commandBuffer, size_t index, std::vector<PointLight*> pointLights) override;
	virtual void createDescriptorSets(size_t imageIndex) override;
	
	virtual void move(float speed, const int direction, float dt) override;
	virtual void rotate(const glm::vec3 rotation, float dt) override;

	virtual void link(Entity* entity) override;

	virtual void destroyTextureImage() override;
	virtual void destroyVertexBuffer() override;
	virtual void destroyIndexBuffer() override;
	virtual void destroyUniformBuffers(size_t swapChainImageSize) override;

	virtual void allocateDescriptorSets(size_t swapChainSize, VkDescriptorPool descriptorPool) override;

	// Inherited via Model
	virtual int hasSpecularTexture() override;
private:
	Utils* _utils;

	Shader* _shader;

	Entity* _linkedEntity;

	int _hasSpecularTexture = 0;

	//Position data
	glm::vec3 _rotation;
	glm::vec3 _position;
	glm::vec3 _scale;
	glm::vec3 _color;

	//Texture data for obj
	std::vector<TextureImage*> _textureImages;

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

	/*std::vector<VkBuffer> _pointLightBuffers;
	std::vector<VkDeviceMemory> _pointLightBuffersMemory;*/
	
	VkDescriptorSetLayout _descriptorSetLayout;
	std::vector<VkDescriptorSet> _descriptorSets;

	void createVertexBuffer();
	void createIndexBuffer();

	void createDescriptorSetsNoTexture(size_t imageIndex);
	void createDescriptorSets1Texture(size_t swapChainSize, VkDescriptorPool descriptorPool);
	void createDescriptorSets2Texture(size_t imageIndex);
	void createDescriptorSets3Texture(size_t swapChainSize, VkDescriptorPool descriptorPool);

	//void set(const Vertex* vertices, const unsigned nrOfVertices, const uint32_t* indices, const unsigned nrOfIndices);
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

};

