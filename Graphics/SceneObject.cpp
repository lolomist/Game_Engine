#include "SceneObject.h"
#include "UBO.h"

SceneObject::SceneObject(std::string objFilePath, std::string texFilePath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Utils* utils)
{
    _utils = utils;
    _rotation = rotation;
    _position = position;
    _scale = scale;

    _hasCamera = false;
    _textureImage = new TextureImage(_utils);

    _textureImage->createTexture(texFilePath);
    _textureImage->createTextureImageView();
    _textureImage->createTextureSampler();

    //loadModelLIB(objFilePath);
    loadModel(objFilePath);

    createVertexBuffer();
    createIndexBuffer();
}

SceneObject::SceneObject(std::string objPath, std::string texturePath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Camera *camera, Utils* utils)
{
    _utils = utils;
    _rotation = rotation;
    _position = position;
    _scale = scale;
    _hasCamera = true;

    _initialPosition = camera->getPosition();
    _camera = camera;
    _camera->setPosition(glm::vec3(position.x + _initialPosition.x, position.y + _initialPosition.y, position.z + _initialPosition.z));
    //_camera = new Camera(glm::vec3(position.x + camera->getPosition().x, position.y + camera->getPosition().y, position.z + camera->getPosition().z), camera->getDirection(), glm::vec3(0.f, 1.f, 0.f));
    _textureImage = new TextureImage(_utils);

    _textureImage->createTexture(texturePath);
    _textureImage->createTextureImageView();
    _textureImage->createTextureSampler();

    //loadModelLIB(objFilePath);
    loadModel(objPath);

    createVertexBuffer();
    createIndexBuffer();
}

glm::vec3 SceneObject::getRotation()
{
    return _rotation;
}

glm::vec3 SceneObject::getPosition()
{
    return _position;
}

glm::vec3 SceneObject::getScale()
{
    return _scale;
}

void SceneObject::setPosition(glm::vec3 position)
{
    _position = position;
}

void SceneObject::setRotation(glm::vec3 rotation)
{
    _rotation = rotation;
}

VkImage SceneObject::getTextureImage()
{
    return _textureImage->getTextureImage();
}

VkDeviceMemory SceneObject::getTextureImageMemory()
{
    return _textureImage->getTextureImageMemory();
}

VkImageView SceneObject::getTextureImageView()
{
    return _textureImage->getTextureImageView();
}

VkSampler SceneObject::getTextureSampler()
{
    return _textureImage->getTextureSampler();
}


void SceneObject::destroyTextureImage()
{
    _textureImage->destroyTextureImage();
}


std::vector<VkBuffer> SceneObject::getUniformBuffers()
{
    return _uniformBuffers;
}

std::vector<VkDeviceMemory> SceneObject::getUniformBuffersMemory()
{
    return _uniformBuffersMemory;
}

std::vector<Vertex> SceneObject::getVertices()
{
    return _vertices;
}

std::vector<uint32_t> SceneObject::getIndices()
{
    return _indices;
}

VkBuffer SceneObject::getVertexBuffer()
{
    return _vertexBuffer;
}

VkDeviceMemory SceneObject::getVertexBufferMemory()
{
    return _vertexBufferMemory;
}

VkBuffer SceneObject::getIndexBuffer()
{
    return _indexBuffer;
}

VkDeviceMemory SceneObject::getIndexBufferMemory()
{
    return _indexBufferMemory;
}


std::vector<VkDescriptorSet> SceneObject::getDescriptorSets()
{
    return _descriptorSets;
}

bool SceneObject::hasCamera()
{
    return _hasCamera;
}

Camera *SceneObject::getCamera()
{
    return _camera;
}

glm::mat4 SceneObject::getModelMatrix()
{
    glm::mat4 ModelMatrix(1.0f);
    ModelMatrix = glm::translate(ModelMatrix, _position);
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(_scale));

    return ModelMatrix;
}


void SceneObject::createUniformBuffer(size_t swapChainImageSize)
{
    VkDeviceSize bufferSize = sizeof(UniformBufferObject);

    _uniformBuffers.resize(swapChainImageSize);
    _uniformBuffersMemory.resize(swapChainImageSize);

    for (size_t i = 0; i < swapChainImageSize; i++) {
        _utils->createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, _uniformBuffers[i], _uniformBuffersMemory[i]);
    }
}


void SceneObject::createDescriptorSets(size_t swapChainSize, VkDescriptorSetLayout descriptorSetLayout, VkDescriptorPool descriptorPool)
{
    std::vector<VkDescriptorSetLayout> layouts(swapChainSize, descriptorSetLayout);
    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = descriptorPool;
    allocInfo.descriptorSetCount = static_cast<uint32_t>(swapChainSize);
    allocInfo.pSetLayouts = layouts.data();

    _descriptorSets.resize(swapChainSize);

    if (vkAllocateDescriptorSets(_utils->getDevice(), &allocInfo, _descriptorSets.data()) != VK_SUCCESS) {
        throw std::runtime_error("echec de l'allocation d'un set de descripteurs!");
    }


    for (size_t i = 0; i < swapChainSize; i++) {
        VkDescriptorBufferInfo bufferInfo{};
        bufferInfo.buffer = _uniformBuffers[i];
        bufferInfo.offset = 0;
        bufferInfo.range = sizeof(UniformBufferObject);

        VkDescriptorImageInfo imageInfo{};

        imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        imageInfo.imageView = getTextureImageView();
        imageInfo.sampler = getTextureSampler();

        std::array<VkWriteDescriptorSet, 2> descriptorWrites{};

        descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites[0].dstSet = _descriptorSets[i];
        descriptorWrites[0].dstBinding = 0;
        descriptorWrites[0].dstArrayElement = 0;
        descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrites[0].descriptorCount = 1;
        descriptorWrites[0].pBufferInfo = &bufferInfo;

        descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites[1].dstSet = _descriptorSets[i];
        descriptorWrites[1].dstBinding = 1;
        descriptorWrites[1].dstArrayElement = 0;
        descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        descriptorWrites[1].descriptorCount = 1;
        descriptorWrites[1].pImageInfo = &imageInfo;

        vkUpdateDescriptorSets(_utils->getDevice(), static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
    }
}

void SceneObject::bindCommandBuffer(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, size_t index)
{
    VkBuffer vertexBuffers[] = { _vertexBuffer };
    VkDeviceSize offsets[] = { 0 };

    vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
    vkCmdBindIndexBuffer(commandBuffer, _indexBuffer, 0, VK_INDEX_TYPE_UINT32);
    vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &_descriptorSets[index], 0, nullptr);
    vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(_indices.size()), 1, 0, 0, 0);
}

void SceneObject::move(float speed, const int direction)
{
    switch (direction) {
    case FORWARD:
        _position.z += speed;
        break;
    case BACKWARD:
        _position.z -= speed;
        break;
    case LEFT:
        _position.x += speed;
        break;
    case RIGHT:
        _position.x -= speed;
        break;
    }
    if (_hasCamera) {
        _camera->setPosition(glm::vec3(_position.x + _initialPosition.x, _position.y + _initialPosition.y, _position.z + _initialPosition.z));
    }
}

void SceneObject::rotate(const glm::vec3 rotation, float dt)
{
    _rotation += rotation * dt;
}

void SceneObject::destroyVertexBuffer()
{
    vkDestroyBuffer(_utils->getDevice(), _vertexBuffer, nullptr);
    vkFreeMemory(_utils->getDevice(), _vertexBufferMemory, nullptr);
}

void SceneObject::destroyIndexBuffer()
{
    vkDestroyBuffer(_utils->getDevice(), _indexBuffer, nullptr);
    vkFreeMemory(_utils->getDevice(), _indexBufferMemory, nullptr);
}

void SceneObject::destroyUniformBuffers(size_t swapChainImageSize)
{
    for (size_t i = 0; i < swapChainImageSize; i++) {
        vkDestroyBuffer(_utils->getDevice(), _uniformBuffers[i], nullptr);
        vkFreeMemory(_utils->getDevice(), _uniformBuffersMemory[i], nullptr);
    }
}

//// Private //
//
//void SceneObject::loadModelLIB(std::string objPath) {
//    tinyobj::attrib_t attrib;
//    std::vector<tinyobj::shape_t> shapes;
//    std::vector<tinyobj::material_t> materials;
//    std::string warn, err;
//
//    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, objPath.c_str())) {
//        throw std::runtime_error(warn + err);
//    }
//
//    std::unordered_map<Vertex, uint32_t> uniqueVertices{};
//
//    //combiner toutes les faces en un seul modèle
//    for (const auto& shape : shapes) {
//        for (const auto& index : shape.mesh.indices) {
//
//            Vertex vertex{};
//
//            /*std::cout << "LIB 0: " << attrib.vertices[3 * index.vertex_index + 0] << std::endl;
//            std::cout << "LIB 1: " << attrib.vertices[3 * index.vertex_index + 1] << std::endl;
//            std::cout << "LIB 2: " << attrib.vertices[3 * index.vertex_index + 2] << std::endl;*/
//
//            vertex.pos = {
//                attrib.vertices[3 * index.vertex_index + 0],
//                attrib.vertices[3 * index.vertex_index + 1],
//                attrib.vertices[3 * index.vertex_index + 2]
//            };
//
//            vertex.texCoord = {
//                 attrib.texcoords[2 * index.texcoord_index + 0],
//                 1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
//            };
//
//            vertex.color = { 1.0f, 1.0f, 1.0f };
//
//            if (uniqueVertices.count(vertex) == 0) {
//                uniqueVertices[vertex] = static_cast<uint32_t>(_vertices.size());
//                _vertices.push_back(vertex);
//            }
//
//            //std::cout << "unique vertices index = " << uniqueVertices[vertex] << std::endl;
//            _indices.push_back(uniqueVertices[vertex]);
//
//        }
//    }
//    std::cout << "LIB : Nbr of vertices : " << _vertices.size() << std::endl;
//    std::cout << "LIB : Nbr of indices : " << _indices.size() << std::endl;
//
//}

void SceneObject::loadModel(std::string objPath)
{
    loadOBJ(objPath.c_str(), _vertices, _indices);
}

void SceneObject::createVertexBuffer() {
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

void SceneObject::createIndexBuffer() {
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



// UTILS //

void SceneObject::copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
    VkCommandBuffer commandBuffer = _utils->beginSingleTimeCommands();

    VkBufferCopy copyRegion{};
    copyRegion.size = size;
    vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

    _utils->endSingleTimeCommands(commandBuffer);
}


