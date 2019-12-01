#include  "../plexiShaders.hpp"
#include "./../plexiBuffer.hpp"
#include "./../../plexi_usrStructs.hpp"
#include "./../plexiHelper.hpp"

#include "OpenGLMain.hpp"
static void glfwErrorCallBack(int errorCode, const char* description){
    if(errorCode == GLFW_NO_ERROR){
        return;
    }

    std::cerr << "GLFW ERROR: " << errorCode << ": " << description << std::endl;
    //todo handle errors
}


bool OpenGL::setRequiredInformation(const PlexiGFX_RequiredInformation &requiredInformation) {
    appName = requiredInformation.appName.c_str();
    requiredInfoSet = true;
    return true;
}

void OpenGL::setOptionInformation(const PlexiGFX_OptionalInformation &optionalInformation) {

}

bool OpenGL::createWindow() {
    if(!glfwInit()){
        std::cerr << "Failed to initialize GLFW" <<  std::endl;
        return false;
    }
    //Enforces OpenGL 4.1 on mac and windows
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwSetErrorCallback(glfwErrorCallBack);

    glfwWindow = glfwCreateWindow(1280, 720, appName, nullptr, nullptr);

    if(!glfwWindow){
        std::cerr << "Failed to create GLFW window" << std::endl;
        return false;
    }
    //Im sure that there is more that needs to be done

    return true;
}

bool OpenGL::initCore() {
    glfwMakeContextCurrent(glfwWindow);
    bool glStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    std::cout << "OpenGL status: " << (glStatus ? "SUCCESSFUL" : "FAILURE") << std::endl;
    std::cout << "\tVendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "\tGPU: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "\tVersion: " << glGetString(GL_VERSION) << std::endl;
    //Todo version check
    return glStatus;
}

bool OpenGL::isSupported() {

    return requiredInfoSet && createWindow() && initCore();
}

bool OpenGL::initBackend() {
    return false;
}

void OpenGL::createGraphicsPipeline(const Plexi::Shaders::ShaderCreateInfo& shaderCreateInfo, const Plexi::Buffer::BufferCreateInfo& bufferCreateInfo) {

}

void OpenGL::submitScene(const std::vector<Plexi::RenderTask> &currentScene) {

}

void OpenGL::cleanup() {
    glfwDestroyWindow(glfwWindow);

    glfwTerminate();
}

GLFWwindow *OpenGL::getWindowRef() {
    return glfwWindow;
}

