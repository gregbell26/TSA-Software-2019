#include "./BackendAPIs/Plexi2DRenderer/acrylic_plexiRenderer_core.hpp"
#include "./BackendAPIs/AcrylicSaveEngine/FileSystemBackend/acrylic_fileSystem.hpp"
#include "./BackendAPIs/AcrylicSaveEngine/FileSystemBackend/acrylic_bitmap.h"
#include "Input.cpp"
#include "UserInput.cpp"
#include "./BackendAPIs/AcrylicSaveEngine/FileSystemBackend/acrylic_font.hpp"
#include <iostream>
#include <ths/log.hpp>
#include "Random.h"
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"

StandardRenderTask obj1 = {
        "plexi_default_primitive",
        {0.0f, 0.0,0.0f, 0.0f},
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

StandardRenderTask obj4 = {
        "plexi_default_primitive",
        {0.0f,0.0f,0.0f,0.0f},
        {0.0f, 0.0f, 0.0f},
        {10.0f, 10.0f},
        1,
        nullptr
};

TextRenderTask txtObj5 = {
        "plexi_default_text",
        "Hello World",
        0,
        {1.0f,1.0f,1.0f,1.0f},
        {0.0f, 0.0f},
        0.025f
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
    plexiConfig.shaderCount = 2;
    plexiConfig.shaderCreateInfos.resize(plexiConfig.shaderCount);
    plexiConfig.shaderCreateInfos[0].shaderName = "plexi_default_primitive";
    plexiConfig.shaderCreateInfos[0].shaderLanguage = plexiConfig.defaultShaderLanguage;
    plexiConfig.shaderCreateInfos[0].glslVertexCode = Plexi::Shaders::loadGLSLShaderFromFile(Plexi::Shaders::locateShader("plexi_vertex_default_primitive", plexiConfig.defaultShaderLanguage));
    plexiConfig.shaderCreateInfos[0].glslFragmentCode = Plexi::Shaders::loadGLSLShaderFromFile(Plexi::Shaders::locateShader("plexi_fragment_default_primitive", plexiConfig.defaultShaderLanguage));
    plexiConfig.shaderCreateInfos[1].shaderName = "plexi_default_text";
    plexiConfig.shaderCreateInfos[1].shaderLanguage = plexiConfig.defaultShaderLanguage;
    plexiConfig.shaderCreateInfos[1].glslVertexCode = Plexi::Shaders::loadGLSLShaderFromFile(Plexi::Shaders::locateShader("plexi_vertex_default_text", plexiConfig.defaultShaderLanguage));
    plexiConfig.shaderCreateInfos[1].glslFragmentCode = Plexi::Shaders::loadGLSLShaderFromFile(Plexi::Shaders::locateShader("plexi_fragment_default_text", plexiConfig.defaultShaderLanguage));
    plexiConfig.bufferCreateInfos.resize(plexiConfig.shaderCount);
    plexiConfig.bufferCreateInfos[0].shaderName = plexiConfig.shaderCreateInfos[0].shaderName;
    plexiConfig.bufferCreateInfos[0].setLayout({
       {Plexi::Shaders::Float3, "in_positionCoords"},
       {Plexi::Shaders::Float2, "in_textureCoords"}
    });

    plexiConfig.bufferCreateInfos[0].vertexArray = Plexi::Buffer::SQUARE_VERTICES_WITH_TEXTURE;
    plexiConfig.bufferCreateInfos[0].vertexArraySize = Plexi::Buffer::SQUARE_VERTICES_WITH_TEXTURE_SIZE;
    plexiConfig.bufferCreateInfos[0].indexArray = Plexi::Buffer::SQUARE_INDICES;
    plexiConfig.bufferCreateInfos[0].indexArraySize = Plexi::Buffer::SQUARE_INDICES_SIZE;

    plexiConfig.bufferCreateInfos[1].shaderName = plexiConfig.shaderCreateInfos[1].shaderName;
    plexiConfig.bufferCreateInfos[1].setLayout({
           {Plexi::Shaders::Float4, "in_allCoords"},
    });

    plexiConfig.bufferCreateInfos[1].vertexArraySize = Plexi::Buffer::TEXT_VERTICES_SIZE;


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
    Plexi::TextureCreateInfo dog = {};
    auto *dogImage = new A2D::Filesystem::ImageLoaders::Bitmaps::Image("./textures/dog.bmp");
    dogImage->PrintInfo();
    dog.height = dogImage->height;
    dog.width = dogImage->width;
    dog.channelCount = dogImage->bytes;
    dog.dataSize = dogImage->length;
    dog.textureData.usingGenericType = false;
    dog.textureData.dataType.image = dogImage->imageData;
    uint32_t dogTexture = Plexi::Texture::create2DTexture(dog, Plexi::getActiveBackend());\
    delete dogImage;

    Plexi::TextureCreateInfo weird = {};
    auto *weirdImage = new A2D::Filesystem::ImageLoaders::Bitmaps::Image("./textures/weirdTexture.bmp");
    weirdImage->PrintInfo();
    weird.height = weirdImage->height;
    weird.width = weirdImage->width;
    weird.channelCount = weirdImage->bytes;
    weird.dataSize = weirdImage->length;
    weird.textureData.usingGenericType = false;
    weird.textureData.dataType.image = weirdImage->imageData;
    uint32_t weirdTexture = Plexi::Texture::create2DTexture(weird, Plexi::getActiveBackend());
    delete weirdImage;



    obj1.textureIds = &plainWhiteTexture;
    obj2.textureIds = &dogTexture;
    obj3.textureIds = &plainWhiteTexture;

    UserInput::initialize();
    UserInput::addKeyMap(GLFW_KEY_W, GLFW_PRESS, moveUp);
    UserInput::addKeyMap(GLFW_KEY_A, GLFW_PRESS, moveLeft);
    UserInput::addKeyMap(GLFW_KEY_S, GLFW_PRESS, moveDown);
    UserInput::addKeyMap(GLFW_KEY_D, GLFW_PRESS, moveRight);
    UserInput::setCursorPressedMoveFunc(scroll);
    UserInput::setScrollFunc(scroll);
    UserInput::setMouseRightFunc(GLFW_MOUSE_BUTTON_LEFT, changeSelection);

    A2D::Filesystem::Loaders::Font::Font newFont;
    newFont.createNewFont("./fonts/OpenSans-Regular.ttf", 26);
    uint32_t OpenSans = Plexi::Texture::createFontFace(newFont.getLoadedFontFace(), 128, Plexi::getActiveBackend());
    txtObj5.fontName = OpenSans;
    while(!glfwWindowShouldClose(Plexi::getWindowRef())){
        glfwPollEvents();
        Plexi::submitScene({obj1, obj3, obj2});
        Plexi::submitScene({txtObj5});
        Plexi::onUpdate();
    }

    Plexi::cleanupPlexi();
    endLogger()
//    readJSON('a');
}
