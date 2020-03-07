#include <BackendAPIs/Plexi2DRenderer/acrylic_plexiRenderer_core.hpp>
#include <BackendAPIs/AcrylicSaveEngine/FileSystemBackend/acrylic_bitmap.h>

#include <filesystem>

#include <ths/log.hpp>

int main() {
    initLogger("A2D", log_severity_error, log_mode_console)

    Plexi::PlexiConfig plexiConfig = {};
    plexiConfig.preferredGraphicsBackend = Plexi::PLEXI_GFX_BACKENDS::PLEXI_OPENGL;
    plexiConfig.defaultShaderLanguage = Plexi::Shaders::ShaderLanguage::GLSL;
    plexiConfig.clearColor = {0.1f, 0.1f, 0.1f, 1.0f};
    plexiConfig.plexiGFXRequiredInformation.appName = "Acrylic 2D";
    plexiConfig.plexiGFXRequiredInformation.cacheEnabled = false;
    plexiConfig.shaderCount = 3;
    plexiConfig.shaderCreateInfos.resize(plexiConfig.shaderCount);
    plexiConfig.shaderCreateInfos[0].shaderName = "plexi_default_primitive";
    plexiConfig.shaderCreateInfos[0].shaderLanguage = plexiConfig.defaultShaderLanguage;
    plexiConfig.shaderCreateInfos[0].glslVertexCode = Plexi::Shaders::loadGLSLShaderFromFile(Plexi::Shaders::locateShader("plexi_vertex_default_primitive", plexiConfig.defaultShaderLanguage));
    plexiConfig.shaderCreateInfos[0].glslFragmentCode = Plexi::Shaders::loadGLSLShaderFromFile(Plexi::Shaders::locateShader("plexi_fragment_default_primitive", plexiConfig.defaultShaderLanguage));
    plexiConfig.shaderCreateInfos[1].shaderName = "plexi_default_text";
    plexiConfig.shaderCreateInfos[1].shaderLanguage = plexiConfig.defaultShaderLanguage;
    plexiConfig.shaderCreateInfos[1].glslVertexCode = Plexi::Shaders::loadGLSLShaderFromFile(Plexi::Shaders::locateShader("plexi_vertex_default_text", plexiConfig.defaultShaderLanguage));
    plexiConfig.shaderCreateInfos[1].glslFragmentCode = Plexi::Shaders::loadGLSLShaderFromFile(Plexi::Shaders::locateShader("plexi_fragment_default_text", plexiConfig.defaultShaderLanguage));
    plexiConfig.shaderCreateInfos[2].shaderName = "cache";
    plexiConfig.shaderCreateInfos[2].shaderLanguage = plexiConfig.defaultShaderLanguage;
    plexiConfig.shaderCreateInfos[2].glslVertexCode = Plexi::Shaders::loadGLSLShaderFromFile(Plexi::Shaders::locateShader("plexi_vertex_default_cached", plexiConfig.defaultShaderLanguage));
    plexiConfig.shaderCreateInfos[2].glslFragmentCode = Plexi::Shaders::loadGLSLShaderFromFile(Plexi::Shaders::locateShader("plexi_fragment_default_cached", plexiConfig.defaultShaderLanguage));
    plexiConfig.bufferCreateInfos.resize(plexiConfig.shaderCount);
    plexiConfig.bufferCreateInfos[0].shaderName = plexiConfig.shaderCreateInfos[0].shaderName;
    plexiConfig.bufferCreateInfos[0].setLayout( {
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

    plexiConfig.bufferCreateInfos[2].shaderName = plexiConfig.shaderCreateInfos[2].shaderName;
    plexiConfig.bufferCreateInfos[2].setLayout( {
                                                        {Plexi::Shaders::Float3, "in_positionCoords"},
                                                        {Plexi::Shaders::Float2, "in_textureCoords"}
                                                });

    plexiConfig.bufferCreateInfos[2].vertexArray = Plexi::Buffer::FULL_SCREEN_VERTICES_WITH_TEXTURE;
    plexiConfig.bufferCreateInfos[2].vertexArraySize = Plexi::Buffer::FULL_SCREEN_VERTICES_WITH_TEXTURE_SIZE;
    plexiConfig.bufferCreateInfos[2].indexArray = Plexi::Buffer::SQUARE_INDICES;
    plexiConfig.bufferCreateInfos[2].indexArraySize = Plexi::Buffer::SQUARE_INDICES_SIZE;

    Plexi::initPlexi(plexiConfig);

    auto* monarchTSALogoImage = new A2D::Filesystem::Loaders::Bitmaps::Image(std::filesystem::path("./textures/MonarchTSALogo.bmp"));

    Plexi::TextureCreateInfo monarchTSALogoInfo  = {};
    monarchTSALogoInfo.height = abs(monarchTSALogoImage->height);
    monarchTSALogoInfo.width = abs(monarchTSALogoImage->width);
    monarchTSALogoInfo.channelCount = monarchTSALogoImage->bytes;
    monarchTSALogoInfo.dataSize = monarchTSALogoImage->length;
    monarchTSALogoInfo.textureData.usingGenericType = false;
    monarchTSALogoInfo.textureData.dataType.image = monarchTSALogoImage->imageData;
    uint32_t monarchTSALogoTexture = Plexi::Texture::create2DTexture(monarchTSALogoInfo, Plexi::getActiveBackend());
    delete monarchTSALogoImage;

    auto* a2dLogoImage = new A2D::Filesystem::Loaders::Bitmaps::Image(std::filesystem::path("./textures/LightModeLogo.bmp"));

    Plexi::TextureCreateInfo a2dLogoInfo  = {};
    a2dLogoInfo.height = a2dLogoImage->height;
    a2dLogoInfo.width = a2dLogoImage->width;
    a2dLogoInfo.channelCount = a2dLogoImage->bytes;
    a2dLogoInfo.dataSize = a2dLogoImage->length;
    a2dLogoInfo.textureData.usingGenericType = false;
    a2dLogoInfo.textureData.dataType.image = a2dLogoImage->imageData;
    uint32_t a2dLogoTexture = Plexi::Texture::create2DTexture(a2dLogoInfo, Plexi::getActiveBackend());
    delete a2dLogoImage;



    StandardRenderTask obj1 = {};
    obj1.graphicsPipelineName = "plexi_default_primitive";
    obj1.RGBAColor = {1.0f, 1.0f, 1.0f, 1.0f};
    obj1.position = {-3.5f, 3.5f, 0.0f};
    obj1.scale = {2.5f, 3.75f};
    obj1.textureCount = 1;
    obj1.textureIds = &a2dLogoTexture;

    StandardRenderTask obj2 = {};
    obj2.graphicsPipelineName = "plexi_default_primitive";
    obj2.RGBAColor = {1.0f, 1.0f, 1.0f, 1.0f};
    obj2.position = {0.0f, 0.0f, -0.1f};
    obj2.scale = {2.5f, 3.75f};
    obj2.textureCount = 1;
    obj2.textureIds = &monarchTSALogoTexture;

    Plexi::submitScene({obj2, obj1});
    while(!glfwWindowShouldClose(Plexi::getWindowRef())){
        glfwPollEvents();
        Plexi::onUpdate();
    }


    Plexi::cleanupPlexi();
    endLogger()

}