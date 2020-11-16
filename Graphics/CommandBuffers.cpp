#include "CommandBuffers.h"

#include <cstdlib>

#include <iostream>
#include <sstream>

CommandBuffers::CommandBuffers(InitVulkan initVulkan, VkDevice device, VkQueue queue)
{
    _graphicsFamilyIndex = initVulkan._graphicsFamilyIndex;
    _device = device;
    _queue = queue;

    createFence();
    createSemaphore();

    createCommandPool();

    createCommandBuffers();
    submitInfo();

    DestroyCommandBuffers();
}

CommandBuffers::~CommandBuffers()
{
    DestroyCommandBuffers();
}

//Create fence to synchronize the GPU queue submits and the CPU, waits for the GPU to be ready on the CPU side
void CommandBuffers::createFence()
{
    VkFenceCreateInfo fenceCreateInfo{};
    fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    vkCreateFence(_device, &fenceCreateInfo, nullptr, &_fence);
}

//Create semaphore to tell the GPU when other process in this GPU has been completed
void CommandBuffers::createSemaphore()
{
    VkSemaphoreCreateInfo semaphoreCreateInfo{};
    semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    vkCreateSemaphore(_device, &semaphoreCreateInfo, nullptr, &_semaphore);
}

//To manages the memory used by buffers
void CommandBuffers::createCommandPool()
{
    VkCommandPoolCreateInfo poolCreateInfo{};
    poolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolCreateInfo.queueFamilyIndex = _graphicsFamilyIndex;
    poolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    if (vkCreateCommandPool(_device, &poolCreateInfo, nullptr, &_commandPool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create command pool!");
    }
}

void CommandBuffers::createCommandBuffers()
{
    VkCommandBufferAllocateInfo commandBufferAllocateInfo{};
    commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    commandBufferAllocateInfo.commandPool = _commandPool;
    commandBufferAllocateInfo.commandBufferCount = 2;
    commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    vkAllocateCommandBuffers(_device, &commandBufferAllocateInfo, _commandBuffer);
    {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        vkBeginCommandBuffer(_commandBuffer[0], &beginInfo);

        vkCmdPipelineBarrier(_commandBuffer[0], VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, 0, 0, nullptr, 0, nullptr, 0, nullptr);

        VkViewport viewport{};
        viewport.maxDepth = 1.0f;
        viewport.minDepth = 0.0f;
        viewport.width = 512;
        viewport.height = 512;
        viewport.x = 0;
        viewport.y = 0;
        vkCmdSetViewport(_commandBuffer[0], 0, 1, &viewport);

        vkEndCommandBuffer(_commandBuffer[0]);
    }
    {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        vkBeginCommandBuffer(_commandBuffer[1], &beginInfo);

        VkViewport viewport{};
        viewport.maxDepth = 1.0f;
        viewport.minDepth = 0.0f;
        viewport.width = 512;
        viewport.height = 512;
        viewport.x = 0;
        viewport.y = 0;
        vkCmdSetViewport(_commandBuffer[1], 0, 1, &viewport);

        vkEndCommandBuffer(_commandBuffer[1]);
    }
}

void CommandBuffers::submitInfo()
{
    {
        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &_commandBuffer[0];
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = &_semaphore;

        vkQueueSubmit(_queue, 1, &submitInfo, VK_NULL_HANDLE);
    }
    {
        VkPipelineStageFlags flags[]{ VK_PIPELINE_STAGE_ALL_COMMANDS_BIT };
        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &_commandBuffer[1];
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = &_semaphore;
        submitInfo.pWaitDstStageMask = flags;

        vkQueueSubmit(_queue, 1, &submitInfo, VK_NULL_HANDLE);
    }
}

void CommandBuffers::DestroyCommandBuffers()
{
    auto ret = vkWaitForFences(_device, 1, &_fence, VK_TRUE, UINT64_MAX);

    //vkQueueWaitIdle(_queue);

    vkDestroyCommandPool(_device, _commandPool, nullptr);
    vkDestroyFence(_device, _fence, nullptr);
    vkDestroySemaphore(_device, _semaphore, nullptr);
}