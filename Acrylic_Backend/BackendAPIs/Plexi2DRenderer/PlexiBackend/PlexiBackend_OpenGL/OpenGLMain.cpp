#define PLEXI_LIBRARY_ACTIVE
#include  "../plexiShaders.hpp"
#include "./../plexiBuffer.hpp"
//#include "./../../plexi_usrStructs.hpp"
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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);

    return true;
}


bool OpenGL::createVertexBuffer(const float *vertices, const size_t &size, pipelineComponentMap& pipelineMap) {
    glGenBuffers(1, &pipelineMap[VERTEX_BUFFER]);
    glBindBuffer(GL_ARRAY_BUFFER, pipelineMap[VERTEX_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    //Todo check for errors - Pos add error Callback?
    return true;
}

bool OpenGL::createIndexBuffer(const uint32_t *indices, const size_t &size, pipelineComponentMap& pipelineMap) {
    glGenBuffers(1, &pipelineMap[INDEX_BUFFER]);
    glBindBuffer(GL_ARRAY_BUFFER, pipelineMap[INDEX_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);//The cherno does it like this so I guess Ill do it?

    return true;
}

bool OpenGL::createVertexArray(const Plexi::Buffer::BufferCreateInfo &bufferCreateInfo, pipelineComponentMap& pipelineMap) {
    if(bufferCreateInfo.getLayout().getBufferElements().empty()){
        std::cerr << "Buffer Layout is empty" << std::endl;
        return false;
    }

    glGenVertexArrays(1, &pipelineMap[VERTEX_ARRAY]);//I have no idea why its called gen and not create

    glBindVertexArray(pipelineMap[VERTEX_ARRAY]);

    glBindBuffer(GL_ARRAY_BUFFER, pipelineMap[VERTEX_ARRAY]);

    const auto& bufferLayout = bufferCreateInfo.getLayout();

    for(const auto& element : bufferLayout){
        glEnableVertexAttribArray(vertexBufferIndex);

        glVertexAttribPointer(
                vertexBufferIndex,
                Plexi::Shaders::getDataTypeCount(element.dataType),
                Plexi::Shaders::convertDataTypeToGLSLBaseType(element.dataType),
                element.normalized ? GL_TRUE : GL_FALSE,
                bufferLayout.getStride(),
                (const void*) element.offset
        );
        //todo Add error check
        vertexBufferIndex++;
    }

    glBindVertexArray(pipelineMap[VERTEX_ARRAY]);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pipelineMap[INDEX_BUFFER]);

    return true;

}

void OpenGL::createGraphicsPipeline(const Plexi::Shaders::ShaderCreateInfo& shaderCreateInfo, const Plexi::Buffer::BufferCreateInfo& bufferCreateInfo) {
    std::cout << "Attempting to create " << bufferCreateInfo.shaderName << " graphics pipeline" << std::endl;
    //Create Pipeline
    pipelineComponentMap pipelineMap = {
            {SHADER_PROGRAM, 0},
            {VERTEX_BUFFER, 0},
            {INDEX_BUFFER, 0},
            {VERTEX_ARRAY, 0}
    };

    if(!shaderCreateInfo.isComplete()){
        //Error message Already displayed. We don't need to do it again
        return;
    }

    std::cout << "Attempting to create OpenGL Shader " << shaderCreateInfo.shaderName << std::endl;
    if(!createShaders(shaderCreateInfo.glslVertexCode, shaderCreateInfo.glslFragmentCode, shaderCreateInfo.shaderName, pipelineMap)){
        //Same as above
        return;
    }

    std::cout << "Shader created successfully" << std::endl;

    createVertexBuffer(bufferCreateInfo.vertexArray, bufferCreateInfo.vertexArraySize, pipelineMap);

    createIndexBuffer(bufferCreateInfo.indexArray, bufferCreateInfo.indexArraySize, pipelineMap);

    //Todo Move this vertex array stuff into a struct or something

    if(!createVertexArray(bufferCreateInfo, pipelineMap)){

        return;
    }

    activePipelines.insert(std::pair(bufferCreateInfo.shaderName, pipelineMap));//Not passing by ref bc we need this always

    glUseProgram(pipelineMap[SHADER_PROGRAM]);


}

void OpenGL::setClearColor(const float &r, const float &g, const float &b, const float &a) {
    glClearColor(r,g,b,a);
}

void OpenGL::submitScene() {

}

void OpenGL::onUpdate() {
    clear();
}

void OpenGL::cleanUpGraphicsPipeline(const std::string& pipelineName) {

    for(auto& [key, item] : activePipelines[pipelineName]){

    }
}

void OpenGL::cleanup() {
    glfwDestroyWindow(glfwWindow);

    glfwTerminate();
}

GLFWwindow *OpenGL::getWindowRef() {
    return glfwWindow;
}

void OpenGL::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}



