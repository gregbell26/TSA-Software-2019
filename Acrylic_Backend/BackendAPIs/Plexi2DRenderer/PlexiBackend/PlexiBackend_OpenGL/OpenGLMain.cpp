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

bool OpenGL::createShaders(const std::string& vertexSource, const std::string& fragmentSource, const std::string& shaderProgramName) {
    // Read our shaders into the appropriate buffers

    // Create an empty vertex shader handle
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Send the vertex shader source code to GL
    // Note that std::string's .c_str is NULL character terminated.
    auto  *source = (const GLchar *)vertexSource.c_str();
    glShaderSource(vertexShader, 1, &source, 0);

    // Compile the vertex shader
    glCompileShader(vertexShader);

    GLint isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);

    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

        // We don't need the shader anymore.
        glDeleteShader(vertexShader);

        // Use the infoLog as you see fit.
        std::cerr << "OpenGL Shader Compilation Error: " << infoLog.data() << std::endl;

        // In this simple program, we'll just leave
        return false;
    }

// Create an empty fragment shader handle
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

// Send the fragment shader source code to GL
// Note that std::string's .c_str is NULL character terminated.
    source = (const GLchar *)fragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &source, 0);

// Compile the fragment shader
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

        // We don't need the shader anymore.
        glDeleteShader(fragmentShader);
        // Either of them. Don't leak shaders.
        glDeleteShader(vertexShader);

        // Use the infoLog as you see fit.

        std::cerr << "OpenGL Shader compilation error " << infoLog.data() << std::endl;
        // In this simple program, we'll just leave
        return false;
    }

    // Vertex and fragment shaders are successfully compiled.
    // Now time to link them together into a program.
    // Get a program object.
    GLuint program = glCreateProgram();

    // Attach our shaders to our program
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    // Link our program
    glLinkProgram(program);

    // Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

        // We don't need the program anymore.
        glDeleteProgram(program);
        // Don't leak shaders either.
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        // Use the infoLog as you see fit.
        std::cerr << "OpenGL Shader link error: " << infoLog.data() << std::endl;
        // In this simple program, we'll just leave
        return false;
    }

    activeShaderProgramIds[shaderProgramName] =program;

    // Always detach shaders after a successful link.
    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);


    return true;
}

bool OpenGL::createVertexBuffer(float *vertices, const size_t &size) {
    glGenBuffers(1, &vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    //Todo check for errors - Pos add error Callback?
    return true;
}

bool OpenGL::createIndexBuffer(uint32_t *indices, const size_t &size) {
    glGenBuffers(1, &indexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, indexBufferId);
    glBufferData(GL_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);//The cherno does it like this so I guess Ill do it?

    return true;
}

bool OpenGL::createVertexArray(const Plexi::Buffer::BufferCreateInfo &bufferCreateInfo) {
    if(bufferCreateInfo.bufferLayout->getBufferElements().empty()){
        std::cerr << "Buffer Layout is empty" << std::endl;
        return false;
    }

    glGenVertexArrays(1, &vertexArrayId);//I have no idea why its called gen and not create

    glBindVertexArray(vertexArrayId);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);

    const auto& bufferLayout = bufferCreateInfo.bufferLayout;

    for(const auto& element : *bufferLayout){
        glEnableVertexAttribArray(vertexBufferIndex);

        glVertexAttribPointer(
                vertexBufferIndex,
                Plexi::Shaders::getDataTypeCount(element.dataType),
                Plexi::Shaders::convertDataTypeToGLSLBaseType(element.dataType),
                element.normalized ? GL_TRUE : GL_FALSE,
                bufferLayout->getStride(),
                (const void*) element.offset
        );
        //todo Add error check
        vertexBufferIndex++;
    }

    glBindVertexArray(vertexArrayId);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);

    return true;

}

void OpenGL::createGraphicsPipeline(const Plexi::Shaders::ShaderCreateInfo& shaderCreateInfo, const Plexi::Buffer::BufferCreateInfo& bufferCreateInfo) {
    std::cout << "Attempting to create " << bufferCreateInfo.shaderName << " graphics pipeline" << std::endl;

    if(!shaderCreateInfo.isComplete()){
        //Error message Already displayed. We don't need to do it again
        return;
    }

    std::cout << "Attempting to create OpenGL Shader " << shaderCreateInfo.shaderName << std::endl;
    if(!createShaders(shaderCreateInfo.glslVertexCode, shaderCreateInfo.glslFragmentCode, shaderCreateInfo.shaderName)){
        //Same as above
        return;
    }

    std::cout << "Shader created successfully" << std::endl;

    createVertexBuffer(bufferCreateInfo.vertexArray, bufferCreateInfo.vertexArraySize);

    createIndexBuffer(bufferCreateInfo.indexArray, bufferCreateInfo.indexArraySize);

    //Todo Move this vertex array stuff into a struct or something

    if(!createVertexArray(bufferCreateInfo)){

        return;
    }

    glUseProgram(activeShaderProgramIds[shaderCreateInfo.shaderName]);


}

void OpenGL::setClearColor(const float &r, const float &g, const float &b, const float &a) {
    glClearColor(r,g,b,a);
}

void OpenGL::submitScene() {

}

void OpenGL::onUpdate() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGL::cleanUpGraphicsPipeline() {

    for(auto& [key, item] : activeShaderProgramIds){

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

}



