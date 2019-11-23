#ifndef PLEXI_HELPER_HPP
#define PLEXI_HELPER_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

struct PlexiGFX_RequiredInformation{
    const char** vulkan_DEVICE_EXTENSIONS = nullptr;

    size_t vulkan_EXT_SIZE = 0;

    std::string appName = "powered by Plexi 2D";
};

struct PlexiGFX_OptionalInformation{
    const char** vulkan_DEVICE_EXTENSIONS = nullptr;

    size_t vulkan_EXT_SIZE = 0;

    const char** vulkan_VALIDATION_LAYERS = nullptr;

    size_t vulkan_VALID_LAYER_SIZE = 0;

};


class PlexiGFXBackend {

public:
    PlexiGFXBackend() = default;
    virtual ~PlexiGFXBackend() = default;

    virtual bool isSupported() = 0;

    virtual bool initBackend() = 0;

    virtual void runBackend() = 0;

    virtual void cleanup() = 0;

    virtual bool setRequiredInformation(const PlexiGFX_RequiredInformation& requiredInformation) = 0;

    virtual void setOptionInformation(const PlexiGFX_OptionalInformation& optionalInformation) = 0;

    virtual GLFWwindow* getWindowRef(){
        return nullptr;
    }

};

#endif