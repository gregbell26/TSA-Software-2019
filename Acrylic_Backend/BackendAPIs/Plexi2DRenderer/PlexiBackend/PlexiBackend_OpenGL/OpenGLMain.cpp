#define PLEXI_LIBRARY_ACTIVE
#include  "../plexiShaders.hpp"
#include "./../plexiBuffer.hpp"
#include "./../plexiHelper.hpp"

#include "OpenGL2DTexture.hpp"

#include "OpenGLMain.hpp"

Plexi2DTexture *texture = new OpenGL2DTexture(101);//fuck you

static void glfwErrorCallBack(int errorCode, const char* description){
    if(errorCode == GLFW_NO_ERROR){
        return;
    }

    logError("GLFW Error: " + std::to_string(errorCode) + ':' + description)
    //todo handle errors
}

#if not defined (MACOS)
static void GLAPIENTRY openGLDebugMessageCallBack(GLenum source,
                                                  GLenum type,
                                                  GLuint id,
                                                  GLenum severity,
                                                  GLsizei length,
                                                  const char* message,
                                                  const void* userParam){
    if(type == GL_DEBUG_TYPE_ERROR)
        logError("OpenGL Error: " + std::string() + message)
    else
        logInformation("OpenGL Message: " + std::string() + message)

}
#endif

bool OpenGL::setRequiredInformation(const PlexiGFX_RequiredInformation &requiredInformation) {
    appName = requiredInformation.appName.c_str();
    requiredInfoSet = true;
    return true;
}

void OpenGL::setOptionInformation(const PlexiGFX_OptionalInformation &optionalInformation) {

}

bool OpenGL::createWindow() {
    if(!glfwInit()){
        logError("Failed to initialize GLFW")
        return false;
    }
    logInformation("Initialized GLFW successfully")
    //Enforces OpenGL 4.1 on mac and windows
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwSetErrorCallback(glfwErrorCallBack);

    glfwWindow = glfwCreateWindow(1280, 720, appName, nullptr, nullptr);

    if(!glfwWindow){
        logError("Failed to create GLFW window")
        glfwTerminate();
        return false;
    }
    //Im sure that there is more that needs to be done

    logInformation("Created GLFW window successfully")
    return true;
}

bool OpenGL::initCore() {
    glfwMakeContextCurrent(glfwWindow);
    bool glStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

#if not defined(MACOS)//OpenGL debugging is not supported on macOS
    glEnable(GL_DEBUG_OUTPUT);
    logInformation("Using OpenGL debug messages")
    glDebugMessageCallback(openGLDebugMessageCallBack, nullptr);
#endif

    if(!glStatus)
        logError("Failed to initialized OpenGL")
    else {
        logInformation("Initialized OpenGL successfully")
        logInformation("OpenGL Info: ")
        logInformation("\tGPU Vendor: " + std::string() + (const char*) glGetString(GL_VENDOR))
        logInformation("\tGPU Name: " + std::string() + (const char*) glGetString(GL_RENDERER))
        logInformation("\tOpenGL Version: " + std::string() + (const char*) glGetString(GL_VERSION))
    }

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
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pipelineMap[INDEX_BUFFER]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);

    return true;
}

bool OpenGL::createVertexArray(const Plexi::Buffer::BufferCreateInfo &bufferCreateInfo, pipelineComponentMap& pipelineMap) {
    if(bufferCreateInfo.getLayout().getBufferElements().empty()){
        std::cerr << "Buffer Layout is empty" << std::endl;
        return false;
    }

    glGenVertexArrays(1, &pipelineMap[VERTEX_ARRAY]);//I have no idea why its called gen and not create

    glBindVertexArray(pipelineMap[VERTEX_ARRAY]);

    glBindBuffer(GL_ARRAY_BUFFER, pipelineMap[VERTEX_BUFFER]);

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

//    glBindVertexArray(pipelineMap[VERTEX_ARRAY]);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pipelineMap[INDEX_BUFFER]);

    return true;

}

void OpenGL::createGraphicsPipeline(const Plexi::Shaders::ShaderCreateInfo& shaderCreateInfo, const Plexi::Buffer::BufferCreateInfo& bufferCreateInfo) {
    logInformation("Attempting to create \'" + bufferCreateInfo.shaderName + "\' graphics pipeline")

    if(!shaderCreateInfo.isComplete()){
        //Error message Already displayed. We don't need to do it again
        logWarning("Failed to create \'" + bufferCreateInfo.shaderName + "\' graphics pipeline")
        return;
    }

    //Create Pipeline
    pipelineComponentMap pipelineMap = {
            {SHADER_PROGRAM, 0},
            {VERTEX_BUFFER, 0},
            {INDEX_BUFFER, 0},
            {VERTEX_ARRAY, 0}
    };

    logInformation("Attempting to create OpenGL Shader Program \'" + shaderCreateInfo.shaderName + "\'")
    if(!createShaders(shaderCreateInfo.glslVertexCode, shaderCreateInfo.glslFragmentCode, shaderCreateInfo.shaderName, pipelineMap)){
        logWarning("Failed to create OpenGL Shader Program \'" + shaderCreateInfo.shaderName + "\'")
        pipelineMap.clear();
        logWarning("Failed to create \'" + bufferCreateInfo.shaderName + "\' graphics pipeline")
        return;
    }

    logInformation("Shader Program created successfully")

    createVertexBuffer(bufferCreateInfo.vertexArray, bufferCreateInfo.vertexArraySize, pipelineMap);

    createIndexBuffer(bufferCreateInfo.indexArray, bufferCreateInfo.indexArraySize, pipelineMap);

    //Todo Move this vertex array stuff into a struct or something

    if(!createVertexArray(bufferCreateInfo, pipelineMap)){
        logInformation("Failed to create OpenGL Vertex Array")
        glDeleteProgram(pipelineMap[SHADER_PROGRAM]);
        pipelineMap[SHADER_PROGRAM] = 0;
        glDeleteBuffers(1, &pipelineMap[VERTEX_BUFFER]);
        pipelineMap[VERTEX_BUFFER] = 0;
        glDeleteBuffers(1, &pipelineMap[INDEX_BUFFER]);
        pipelineMap[INDEX_BUFFER] = 0;
        glDeleteVertexArrays(1, &pipelineMap[VERTEX_ARRAY]);
        pipelineMap[VERTEX_ARRAY] = 0;
        pipelineMap.clear();
        logWarning("Failed to create \'" + bufferCreateInfo.shaderName + "\' graphics pipeline")
        return;
    }

    activePipelines.insert(std::pair(bufferCreateInfo.shaderName, pipelineMap));//Not passing by ref bc we need this always

    logInformation("Created \'" + bufferCreateInfo.shaderName + "\' Graphics Pipeline Successfully")

    glUseProgram(pipelineMap[SHADER_PROGRAM]);

    setInt(bufferCreateInfo.shaderName, "texture2D", 0);//Tell openGL we have will want to use this shader slot


}

void OpenGL::setClearColor(const float &r, const float &g, const float &b, const float &a) {
    glClearColor(r,g,b,a);
}

void OpenGL::submitScene() {

}

void OpenGL::onUpdate() {
    clear();
    setMat4("plexi_default_primitive", "viewProjection", glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, -1.0f, 1.0f));
    {
        setFloat4("plexi_default_primitive", "color", {0.0f, 0.5f, 0.75f, 1.0f});
    //    try {
    //        textureMap.at(101)->bind(0);
    //    }catch(std::out_of_range& err){
    //        std::cout << "Texture id: " << 101 << "does not exist" << std::endl;
    //    }
        texture->bind(0);

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), {0.0f, 0.0f, -0.1f}) * glm::scale(glm::mat4(1.0f), { 2.0f, 2.0f, 2.0f });
        setMat4("plexi_default_primitive", "transform", transform);
        glBindVertexArray(activePipelines["plexi_default_primitive"][VERTEX_ARRAY]);
    //    const uint32_t fuckYou[] = {0, 1, 2, 2, 3, 0} ;
        glDrawElements(GL_TRIANGLES, 7, GL_UNSIGNED_INT, nullptr);
    //    try {
    //        textureMap.at(101)->unbind();
    //    }catch(std::out_of_range& err){
    //        std::cout << "Texture id: " << 101 << "does not exist" << std::endl;
    //    }

        texture->unbind();
    }

    {
        setFloat4("plexi_default_primitive", "color", {0.75f, 0.0f, 0.5f, 1.0f});

        texture->bind(0);

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), {-3.0f, -1.5f, 0.0f}) * glm::scale(glm::mat4(1.0f), { 0.25f, 3.0f, 0.25f });
        setMat4("plexi_default_primitive", "transform", transform);
        glBindVertexArray(activePipelines["plexi_default_primitive"][VERTEX_ARRAY]);

        glDrawElements(GL_TRIANGLES, 7, GL_UNSIGNED_INT, nullptr);

        texture->unbind();
    }

    {
        setFloat4("plexi_default_primitive", "color", {0.0f, 0.75f, 0.5f, 1.0f});

        texture->bind(0);

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), {3.0f, -1.5f, 0.0f}) * glm::scale(glm::mat4(1.0f), { 0.25f, 3.0f, 0.25f });
        setMat4("plexi_default_primitive", "transform", transform);
        glBindVertexArray(activePipelines["plexi_default_primitive"][VERTEX_ARRAY]);

        glDrawElements(GL_TRIANGLES, 7, GL_UNSIGNED_INT, nullptr);

        texture->unbind();
    }


    glfwSwapBuffers(glfwWindow);

}

void OpenGL::cleanUpGraphicsPipeline(const std::string& pipelineName) {
    if(pipelineName == "all"){
        logInformation("Cleaning up all pipelines...")
        for(auto& [pipeline, componentMap] : activePipelines){
            logInformation("\tCleaning up graphics pipeline \'" + pipeline + "\'")
            glDeleteProgram(componentMap[SHADER_PROGRAM]);
            componentMap[SHADER_PROGRAM] = 0;
            glDeleteBuffers(1, &componentMap[VERTEX_BUFFER]);
            componentMap[VERTEX_BUFFER] = 0;
            glDeleteBuffers(1, &componentMap[INDEX_BUFFER]);
            componentMap[INDEX_BUFFER] = 0;
            glDeleteVertexArrays(1, &componentMap[VERTEX_ARRAY]);
            componentMap[VERTEX_ARRAY] = 0;
            componentMap.clear();
        }
        activePipelines.clear();
        return;
    }

    try {
        logInformation("Cleaning up graphics pipeline \'" + pipelineName + "\'")
        pipelineComponentMap &tempMap = activePipelines.at(pipelineName);
        glDeleteProgram(tempMap[SHADER_PROGRAM]);
        tempMap[SHADER_PROGRAM] = 0;
        glDeleteBuffers(1, &tempMap[VERTEX_BUFFER]);
        tempMap[VERTEX_BUFFER] = 0;
        glDeleteBuffers(1, &tempMap[INDEX_BUFFER]);
        tempMap[INDEX_BUFFER] = 0;
        glDeleteVertexArrays(1, &tempMap[VERTEX_ARRAY]);
        tempMap[VERTEX_ARRAY] = 0;
        tempMap.clear();
    } catch (std::out_of_range& err){
        logWarning("Pipeline \'" + pipelineName + "\' does not exist. Please check your spelling.")
        logWarning("Error details: " + std::string() + err.what())
        return;
    }





}


void OpenGL::cleanup() {
    cleanUpGraphicsPipeline("all");
    glfwDestroyWindow(glfwWindow);

    glfwTerminate();
}

void OpenGL::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGL::addTexture(Plexi2DTexture* texture) {
//    uint32_t id = texture->getId();
//    this->textureMap.insert(std::pair(id, texture));
    //textureMap.insert(std::pair(texture->getId(), texture));
    //whiteTextureId = texture->getId();
//    this->whiteTextureId = id;
}

Plexi2DTexture* OpenGL::getNewTexture() {
//    textureMap.insert({currentTextureId, new OpenGL2DTexture(currentTextureId)});
//    currentTextureId++;
//    return textureMap[currentTextureId-1];
    return texture;
}





