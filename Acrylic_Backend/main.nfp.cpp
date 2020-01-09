#include "./BackendAPIs/Plexi2DRenderer/acrylic_plexiRenderer_core.hpp"
#include "./BackendAPIs/AcrylicSaveEngine/FileSystemBackend/acrylic_fileSystem.hpp"
#include "./BackendAPIs/AcrylicSaveEngine/FileSystemBackend/acrylic_bitmap.h"
#include "UserInput.cpp"
#include <iostream>
#include <ths/log.hpp>

StandardRenderTask obj1 = {
        "plexi_default_primitive",
        {0.25f, 0.75f,0.1f, 1.0f},
        {0.0f, 0.0f, 0.0f},
        {3.0f, 3.0f},
        1,
        nullptr
};

StandardRenderTask obj2 = {
        "plexi_default_primitive",
        {0.75f, 0.1f,0.25f, 1.0f},
        {-1.0f, -1.0f, 0.1f},
        {2.5f, 2.5f},
        1,
        nullptr
};

StandardRenderTask obj3 = {
        "plexi_default_primitive",
        {0.25f, 0.1f,0.75f, 1.0f},
        {1.0f, 1.0f, -0.1f},
        {3.5f, 3.5f},
        1,
        nullptr
};



StandardRenderTask* selectedOBJ = &obj1;
short selected = 0;

UserInput::Returns moveUp(int times){
    double move = (float) times / 50.0f;
    selectedOBJ->position.y += move;
    return {};
}
UserInput::Returns moveDown(int times){
    double move = (float) times / 50.0f;
    selectedOBJ->position.y -= move;
    return {};
}
UserInput::Returns moveLeft(int times){
    double move = (float) times / 50.0f;
    selectedOBJ->position.x -= move;
    return {};
}
UserInput::Returns moveRight(int times){

    double move = (float) times / 50.0f;
    selectedOBJ->position.x += move;
    return {};
}

UserInput::Returns changeSelection(int times){
    if(times == 0 ) {
        if (selected > 2) {
            selected = 0;
        } else
            selected++;

        switch (selected) {
            case 0:
                selectedOBJ = &obj1;
                break;
            case 1:
                selectedOBJ = &obj2;
                break;
            case 2:
                selectedOBJ = &obj3;
                break;
        }
    }
    return {};
}

UserInput::Returns scroll(double i, double j){
    j /=1000;
    selectedOBJ->scale.x+= (float) j;
    return {};
}
int main(){
    initLogger("A2D", log_severity_information, log_mode_all)
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
    uint32_t data = 0xFFFFFFFF;
    textureCreateInfo.textureData.dataType.generic = &data;
    textureCreateInfo.textureData.usingGenericType = true;
    uint32_t plainWhiteTexture = Plexi::Texture::create2DTexture(textureCreateInfo, Plexi::getActiveBackend());
    logInformation("Texture Created")
    Plexi::TextureCreateInfo dog = {};
    std::cout << std::filesystem::current_path() << std::endl;
    auto *dogImage = new A2D::Filesystem::ImageLoaders::Bitmaps::Image("dog.bmp");
    dog.height = dogImage->height;
    dog.width = dogImage->width;
    dog.channelCount = dogImage->bytes;
    dog.dataSize = dogImage->length;
    dog.textureData.usingGenericType = false;
    dog.textureData.dataType.image = dogImage->imageData;
    uint32_t dogTexture = Plexi::Texture::create2DTexture(dog, Plexi::getActiveBackend());
    obj1.textureIds = &plainWhiteTexture;
    obj2.textureIds = &dogTexture;
//    obj2.textureIds = &plainWhiteTexture;
    obj3.textureIds = &plainWhiteTexture;

    UserInput::initialize();
    UserInput::addKeyMap(GLFW_KEY_W, GLFW_PRESS, moveUp);
    UserInput::addKeyMap(GLFW_KEY_A, GLFW_PRESS, moveLeft);
    UserInput::addKeyMap(GLFW_KEY_S, GLFW_PRESS, moveDown);
    UserInput::addKeyMap(GLFW_KEY_D, GLFW_PRESS, moveRight);
    UserInput::setCursorPressedMoveFunc(scroll);
    UserInput::setScrollFunc(scroll);
    UserInput::setMouseRightFunc(GLFW_MOUSE_BUTTON_LEFT, changeSelection);



    while(!glfwWindowShouldClose(Plexi::getWindowRef())){
        glfwPollEvents();
        Plexi::submitScene({obj1, obj3, obj2});
        Plexi::onUpdate();
    }
    Plexi::cleanupPlexi();
    endLogger()
//    readJSON('a');
}
