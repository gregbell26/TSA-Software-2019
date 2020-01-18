#include "./BackendAPIs/Plexi2DRenderer/acrylic_plexiRenderer_core.hpp"
#include "./BackendAPIs/AcrylicSaveEngine/FileSystemBackend/acrylic_fileSystem.hpp"
#include "acrylic_frameTimer.h"
#include "./BackendAPIs/AcrylicSaveEngine/FileSystemBackend/acrylic_bitmap.h"
#include "./BackendAPIs/AcrylicSaveEngine/FileSystemBackend/acrylic_font.hpp"
#include <iostream>
#include <ths/log.hpp>
#include "Random.h"
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"

StandardRenderTask Obj7 = {
        "plexi_default_primitive",
        {1.0f,1.0f,1.0f,1.0f},
        {1.0f,1.0f,-0.1f},
        {2.0f,2.0f},
        1,
        nullptr
};

TextRenderTask txtObj1 = {
        "plexi_default_text",
        "the quick brown fox jumped over the lazy dog",
        0,
        {0.75f,0.0f,0.5f,1.0f},
        {-50.0f, 15.0f},
        0.1f
};

TextRenderTask txtObj2 {
        "plexi_default_text",
        "THE QUICK BROWN FOX JUMPED OVER THE LAZY DOG",
        0,
        {0.0f,0.5f,0.75f,1.0f},
        {-60.0f, -15.0f},
        0.1f
};

TextRenderTask txtObj3 {
        "plexi_default_text",
        "1234567890!@#$%^&*()~`:;\"\'/?\\|_+{_}+][]<><,.,?:",
        0,
        {0.0f, 0.75f, 0.5f,1.0f},
        {-50.0f, 0.0f},
        0.1f
};




//using namespace A2D::Filesystem::Loaders::Json;
//using namespace A2D::Filesystem::Loaders;

int main(){
//    auto j = interpretJson(readFile("test1.json"));
//    auto j2 = interpretJson("");
//    std::cout << j.smap.at("str") << std::endl;
//    std::cout << j.imap.at("int") << std::endl;
//    std::cout << j.fmap.at("flo") << std::endl;
//    std::cout << j.jmap.at("json1").smap.at("in1") << std::endl;
//    std::cout << j.jmap.at("json1").jmap.at("json2").smap.at("in2") << std::endl;

//    return 0;

    Timer::frameTimer timer;


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

    auto* DogImage = new A2D::Filesystem::ImageLoaders::Bitmaps::Image(A2D::Filesystem::Loaders::readFile("./textures/dog.bmp"));
    Plexi::TextureCreateInfo doginfo = {};
    doginfo.height = DogImage->height;
    doginfo.width = DogImage->width;
    doginfo.channelCount = DogImage->bytes;
    doginfo.dataSize = DogImage->length;
    doginfo.textureData.usingGenericType = false;
    doginfo.textureData.dataType.image = DogImage->imageData;
    uint32_t dogtexture = Plexi::Texture::create2DTexture(doginfo, Plexi::getActiveBackend());
    Obj7.textureIds = &dogtexture;
    delete DogImage;

    A2D::Filesystem::Loaders::Font::Font newFont;
    newFont.createNewFont("./fonts/OpenSans-Light.ttf", 48);
    uint32_t OpenSans = Plexi::Texture::createFontFace(newFont.getLoadedFontFace(), 128, Plexi::getActiveBackend());
    txtObj1.fontName = OpenSans;
    txtObj2.fontName = OpenSans;
    txtObj3.fontName = OpenSans;
    newFont.cleanUp();


    timer.startTimer();
    unsigned frames = 0;
    glfwSwapInterval(1);
    Plexi::submitScene({txtObj1, txtObj2, txtObj3});
    Plexi::submitScene({Obj7});
    while(!glfwWindowShouldClose(Plexi::getWindowRef())){
        glfwPollEvents();
        Plexi::onUpdate();
        frames++;
    }

    Plexi::cleanupPlexi();

    logInformation(std::to_string(timer.getTime())+"s have elapsed")
    logInformation("average FPS: " + std::to_string(timer.getFPS(frames)))

    endLogger()
}
