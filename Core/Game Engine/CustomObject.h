//#pragma once
//
//#include "TextureImage.h"
//#include "Model.h"
//#include "Vertex.h"
//#include "Camera.h"
//#include "Shaders_class/Shader.h"
//#include <glm/gtx/hash.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/glm.hpp>
//#include <string>
////#include <tiny_obj_loader.h>
//#include <unordered_map>
//
//#include "OBJLoader.h"
//
//class CustomObject : public Model
//{
//public:
//	CustomObject(std::string objPath, std::string texturePath, Shader *shader, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Utils*);
//	CustomObject(std::string objPath, std::string texturePath, Shader*shader, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Camera *camera, Utils*);
//	CustomObject(std::string objPath, Shader *shader, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Utils*);
//	CustomObject(std::string objPath, Shader*shader, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Camera *camera, Utils*);
//
//	virtual glm::vec3 getRotation() override;
//	virtual const glm::vec3 getPosition() const override;
//	virtual glm::vec3 getScale() override;
//	virtual glm::vec3 getColor() override;
//
//	virtual void setPosition(glm::vec3 position) override;
//	virtual void setRotation(glm::vec3 rotation) override;
//	virtual void setScale(glm::vec3 scale) override;
//	virtual void setColor(glm::vec3 color) override;
//
//	VkImage getTextureImage();
//	VkDeviceMemory getTextureImageMemory();
//	VkImageView getTextureImageView();
//	VkSampler getTextureSampler();
//	virtual void destroyTextureImage();
//
//	std::vector<VkBuffer> getUniformBuffers();
//	virtual std::vector<VkDeviceMemory> getUniformBuffersMemory() override;
//	std::vector<VkBuffer> getLightBuffers();
//	std::vector<VkDeviceMemory> getLightBuffersMemory();
//	std::vector<Vertex> getVertices();
//	std::vector<uint32_t> getIndices();
//	VkBuffer getVertexBuffer();
//	VkDeviceMemory getVertexBufferMemory();
//	VkBuffer getIndexBuffer();
//	VkDeviceMemory getIndexBufferMemory();
//
//	bool hasCamera();
//	Camera *getCamera();
//
//	virtual glm::mat4 getModelMatrix() override;
//
//	virtual void createUniformBuffer(size_t swapChainImageSize) override;
//	virtual void bindPipeline(VkCommandBuffer commandBuffer) override;
//	virtual void bindCommandBuffer(VkCommandBuffer commandBuffer, size_t index, std::vector<PointLight*>pointLights) override;
//
//	void move(float speed, const int direction, float dt);
//	void rotate(const glm::vec3 rotation, float dt);
//
//	void link(Entity* entity) override;
//
//	void destroyVertexBuffer();
//	void destroyIndexBuffer();
//	void destroyUniformBuffers(size_t swapChainImageSize);
//
//private:
//	Utils* _utils;
//
//	Shader* _shader;
//
//	//Position data
//	glm::vec3 _rotation;
//	glm::vec3 _position;
//	glm::vec3 _scale;
//
//	glm::mat4 _modelMatrix;
//
//	//Texture data for obj
//	TextureImage* _textureImage;
//
//	//Vertex data for obj
//	std::vector<Vertex> _vertices;
//	VkBuffer _vertexBuffer;
//	VkDeviceMemory _vertexBufferMemory;
//
//	//Index data for obj
//	std::vector<uint32_t> _indices;
//	VkBuffer _indexBuffer;
//	VkDeviceMemory _indexBufferMemory;
//
//	std::vector<VkBuffer> _uniformBuffers;
//	std::vector<VkDeviceMemory> _uniformBuffersMemory;
//	std::vector<VkBuffer> _lightBuffers;
//	std::vector<VkDeviceMemory> _lightBuffersMemory;
//
//	std::vector<VkDescriptorSet> _descriptorSets;
//
//	Entity* _linkedEntity;
//
//	bool _hasCamera;
//	Camera* _camera;
//	bool _hasTexture = false;
//
//	void loadModel(std::string);
//	void createVertexBuffer();
//	void createIndexBuffer();
//
//	// Utils
//	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
//
//
//	// Inherited via Model
//	virtual void allocateDescriptorSets(size_t swapChainSize, VkDescriptorPool descriptorPool) override;
//
//	virtual void createDescriptorSets(size_t imageIndex) override;
//
//};