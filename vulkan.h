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

    void createGraphicsPipeline();

    void mainLoop();

    void cleanUp();

private:
    GLFWwindow* glfwWindow;

    VkInstance vkInstance;
    VkPhysicalDevice vkPhysicalDevice = VK_NULL_HANDLE;//Physical Device
    VkDevice vkDevice;//Logical Device - issues commands to the physical device

    VkQueue vkQueue;
    VkQueue vkPresentQueue;

    VkDebugUtilsMessengerEXT debugBus;

    VkSurfaceKHR vkSurface;

    VkSwapchainKHR vkSwapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;

    std::vector<VkImageView> swapChainImageViews;


};


#endif //MAIN_H
