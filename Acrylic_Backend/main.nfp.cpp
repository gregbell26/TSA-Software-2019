#include "./BackendAPIs/Plexi2DRenderer/acrylic_plexiRenderer_core.hpp"
#include "./BackendAPIs/AcrylicSaveEngine/FileSystemBackend/acrylic_fileSystem.hpp"
#include "./BackendAPIs/AcrylicSaveEngine/FileSystemBackend/acrylic_bitmap.h"
#include "./BackendAPIs/AcrylicSaveEngine/FileSystemBackend/acrylic_font.hpp"
#include <iostream>
#include <ths/log.hpp>
#include "Random.h"
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"

TextRenderTask txtObj5 = {
        "plexi_default_text",
        "The Quick Brown Fox Jumped Over The Lazy Dog",
        0,
        {0.75f,0.0f,0.5f,1.0f},
        {-50.0f, 0.0f},
        0.1f
};



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


    A2D::Filesystem::Loaders::Font::Font newFont;
    newFont.createNewFont("./fonts/OpenSans-Light.ttf", 48);
    uint32_t OpenSans = Plexi::Texture::createFontFace(newFont.getLoadedFontFace(), 128, Plexi::getActiveBackend());
    txtObj5.fontName = OpenSans;
    newFont.cleanUp();

    Plexi::submitScene({txtObj5});
    while(!glfwWindowShouldClose(Plexi::getWindowRef())){
        glfwPollEvents();
        Plexi::onUpdate();
    }

    Plexi::cleanupPlexi();
    endLogger()
}
