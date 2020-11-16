//#include "Cube.h"
//#include "Lights/PointLight.h"
//
//Cube::Cube(glm::vec3 color, Shader *shader, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Utils *utils)
//{
//    _utils = utils;
//    _rotation = rotation;
//    _position = position;
//    _scale = scale;
//    _color = color;
//    _shader = shader;
//
//    loadModel("models/cube.obj");
//
//    createVertexBuffer();
//    createIndexBuffer();
//}
//
//Cube::Cube(std::string texturePath, Shader* shader, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Utils* utils)
//{
//    _utils = utils;
//    _rotation = rotation;
//    _position = position;
//    _scale = scale;
//    _color = glm::vec3(1.f);
//    _shader = shader;
//
//    TextureImage *texture = new TextureImage(_utils);
//    texture->createTexture(texturePath);
//    texture->createTextureImageView();
//    texture->createTextureSampler();
//
//    _textureImages.push_back(texture);
//
//    loadModel("models/cube.obj");
//
//    createVertexBuffer();
//    createIndexBuffer();
//}
//
//Cube::Cube(std::string texturePath, std::string specularTexturePath, Shader* shader, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Utils* utils)
//{
//    _utils = utils;
//    _rotation = rotation;
//    _position = position;
//    _scale = scale;
//    _color = glm::vec3(1.f);
//    _shader = shader;
//
//    TextureImage* texture = new TextureImage(_utils);
//    texture->createTexture(texturePath);
//    texture->createTextureImageView();
//    texture->createTextureSampler();
//
//    TextureImage* specularTexture = new TextureImage(_utils);
//    specularTexture->createTexture(specularTexturePath);
//    specularTexture->createTextureImageView();
//    specularTexture->createTextureSampler();
//
//    _textureImages.push_back(texture);
//    _textureImages.push_back(specularTexture);
//
//    loadModel("models/cube.obj");
//
//    createVertexBuffer();
//    createIndexBuffer();
//}
//
//Cube::Cube(std::string texturePath, std::string specularTexturePath, std::string specularAndEffuseTexturePath, Shader* shader, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Utils* utils)
//{
//    _utils = utils;
//    _rotation = rotation;
//    _position = position;
//    _scale = scale;
//    _color = glm::vec3(1.f);
//    _shader = shader;
//
//
//    TextureImage* texture = new TextureImage(_utils);
//    texture->createTexture(texturePath);
//    texture->createTextureImageView();
//    texture->createTextureSampler();
//
//    TextureImage* specularTexture = new TextureImage(_utils);
//    specularTexture->createTexture(specularTexturePath);
//    specularTexture->createTextureImageView();
//    specularTexture->createTextureSampler();
//
//    TextureImage* effuseTexture = new TextureImage(_utils);
//    effuseTexture->createTexture(specularAndEffuseTexturePath);
//    effuseTexture->createTextureImageView();
//    effuseTexture->createTextureSampler();
//
//    _textureImages.push_back(texture);
//    _textureImages.push_back(specularTexture);
//    _textureImages.push_back(effuseTexture);
//
//    loadModel("models/cube.obj");
//
//    createVertexBuffer();
//    createIndexBuffer();
//}
//
//const glm::vec3 Cube::getPosition() const
//{
//    return _position;
//}
//
//glm::vec3 Cube::getRotation()
//{
//    return _rotation;
//}
//
//glm::vec3 Cube::getScale()
//{
//    return _scale;
//}
//
//void Cube::setPosition(glm::vec3 position)
//{
//    _position = position;
//}
//
//void Cube::setRotation(glm::vec3 rotation)
//{
//    _rotation = rotation;
//}
//
//void Cube::setScale(glm::vec3 scale)
//{
//    _scale = scale;
//}
//
//glm::mat4 Cube::getModelMatrix()
//{
//    glm::mat4 ModelMatrix(1.0f);
//    ModelMatrix = glm::translate(ModelMatrix, _position);
//    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
//    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
//    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
//    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(_scale));
//
//    return ModelMatrix;
//}
//
//void Cube::loadModel(std::string objPath)
//{
//    //loadOBJ(objPath.c_str(), _vertices, _indices, _verticesPos, _color);
//}
//
//std::vector<VkDeviceMemory> Cube::getUniformBuffersMemory()
//{
//    return _uniformBuffersMemory;
//}
//
////std::vector<VkDeviceMemory> Cube::getPointLightBuffersMemory()
////{
////    return _pointLightBuffersMemory;
////}
//
//void Cube::createUniformBuffer(size_t swapChainImageSize)
//{
//    VkDeviceSize ubobufferSize = sizeof(UniformBufferObject);
//
//    _uniformBuffers.resize(swapChainImageSize);
//    _uniformBuffersMemory.resize(swapChainImageSize);
//
//    for (size_t i = 0; i < swapChainImageSize; i++) {
//        _utils->createBuffer(ubobufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, _uniformBuffers[i], _uniformBuffersMemory[i]);
//    }
//}
//
//void Cube::bindPipeline(VkCommandBuffer commandBuffer)
//{
//    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _shader->getGraphicsPipeline());
//}
//
//void Cube::bindCommandBuffer(VkCommandBuffer commandBuffer, size_t index, std::vector<PointLight *>pointLights)
//{
//    VkBuffer vertexBuffers[] = { _vertexBuffer };
//    VkDeviceSize offsets[] = { 0 };
//
//    vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
//    vkCmdBindIndexBuffer(commandBuffer, _indexBuffer, 0, VK_INDEX_TYPE_UINT32);
//    vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _shader->getPipelineLayout(), 0, 1, &_descriptorSets[index], 0, nullptr);
//    vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(_indices.size()), 1, 0, 0, 0);
//}
//
//void Cube::createDescriptorSets(size_t imageIndex)
//{
//    if (_textureImages.size() == 0) {
//        createDescriptorSetsNoTexture(imageIndex);
//    }
//    //if (_textureImages.size() == 1) {
//    //    createDescriptorSets1Texture(swapChainSize, descriptorPool);
//    //}*/
//    if (_textureImages.size() == 2) {
//        createDescriptorSets2Texture(imageIndex);
//    }
//  /*  if (_textureImages.size() == 3) {
//        createDescriptorSets3Texture(swapChainSize, descriptorPool);
//    }*/
//}
//
//void Cube::createVertexBuffer()
//{
//    VkDeviceSize bufferSize = sizeof(_vertices[0]) * _vertices.size();
//
//    VkBuffer stagingBuffer;
//    VkDeviceMemory stagingBufferMemory;
//    _utils->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);
//
//    void* data;
//    vkMapMemory(_utils->getDevice(), stagingBufferMemory, 0, bufferSize, 0, &data);
//    memcpy(data, _vertices.data(), (size_t)bufferSize);
//    vkUnmapMemory(_utils->getDevice(), stagingBufferMemory);
//
//    _utils->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, _vertexBuffer, _vertexBufferMemory);
//
//    copyBuffer(stagingBuffer, _vertexBuffer, bufferSize);
//
//    vkDestroyBuffer(_utils->getDevice(), stagingBuffer, nullptr);
//    vkFreeMemory(_utils->getDevice(), stagingBufferMemory, nullptr);
//}
//
//void Cube::createIndexBuffer()
//{
//    VkDeviceSize bufferSize = sizeof(_indices[0]) * _indices.size();
//
//    VkBuffer stagingBuffer;
//    VkDeviceMemory stagingBufferMemory;
//    _utils->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);
//
//    void* data;
//    vkMapMemory(_utils->getDevice(), stagingBufferMemory, 0, bufferSize, 0, &data);
//    memcpy(data, _indices.data(), (size_t)bufferSize);
//    vkUnmapMemory(_utils->getDevice(), stagingBufferMemory);
//
//    _utils->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, _indexBuffer, _indexBufferMemory);
//
//    copyBuffer(stagingBuffer, _indexBuffer, bufferSize);
//
//    vkDestroyBuffer(_utils->getDevice(), stagingBuffer, nullptr);
//    vkFreeMemory(_utils->getDevice(), stagingBufferMemory, nullptr);
//}
//
//void Cube::move(float speed, const int direction, float dt)
//{
//    switch (direction) {
//    case UP:
//        _position = this->moveUp(_position, speed, dt, _linkedEntity);
//        break;
//    case DOWN:
//        _position = this->moveDown(_position, speed, dt, _linkedEntity);
//        break;
//    case FORWARD:
//        _position = this->moveForward(_position, speed, dt, _linkedEntity);
//        break;
//    case BACKWARD:
//        _position = this->moveBackward(_position, speed, dt, _linkedEntity);
//        break;
//    case LEFT:
//        _position = this->moveLeft(_position, speed, dt, _linkedEntity);
//        break;
//    case RIGHT:
//        _position = this->moveRight(_position, speed, dt, _linkedEntity);
//        break;
//    }
//}
//
//void Cube::rotate(const glm::vec3 rotation, float dt)
//{
//    _rotation += rotation * dt;
//}
//
//void Cube::link(Entity* entity)
//{
//    _linkedEntity = entity;
//    //entity->link(const_cast<Cube>(this));
//}
//
//void Cube::destroyTextureImage()
//{
//    if (_textureImages.size() > 0) {
//        for (uint32_t textureIdx = 0; textureIdx < _textureImages.size(); textureIdx++) {
//            _textureImages[textureIdx]->destroyTextureImage();
//        }
//    }
//}
//
//void Cube::destroyVertexBuffer()
//{
//    vkDestroyBuffer(_utils->getDevice(), _vertexBuffer, nullptr);
//    vkFreeMemory(_utils->getDevice(), _vertexBufferMemory, nullptr);
//}
//
//void Cube::destroyIndexBuffer()
//{
//    vkDestroyBuffer(_utils->getDevice(), _indexBuffer, nullptr);
//    vkFreeMemory(_utils->getDevice(), _indexBufferMemory, nullptr);
//}
//
//void Cube::destroyUniformBuffers(size_t swapChainImageSize)
//{
//    for (size_t i = 0; i < swapChainImageSize; i++) {
//        vkDestroyBuffer(_utils->getDevice(), _uniformBuffers[i], nullptr);
//        vkFreeMemory(_utils->getDevice(), _uniformBuffersMemory[i], nullptr);
//    }
//}
//
////void Cube::set(const Vertex* vertices, const unsigned nrOfVertices, const uint32_t* indices, const unsigned nrOfIndices)
////{
////    for (size_t i = 0; i < nrOfVertices; i++)
////    {
////       _vertices.push_back(vertices[i]);
////    }
////
////    for (size_t i = 0; i < nrOfIndices; i++)
////    {
////        _indices.push_back(indices[i]);
////    }
////}
//
////Utils
//
//void Cube::createDescriptorSetsNoTexture(size_t i)
//{
//        VkDescriptorBufferInfo bufferInfo{};
//        bufferInfo.buffer = _uniformBuffers[i];
//        bufferInfo.offset = 0;
//        bufferInfo.range = sizeof(UniformBufferObject);
//
//        std::vector<VkWriteDescriptorSet> descriptorWrites;
//
//        VkWriteDescriptorSet descriptorWriteBuffer{};
//        descriptorWriteBuffer.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
//        descriptorWriteBuffer.dstSet = _descriptorSets[i];
//        descriptorWriteBuffer.dstBinding = 0;
//        descriptorWriteBuffer.dstArrayElement = 0;
//        descriptorWriteBuffer.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
//        descriptorWriteBuffer.descriptorCount = 1;
//        descriptorWriteBuffer.pBufferInfo = &bufferInfo;
//        descriptorWrites.push_back(descriptorWriteBuffer);
//
//        vkUpdateDescriptorSets(_utils->getDevice(), static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
//}
//
//void Cube::createDescriptorSets1Texture(size_t swapChainSize, VkDescriptorPool descriptorPool)
//{
//    std::vector<VkDescriptorSetLayout> layouts(swapChainSize, _shader->getDescriptorSetLayout());
//    VkDescriptorSetAllocateInfo allocInfo{};
//    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
//    allocInfo.descriptorPool = descriptorPool;
//    allocInfo.descriptorSetCount = static_cast<uint32_t>(swapChainSize);
//    allocInfo.pSetLayouts = layouts.data();
//
//    _descriptorSets.resize(swapChainSize);
//
//    if (vkAllocateDescriptorSets(_utils->getDevice(), &allocInfo, _descriptorSets.data()) != VK_SUCCESS) {
//        throw std::runtime_error("echec de l'allocation d'un set de descripteurs!");
//    }
//
//    for (size_t i = 0; i < swapChainSize; i++) {
//        VkDescriptorBufferInfo bufferInfo{};
//        bufferInfo.buffer = _uniformBuffers[i];
//        bufferInfo.offset = 0;
//        bufferInfo.range = sizeof(UniformBufferObject);
//
//        std::vector<VkWriteDescriptorSet> descriptorWrites;
//
//        VkWriteDescriptorSet descriptorWriteBuffer{};
//        descriptorWriteBuffer.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
//        descriptorWriteBuffer.dstSet = _descriptorSets[i];
//        descriptorWriteBuffer.dstBinding = 0;
//        descriptorWriteBuffer.dstArrayElement = 0;
//        descriptorWriteBuffer.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
//        descriptorWriteBuffer.descriptorCount = 1;
//        descriptorWriteBuffer.pBufferInfo = &bufferInfo;
//        descriptorWrites.push_back(descriptorWriteBuffer);
//
//        if (_textureImages.size() > 0) {
//            VkDescriptorImageInfo imageInfo{};
//            imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
//            imageInfo.imageView = _textureImages[0]->getTextureImageView();
//            imageInfo.sampler = _textureImages[0]->getTextureSampler();
//
//            VkWriteDescriptorSet descriptorWriteImage{};
//            descriptorWriteImage.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
//            descriptorWriteImage.dstSet = _descriptorSets[i];
//            descriptorWriteImage.dstBinding = 1;
//            descriptorWriteImage.dstArrayElement = 0;
//            descriptorWriteImage.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
//            descriptorWriteImage.descriptorCount = 1;
//            descriptorWriteImage.pImageInfo = &imageInfo;
//
//            descriptorWrites.push_back(descriptorWriteImage);
//        }
//        vkUpdateDescriptorSets(_utils->getDevice(), static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
//    }
//}
//
//void Cube::createDescriptorSets2Texture(size_t i)
//{
//    //for (size_t i = 0; i < swapChainSize; i++) {
//        VkDescriptorBufferInfo bufferInfo{};
//        bufferInfo.buffer = _uniformBuffers[i];
//        bufferInfo.offset = 0;
//        bufferInfo.range = sizeof(UniformBufferObject);
//
//        std::vector<VkWriteDescriptorSet> descriptorWrites;
//
//        VkWriteDescriptorSet descriptorWriteBuffer{};
//        descriptorWriteBuffer.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
//        descriptorWriteBuffer.dstSet = _descriptorSets[i];
//        descriptorWriteBuffer.dstBinding = 0;
//        descriptorWriteBuffer.dstArrayElement = 0;
//        descriptorWriteBuffer.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
//        descriptorWriteBuffer.descriptorCount = 1;
//        descriptorWriteBuffer.pBufferInfo = &bufferInfo;
//        descriptorWrites.push_back(descriptorWriteBuffer);
//
//        if (_textureImages.size() > 0) {
//            VkDescriptorImageInfo imageInfo{};
//            imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
//            imageInfo.imageView = _textureImages[0]->getTextureImageView();
//            imageInfo.sampler = _textureImages[0]->getTextureSampler();
//
//            VkDescriptorImageInfo imageInfoSpec{};
//            imageInfoSpec.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
//            imageInfoSpec.imageView = _textureImages[1]->getTextureImageView();
//            imageInfoSpec.sampler = _textureImages[1]->getTextureSampler();
//
//            VkWriteDescriptorSet descriptorWriteImage{};
//            descriptorWriteImage.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
//            descriptorWriteImage.dstSet = _descriptorSets[i];
//            descriptorWriteImage.dstBinding = 1;
//            descriptorWriteImage.dstArrayElement = 0;
//            descriptorWriteImage.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
//            descriptorWriteImage.descriptorCount = 1;
//            descriptorWriteImage.pImageInfo = &imageInfo;
//
//            VkWriteDescriptorSet descriptorWriteImageSpec{};
//            descriptorWriteImageSpec.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
//            descriptorWriteImageSpec.dstSet = _descriptorSets[i];
//            descriptorWriteImageSpec.dstBinding = 2;
//            descriptorWriteImageSpec.dstArrayElement = 0;
//            descriptorWriteImageSpec.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
//            descriptorWriteImageSpec.descriptorCount = 1;
//            descriptorWriteImageSpec.pImageInfo = &imageInfoSpec;
//            descriptorWrites.push_back(descriptorWriteImage);
//            descriptorWrites.push_back(descriptorWriteImageSpec);
//
//        }
//
//        vkUpdateDescriptorSets(_utils->getDevice(), static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
//
//        //VkWriteDescriptorSet descriptorWritePointLightBuffer{};
//        //descriptorWritePointLightBuffer.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
//        //descriptorWritePointLightBuffer.dstSet = _descriptorSets[i];
//        //descriptorWritePointLightBuffer.dstBinding = 3;
//        //descriptorWritePointLightBuffer.dstArrayElement = 0;
//        //descriptorWritePointLightBuffer.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
//        //descriptorWritePointLightBuffer.descriptorCount = 1;
//        //descriptorWritePointLightBuffer.pBufferInfo = &pointLightbufferInfo;
//        ////descriptorWrites.push_back(descriptorWritePointLightBuffer);
//
//        //vkUpdateDescriptorSets(_utils->getDevice(), 1, &descriptorWritePointLightBuffer, 0, nullptr);
//    ////}
//}
//
//void Cube::createDescriptorSets3Texture(size_t swapChainSize, VkDescriptorPool descriptorPool)
//{
//    std::vector<VkDescriptorSetLayout> layouts(swapChainSize, _shader->getDescriptorSetLayout());
//    VkDescriptorSetAllocateInfo allocInfo{};
//    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
//    allocInfo.descriptorPool = descriptorPool;
//    allocInfo.descriptorSetCount = static_cast<uint32_t>(swapChainSize);
//    allocInfo.pSetLayouts = layouts.data();
//
//    _descriptorSets.resize(swapChainSize);
//
//    if (vkAllocateDescriptorSets(_utils->getDevice(), &allocInfo, _descriptorSets.data()) != VK_SUCCESS) {
//        throw std::runtime_error("echec de l'allocation d'un set de descripteurs!");
//    }
//
//    for (size_t i = 0; i < swapChainSize; i++) {
//        VkDescriptorBufferInfo bufferInfo{};
//        bufferInfo.buffer = _uniformBuffers[i];
//        bufferInfo.offset = 0;
//        bufferInfo.range = sizeof(UniformBufferObject);
//
//        std::vector<VkWriteDescriptorSet> descriptorWrites;
//
//        VkWriteDescriptorSet descriptorWriteBuffer{};
//        descriptorWriteBuffer.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
//        descriptorWriteBuffer.dstSet = _descriptorSets[i];
//        descriptorWriteBuffer.dstBinding = 0;
//        descriptorWriteBuffer.dstArrayElement = 0;
//        descriptorWriteBuffer.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
//        descriptorWriteBuffer.descriptorCount = 1;
//        descriptorWriteBuffer.pBufferInfo = &bufferInfo;
//        descriptorWrites.push_back(descriptorWriteBuffer);
//
//        if (_textureImages.size() > 0) {
//            VkDescriptorImageInfo imageInfo{};
//            imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
//            imageInfo.imageView = _textureImages[0]->getTextureImageView();
//            imageInfo.sampler = _textureImages[0]->getTextureSampler();
//
//            VkDescriptorImageInfo imageInfoSpec{};
//            imageInfoSpec.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
//            imageInfoSpec.imageView = _textureImages[1]->getTextureImageView();
//            imageInfoSpec.sampler = _textureImages[1]->getTextureSampler();
//
//            VkDescriptorImageInfo imageInfoEffuse{};
//            imageInfoEffuse.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
//            imageInfoEffuse.imageView = _textureImages[2]->getTextureImageView();
//            imageInfoEffuse.sampler = _textureImages[2]->getTextureSampler();
//
//            VkWriteDescriptorSet descriptorWriteImage{};
//            descriptorWriteImage.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
//            descriptorWriteImage.dstSet = _descriptorSets[i];
//            descriptorWriteImage.dstBinding = 1;
//            descriptorWriteImage.dstArrayElement = 0;
//            descriptorWriteImage.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
//            descriptorWriteImage.descriptorCount = 1;
//            descriptorWriteImage.pImageInfo = &imageInfo;
//
//            VkWriteDescriptorSet descriptorWriteImageSpec{};
//            descriptorWriteImageSpec.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
//            descriptorWriteImageSpec.dstSet = _descriptorSets[i];
//            descriptorWriteImageSpec.dstBinding = 2;
//            descriptorWriteImageSpec.dstArrayElement = 0;
//            descriptorWriteImageSpec.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
//            descriptorWriteImageSpec.descriptorCount = 1;
//            descriptorWriteImageSpec.pImageInfo = &imageInfoSpec;
//
//            VkWriteDescriptorSet descriptorWriteImageEffuse{};
//            descriptorWriteImageEffuse.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
//            descriptorWriteImageEffuse.dstSet = _descriptorSets[i];
//            descriptorWriteImageEffuse.dstBinding = 3;
//            descriptorWriteImageEffuse.dstArrayElement = 0;
//            descriptorWriteImageEffuse.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
//            descriptorWriteImageEffuse.descriptorCount = 1;
//            descriptorWriteImageEffuse.pImageInfo = &imageInfoEffuse;
//
//            descriptorWrites.push_back(descriptorWriteImage);
//            descriptorWrites.push_back(descriptorWriteImageSpec);
//            descriptorWrites.push_back(descriptorWriteImageEffuse);
//        }
//        vkUpdateDescriptorSets(_utils->getDevice(), static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
//    }
//}
//
//void Cube::copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
//    VkCommandBuffer commandBuffer = _utils->beginSingleTimeCommands();
//
//    VkBufferCopy copyRegion{};
//    copyRegion.size = size;
//    vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);
//
//    _utils->endSingleTimeCommands(commandBuffer);
//}
//
//int Cube::hasSpecularTexture()
//{
//    return _hasSpecularTexture;
//}
//
////std::vector<VkDescriptorSet> Cube::getDescriptorSets()
////{
////    return _descriptorSets;
////}
//
////void Cube::setDescriptorSets(std::vector<VkDescriptorSet> descriptorSets)
////{
////    _descriptorSets = descriptorSets;
////}
//
//void Cube::allocateDescriptorSets(size_t swapChainSize, VkDescriptorPool descriptorPool)
//{
//    std::vector<VkDescriptorSetLayout> layouts(swapChainSize, _shader->getDescriptorSetLayout());
//    VkDescriptorSetAllocateInfo allocInfo{};
//    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
//    allocInfo.descriptorPool = descriptorPool;
//    allocInfo.descriptorSetCount = static_cast<uint32_t>(swapChainSize);
//    allocInfo.pSetLayouts = layouts.data();
//
//    _descriptorSets.resize(swapChainSize);
//
//    if (vkAllocateDescriptorSets(_utils->getDevice(), &allocInfo, _descriptorSets.data()) != VK_SUCCESS) {
//        throw std::runtime_error("echec de l'allocation d'un set de descripteurs!");
//    }
//}
//
//void Cube::setColor(glm::vec3 color)
//{
//    _color = color;
//}
//
//glm::vec3 Cube::getColor()
//{
//    return _color;
//}
