#ifndef OPENGL_MAIN_HPP
#define OPENGL_MAIN_HPP

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <map>

class OpenGL: public PlexiGFXBackend {
public:
    OpenGL() = default;
    ~OpenGL() override = default;

    bool isSupported() override ;

    bool setRequiredInformation(const PlexiGFX_RequiredInformation& requiredInformation) override;

    void setOptionInformation(const PlexiGFX_OptionalInformation& optionalInformation) override;

    bool initBackend() override;

    void createGraphicsPipeline(const Plexi::Shaders::ShaderCreateInfo& shaderCreateInfo, const Plexi::Buffer::BufferCreateInfo& bufferCreateInfo) override;

    void setClearColor(const float& r, const float& g, const float& b, const float& a) override;

    void submitScene() override;



    void onUpdate() override;

    void cleanup() override;


    GLFWwindow* getWindowRef() override;

private:
    bool createWindow();

    bool initCore();

    bool createShaders(const std::string& vertexSource, const std::string& fragmentSource, const std::string& shaderProgramName);

    bool createVertexBuffer(const float* vertices, const size_t& size);

    bool createIndexBuffer(const uint32_t* indices, const size_t& size);

    bool createVertexArray(const Plexi::Buffer::BufferCreateInfo& bufferCreateInfo);

    void clear();

    void cleanUpGraphicsPipeline();

public:

private:
    const char* appName;
    bool requiredInfoSet = false;

    GLFWwindow* glfwWindow;

    //Maybe add this as a vector in future
    std::map<std::string, GLuint> activeShaderProgramIds;
    GLuint vertexBufferId;
    GLuint indexBufferId;
    GLuint vertexArrayId;
    uint32_t vertexBufferIndex = 0;

};


#endif //OPENGL_MAIN_HPP
