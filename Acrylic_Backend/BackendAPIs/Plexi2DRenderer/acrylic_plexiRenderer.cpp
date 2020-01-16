#include "PlexiBackend/plexiShaders.hpp"
#include "./PlexiBackend/plexiBuffer.hpp"
#include "./PlexiBackend/plexiHelper.hpp"
#include "./PlexiBackend/acrylic_plexiBackend.hpp"
#include "plexi_usrStructs.hpp"
#include "./PlexiBackend/plexiTexture.hpp"


#include "acrylic_plexiRenderer.hpp"




void Plexi::initPlexi() {
    logInformation("Using Default Plexi2D Config.")
    const std::string shaderNames[] = {
            "plexi_default_primitive",
//            "plexi_default_text"
    };
    const std::string vertShaderFileNames[] = {
            "plexi_vertex_default_primitive",
//            "plexi_vertex_default_text"
    };
    const std::string fragShaderFileNames[] = {
            "plexi_fragment_default_primitive",
//            "plexi_fragment_default_text"
    };

    PlexiConfig plexiConfig = {};
    plexiConfig.preferredGraphicsBackend = PLEXI_DEFAULT_GFX_BACKEND;


    plexiConfig.shaderCount = 1;
    plexiConfig.clearColor = {0.1f, 0.1f, 0.1f, 1.0f};

    if(plexiConfig.preferredGraphicsBackend == PLEXI_VULKAN) {
        //Only for vulkan - Do check to see if these need to be populated in the initPlexi function - If they aren't runtime error as this is information that Vulkan needs to know
        std::vector<const char *> deviceExtensions = {
                "VK_KHR_SWAPCHAIN_EXTENSION_NAME"
        };
        std::vector<const char *> validationLayers = {"VK_LAYER_KHRONOS_validation"};

        plexiConfig.plexiGFXRequiredInformation.vulkan_DEVICE_EXTENSIONS = deviceExtensions.data();
        plexiConfig.plexiGFXRequiredInformation.vulkan_EXT_SIZE = deviceExtensions.size();

        //we are leaving the other items inited to the default values

        plexiConfig.plexiGFXOptionalInformation.vulkan_VALIDATION_LAYERS = validationLayers.data();
        plexiConfig.plexiGFXOptionalInformation.vulkan_VALID_LAYER_SIZE = validationLayers.size();
        plexiConfig.defaultShaderLanguage = Shaders::SPIRV;

    } else if (plexiConfig.preferredGraphicsBackend == PLEXI_OPENGL){

        plexiConfig.defaultShaderLanguage = Shaders::GLSL;

    }

    //Populate the shader create info structs
    plexiConfig.shaderCreateInfos.resize(plexiConfig.shaderCount);
    for(size_t i = 0; i < plexiConfig.shaderCount; i++){
        auto& shaderCreateInfo = plexiConfig.shaderCreateInfos[i];//get ref to current index so I don't have to type the whole thing every time
        shaderCreateInfo.shaderName = shaderNames[i];
        shaderCreateInfo.shaderLanguage = plexiConfig.defaultShaderLanguage;
        if(shaderCreateInfo.shaderLanguage == Shaders::SPIRV){
            logWarning("Unsupported default shader. (SPIR-V is currently unavailable)")
        } else if(shaderCreateInfo.shaderLanguage == Shaders::GLSL){
            shaderCreateInfo.glslVertexCode = Shaders::loadGLSLShaderFromFile(Shaders::locateShader(vertShaderFileNames[i], Shaders::GLSL));
            shaderCreateInfo.glslFragmentCode = Shaders::loadGLSLShaderFromFile(Shaders::locateShader(fragShaderFileNames[i], Shaders::GLSL));
        }

        if(!shaderCreateInfo.isComplete()){
            logError("An error occurred while loading shaders")
        }
    }
    //Populate the buffer create info structs
    plexiConfig.bufferCreateInfos.resize(plexiConfig.shaderCount);
    //Can't do this in a loop as its different

    auto& bufferCreateInfo = plexiConfig.bufferCreateInfos[0];
    bufferCreateInfo.shaderName = shaderNames[0];
    bufferCreateInfo.setLayout({
        {Shaders::Float3, "positionCoords"},
        {Shaders::Float2, "textureCoords"}
    });

    bufferCreateInfo.vertexArray = Buffer::SQUARE_VERTICES_WITH_TEXTURE;
    bufferCreateInfo.vertexArraySize = Buffer::SQUARE_VERTICES_WITH_TEXTURE_SIZE;
    bufferCreateInfo.indexArray = Buffer::SQUARE_INDICES;
    bufferCreateInfo.indexArraySize = Buffer::SQUARE_INDICES_SIZE;


    initPlexi(plexiConfig);

}

void Plexi::initPlexi(Plexi::PlexiConfig &plexiConfig) {
    initLogger("Plexi2D", log_severity_information, log_mode_all)
    if (plexiConfig.preferredGraphicsBackend == PLEXI_NULL_BACKEND) {
        logError("No plexi renderer specified. Please specify a plexi config or change the default renderer")
        return;
    } else {

        GFXBackendMap[plexiConfig.preferredGraphicsBackend]->setRequiredInformation(plexiConfig.plexiGFXRequiredInformation);
        GFXBackendMap[plexiConfig.preferredGraphicsBackend]->setOptionInformation(plexiConfig.plexiGFXOptionalInformation);


        if(!GFXBackendMap[plexiConfig.preferredGraphicsBackend]->isSupported()){
            logError("Selected Plexi renderer is unsupported. Please specify a plexi config or change the default renderer")
            return;
        }

    }

    plexiConfig.activeBackendName = plexiConfig.preferredGraphicsBackend;

    activeConfig = plexiConfig;

    for(size_t i = 0; i < activeConfig.shaderCount; i++){
        GFXBackendMap[activeConfig.activeBackendName]->createGraphicsPipeline(activeConfig.shaderCreateInfos[i], activeConfig.bufferCreateInfos[i]);
    }
    GFXBackendMap[activeConfig.activeBackendName]->setClearColor(activeConfig.clearColor.red, activeConfig.clearColor.green, activeConfig.clearColor.blue, activeConfig.clearColor.green);




    //Assuming that if we got here there were no errors in checking for support

    //Remove all other pointer to backend backends then delete the unused references

    for(auto &[GFXBackendName, GFXBackend] : GFXBackendMap){
        if(GFXBackendName != activeConfig.activeBackendName){
            delete GFXBackend;
        }
    }

    activeConfig.setPlexiInit(GFXBackendMap[activeConfig.activeBackendName]->initBackend());
    logInformation("Plexi initialization complete with default parameters. Current Plexi status: " + std::string() + (activeConfig.getPlexiInit() ?  "OK" : "FAILURE" ))
}


void Plexi::submitScene(const std::vector<StandardRenderTask>& tasks) {
    GFXBackendMap[activeConfig.activeBackendName]->submitScene(tasks);

}

void Plexi::submitScene(const std::vector<TextRenderTask> &tasks) {

}


void Plexi::setClearColor(const float &r, const float &g, const float &b, const float &a) {
    GFXBackendMap[activeConfig.activeBackendName]->setClearColor(r,g,b,a);
}

void Plexi::onUpdate() {

    GFXBackendMap[activeConfig.activeBackendName]->onUpdate();
}


GLFWwindow* Plexi::getWindowRef() {
    if (activeConfig.getPlexiInit())
        return GFXBackendMap[activeConfig.activeBackendName]->getWindowRef();
    return nullptr;
}

void Plexi::cleanupPlexi() {
    GFXBackendMap[activeConfig.activeBackendName]->cleanup();

    delete GFXBackendMap[activeConfig.activeBackendName];

    activeConfig.activeBackendName = PLEXI_NULL_BACKEND;

    activeConfig.setPlexiInit(false);

    //maybe deref active config?
}

Plexi::PLEXI_GFX_BACKENDS Plexi::getActiveBackend() {
    return activeConfig.activeBackendName;
}


