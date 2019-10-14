#ifndef VULKAN_MAIN_HPP
#define VULKAN_MAIN_HPP

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <vector>



class Vulkan {
public:
    Vulkan();

    void setRequiredExtensions(std::vector<const char*> requiredExtensions);

    //Create instance - If that fails vulkan is not supported
    //Enum physical devices - If that's 0 vulkan is not supported
    //Extension check - Make sure all required extensions are supported
    bool isSupported();

    bool initBackend();

private:
    //PRIVATE FUNCTIONS

public:
    //PUBLIC VARIABLES

private:
    //PRIVATE VARIABLES
    std::vector<const char*> requiredExtensions;
};

#endif//VULKAN_MAIN_HPP