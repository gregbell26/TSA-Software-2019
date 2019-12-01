#ifndef OPENGL_MAIN_HPP
#define OPENGL_MAIN_HPP

#include <GLFW/glfw3.h>
#include <glad/glad.h>

class OpenGL: public PlexiGFXBackend {
public:
    OpenGL() = default;
    ~OpenGL() override = default;

    bool isSupported() override ;

    bool setRequiredInformation(const PlexiGFX_RequiredInformation& requiredInformation) override;

    void setOptionInformation(const PlexiGFX_OptionalInformation& optionalInformation) override;

    bool initBackend() override;

    void createGraphicsPipeline(const Plexi::Shaders::ShaderCreateInfo& shaderCreateInfo, const Plexi::Buffer::BufferCreateInfo& bufferCreateInfo) override;

    void submitScene(const std::vector<Plexi::RenderTask>& currentScene) override;

    void onUpdate() override;

    void cleanup() override;


    GLFWwindow* getWindowRef() override;

private:
    bool createWindow();
    bool initCore();

public:

private:
    const char* appName;
    bool requiredInfoSet = false;

    GLFWwindow* glfwWindow;

};


#endif //OPENGL_MAIN_HPP
