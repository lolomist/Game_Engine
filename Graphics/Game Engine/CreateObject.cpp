#include "CreateObject.h"

//Just Color
CreateObject::CreateObject(std::string modelPath, glm::vec3 color, Shader* shader, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Utils* utils)
{
    _utils = utils;
    _rotation = rotation;
    _position = position;
    _scale = scale;
    _color = color;
    _shader = shader;

    loadModel(modelPath);

    createVertexBuffer();
    createIndexBuffer();
}

// Simple Texture
CreateObject::CreateObject(std::string modelPath, std::string texturePath, Shader* shader, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Utils* utils)
{
    _utils = utils;
    _rotation = rotation;
    _position = position;
    _scale = scale;
    _color = glm::vec3(1.f);
    _shader = shader;

    TextureImage* texture = new TextureImage(_utils);
    texture->createTexture(texturePath);
    texture->createTextureImageView();
    texture->createTextureSampler();

    _textureImages.push_back(texture);

    loadModel(modelPath);

    createVertexBuffer();
    createIndexBuffer();
}

//Specular Texture
CreateObject::CreateObject(std::string modelPath, std::string texturePath, std::string specularTexturePath, Shader* shader, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Utils* utils)
{
    _utils = utils;
    _rotation = rotation;
    _position = position;
    _scale = scale;
    _color = glm::vec3(1.f);
    _shader = shader;
    _hasSpecularTexture = 1;

    TextureImage* texture = new TextureImage(_utils);
    texture->createTexture(texturePath);
    texture->createTextureImageView();
    texture->createTextureSampler();

    TextureImage* specTexture = new TextureImage(_utils);
    specTexture->createTexture(specularTexturePath);
    specTexture->createTextureImageView();
    specTexture->createTextureSampler();

    _textureImages.push_back(texture);
    _textureImages.push_back(specTexture);

    loadModel(modelPath);

    createVertexBuffer();
    createIndexBuffer();
}

//Emission Texture
CreateObject::CreateObject(std::string modelPath, std::string texturePath, std::string emissionTexturePath, Shader* shader, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Utils* utils, bool isEmissionTexture)
{
    _utils = utils;
    _rotation = rotation;
    _position = position;
    _scale = scale;
    _color = glm::vec3(1.f);
    _shader = shader;
    _hasSpecularTexture = 2;

    TextureImage* texture = new TextureImage(_utils);
    texture->createTexture(texturePath);
    texture->createTextureImageView();
    texture->createTextureSampler();

    TextureImage* emissionTexture = new TextureImage(_utils);
    emissionTexture->createTexture(emissionTexturePath);
    emissionTexture->createTextureImageView();
    emissionTexture->createTextureSampler();

    _textureImages.push_back(texture);
    _textureImages.push_back(emissionTexture);

    loadModel(modelPath);

    createVertexBuffer();
    createIndexBuffer();
}

CreateObject::CreateObject(std::string modelPath, std::string texturePath, std::string specularTexturePath, std::string emissionTexturePath, Shader* shader, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Utils* utils)
{
    _utils = utils;
    _rotation = rotation;
    _position = position;
    _scale = scale;
    _color = glm::vec3(1.f);
    _shader = shader;
    _hasSpecularTexture = 3;

    TextureImage* texture = new TextureImage(_utils);
    texture->createTexture(texturePath);
    texture->createTextureImageView();
    texture->createTextureSampler();

    TextureImage* specularTexture = new TextureImage(_utils);
    specularTexture->createTexture(specularTexturePath);
    specularTexture->createTextureImageView();
    specularTexture->createTextureSampler();

    TextureImage* emissionTexture = new TextureImage(_utils);
    emissionTexture->createTexture(emissionTexturePath);
    emissionTexture->createTextureImageView();
    emissionTexture->createTextureSampler();

    _textureImages.push_back(texture);
    _textureImages.push_back(specularTexture);
    _textureImages.push_back(emissionTexture);

    loadModel(modelPath);

    createVertexBuffer();
    createIndexBuffer();
}

//
//CreateObject::CreateObject(std::string modelPath, glm::vec3 color, std::string specularTexturePath, std::string emissionTexturePath, Shader* shader, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Utils* utils)
//{
//    _utils = utils;
//    _rotation = rotation;
//    _position = position;
//    _scale = scale;
//    _color = color;
//    _shader = shader;
//    _hasSpecularTexture = 4;
//
//    TextureImage* specularTexture = new TextureImage(_utils);
//    specularTexture->createTexture(specularTexturePath);
//    specularTexture->createTextureImageView();
//    specularTexture->createTextureSampler();
//
//    TextureImage* emissionTexture = new TextureImage(_utils);
//    emissionTexture->createTexture(emissionTexturePath);
//    emissionTexture->createTextureImageView();
//    emissionTexture->createTextureSampler();
//
//    _textureImages.push_back(specularTexture);
//    _textureImages.push_back(emissionTexture);
//
//    loadModel(modelPath);
//
//    createVertexBuffer();
//    createIndexBuffer();
//}

const glm::vec3 CreateObject::getPosition() const
{
    return _position;
}

glm::vec3 CreateObject::getRotation()
{
    return _rotation;
}

glm::vec3 CreateObject::getScale()
{
    return _scale;
}

glm::vec3 CreateObject::getColor()
{
    return _color;
}

void CreateObject::setPosition(glm::vec3 position)
{
    _position = position;
}

void CreateObject::setRotation(glm::vec3 rotation)
{
    _rotation = rotation;
}

void CreateObject::setScale(glm::vec3 scale)
{
    _scale = scale;
}

void CreateObject::setColor(glm::vec3 color)
{
    _color = color;
}

void CreateObject::move(float speed, const int direction, float dt)
{
    switch (direction) {
    case UP:
        _position = this->moveUp(_position, speed, dt, _linkedEntity);
        break;
    case DOWN:
        _position = this->moveDown(_position, speed, dt, _linkedEntity);
        break;
    case FORWARD:
        _position = this->moveForward(_position, speed, dt, _linkedEntity);
        break;
    case BACKWARD:
        _position = this->moveBackward(_position, speed, dt, _linkedEntity);
        break;
    case LEFT:
        _position = this->moveLeft(_position, speed, dt, _linkedEntity);
        break;
    case RIGHT:
        _position = this->moveRight(_position, speed, dt, _linkedEntity);
        break;
    }
    updateVertex();
}

void CreateObject::rotate(const glm::vec3 rotation, float dt)
{
    _rotation += rotation * dt;
}

void CreateObject::link(Entity* entity)
{
    _linkedEntity = entity;
}

glm::mat4 CreateObject::getModelMatrix()
{
    glm::mat4 ModelMatrix(1.0f);
    ModelMatrix = glm::translate(ModelMatrix, _position);
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(_scale));

    return ModelMatrix;
}

std::vector<VkDeviceMemory> CreateObject::getUniformBuffersMemory()
{
    return _uniformBuffersMemory;
}

void CreateObject::allocateDescriptorSets(size_t swapChainSize, VkDescriptorPool descriptorPool)
{
    std::vector<VkDescriptorSetLayout> layouts(swapChainSize, _shader->getDescriptorSetLayout());
    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = descriptorPool;
    allocInfo.descriptorSetCount = static_cast<uint32_t>(swapChainSize);
    allocInfo.pSetLayouts = layouts.data();

    _descriptorSets.resize(swapChainSize);

    if (vkAllocateDescriptorSets(_utils->getDevice(), &allocInfo, _descriptorSets.data()) != VK_SUCCESS) {
        throw std::runtime_error("echec de l'allocation d'un set de descripteurs!");
    }
}

void CreateObject::createUniformBuffer(size_t swapChainImageSize)
{
    VkDeviceSize ubobufferSize = sizeof(UniformBufferObject);

    _uniformBuffers.resize(swapChainImageSize);
    _uniformBuffersMemory.resize(swapChainImageSize);

    for (size_t i = 0; i < swapChainImageSize; i++) {
        _utils->createBuffer(ubobufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, _uniformBuffers[i], _uniformBuffersMemory[i]);
    }
}

void CreateObject::createDescriptorSets(size_t imageIndex)
{
    if (_textureImages.size() == 0)
        createDescriptorSetNoTexture(imageIndex);
    else if (_textureImages.size() == 1)
        createDescriptorSetTexture(imageIndex);
    else if (_textureImages.size() == 2)
        createDescriptorSetSpecularTexture(imageIndex);
    else if (_textureImages.size() == 3)
        createDescriptorSetSpecularEmissionTexture(imageIndex);
}

void CreateObject::bindPipeline(VkCommandBuffer commandBuffer)
{
    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _shader->getGraphicsPipeline());
}

void CreateObject::bindCommandBuffer(VkCommandBuffer commandBuffer, size_t index, std::vector<PointLight*> pointLights)
{
    VkBuffer vertexBuffers[] = { _vertexBuffer };
    VkDeviceSize offsets[] = { 0 };

    vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
    vkCmdBindIndexBuffer(commandBuffer, _indexBuffer, 0, VK_INDEX_TYPE_UINT32);
    vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _shader->getPipelineLayout(), 0, 1, &_descriptorSets[index], 0, nullptr);
    vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(_indices.size()), 1, 0, 0, 0);
}


void CreateObject::destroyTextureImage()
{
    if (_textureImages.size() > 0) {
        for (uint32_t textureIdx = 0; textureIdx < _textureImages.size(); textureIdx++) {
            _textureImages[textureIdx]->destroyTextureImage();
        }
    }
}

void CreateObject::destroyVertexBuffer()
{
    vkDestroyBuffer(_utils->getDevice(), _vertexBuffer, nullptr);
    vkFreeMemory(_utils->getDevice(), _vertexBufferMemory, nullptr);
}

void CreateObject::destroyIndexBuffer()
{
    vkDestroyBuffer(_utils->getDevice(), _indexBuffer, nullptr);
    vkFreeMemory(_utils->getDevice(), _indexBufferMemory, nullptr);
}

void CreateObject::destroyUniformBuffers(size_t swapChainImageSize)
{
    for (size_t i = 0; i < swapChainImageSize; i++) {
        vkDestroyBuffer(_utils->getDevice(), _uniformBuffers[i], nullptr);
        vkFreeMemory(_utils->getDevice(), _uniformBuffersMemory[i], nullptr);
    }
}

void CreateObject::loadModel(std::string objPath)
{
   _verticesPos = loadOBJ(objPath.c_str(), _vertices, _indices, _verticesPos, _color);
   updateVertex();
   _verticesFloat = &_verticesPos[0].x;
}

void CreateObject::createVertexBuffer()
{
    VkDeviceSize bufferSize = sizeof(_vertices[0]) * _vertices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    _utils->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(_utils->getDevice(), stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, _vertices.data(), (size_t)bufferSize);
    vkUnmapMemory(_utils->getDevice(), stagingBufferMemory);

    _utils->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, _vertexBuffer, _vertexBufferMemory);

    copyBuffer(stagingBuffer, _vertexBuffer, bufferSize);

    vkDestroyBuffer(_utils->getDevice(), stagingBuffer, nullptr);
    vkFreeMemory(_utils->getDevice(), stagingBufferMemory, nullptr);
}

void CreateObject::createIndexBuffer()
{
    VkDeviceSize bufferSize = sizeof(_indices[0]) * _indices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    _utils->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(_utils->getDevice(), stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, _indices.data(), (size_t)bufferSize);
    vkUnmapMemory(_utils->getDevice(), stagingBufferMemory);

    _utils->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, _indexBuffer, _indexBufferMemory);

    copyBuffer(stagingBuffer, _indexBuffer, bufferSize);

    vkDestroyBuffer(_utils->getDevice(), stagingBuffer, nullptr);
    vkFreeMemory(_utils->getDevice(), stagingBufferMemory, nullptr);
}

void CreateObject::copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
{
    VkCommandBuffer commandBuffer = _utils->beginSingleTimeCommands();

    VkBufferCopy copyRegion{};
    copyRegion.size = size;
    vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

    _utils->endSingleTimeCommands(commandBuffer);
}

void CreateObject::createDescriptorSetNoTexture(size_t i)
{
    VkDescriptorBufferInfo bufferInfo{};
    bufferInfo.buffer = _uniformBuffers[i];
    bufferInfo.offset = 0;
    bufferInfo.range = sizeof(UniformBufferObject);

    std::vector<VkWriteDescriptorSet> descriptorWrites;

    VkWriteDescriptorSet descriptorWriteBuffer{};
    descriptorWriteBuffer.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWriteBuffer.dstSet = _descriptorSets[i];
    descriptorWriteBuffer.dstBinding = 0;
    descriptorWriteBuffer.dstArrayElement = 0;
    descriptorWriteBuffer.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptorWriteBuffer.descriptorCount = 1;
    descriptorWriteBuffer.pBufferInfo = &bufferInfo;
    descriptorWrites.push_back(descriptorWriteBuffer);

    vkUpdateDescriptorSets(_utils->getDevice(), static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
}

void CreateObject::createDescriptorSetTexture(size_t i)
{
    VkDescriptorBufferInfo bufferInfo{};
    bufferInfo.buffer = _uniformBuffers[i];
    bufferInfo.offset = 0;
    bufferInfo.range = sizeof(UniformBufferObject);
    
    std::vector<VkWriteDescriptorSet> descriptorWrites;
    
    VkWriteDescriptorSet descriptorWriteBuffer{};
    descriptorWriteBuffer.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWriteBuffer.dstSet = _descriptorSets[i];
    descriptorWriteBuffer.dstBinding = 0;
    descriptorWriteBuffer.dstArrayElement = 0;
    descriptorWriteBuffer.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptorWriteBuffer.descriptorCount = 1;
    descriptorWriteBuffer.pBufferInfo = &bufferInfo;
    descriptorWrites.push_back(descriptorWriteBuffer);
    
    VkDescriptorImageInfo imageInfo{};
    imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    imageInfo.imageView = _textureImages[0]->getTextureImageView();
    imageInfo.sampler = _textureImages[0]->getTextureSampler();
    
    VkWriteDescriptorSet descriptorWriteImage{};
    descriptorWriteImage.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWriteImage.dstSet = _descriptorSets[i];
    descriptorWriteImage.dstBinding = 1;
    descriptorWriteImage.dstArrayElement = 0;
    descriptorWriteImage.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    descriptorWriteImage.descriptorCount = 1;
    descriptorWriteImage.pImageInfo = &imageInfo;

    VkWriteDescriptorSet descriptorWriteImageSpecular{};
    descriptorWriteImageSpecular.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWriteImageSpecular.dstSet = _descriptorSets[i];
    descriptorWriteImageSpecular.dstBinding = 2;
    descriptorWriteImageSpecular.dstArrayElement = 0;
    descriptorWriteImageSpecular.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    descriptorWriteImageSpecular.descriptorCount = 1;
    descriptorWriteImageSpecular.pImageInfo = &imageInfo;

    VkWriteDescriptorSet descriptorWriteImageEmission{};
    descriptorWriteImageEmission.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWriteImageEmission.dstSet = _descriptorSets[i];
    descriptorWriteImageEmission.dstBinding = 3;
    descriptorWriteImageEmission.dstArrayElement = 0;
    descriptorWriteImageEmission.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    descriptorWriteImageEmission.descriptorCount = 1;
    descriptorWriteImageEmission.pImageInfo = &imageInfo;
    
    descriptorWrites.push_back(descriptorWriteImage);
    descriptorWrites.push_back(descriptorWriteImageSpecular);
    descriptorWrites.push_back(descriptorWriteImageEmission);
    vkUpdateDescriptorSets(_utils->getDevice(), static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
}

void CreateObject::createDescriptorSetSpecularTexture(size_t i)
{
    VkDescriptorBufferInfo bufferInfo{};
    bufferInfo.buffer = _uniformBuffers[i];
    bufferInfo.offset = 0;
    bufferInfo.range = sizeof(UniformBufferObject);

    std::vector<VkWriteDescriptorSet> descriptorWrites;

    VkWriteDescriptorSet descriptorWriteBuffer{};
    descriptorWriteBuffer.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWriteBuffer.dstSet = _descriptorSets[i];
    descriptorWriteBuffer.dstBinding = 0;
    descriptorWriteBuffer.dstArrayElement = 0;
    descriptorWriteBuffer.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptorWriteBuffer.descriptorCount = 1;
    descriptorWriteBuffer.pBufferInfo = &bufferInfo;
    descriptorWrites.push_back(descriptorWriteBuffer);

    VkDescriptorImageInfo imageInfo{};
    imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    imageInfo.imageView = _textureImages[0]->getTextureImageView();
    imageInfo.sampler = _textureImages[0]->getTextureSampler();

    VkWriteDescriptorSet descriptorWriteImage{};
    descriptorWriteImage.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWriteImage.dstSet = _descriptorSets[i];
    descriptorWriteImage.dstBinding = 1;
    descriptorWriteImage.dstArrayElement = 0;
    descriptorWriteImage.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    descriptorWriteImage.descriptorCount = 1;
    descriptorWriteImage.pImageInfo = &imageInfo;

    VkDescriptorImageInfo imageInfoSpecular{};
    imageInfoSpecular.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    imageInfoSpecular.imageView = _textureImages[1]->getTextureImageView();
    imageInfoSpecular.sampler = _textureImages[1]->getTextureSampler();

    VkWriteDescriptorSet descriptorWriteImageSpecular{};
    descriptorWriteImageSpecular.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWriteImageSpecular.dstSet = _descriptorSets[i];
    descriptorWriteImageSpecular.dstBinding = 2;
    descriptorWriteImageSpecular.dstArrayElement = 0;
    descriptorWriteImageSpecular.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    descriptorWriteImageSpecular.descriptorCount = 1;
    descriptorWriteImageSpecular.pImageInfo = &imageInfoSpecular;

    VkWriteDescriptorSet descriptorWriteImageEmission{};
    descriptorWriteImageEmission.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWriteImageEmission.dstSet = _descriptorSets[i];
    descriptorWriteImageEmission.dstBinding = 3;
    descriptorWriteImageEmission.dstArrayElement = 0;
    descriptorWriteImageEmission.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    descriptorWriteImageEmission.descriptorCount = 1;
    descriptorWriteImageEmission.pImageInfo = &imageInfo;

    descriptorWrites.push_back(descriptorWriteImage);
    descriptorWrites.push_back(descriptorWriteImageSpecular);
    descriptorWrites.push_back(descriptorWriteImageEmission);
    vkUpdateDescriptorSets(_utils->getDevice(), static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
}

void CreateObject::createDescriptorSetSpecularEmissionTexture(size_t i)
{
    VkDescriptorBufferInfo bufferInfo{};
    bufferInfo.buffer = _uniformBuffers[i];
    bufferInfo.offset = 0;
    bufferInfo.range = sizeof(UniformBufferObject);

    std::vector<VkWriteDescriptorSet> descriptorWrites;

    VkWriteDescriptorSet descriptorWriteBuffer{};
    descriptorWriteBuffer.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWriteBuffer.dstSet = _descriptorSets[i];
    descriptorWriteBuffer.dstBinding = 0;
    descriptorWriteBuffer.dstArrayElement = 0;
    descriptorWriteBuffer.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptorWriteBuffer.descriptorCount = 1;
    descriptorWriteBuffer.pBufferInfo = &bufferInfo;
    descriptorWrites.push_back(descriptorWriteBuffer);

    VkDescriptorImageInfo imageInfo{};
    imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    imageInfo.imageView = _textureImages[0]->getTextureImageView();
    imageInfo.sampler = _textureImages[0]->getTextureSampler();

    VkWriteDescriptorSet descriptorWriteImage{};
    descriptorWriteImage.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWriteImage.dstSet = _descriptorSets[i];
    descriptorWriteImage.dstBinding = 1;
    descriptorWriteImage.dstArrayElement = 0;
    descriptorWriteImage.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    descriptorWriteImage.descriptorCount = 1;
    descriptorWriteImage.pImageInfo = &imageInfo;

    VkDescriptorImageInfo imageInfoSpecular{};
    imageInfoSpecular.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    imageInfoSpecular.imageView = _textureImages[1]->getTextureImageView();
    imageInfoSpecular.sampler = _textureImages[1]->getTextureSampler();

    VkWriteDescriptorSet descriptorWriteImageSpecular{};
    descriptorWriteImageSpecular.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWriteImageSpecular.dstSet = _descriptorSets[i];
    descriptorWriteImageSpecular.dstBinding = 2;
    descriptorWriteImageSpecular.dstArrayElement = 0;
    descriptorWriteImageSpecular.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    descriptorWriteImageSpecular.descriptorCount = 1;
    descriptorWriteImageSpecular.pImageInfo = &imageInfoSpecular;

    VkDescriptorImageInfo imageInfoEmission{};
    imageInfoEmission.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    imageInfoEmission.imageView = _textureImages[2]->getTextureImageView();
    imageInfoEmission.sampler = _textureImages[2]->getTextureSampler();

    VkWriteDescriptorSet descriptorWriteImageEmission{};
    descriptorWriteImageEmission.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWriteImageEmission.dstSet = _descriptorSets[i];
    descriptorWriteImageEmission.dstBinding = 3;
    descriptorWriteImageEmission.dstArrayElement = 0;
    descriptorWriteImageEmission.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    descriptorWriteImageEmission.descriptorCount = 1;
    descriptorWriteImageEmission.pImageInfo = &imageInfoEmission;

    descriptorWrites.push_back(descriptorWriteImage);
    descriptorWrites.push_back(descriptorWriteImageSpecular);
    descriptorWrites.push_back(descriptorWriteImageEmission);
    vkUpdateDescriptorSets(_utils->getDevice(), static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
}

void CreateObject::updateVertex()
{
    static std::vector<glm::vec3> initialVertexPosition = _verticesPos;

    for (size_t i = 0; i != _verticesPos.size(); i++) {
        _verticesPos.at(i).x = initialVertexPosition.at(i).x + _position.x;
        _verticesPos.at(i).y = initialVertexPosition.at(i).y + _position.y;
        _verticesPos.at(i).z = initialVertexPosition.at(i).z + _position.z;
    }
    _verticesFloat = &_verticesPos[0].x;
}

void CreateObject::printVerticesFloat()
{
    for (size_t i = 0; i < _verticesPos.size() * 3; i++) {
        std::cout << "VERTICES FLOAT [" << i << "] = " << _verticesFloat[i] << std::endl;
    }
}

float* CreateObject::getVerticesFloat()
{
    return _verticesFloat;
}

std::vector<Vertex> CreateObject::getVertices()
{
    return _vertices;
}

std::vector<glm::vec3> CreateObject::getVerticesPos()
{
    return _verticesPos;
}

void CreateObject::printVertices()
{
    for (size_t i = 0; i != _verticesPos.size(); i++) {
        std::cout << "VERTEX[" << i << "] X = " << _verticesPos.at(i).x << std::endl;
        std::cout << "VERTEX[" << i << "] Y = " << _verticesPos.at(i).y << std::endl;
        std::cout << "VERTEX[" << i << "] Z = " << _verticesPos.at(i).z << std::endl;
    }
}

void CreateObject::setEmissionRate(float emissionRate)
{
    _emissionRate = emissionRate;
}

void CreateObject::setEmissionColor(glm::vec3 emissionColor)
{
    _emissionColor = emissionColor;
}

glm::vec3 CreateObject::getEmissionColor()
{
    return _emissionColor;
}

float CreateObject::getEmissionRate()
{
    return _emissionRate;
}

int CreateObject::hasSpecularTexture()
{
    return _hasSpecularTexture;
}
