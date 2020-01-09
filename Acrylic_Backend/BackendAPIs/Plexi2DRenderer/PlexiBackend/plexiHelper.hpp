#ifndef PLEXI_HELPER_HPP
#define PLEXI_HELPER_HPP

#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <utility>
#include <vector>
#include <glm/glm.hpp>

// All shared structs are defined here -- Might want to move into own header

//Set up structs
struct PlexiGFX_RequiredInformation{
    const char** vulkan_DEVICE_EXTENSIONS = nullptr;

    size_t vulkan_EXT_SIZE = 0;

    std::string appName = "powered by Plexi 2D";
};

struct PlexiGFX_OptionalInformation {
    const char** vulkan_DEVICE_EXTENSIONS = nullptr;

    size_t vulkan_EXT_SIZE = 0;

    const char** vulkan_VALIDATION_LAYERS = nullptr;

    size_t vulkan_VALID_LAYER_SIZE = 0;

};

//Texture Structs
union TextureDataType {
    void* generic;
    unsigned char* image;
};

struct PlexiTextureData {
    TextureDataType dataType;
    bool usingGenericType = false;
};

struct StandardRenderTask {
    std::string graphicsPipelineName;
    glm::vec4 RGBAColor;
    glm::vec3 position;
    glm::vec2 scale;
    unsigned short textureCount;
    const uint32_t* textureIds = nullptr;

    StandardRenderTask(std::string pipelineName,  const glm::vec4& color, const glm::vec3& pos, const glm::vec2& in_scale, const unsigned short &texCount, const uint32_t* texIds) :
            graphicsPipelineName(std::move(pipelineName)), position(pos), RGBAColor(color), scale(in_scale), textureCount(texCount)
    {
        textureIds = texIds;
    }
    StandardRenderTask() :
        StandardRenderTask("", glm::vec4(0.0f), glm::vec3(0.0f), glm::vec2(0.0f), 0, nullptr)
    {}


};


class Plexi2DTexture {
public:
    Plexi2DTexture() = default;
    virtual ~Plexi2DTexture() = default;
    virtual void createTexture(const PlexiTextureData& data, uint32_t dataSize, uint32_t height, uint32_t width, uint32_t channelCount){};//return void or id Im not sure

    virtual void bind(uint32_t textureSlot){};

    virtual void unbind(){};

    [[nodiscard]] virtual uint32_t getId() const { return 1001;};

};


class PlexiGraphicsAPI {

public:
    PlexiGraphicsAPI() = default;
    virtual ~PlexiGraphicsAPI() = default;

    virtual bool isSupported() = 0;

    virtual bool setRequiredInformation(const PlexiGFX_RequiredInformation& requiredInformation) = 0;

    virtual void setOptionInformation(const PlexiGFX_OptionalInformation& optionalInformation) = 0;

    virtual bool initBackend() = 0;

    virtual void createGraphicsPipeline(const Plexi::Shaders::ShaderCreateInfo& shaderCreateInfo, const Plexi::Buffer::BufferCreateInfo& bufferCreateInfo) = 0;

    virtual void addTexture(Plexi2DTexture* texture) = 0;

    virtual Plexi2DTexture* getNewTexture() = 0;

    virtual void submitScene(const std::vector<StandardRenderTask>& standardRenderTasks) = 0;

    virtual void setClearColor(const float& r, const float& g, const float& b, const float& a) = 0;

    virtual void onUpdate() {

    }

    virtual void cleanup() = 0;


    virtual GLFWwindow* getWindowRef(){
        return nullptr;
    }

};

class PlexiBuffer {

};

#endif