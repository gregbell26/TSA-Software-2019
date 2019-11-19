#ifndef VULKAN_MAIN_HPP
#define VULKAN_MAIN_HPP

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>



class Vulkan {
public:
    Vulkan() = default;


    //Create instance - If that fails vulkan is not supported
    //Enum physical devices - If that's 0 vulkan is not supported
    //Extension check - Make sure all required extensions are supported
    bool isSupported();

    bool setRequiredInformation(const char **EXTENSIONS, size_t EXT_SIZE, const char* name);

    void setOptionInformation(const char **VALIDATION_LAYERS, size_t VALID_LAYER_SIZE, const char** EXTENSIONS, size_t EXT_SIZE);

    bool initBackend();

    void runBackend();

    void cleanup();

    GLFWwindow* getWindow();



private:
    //PRIVATE FUNCTIONS
    void initWindow();

    //Creators
    std::vector<const char*> getRequiredExtensions();

    bool createInstance();



    //Destroy-ers
    //Stuff to safely clean up - Prevent memory leaks and what not
    void destroyWindow();



public:
    //PUBLIC VARIABLES

private:
    //PRIVATE VARIABLES
    bool requiredExtensionsSet = false;

    bool validationLayersEnabled = false;

    const char* applicationName;

    GLFWwindow* glfwWindow;

    VkInstance vulkanInstance;


    std::vector<const char*> requiredExtensions;
    std::vector<const char*> optionalValidationLayers;

    std::vector<const char*> optionalExtensions;
};

#endif//VULKAN_MAIN_HPP