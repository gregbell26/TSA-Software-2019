#ifndef VULKAN_H
#define VULKAN_H

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>
#include <vector>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
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

    void supportedExtensions();

    void setUpDebugBus();

    void initVulkan();

    void pickPhysicalDevice();

    bool isPhysicalDeviceSuitable(VkPhysicalDevice physicalDevice);

    void mainLoop();

    void cleanUp();

private:
    GLFWwindow* glfwWindow;

    VkInstance vkInstance;
    VkPhysicalDevice vkPhysicalDevice = VK_NULL_HANDLE;

    VkDebugUtilsMessengerEXT debugBus;
};


#endif //MAIN_H
