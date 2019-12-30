#include "./BackendAPIs/Plexi2DRenderer/acrylic_plexiRenderer_core.hpp"
#include "./BackendAPIs/AcrylicSaveEngine/FileSystemBackend/acrylic_fileSystem.hpp"
#include "UserInput.cpp"
#include <iostream>

static float red = 0.0f;
static float blue = 0.0f;
static float green = 0.0f;
static bool usingRed = true;
UserInput::Returns doTheThing(int times){
    float t = (float)times/10;
    if(usingRed){
        red += t;
        blue -= t;
        if(blue <= 0.0f)
            blue = 0.0f;
    } else {
        blue += t;
        red -= t;
        if(red <= 0.0f)
            red = 0.0f;
    }
    if(red >= 1.0f){
//        red = 0.0f;
        usingRed = false;
    } else if(blue >= 1.0f){
//        blue = 0.0f;
        usingRed = true;
    }
    Plexi::setClearColor(red, 0.0f, blue, 1.0f);

    return {};
}

UserInput::Returns scroll(double i, double j){
    j = abs(j);
    float t = (float)(j)/1000;
    if(usingRed){
        red += t;
        blue -= t;
        if(blue <= 0.0f)
            blue = 0.0f;
    } else {
        blue += t;
        red -= t;
        if(red <= 0.0f)
            red = 0.0f;
    }
    if(red >= 1.0f){
//        red = 0.0f;
        usingRed = false;
    } else if(blue >= 1.0f){
//        blue = 0.0f;
        usingRed = true;
    }
    Plexi::setClearColor(red, 0.0f, blue, 1.0f);
    return {};
}
int main(){
    Plexi::PlexiConfig plexiConfig = {};
    plexiConfig.preferredGraphicsBackend = Plexi::PLEXI_GFX_BACKENDS::PLEXI_OPENGL;
    plexiConfig.defaultShaderLanguage = Plexi::Shaders::ShaderLanguage::GLSL;
    plexiConfig.clearColor = {0.1f, 0.1f, 0.1f, 1.0f};
    plexiConfig.plexiGFXRequiredInformation.appName = "Acrylic Testinator 1000";
    plexiConfig.shaderCount = 1;
    plexiConfig.shaderCreateInfos.resize(plexiConfig.shaderCount);
    plexiConfig.shaderCreateInfos[0].shaderName = "plexi_default_primitive";
    plexiConfig.shaderCreateInfos[0].shaderLanguage = plexiConfig.defaultShaderLanguage;
    plexiConfig.shaderCreateInfos[0].glslVertexCode = Plexi::Shaders::loadGLSLShaderFromFile(Plexi::Shaders::locateShader("plexi_vertex_default_primitive", plexiConfig.defaultShaderLanguage));
    plexiConfig.shaderCreateInfos[0].glslFragmentCode = Plexi::Shaders::loadGLSLShaderFromFile(Plexi::Shaders::locateShader("plexi_fragment_default_primitive", plexiConfig.defaultShaderLanguage));
    plexiConfig.bufferCreateInfos.resize(plexiConfig.shaderCount);
    plexiConfig.bufferCreateInfos[0].shaderName = plexiConfig.shaderCreateInfos[0].shaderName;
    plexiConfig.bufferCreateInfos[0].setLayout({
       {Plexi::Shaders::Float3, "positionCoords"},
       {Plexi::Shaders::Float2, "textureCoords"}
    });

    plexiConfig.bufferCreateInfos[0].vertexArray = Plexi::Buffer::SQUARE_VERTICES_WITH_TEXTURE;
    plexiConfig.bufferCreateInfos[0].vertexArraySize = Plexi::Buffer::SQUARE_VERTICES_WITH_TEXTURE_SIZE;
    plexiConfig.bufferCreateInfos[0].indexArray = Plexi::Buffer::SQUARE_INDICES;
    plexiConfig.bufferCreateInfos[0].indexArraySize = Plexi::Buffer::SQUARE_INDICES_SIZE;

    Plexi::initPlexi(plexiConfig);

    Plexi::TextureCreateInfo textureCreateInfo = {};
    textureCreateInfo.height = 1;
    textureCreateInfo.width = 1;
    textureCreateInfo.channelCount = 4;
    textureCreateInfo.dataSize = sizeof(uint32_t);
    uint32_t data = 0xffffffff;
    textureCreateInfo.textureData = &data;

    uint32_t plainWhiteTexture = Plexi::Texture::create2DTexture(textureCreateInfo, Plexi::getActiveBackend());

    UserInput::initialize();
    UserInput::addKeyMap(GLFW_KEY_W, GLFW_PRESS, doTheThing);
    UserInput::addKeyMap(GLFW_KEY_A, GLFW_PRESS, doTheThing);
    UserInput::addKeyMap(GLFW_KEY_S, GLFW_PRESS, doTheThing);
    UserInput::addKeyMap(GLFW_KEY_D, GLFW_PRESS, doTheThing);
    UserInput::setCursorPressedMoveFunc(scroll);
    UserInput::setScrollFunc(scroll);
    UserInput::setMouseRightFunc(GLFW_MOUSE_BUTTON_LEFT, doTheThing);



    while(!glfwWindowShouldClose(Plexi::getWindowRef())){
        glfwPollEvents();
        Plexi::onUpdate();
    }
    Plexi::cleanupPlexi();
//    readJSON('a');
}
