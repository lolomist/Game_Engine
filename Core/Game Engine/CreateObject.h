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

class CreateObject : public Model
{
public:
	//Just Color
	CreateObject(std::string modelPath, glm::vec3 color, Shader* shader, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Utils* utils);
	// Simple Texture
	CreateObject(std::string modelPath, std::string texturePath, Shader* shader, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Utils* utils);
	//Specular Texture
	CreateObject(std::string modelPath, std::string texturePath, std::string specularTexturePath, Shader* shader, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Utils* utils);
	//Emission Texture
	CreateObject(std::string modelPath, std::string texturePath, std::string emissionTexturePath, Shader* shader, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Utils* utils, bool isEmissionTexture);
	//Specular + Emission Texture
	CreateObject(std::string modelPath, std::string texturePath, std::string specularTexturePath, std::string emissionTexturePath, Shader* shader, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Utils* utils);
	//Color + Specular + Emission Texture
	//CreateObject(std::string modelPath, glm::vec3 color, std::string specularTexturePath, std::string emissionTexturePath, Shader* shader, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Utils* utils);

	virtual const glm::vec3 getPosition() const override;
	virtual glm::vec3 getRotation() override;
	virtual glm::vec3 getScale() override;
	virtual glm::vec3 getColor() override;
	virtual void setPosition(glm::vec3 position) override;
	virtual void setRotation(glm::vec3 rotation) override;
	virtual void setScale(glm::vec3 scale) override;
	virtual void setColor(glm::vec3 color) override;
	virtual void move(float speed, const int direction, float dt) override;
	virtual void rotate(const glm::vec3 rotation, float dt) override;
	virtual void link(Entity* entity) override;
	virtual glm::mat4 getModelMatrix() override;
	virtual std::vector<VkDeviceMemory> getUniformBuffersMemory() override;
	virtual void allocateDescriptorSets(size_t swapChainSize, VkDescriptorPool descriptorPool) override;
	virtual void createUniformBuffer(size_t swapChainImageSize) override;
	virtual void bindPipeline(VkCommandBuffer commandBuffer) override;
	virtual void bindCommandBuffer(VkCommandBuffer commandBuffer, size_t index, std::vector<PointLight*> pointLights) override;
	virtual void createDescriptorSets(size_t imageIndex) override;
	virtual void destroyTextureImage() override;
	virtual void destroyVertexBuffer() override;
	virtual void destroyIndexBuffer() override;
	virtual void destroyUniformBuffers(size_t swapChainImageSize) override;
	virtual int hasSpecularTexture() override;
	virtual glm::vec3 getEmissionColor() override;
	virtual float getEmissionRate() override;
	virtual void setEmissionRate(float emissionRate) override;
	virtual void setEmissionColor(glm::vec3 emissionColor) override;
	virtual std::vector<Vertex> getVertices() override;
	virtual std::vector<glm::vec3> getVerticesPos() override;
	virtual void printVertices() override;
	virtual float* getVerticesFloat() override;

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

	glm::vec3 _emissionColor = glm::vec3(0.f, 0.f, 0.f);
	float _emissionRate = 1.0;

	//Texture data for obj
	std::vector<TextureImage*> _textureImages;

	//Vertex data for obj
	std::vector<Vertex> _vertices;
	std::vector<glm::vec3> _verticesPos;
	float* _verticesFloat;
	VkBuffer _vertexBuffer;
	VkDeviceMemory _vertexBufferMemory;

	//Index data for obj
	std::vector<uint32_t> _indices;
	VkBuffer _indexBuffer;
	VkDeviceMemory _indexBufferMemory;

	//Buffer data
	std::vector<VkBuffer> _uniformBuffers;
	std::vector<VkDeviceMemory> _uniformBuffersMemory;
	VkDescriptorSetLayout _descriptorSetLayout;
	std::vector<VkDescriptorSet> _descriptorSets;

	void loadModel(std::string objPath);
	void createVertexBuffer();
	void createIndexBuffer();
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

	void createDescriptorSetNoTexture(size_t imageIndex);
	void createDescriptorSetTexture(size_t imageIndex);
	void createDescriptorSetSpecularTexture(size_t imageIndex);
	void createDescriptorSetSpecularEmissionTexture(size_t imageIndex);
	void updateVertex();
	void printVerticesFloat();
};