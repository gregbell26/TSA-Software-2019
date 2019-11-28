#ifndef OPENGL_MAIN_HPP
#define OPENGL_MAIN_HPP

#include <GLFW/glfw3.h>
#include <glad/glad.h>

class OpenGL: public PlexiGFXBackend {
public:
    OpenGL() = default;
    ~OpenGL() = default;

    bool isSupported() override ;

    bool setRequiredInformation(const PlexiGFX_RequiredInformation& requiredInformation) override;

    void setOptionInformation(const PlexiGFX_OptionalInformation& optionalInformation) override;

    bool initBackend() override;

    void bindShaders(const Plexi::Shader& VERTEX_SHADER, const Plexi::Shader& FRAGMENT_SHADER) override;
//    virtual void runBackend() = 0;

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
