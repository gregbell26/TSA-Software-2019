#ifndef OPENGL_MAIN_HPP
#define OPENGL_MAIN_HPP

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <algorithm>
#include <ths/log.hpp>

#define pipelineComponentMap std::map<OPEN_GL_GFX_PIPELINE_COMPONENT_IDS, GLuint>

class OpenGL: public PlexiGraphicsAPI {
protected:
    //Enums and Config
    enum OPEN_GL_GFX_PIPELINE_COMPONENT_IDS {
        SHADER_PROGRAM = 0,
        VERTEX_BUFFER,
        INDEX_BUFFER,
        VERTEX_ARRAY

    };

public:
    OpenGL() = default;
    ~OpenGL() override = default;

    bool isSupported() override ;

    bool setRequiredInformation(const PlexiGFX_RequiredInformation& requiredInformation) override;

    void setOptionInformation(const PlexiGFX_OptionalInformation& optionalInformation) override;

    bool initBackend() override;

    void createGraphicsPipeline(const Plexi::Shaders::ShaderCreateInfo& shaderCreateInfo, const Plexi::Buffer::BufferCreateInfo& bufferCreateInfo) override;

    void setClearColor(const float& r, const float& g, const float& b, const float& a) override;

    void submitScene(const std::vector<StandardRenderTask>& standardRenderTasks) override;

    void submitScene(const std::vector<TextRenderTask>& textRenderTasks) override;

    void addTexture(Plexi2DTexture* texture) override;

    uint32_t addFontFace(FT_Face& fontFace, uint32_t charCount) override;

    Plexi2DTexture* getNewTexture() override;


    void onUpdate() override;

    void removeTexture() override;

    void removeTexture(uint32_t textureId) override;

    void removeFont() override;

    void removeFont(uint32_t fontId) override;

    void cleanup() override;


    GLFWwindow* getWindowRef() override { return glfwWindow; };

private:
    bool createWindow();

    bool initCore();

    void clear();

    //Pipeline Helper Functions
    bool createShaders(const std::string& vertexSource, const std::string& fragmentSource, const std::string& shaderProgramName, pipelineComponentMap& pipelineMap);

    bool createVertexBuffer(const float* vertices, const size_t& size, const bool& dynamicMode, pipelineComponentMap& pipelineMap);

    bool createIndexBuffer(const uint32_t* indices, const size_t& size, pipelineComponentMap& pipelineMap);

    bool createVertexArray(const Plexi::Buffer::BufferCreateInfo& bufferCreateInfo, pipelineComponentMap& pipelineMap);

    void cleanUpGraphicsPipeline(const std::string& pipelineName);

    //Shader Helper Functions
    void setInt(const std::string& pipelineName, const std::string& uniformName, const int& newValue);

    void setFloat(const std::string& pipelineName, const std::string& uniformName, const float& newValue);

    void setFloat2(const std::string& pipelineName, const std::string& uniformName, const glm::vec2& newValue);

    void setFloat3(const std::string& pipelineName, const std::string& uniformName, const glm::vec3& newValue);

    void setFloat4(const std::string& pipelineName, const std::string& uniformName, const glm::vec4& newValue);

    void setMat3(const std::string& pipelineName, const std::string& uniformName, const glm::mat3& newValue);

    void setMat4(const std::string& pipelineName, const std::string& uniformName, const glm::mat4& newValue);


public:
    struct Character {
        GLuint glTextureId;
        glm::vec2 size;
        glm::vec2 bearing;
        uint32_t glAdvance;
    };

private:
    const char* appName;
    bool requiredInfoSet = false;

    GLFWwindow* glfwWindow;

    uint32_t onUpdateErrorCounter = 0;

    std::map<std::string, pipelineComponentMap> activePipelines;

};


#endif //OPENGL_MAIN_HPP
