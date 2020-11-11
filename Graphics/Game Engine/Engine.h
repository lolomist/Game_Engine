#pragma once
//#define STB_IMAGE_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#define GLFW_INCLUDE_VULKAN

#include "Shaders_class/TextureShader.h"
#include "Shaders_class/ColorShader.h"
#include "TextureImage.h"
//#include "CustomObject.h"
#include "Camera.h"
#include "UBO.h"
#include "Window.h"
#include "Model.h"
//#include "Cube.h"
#include "CreateObject.h"
#include "Lights/DirectionalLight.h"
#include "Lights/PointLight.h"
#include "Lights/SpotLight.h"

#include <optional>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <optional>
#include <set>
#include <algorithm>

#include <glm/glm.hpp>
#include <array>
#include <chrono>
#include "Shaders_class/LightSourceShader.h"
#include "Shaders_class/TextureMapsShader.h"

const uint32_t WIDTH = 1280;
const uint32_t HEIGHT = 720;

//const std::string MODEL_PATH = "models/book.obj";
//const std::string TEXTURE_PATH = "textures/book.png";

const std::string MODEL_PATH = "models/viking_room.obj";
const std::string TEXTURE_PATH = "textures/viking_room.png";

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

const int MAX_FRAMES_IN_FLIGHT = 2;

#ifdef NDEBUG
constexpr bool enableValidationLayers = false;
#else
constexpr bool enableValidationLayers = true;
#endif

class Engine {
public:
   /* Engine(int windowWidth, int windowHeight, std::string title) {
        initWindow(windowWidth, windowHeight, title);
        initVulkan();
    }*/
    Engine(Window *window) {
        this->window = window;
        initVulkan();
    }

    Engine(Window* window, glm::vec3 clearColor) {
        this->window = window;
        this->clearColor = clearColor;
        initVulkan();
    }
    ~Engine() {
        vkDeviceWaitIdle(device);
        cleanup();
    }

    // Custom Object with Texture
    Model *createCustomModel(std::string objPath, std::string texturePath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
        Utils* utils = new Utils(device, physicalDevice, commandPool, graphicsQueue);

        Model *obj = new CreateObject(objPath, texturePath, textureSpecularShader, position, rotation, scale, utils);
        sceneObjects.push_back(obj);
        return obj;
    }

    // Texture With Camera
   /* Model* createCustomModel(std::string objPath, std::string texturePath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Camera *camera) {
        this->camera = camera;
        Utils* utils = new Utils(device, physicalDevice, commandPool, graphicsQueue);

        Model* obj = new CustomObject(objPath, texturePath, textureShader, position, rotation, scale, camera, utils);
        sceneObjects.push_back(obj);
        return obj;
    }*/

    // Custom Object With No texture (just Color)
    Model* createCustomModel(std::string objPath, glm::vec3 color, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
        Utils* utils = new Utils(device, physicalDevice, commandPool, graphicsQueue);

        Model* obj = new CreateObject(objPath, color, colorShader, position, rotation, scale, utils);
        sceneObjects.push_back(obj);
        return obj;
    }

    // No texture With Camera
  /*  Model* createCustomModel(std::string objPath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Camera* camera) {
        this->camera = camera;
        Utils* utils = new Utils(device, physicalDevice, commandPool, graphicsQueue);

        Model* obj = new CustomObject(objPath, colorShader, position, rotation, scale, camera, utils);
        sceneObjects.push_back(obj);
        return obj;
    }*/

    //Simple cube without texture (just color)
    Model* createCube(glm::vec3 color, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
        Utils* utils = new Utils(device, physicalDevice, commandPool, graphicsQueue);

        Model* obj = new CreateObject("models/cube.obj", color, colorShader, position, rotation, scale, utils);
        sceneObjects.push_back(obj);
        return obj;
    }

    ////Simple cube with color + specular + effuse
    //Model* createCube(glm::vec3 color, std::string specularTexturePath, std::string effuseTexturePath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
    //    Utils* utils = new Utils(device, physicalDevice, commandPool, graphicsQueue);

    //    Model* obj = new CreateObject("models/cube.obj", color, specularTexturePath, effuseTexturePath, colorShader, position, rotation, scale, utils);
    //    sceneObjects.push_back(obj);
    //    return obj;
    //}

    //Simple cube with texture
    Model* createCube(std::string texturePath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
        Utils* utils = new Utils(device, physicalDevice, commandPool, graphicsQueue);

        Model* obj = new CreateObject("models/cube.obj", texturePath, textureSpecularShader, position, rotation, scale, utils);
        sceneObjects.push_back(obj);
        return obj;
    }

    //Simple cube with texture + specular Texture
    Model* createCube(std::string texturePath, std::string specularTexturePath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
        Utils* utils = new Utils(device, physicalDevice, commandPool, graphicsQueue);
        Model* obj = new CreateObject("models/cube.obj", texturePath, specularTexturePath, textureSpecularShader, position, rotation, scale, utils);
        sceneObjects.push_back(obj);
        return obj;
    }

    //Simple cube with texture + Emission Texture
    Model* createCube(std::string texturePath, std::string emissionTexturePath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, bool isEmissionTexture) {
        Utils* utils = new Utils(device, physicalDevice, commandPool, graphicsQueue);
        Model* obj = new CreateObject("models/cube.obj", texturePath, emissionTexturePath, textureSpecularShader, position, rotation, scale, utils, true);
        sceneObjects.push_back(obj);
        return obj;
    }

    //Simple cube with texture + Specular Texture + Emission Texture
    Model* createCube(std::string texturePath, std::string specularTexturePath, std::string emissionTexturePath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
        Utils* utils = new Utils(device, physicalDevice, commandPool, graphicsQueue);
        Model* obj = new CreateObject("models/cube.obj", texturePath, specularTexturePath, emissionTexturePath, textureSpecularShader, position, rotation, scale, utils);
        sceneObjects.push_back(obj);
        return obj;
    }

    //Simple cube with texture + EffuseTexture
   /* Model* createCube(std::string texturePath, std::string effuseTexturePath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, bool isEffuseTexure) {
        Utils* utils = new Utils(device, physicalDevice, commandPool, graphicsQueue);
        if (isEffuseTexure == false) {
            Model* obj = new Cube(texturePath, effuseTexturePath, textureSpecularShader, position, rotation, scale, utils);
            sceneObjects.push_back(obj);
            return obj;
        }
        if (isEffuseTexure == true) {
            Model* obj = new Cube(texturePath, effuseTexturePath, textureEffuseShader, position, rotation, scale, utils);
            sceneObjects.push_back(obj);
            return obj;
        }
    }*/

    //Simple cube with texture + specularTexture + EffuseTexture
   /* Model* createCube(std::string texturePath, std::string specularTexturePath, std::string specularAndEffuseTexturePath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
        Utils* utils = new Utils(device, physicalDevice, commandPool, graphicsQueue);

        Model* obj = new Cube(texturePath, specularTexturePath, specularAndEffuseTexturePath, textureSpecularAndEffuseShader, position, rotation, scale, utils);
        sceneObjects.push_back(obj);
        return obj;
    }*/

    Camera* createCamera(glm::vec3 position, glm::vec3 direction) {
        camera = new Camera(position, direction);
        return camera;
    }

    /******       *******
            LIGHT
    *******       *******/

    void setDirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {
        directionalLight->setDirection(direction);
        directionalLight->setAmbient(ambient);
        directionalLight->setDiffuse(diffuse);
        directionalLight->setSpecular(specular);

        //DirectionalLight* light = new DirectionalLight(direction, ambient, diffuse, specular);

        //directionalLights.push_back(light);
    }

    DirectionalLight* getDirectionalLight() {
        return directionalLight;
    }

    //Point Light With Precise value (attention complexe oulala)
    PointLight* createPointLight(glm::vec3 position, float constant, float linear, float quadratic, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, bool showLight) {
        if (showLight == false) {
            Utils* utils = new Utils(device, physicalDevice, commandPool, graphicsQueue);
            PointLight *light = new PointLight(position, constant, linear, quadratic, ambient, diffuse, specular, textureSpecularShader, utils);
            pointLights.push_back(light);
            return light;
        }
        else {
            Utils* utils = new Utils(device, physicalDevice, commandPool, graphicsQueue);
            Model* cube = new CreateObject("models/cube.obj",glm::vec3(1.f), lightSourceShader, position, glm::vec3(0.f), glm::vec3(0.5f), utils);

            PointLight* light = new PointLight(position, constant, linear, quadratic, ambient, diffuse, specular, cube, textureSpecularShader, utils);
            pointLights.push_back(light);
            sceneObjects.push_back(cube);
            return light;
        }
    }

    //Point Light With custom Color
    PointLight* createPointLight(glm::vec3 position, glm::vec3 color, float constant, float linear, float quadratic, bool showLight) {
        if (showLight == false) {
            Utils* utils = new Utils(device, physicalDevice, commandPool, graphicsQueue);
            PointLight* light = new PointLight(position, constant, linear, quadratic, glm::vec3(color.x * 0.1, color.y * 0.1, color.z * 0.1), color, color, textureSpecularShader, utils);
            pointLights.push_back(light);
            return light;
        }
        else {
            Utils* utils = new Utils(device, physicalDevice, commandPool, graphicsQueue);
            Model* cube = new CreateObject("models/cube.obj", color, lightSourceShader, position, glm::vec3(0.f), glm::vec3(0.5f), utils);

            PointLight* light = new PointLight(position, constant, linear, quadratic, glm::vec3(color.x * 0.1, color.y * 0.1, color.z * 0.1), color, color, cube, textureSpecularShader, utils);
            pointLights.push_back(light);
            sceneObjects.push_back(cube);
            return light;
        }
    }

    //Spot Light With Precise value (attention complexe oulala)
    SpotLight* createSpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
        float constant, float linear, float quadratic, float cutOff, float outerCutOff, bool showLight) {
        if (showLight == false) {
            SpotLight* light = new SpotLight(position, direction, ambient, diffuse, specular, constant, linear, quadratic, cutOff, outerCutOff);
            spotLights.push_back(light);
            return light;
        }
        else {
            Utils* utils = new Utils(device, physicalDevice, commandPool, graphicsQueue);
            Model* cube = new CreateObject("models/cube.obj", glm::vec3(1.f, 0.f, 0.f), lightSourceShader, position, glm::vec3(0.f), glm::vec3(0.5f), utils);

            SpotLight* light = new SpotLight(position, direction, ambient, diffuse, specular, constant, linear, quadratic, cutOff, outerCutOff, cube);
            spotLights.push_back(light);
            sceneObjects.push_back(cube);
            return light;
        }
    }

    //SpotLight with custom color and other stuff
    SpotLight* createSpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 color,
        float constant, float linear, float quadratic, float cutOff, float outerCutOff, bool showLight) {
        if (showLight == false) {
            SpotLight* light = new SpotLight(position, direction, glm::vec3(0.f), color, color, constant, linear, quadratic, cutOff, outerCutOff);
            spotLights.push_back(light);
            return light;
        }
        else {
            Utils* utils = new Utils(device, physicalDevice, commandPool, graphicsQueue);
            Model* cube = new CreateObject("models/cube.obj", color, lightSourceShader, position, glm::vec3(0.f), glm::vec3(0.5f), utils);

            SpotLight* light = new SpotLight(position, direction, glm::vec3(0.f), color, color, constant, linear, quadratic, cutOff, outerCutOff, cube);
            spotLights.push_back(light);
            sceneObjects.push_back(cube);
            return light;
        }
    }

   /* Light* createLight(glm::vec3 position, glm::vec3 color) {
        light = new Light(position, color);
        return light;
    }

    Light* createLight(glm::vec3 position, glm::vec3 color, bool showLight) {
        if (showLight == false) {
            light = new Light(position, color);
        }
        else {
            Utils* utils = new Utils(device, physicalDevice, commandPool, graphicsQueue);
            Model* cube = new Cube(color, lightSourceShader, position, glm::vec3(0.f), glm::vec3(0.5f), utils);

            light = new Light(position, color, cube);
            sceneObjects.push_back(cube);
        }
        return light;
    }*/

    
    /*void draw(CustomObject *obj) {
        vkWaitForFences(device, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);
        uint32_t imageIndex = getNextImage();
        updateUniformBuffer(obj, imageIndex);
        renderImage(imageIndex);
    }*/

    void drawObjects() {
        vkWaitForFences(device, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);
        uint32_t imageIndex = getNextImage();

        for (size_t objIndex = 0; objIndex < sceneObjects.size(); objIndex++) {
            updateUniformBuffer(sceneObjects[objIndex], imageIndex);
        }

        renderImage(imageIndex);
    }

    bool isWindowOpen() {
        if (isObjectsInit == false) {
            initObjects();
            isObjectsInit = true;
        }
        updateTime();

        return window->isWindowOpen();
    }

    float getTime() {
        return dt;
    }

   /* TextureShader* getTextureShader() {
        return textureShader;
    }*/

   /* ColorShader* getColorShader() {
        return colorShader;
    }*/

   /* GLFWwindow* getWindow() {
        return glfwWindow;
    }*/

    void run() {
        //initWindow();
        //initVulkan();
        //mainLoop();
        cleanup();
    }

private:
    glm::vec3 clearColor = glm::vec3(0.35f, 0.35f, 0.35f);

    bool isObjectsInit = false;

    //GLFWwindow* glfwWindow;
    Window* window;
    VkInstance instance;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;
    VkQueue graphicsQueue;
    VkSurfaceKHR surface;
    VkQueue presentQueue;
    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VkImageView> swapChainImageViews;
    VkRenderPass renderPass;
    //VkDescriptorSetLayout descriptorSetLayout;
    //VkPipelineLayout pipelineLayout;
    //VkPipeline graphicsPipeline;
    std::vector<VkFramebuffer> swapChainFramebuffers;
    VkCommandPool commandPool;
    std::vector<VkCommandBuffer> drawCommandBuffers;
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    std::vector<VkFence> imagesInFlight;

    std::vector<VkDescriptorSet> _tmpDescriptorSet;

    //std::vector<VkBuffer> uniformBuffers;
    //std::vector<VkDeviceMemory> uniformBuffersMemory;
    VkDescriptorPool descriptorPool;
    //std::vector<VkDescriptorSet> descriptorSets;

    //SceneObject* sceneObject;
    std::vector<Model*> sceneObjects;

    VkImage depthImage;
    VkDeviceMemory depthImageMemory;
    VkImageView depthImageView;

    //Camera 
    //glm::vec3 camPosition = glm::vec3(0.f, 0.f, 4.0f);
    //Camera camera = Camera(glm::vec3(0.f, 0.f, 5.0f), glm::vec3(0.f, 0.f, -90.f), glm::vec3(0.f, 1.f, 0.f));
    //Camera camera = Camera(glm::vec3(0.f, 3.5f, -6.5f), glm::vec3(-25.f, 0.f, 90.f));
    Camera *camera;

    //Light* light = new Light();
    DirectionalLight* directionalLight = new DirectionalLight(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f, 0.5f, 0.5f));
    std::vector<PointLight *> pointLights;
    std::vector<SpotLight *> spotLights;

    //Delta time
    float dt = 0.f;
    float currentTime;
    std::chrono::steady_clock::time_point lastTime = std::chrono::high_resolution_clock::now();
    //float lastTime = 0.f;

    //Mouse Input
    double lastMouseX = 0.0;
    double lastMouseY = 0.0;
    double mouseX = 0.0;
    double mouseY = 0.0;
    double mouseOffsetX = 0.0;
    double mouseOffsetY = 0.0;
    bool firstMouse = true;

    size_t currentFrame = 0;

    glm::vec3 lightPos = glm::vec3(0.f, -5.f, 0.f);

    //TextureShader* textureShader;
    TextureMapsShader* textureSpecularShader;
    //TextureMapsShader* textureEffuseShader;
    //TextureMapsShader* textureSpecularAndEffuseShader;
    ColorShader* colorShader;
    LightSourceShader* lightSourceShader;

    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    //void initWindow(int windowWidth, int windowHeight, std::string title) {
    //    glfwInit();
    //    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    //    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    //    glfwWindow = glfwCreateWindow(windowWidth, windowHeight, title.c_str(), nullptr, nullptr);
    //    glfwSetWindowUserPointer(glfwWindow, this);
    //    glfwSetFramebufferSizeCallback(glfwWindow, framebufferResizeCallback);
    //    //glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //}

    /*static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
        std::cout << "Resize callback !" << std::endl;
        auto app = reinterpret_cast<Engine*>(glfwGetWindowUserPointer(window));
        app->framebufferResized = true;
    }*/

    //void initVulkan() {
    //    createInstance();
    //    createSurface();
    //    pickPhysicalDevice();
    //    createLogicalDevice();
    //    createSwapChain();
    //    createImageViews();
    //    createRenderPass();
    //    createDescriptorSetLayout();
    //    createGraphicsPipeline();
    //    createCommandPool();
    //    createDepthResources();
    //    createFramebuffers();
    //    Utils* utils = new Utils(device, physicalDevice, commandPool, graphicsQueue);
    //    sceneObjects.push_back(new SceneObject("models/viking_room.obj", "textures/viking_room.png", glm::vec3(15.5f, 0.0f, 0.5f), glm::vec3(-90.0f, 0.f, 180.f), glm::vec3(10.f), utils));
    //    //sceneObjects.push_back(new SceneObject("models/viking_room.obj", "textures/viking_room.png", glm::vec3(4.0f, 0.0f, -1.5f), glm::vec3(0.0f), glm::vec3(1.f), false, utils));
    //    sceneObjects.push_back(new SceneObject("models/book.obj", "textures/book.png", glm::vec3(-2.5f, 0.0f, -0.5f), glm::vec3(0.0f), glm::vec3(1.f), utils));
    //    sceneObjects.push_back(new SceneObject("models/box.obj", "textures/box.jpg", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.f), utils));
    //    sceneObjects.push_back(new SceneObject("models/spaceship.obj", "textures/spaceship1.jpg", glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f), glm::vec3(0.5f), &camera, utils));
    //    std::cout << "Total Object " << sceneObjects.size() << std::endl;
    //    createDescriptorPool(sceneObjects.size());


    //    for (size_t objIndex = 0; objIndex < sceneObjects.size(); objIndex++) {
    //      /*  if (sceneObjects[objIndex]->hasCamera()) {
    //            camera = sceneObjects[objIndex]->getCamera();
    //        }*/
    //        sceneObjects[objIndex]->createUniformBuffer(swapChainImages.size());
    //        sceneObjects[objIndex]->createDescriptorSets(swapChainImages.size(), descriptorSetLayout, descriptorPool);
    //    }

    //    createDrawCommandBuffers();
    //    createSyncObjects();
    //}

    void initVulkan() {
        createInstance();
        createSurface();
        pickPhysicalDevice();
        createLogicalDevice();
        createSwapChain();
        createImageViews();
        createRenderPass();

        /*createDescriptorSetLayout();
        createGraphicsPipeline();*/
        //textureShader = new TextureShader(swapChainExtent, device, renderPass);
        textureSpecularShader = new TextureMapsShader(swapChainExtent, device, renderPass, true);
        //textureEffuseShader = new TextureMapsShader(swapChainExtent, device, renderPass, false);
        //textureSpecularAndEffuseShader = new TextureMapsShader(swapChainExtent, device, renderPass, true, true);
        colorShader = new ColorShader(swapChainExtent, device, renderPass);
        lightSourceShader = new LightSourceShader(swapChainExtent, device, renderPass);

        createCommandPool();
        createDepthResources();
        createFramebuffers();
    }

    void initObjects() {
        std::cout << "InitObjects : Total Object " << sceneObjects.size() << std::endl;
        
        if (sceneObjects.size() > 0) {
            createDescriptorPool(sceneObjects.size());

            for (size_t objIndex = 0; objIndex < sceneObjects.size(); objIndex++) {
                sceneObjects[objIndex]->createUniformBuffer(swapChainImages.size());
                sceneObjects[objIndex]->allocateDescriptorSets(swapChainImages.size(), descriptorPool);
                for (size_t i = 0; i < swapChainImages.size(); i++) {
                    sceneObjects[objIndex]->createDescriptorSets(i);
                }
            }

           createDrawCommandBuffers();
           createSyncObjects();
        }
    }

    void recreateSwapChain() {
        std::cout << "Recreate Swap Chain" << std::endl;
        int width = 0, height = 0;
        window->getFrameBufferSize(&width, &height);
        //glfwGetFramebufferSize(glfwWindow, &width, &height);

        // la taille de la fenêtre est à 0 lorsqu'on minimise la fenetre, on mets en pause la fenêtre dans ce cas
        while (width == 0 || height == 0) {
            window->getFrameBufferSize(&width, &height);
            glfwWaitEvents();
        }

        vkDeviceWaitIdle(device);

        cleanupSwapChain();

        createSwapChain();
        createImageViews();
        createRenderPass();
        //textureShader->createGraphicsPipeline(swapChainExtent, device, renderPass);
        textureSpecularShader->createGraphicsPipeline(swapChainExtent, device, renderPass);
        //textureEffuseShader->createGraphicsPipeline(swapChainExtent, device, renderPass);
        //textureSpecularAndEffuseShader->createGraphicsPipeline(swapChainExtent, device, renderPass);
        colorShader->createGraphicsPipeline(swapChainExtent, device, renderPass);
        lightSourceShader->createGraphicsPipeline(swapChainExtent, device, renderPass);
        createDepthResources();
        createFramebuffers();

        createDescriptorPool(sceneObjects.size());

        for (size_t objIndex = 0; objIndex < sceneObjects.size(); objIndex++) {
            sceneObjects[objIndex]->createUniformBuffer(swapChainImages.size());
            sceneObjects[objIndex]->allocateDescriptorSets(swapChainImages.size(), descriptorPool);
            for (size_t i = 0; i < swapChainImages.size(); i++) {
                sceneObjects[objIndex]->createDescriptorSets(i);
            }
        }

        createDrawCommandBuffers();
    }

    void update() {
        updateTime();
        //updateInput();

        //sceneObjects[0]->rotate(glm::vec3(50.0f, 0.f, 0.f), dt);
    }

    void updateTime() {
        auto currentTime = std::chrono::high_resolution_clock::now();
        dt = std::chrono::duration<float, std::chrono::seconds::period>((currentTime - lastTime)).count();
        lastTime = currentTime;

       /* auto currentTime = static_cast<float>(glfwGetTime());
        dt = currentTime - lastTime;
        lastTime = currentTime;*/

        //std::cout << "DELT " << dt << std::endl;
    }

    //    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    //    {
    //        obj->move(0.1f, LEFT);
    //    }
    //    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    //    {
    //        obj->move(0.1f, BACKWARD);
    //    }
    //    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    //    {
    //        obj->move(0.1f, RIGHT);
    //    }
    //    
    //    // update camera after moving the object
    //   /* if (obj->hasCamera()) {
    //        camera = obj->getCamera();
    //    }*/

    //    /* if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    //     {
    //         camPosition.y -= 0.05f;
    //     }
    //     if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    //     {
    //         camPosition.y += 0.05f;
    //     }*/
    //}

    void cleanupSwapChain() {
        vkDestroyImageView(device, depthImageView, nullptr);
        vkDestroyImage(device, depthImage, nullptr);
        vkFreeMemory(device, depthImageMemory, nullptr);

        for (auto framebuffer : swapChainFramebuffers) {
            vkDestroyFramebuffer(device, framebuffer, nullptr);
        }

        vkFreeCommandBuffers(device, commandPool, static_cast<uint32_t>(drawCommandBuffers.size()), drawCommandBuffers.data());

        //textureShader->destroyPipeline();
        textureSpecularShader->destroyPipeline();
        //textureEffuseShader->destroyPipeline();
        //textureSpecularAndEffuseShader->destroyPipeline();
        colorShader->destroyPipeline();
        lightSourceShader->destroyPipeline();
        vkDestroyRenderPass(device, renderPass, nullptr);

        for (auto imageView : swapChainImageViews) {
            vkDestroyImageView(device, imageView, nullptr);
        }

        vkDestroySwapchainKHR(device, swapChain, nullptr);

        for (size_t objIndex = 0; objIndex < sceneObjects.size(); objIndex++) {
            sceneObjects[objIndex]->destroyUniformBuffers(swapChainImages.size());
        }

        vkDestroyDescriptorPool(device, descriptorPool, nullptr);
    }

    void cleanup() {
        cleanupSwapChain();

        for (size_t i = 0; i < sceneObjects.size(); i++) {
            sceneObjects[i]->destroyTextureImage();
            sceneObjects[i]->destroyIndexBuffer();
            sceneObjects[i]->destroyVertexBuffer();
        }

        //textureShader->destroyDescriptorSetLayout();
        textureSpecularShader->destroyDescriptorSetLayout();
        //textureEffuseShader->destroyDescriptorSetLayout();
        //textureSpecularAndEffuseShader->destroyDescriptorSetLayout();
        colorShader->destroyDescriptorSetLayout();
        lightSourceShader->destroyDescriptorSetLayout();

        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            vkDestroySemaphore(device, renderFinishedSemaphores[i], nullptr);
            vkDestroySemaphore(device, imageAvailableSemaphores[i], nullptr);
            vkDestroyFence(device, inFlightFences[i], nullptr);
        }

        vkDestroyCommandPool(device, commandPool, nullptr);

        vkDestroyDevice(device, nullptr);

        vkDestroySurfaceKHR(instance, surface, nullptr);
        vkDestroyInstance(instance, nullptr);

        window->destroyWindow();
        glfwTerminate();
    }

    void drawFrame() {
        vkWaitForFences(device, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);
        uint32_t imageIndex = getNextImage();

        for (size_t objIndex = 0; objIndex < sceneObjects.size(); objIndex++) {
            updateUniformBuffer(sceneObjects[objIndex], imageIndex);
        }

        renderImage(imageIndex);
    }

    uint32_t getNextImage() {
        uint32_t imageIndex;
        VkResult result = vkAcquireNextImageKHR(device, swapChain, UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

        if (result == VK_ERROR_OUT_OF_DATE_KHR) {
            recreateSwapChain();
            return imageIndex;
        }
        else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("échec de la présentation d'une image à la swap chain!");
        }

        return imageIndex;
    }

    void updateUniformBuffer(Model* obj, uint32_t currentImage) {
        UniformBufferObject ubo{};

        ubo.model = obj->getModelMatrix();

        /*if (obj->getIsTPS() == true) {
               ubo.view = glm::lookAt(obj->getPosition(), obj->getPosition(), glm::vec3(0.0f, 0.0f, 1.0f));
          }*/
          //else {
        ubo.view = camera->getViewMatrix();
        //}

        float fov = 70.f;
        float nearPlane = 0.1f;
        float farPlane = 1000.f;
        ubo.proj = glm::perspective(glm::radians(fov), swapChainExtent.width / (float)swapChainExtent.height, nearPlane, farPlane);

        // Conversion des données pour compatibilité vulkan
        ubo.proj[1][1] *= -1;


        //glm::vec3 lightColor = light->getColor();

        //glm::vec3 diffuseColor = lightColor * glm::vec3(0.3f);
        //glm::vec3 ambientColor = diffuseColor * glm::vec3(0.1f);

        //ubo.light.pos = light->getPosition();

        ubo.dirLight.direction = directionalLight->getDirection();
        ubo.dirLight.ambient = directionalLight->getAmbient();
        ubo.dirLight.diffuse = directionalLight->getDiffuse();
        ubo.dirLight.specular = directionalLight->getSpecular();

        ubo.pointLightsCount = static_cast<int>(pointLights.size());

        for (size_t i = 0; i < pointLights.size(); i++) {
            ubo.pointLights[i].position = pointLights[i]->getPosition();
            ubo.pointLights[i].ambient = pointLights[i]->getAmbient();
            ubo.pointLights[i].diffuse = pointLights[i]->getDiffuse();
            ubo.pointLights[i].specular = pointLights[i]->getSpecular();
            ubo.pointLights[i].constant = pointLights[i]->getConstant();
            ubo.pointLights[i].linear = pointLights[i]->getLinear();
            ubo.pointLights[i].quadratic = pointLights[i]->getQuadratic();
        }

        ubo.spotLightCount = static_cast<int>(spotLights.size());

        for (size_t i = 0; i < spotLights.size(); i++) {
            ubo.spotLight[i].pos = spotLights[i]->getPosition();
            ubo.spotLight[i].direction = spotLights[i]->getDirection();
            ubo.spotLight[i].ambient = spotLights[i]->getAmbient();
            ubo.spotLight[i].diffuse = spotLights[i]->getDiffuse();
            ubo.spotLight[i].specular = spotLights[i]->getSpecular();
            ubo.spotLight[i].quadratic = spotLights[i]->getQuadratic();
            ubo.spotLight[i].linear = spotLights[i]->getLinear();
            ubo.spotLight[i].constant = spotLights[i]->getConstant();
            ubo.spotLight[i].cutOff = spotLights[i]->getCutOff();
            ubo.spotLight[i].outerCutOff = spotLights[i]->getOuterCutOff();
        }
        ubo.time = glfwGetTime();

        ubo.objectColor = obj->getColor();

        ubo.cameraPos = camera->getPosition();

        ubo.hasSpecularTexture = obj->hasSpecularTexture();

        ubo.material.ambient = glm::vec3(1.0f, 0.5f, 0.31f);
        ubo.material.diffuse = glm::vec3(1.0f, 0.5f, 0.31f);
        ubo.material.specular = glm::vec3(0.5f, 0.5f, 0.5f);
        ubo.material.shininess = 32.0f;

        //std::cout << "ligt pos Y : " << ubo.lightPos.y << std::endl;
        //std::cout << "DELT " << dt << std::endl;*/

        void* data;
        vkMapMemory(device, obj->getUniformBuffersMemory()[currentImage], 0, sizeof(ubo), 0, &data);
        memcpy(data, &ubo, sizeof(ubo));
        vkUnmapMemory(device, obj->getUniformBuffersMemory()[currentImage]);
    }

    void renderImage(uint32_t imageIndex) {
        // Vérifier si une frame précédente est en train d'utiliser cette image (il y a une fence à attendre)
        if (imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
            vkWaitForFences(device, 1, &imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
        }
        // Marque l'image comme étant à nouveau utilisée par cette frame
        imagesInFlight[imageIndex] = inFlightFences[currentFrame];

        VkSemaphore waitSemaphores[] = { imageAvailableSemaphores[currentFrame] };
        VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
        VkSemaphore signalSemaphores[] = { renderFinishedSemaphores[currentFrame] };

        VkSubmitInfo submitInfo{};

        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;

        VkCommandBuffer commandBuffers[] = { drawCommandBuffers[imageIndex] };
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = commandBuffers;
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        vkResetFences(device, 1, &inFlightFences[currentFrame]);

        if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS) {
            throw std::runtime_error("échec de l'envoi d'un command buffer!");
        }

        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;

        VkSwapchainKHR swapChains[] = { swapChain };
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;
        presentInfo.pImageIndices = &imageIndex;

        VkResult result = vkQueuePresentKHR(presentQueue, &presentInfo);

        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || window->getFrameBufferResized()) {
            window->setFrameBufferResized(false);
            recreateSwapChain();
        }
        else if (result != VK_SUCCESS) {
            throw std::runtime_error("échec de la présentation d'une image!");
        }
        currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
    }

    void createInstance() {
        if (enableValidationLayers && !checkValidationLayerSupport()) {
            throw std::runtime_error("validation layers requested, but not available!");
        }

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        if (!checkExtensions(glfwExtensions, glfwExtensionCount)) {
            throw std::runtime_error("Extensions are not included in the supported extensions list");
        }
        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;

        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        }
        else {
            createInfo.enabledLayerCount = 0;
        }

        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        };
    }

    bool checkExtensions(const char** extensions, uint32_t extensionCount) {

        // get available extensions:
        uint32_t count = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr);
        std::vector<VkExtensionProperties> vkExtensions(count);

        vkEnumerateInstanceExtensionProperties(nullptr, &count, vkExtensions.data());

        std::cout << "available extensions:\n";
        for (const auto& extension : vkExtensions) {
            std::cout << '\t' << extension.extensionName << '\n';
        }
        std::cout << "parameter extensions:\n";
        for (uint32_t i = 0; i < extensionCount; i++) {
            std::cout << '\t' << extensions[i] << '\n';
        }

        // search if the extensions are inside the supported extensions list
        uint32_t extcount = 0;
        while (extcount < extensionCount) {
            bool extensionFound = false;
            for (const auto& vkExtension : vkExtensions) {
                if (strcmp(extensions[extcount], vkExtension.extensionName) == 0) {
                    extensionFound = true;
                }
            }
            if (extensionFound) {
                extcount++;
            }
            else {
                return false;
            }
        }
        return true;

    }

    bool checkValidationLayerSupport() {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for (const char* layerName : validationLayers) {
            bool layerFound = false;

            for (const auto& layerProperties : availableLayers) {
                if (strcmp(layerName, layerProperties.layerName) == 0) {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound) {
                return false;
            }
        }

        return true;
    }

    void createSurface() {
        surface = window->createWindowSurface(instance);
    }

    void pickPhysicalDevice() {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

        if (deviceCount == 0) {
            throw std::runtime_error("failed to find GPUs with Vulkan support!");
        }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

        for (const auto& device : devices) {
            if (isDeviceSuitable(device)) {
                physicalDevice = device;
                break;
            }
        }

        if (physicalDevice == VK_NULL_HANDLE) {
            throw std::runtime_error("failed to find a suitable GPU!");
        }
    }

    void createLogicalDevice() {
        QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };

        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies) {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkPhysicalDeviceFeatures deviceFeatures{};
        deviceFeatures.samplerAnisotropy = VK_TRUE;

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();

        createInfo.pEnabledFeatures = &deviceFeatures;

        createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
        createInfo.ppEnabledExtensionNames = deviceExtensions.data();

        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        }
        else {
            createInfo.enabledLayerCount = 0;
        }

        if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
            throw std::runtime_error("échec lors de la création d'un logical device!");
        }

        vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
        vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);
    }

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) {
        QueueFamilyIndices indices;

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        for (const auto& queueFamily : queueFamilies) {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                indices.graphicsFamily = i;
                std::cout << "graphics familiy " << i << std::endl;
            }

            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

            if (presentSupport) {
                indices.presentFamily = i;
                std::cout << "graphics familiy support KHR " << i << std::endl;
            }

            if (indices.isComplete()) {
                break;
            }

            i++;
        }

        return indices;
    }

    void createSwapChain() {
        SwapChainSupportDetails swapChainSupport = querySwapChainSupport(physicalDevice);

        VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
        VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
        VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

        uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;

        if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
            imageCount = swapChainSupport.capabilities.maxImageCount;
        }

        VkSwapchainCreateInfoKHR createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        createInfo.surface = surface;

        createInfo.minImageCount = imageCount;
        createInfo.imageFormat = surfaceFormat.format;
        createInfo.imageColorSpace = surfaceFormat.colorSpace;
        createInfo.imageExtent = extent;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
        uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };

        if (indices.graphicsFamily != indices.presentFamily) {
            std::cout << "Concurrent sharing mode" << std::endl;
            createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices;
        }
        else {
            createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            createInfo.queueFamilyIndexCount = 0; // Optionnel
            createInfo.pQueueFamilyIndices = nullptr; // Optionnel
        }

        createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        createInfo.presentMode = presentMode;
        createInfo.clipped = VK_TRUE;

        createInfo.oldSwapchain = VK_NULL_HANDLE;

        if (vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapChain) != VK_SUCCESS) {
            throw std::runtime_error("échec de la création de la swap chain!");
        }

        vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr);
        swapChainImages.resize(imageCount);
        vkGetSwapchainImagesKHR(device, swapChain, &imageCount, swapChainImages.data());

        swapChainImageFormat = surfaceFormat.format;
        swapChainExtent = extent;
    }

    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device) {
        SwapChainSupportDetails details;

        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

        if (formatCount != 0) {
            details.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
        }

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

        if (presentModeCount != 0) {
            details.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
        }

        return details;
    }

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) {
        for (const auto& availableFormat : availableFormats) {
            if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
                std::cout << "Best swap surface format" << std::endl;
                return availableFormat;
            }
        }

        std::cout << "swap surface format fallback" << std::endl;
        return availableFormats[0];
    }

    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) {
        for (const auto& availablePresentMode : availablePresentModes) {
            if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
                std::cout << "Swap Present mode triple buffering" << std::endl;
                return availablePresentMode;
            }
        }
        std::cout << "Swap Present mode fallback" << std::endl;
        return VK_PRESENT_MODE_FIFO_KHR;
    }

    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) {
        if (capabilities.currentExtent.width != UINT32_MAX) {
            return capabilities.currentExtent;
        }
        else {
            int width, height;
            window->getFrameBufferSize(&width, &height);
            VkExtent2D actualExtent = {
                static_cast<uint32_t>(width),
                static_cast<uint32_t>(height)
            };

            actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
            actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

            return actualExtent;
        }
    }

    void createImageViews() {
        swapChainImageViews.resize(swapChainImages.size());

        for (size_t i = 0; i < swapChainImages.size(); i++) {
            swapChainImageViews[i] = createImageView(swapChainImages[i], swapChainImageFormat, VK_IMAGE_ASPECT_COLOR_BIT, 1);
        }
    }

    void createRenderPass() {
        VkAttachmentDescription depthAttachment{};
        depthAttachment.format = findDepthFormat();
        depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        VkAttachmentReference depthAttachmentRef{};
        depthAttachmentRef.attachment = 1;
        depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        VkAttachmentDescription colorAttachment{};
        colorAttachment.format = swapChainImageFormat;
        colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        VkAttachmentReference colorAttachmentRef{};
        colorAttachmentRef.attachment = 0;
        colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkSubpassDescription subpass{};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments = &colorAttachmentRef;
        subpass.pDepthStencilAttachment = &depthAttachmentRef;

        VkSubpassDependency dependency{};
        dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
        dependency.dstSubpass = 0;
        dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.srcAccessMask = 0;
        dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

        std::array<VkAttachmentDescription, 2> attachments = { colorAttachment, depthAttachment };
        VkRenderPassCreateInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
        renderPassInfo.pAttachments = attachments.data();
        renderPassInfo.subpassCount = 1;
        renderPassInfo.pSubpasses = &subpass;
        renderPassInfo.dependencyCount = 1;
        renderPassInfo.pDependencies = &dependency;

        if (vkCreateRenderPass(device, &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS) {
            throw std::runtime_error("échec de la création de la render pass!");
        }
    }

    void createFramebuffers() {
        swapChainFramebuffers.resize(swapChainImageViews.size());

        for (size_t i = 0; i < swapChainImageViews.size(); i++) {
            std::array<VkImageView, 2> attachments = {
                 swapChainImageViews[i],
                 depthImageView
            };

            VkFramebufferCreateInfo framebufferInfo{};
            framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            framebufferInfo.renderPass = renderPass;
            framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
            framebufferInfo.pAttachments = attachments.data();
            framebufferInfo.width = swapChainExtent.width;
            framebufferInfo.height = swapChainExtent.height;
            framebufferInfo.layers = 1;

            if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("échec de la création d'un framebuffer!");
            }
        }
    }

    void createCommandPool() {
        QueueFamilyIndices queueFamilyIndices = findQueueFamilies(physicalDevice);

        VkCommandPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
        poolInfo.flags = 0; // Optionel

        if (vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
            throw std::runtime_error("échec de la création d'une command pool!");
        }
    }

    void createDepthResources() {
        VkFormat depthFormat = findDepthFormat();
        //hasStencilComponent(depthFormat);

        createImage(swapChainExtent.width, swapChainExtent.height, 1, depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, depthImage, depthImageMemory);
        depthImageView = createImageView(depthImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT, 1);
    }

    VkFormat findDepthFormat() {
        return findSupportedFormat(
            { VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT },
            VK_IMAGE_TILING_OPTIMAL,
            VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
        );
    }

    VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features) {
        for (VkFormat format : candidates) {
            VkFormatProperties props;
            vkGetPhysicalDeviceFormatProperties(physicalDevice, format, &props);

            if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
                std::cout << "support tiling Linear" << std::endl;
                return format;
            }
            else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
                std::cout << "support tiling Optimal" << std::endl;
                return format;
            }
        }
        throw std::runtime_error("aucun des formats demandés n'est supporté!");
    }

    bool hasStencilComponent(VkFormat format) {
        return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
    }

    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels) {
        VkImageViewCreateInfo viewInfo{};
        viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        viewInfo.image = image;
        viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        viewInfo.format = format;
        viewInfo.subresourceRange.aspectMask = aspectFlags;
        viewInfo.subresourceRange.baseMipLevel = 0;
        viewInfo.subresourceRange.levelCount = mipLevels;
        viewInfo.subresourceRange.baseArrayLayer = 0;
        viewInfo.subresourceRange.layerCount = 1;

        VkImageView imageView;
        if (vkCreateImageView(device, &viewInfo, nullptr, &imageView) != VK_SUCCESS) {
            throw std::runtime_error("échec de la creation de la vue sur une image!");
        }
        return imageView;
    }

    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
        VkCommandBuffer commandBuffer = beginSingleTimeCommands();

        VkBufferCopy copyRegion{};
        copyRegion.size = size;
        vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

        endSingleTimeCommands(commandBuffer);
    }

    void createDescriptorPool(size_t descriptorCount) {
        std::array<VkDescriptorPoolSize, 4> poolSizes{};
        poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        poolSizes[0].descriptorCount = static_cast<uint32_t>(swapChainImages.size() * descriptorCount);
        poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        poolSizes[1].descriptorCount = static_cast<uint32_t>(swapChainImages.size() * descriptorCount);
        poolSizes[2].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        poolSizes[2].descriptorCount = static_cast<uint32_t>(swapChainImages.size() * descriptorCount);
        poolSizes[3].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        poolSizes[3].descriptorCount = static_cast<uint32_t>(swapChainImages.size() * descriptorCount);

        VkDescriptorPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
        poolInfo.pPoolSizes = poolSizes.data();
        poolInfo.maxSets = static_cast<uint32_t>(swapChainImages.size() * descriptorCount);

        if (vkCreateDescriptorPool(device, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
            throw std::runtime_error("echec de la creation de la pool de descripteurs!");
        }
    }

    void createDrawCommandBuffers() {
        drawCommandBuffers.resize(swapChainFramebuffers.size());

        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = commandPool;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = (uint32_t)drawCommandBuffers.size();

        if (vkAllocateCommandBuffers(device, &allocInfo, drawCommandBuffers.data()) != VK_SUCCESS) {
            throw std::runtime_error("échec de l'allocation de command buffers!");
        }

        for (size_t i = 0; i < drawCommandBuffers.size(); i++) {
            VkCommandBufferBeginInfo beginInfo{};
            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            beginInfo.flags = 0; // Optionnel
            beginInfo.pInheritanceInfo = nullptr; // Optionel

            if (vkBeginCommandBuffer(drawCommandBuffers[i], &beginInfo) != VK_SUCCESS) {
                throw std::runtime_error("erreur au début de l'enregistrement d'un command buffer!");
            }

            VkRenderPassBeginInfo renderPassInfo{};
            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassInfo.renderPass = renderPass;
            renderPassInfo.framebuffer = swapChainFramebuffers[i];
            renderPassInfo.renderArea.offset = { 0, 0 };
            renderPassInfo.renderArea.extent = swapChainExtent;

            std::array<VkClearValue, 2> clearValues{};
            clearValues[0].color = { clearColor.x, clearColor.y, clearColor.z, 1.0f };
            clearValues[1].depthStencil = { 1.0f, 0 };

            renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
            renderPassInfo.pClearValues = clearValues.data();

            vkCmdBeginRenderPass(drawCommandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
           /* vkCmdBindPipeline(drawCommandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);*/

            for (size_t objIndex = 0; objIndex < sceneObjects.size(); objIndex++) {
                sceneObjects[objIndex]->bindPipeline(drawCommandBuffers[i]);
                sceneObjects[objIndex]->bindCommandBuffer(drawCommandBuffers[i], i, pointLights);
            }

            vkCmdEndRenderPass(drawCommandBuffers[i]);
            if (vkEndCommandBuffer(drawCommandBuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("échec de l'enregistrement d'un command buffer!");
            }
        }
    }

    void createSyncObjects() {
        imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
        imagesInFlight.resize(swapChainImages.size(), VK_NULL_HANDLE);

        VkSemaphoreCreateInfo semaphoreInfo{};
        semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        VkFenceCreateInfo fenceInfo{};
        fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
                vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS ||
                vkCreateFence(device, &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS) {

                throw std::runtime_error("échec de la création des objets de synchronisation pour une frame!");
            }
        }
    }

    bool isDeviceSuitable(VkPhysicalDevice device) {
        QueueFamilyIndices indices = findQueueFamilies(device);

        bool extensionsSupported = checkDeviceExtensionSupport(device);

        bool swapChainAdequate = false;
        if (extensionsSupported) {
            SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device);
            swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
        }

        VkPhysicalDeviceFeatures supportedFeatures;
        vkGetPhysicalDeviceFeatures(device, &supportedFeatures);

        return indices.isComplete() && extensionsSupported && swapChainAdequate && supportedFeatures.samplerAnisotropy;
    }

    bool checkDeviceExtensionSupport(VkPhysicalDevice device) {
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

        for (const auto& extension : availableExtensions) {
            requiredExtensions.erase(extension.extensionName);
        }

        return requiredExtensions.empty();
    }

    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
        VkPhysicalDeviceMemoryProperties memProperties;
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

        for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
            if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
                return i;
            }
        }

        throw std::runtime_error("aucun type de memoire ne satisfait le buffer!");
    }

    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory) {
        VkBufferCreateInfo bufferInfo{};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = size;
        bufferInfo.usage = usage;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        if (vkCreateBuffer(device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
            throw std::runtime_error("echec de la creation d'un buffer!");
        }

        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements(device, buffer, &memRequirements);

        VkMemoryAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);

        // l'appel de cette fonction est limité 
        // Meilleure solution : allouer une grande zone mémoire et utiliser un gestionnaire ( + d'infos chapitre buffer intermédiaire (Vertex buffers))
        if (vkAllocateMemory(device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
            throw std::runtime_error("echec de l'allocation de memoire!");
        }

        vkBindBufferMemory(device, buffer, bufferMemory, 0);
    }

    void createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory) {
        VkImageCreateInfo imageInfo{};
        imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        imageInfo.imageType = VK_IMAGE_TYPE_2D;
        imageInfo.extent.width = width;
        imageInfo.extent.height = height;
        imageInfo.extent.depth = 1;
        imageInfo.mipLevels = mipLevels;
        imageInfo.arrayLayers = 1;
        imageInfo.format = format;
        imageInfo.tiling = tiling;
        imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        imageInfo.usage = usage;
        imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
        imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        if (vkCreateImage(device, &imageInfo, nullptr, &image) != VK_SUCCESS) {
            throw std::runtime_error("echec de la creation d'une image!");
        }

        VkMemoryRequirements memRequirements;
        vkGetImageMemoryRequirements(device, image, &memRequirements);

        VkMemoryAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);

        if (vkAllocateMemory(device, &allocInfo, nullptr, &imageMemory) != VK_SUCCESS) {
            throw std::runtime_error("echec de l'allocation de la memoire d'une image!");
        }

        vkBindImageMemory(device, image, imageMemory, 0);
    }

    VkCommandBuffer beginSingleTimeCommands() {
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = commandPool;
        allocInfo.commandBufferCount = 1;

        VkCommandBuffer commandBuffer;
        vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer);

        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

        vkBeginCommandBuffer(commandBuffer, &beginInfo);

        return commandBuffer;
    }

    void endSingleTimeCommands(VkCommandBuffer commandBuffer) {
        vkEndCommandBuffer(commandBuffer);

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer;

        vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
        vkQueueWaitIdle(graphicsQueue);

        vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
    }

    VkDevice getDevice() {
        return device;
    }
};