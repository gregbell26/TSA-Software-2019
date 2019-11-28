#ifndef VULKAN_MAIN_HPP
#define VULKAN_MAIN_HPP

#define GLFW_INCLUDE_NONE

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>


class Vulkan: public PlexiGFXBackend {
public:
    Vulkan() = default;


    //Create instance - If that fails vulkan is not supported
    //Enum physical devices - If that's 0 vulkan is not supported
    //Extension check - Make sure all required extensions are supported
    bool isSupported() override;

    bool setRequiredInformation(const PlexiGFX_RequiredInformation &requiredInformation) override;

    void setOptionInformation(const PlexiGFX_OptionalInformation &optionalInformation) override;

    bool initBackend() override;

    void bindShaders(const Plexi::Shader& VERTEX_SHADER, const Plexi::Shader& FRAGMENT_SHADER) override;

//    void runBackend() override;

    void cleanup() override;

    GLFWwindow* getWindowRef() override;



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