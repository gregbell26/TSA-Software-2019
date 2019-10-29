#ifndef VULKAN_H
#define VULKAN_H

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <functional>
#include <cstdlib>
#include <vector>
#include <set>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int MAX_FRAMES_IN_FLIGHT = 2;

const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
};

const std::vector<const char *> deviceExtensions= {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME

};

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif


class Vulkan {
public:
    void run();

private:
    void initWindow();

    void createInstance();

    bool checkValidationLayerSupport();

    std::vector<const char*> getRequiredExtensions();

    void getSupportedExtensions();

    bool checkDeviceExtensionSupport(VkPhysicalDevice);

    void setUpDebugBus();

    void createSurface();

    void initVulkan();

    void pickPhysicalDevice();

    bool isPhysicalDeviceSuitable(VkPhysicalDevice);

    void createLogicalDevice();

    void createSwapChain();

    void createImageViews();

    void createRenderPass();

    void createGraphicsPipeline();

    void createFrameBuffers();

    void createCommandPool();

    void createVertexBuffer();

    uint32_t findMemoryTypes(uint32_t, VkMemoryPropertyFlags);

    void createCommandBuffers();

    void createSyncObjects();

    void cleanUpSwapChain();

    void recreateSwapChain();

    void mainLoop();

    void drawFrame();

    void cleanUp();

private:
    size_t currentFrame = 0;

    GLFWwindow* glfwWindow;

    VkInstance vkInstance;
    VkPhysicalDevice vkPhysicalDevice = VK_NULL_HANDLE;//Physical Device
    VkDevice vkDevice;//Logical Device - issues commands to the physical device

    VkQueue vkGraphicsQueue;
    VkQueue vkPresentQueue;

    VkDebugUtilsMessengerEXT debugBus;

    VkSurfaceKHR vkSurface;

    VkSwapchainKHR vkSwapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;

    VkRenderPass vkRenderPass;
    VkPipelineLayout vkPipelineLayout;
    VkPipeline vkGraphicsPipeline;

    std::vector<VkFramebuffer> swapChainFrameBuffer;
    std::vector<VkImageView> swapChainImageViews;

    VkCommandPool vkCommandPool;
    std::vector<VkCommandBuffer> commandBuffers;

    std::vector<VkSemaphore> imageAvailableSemaphore;
    std::vector<VkSemaphore> renderFinishedSemaphore;
    std::vector<VkFence> inFlightFence;

    VkBuffer vkVertexBuffer;
    VkDeviceMemory vkVertexBufferMemory;
public:
    bool frameBufferResized = false;



};


#endif //MAIN_H
