#include  "./../shaders.hpp"
#include "./../plexiHelper.hpp"


#include "OpenGLMain.hpp"

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

void OpenGL::bindShaders(const Plexi::Shader &VERTEX_SHADER, const Plexi::Shader &FRAGMENT_SHADER) {

}

void OpenGL::cleanup() {
    glfwDestroyWindow(glfwWindow);

    glfwTerminate();
}

GLFWwindow *OpenGL::getWindowRef() {
    return glfwWindow;
}

