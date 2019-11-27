#include "./PlexiBackend/shaders.hpp"
#include "./PlexiBackend/plexiHelper.hpp"
#include "./PlexiBackend/acrylic_plexiBackend.hpp"
#include "plexi_usrStructs.hpp" //All structs to work with plexi are defined here



#include "acrylic_plexiRenderer.hpp"

void Plexi::initPlexi() {
    //TODO: CONNECT LOGGER - For now we'll be using std::out

    PlexiConfig plexiConfig = {};
    plexiConfig.userPreferredGFXBackend = PLEXI_DEFAULT_GFX_BACKEND;

    plexiConfig.vertexShaderNames = {//Might want to move these to be defines or something
            "plexi_vertex_default_primitive",
            "plexi_vertex_default_text"
    };
    plexiConfig.fragmentShaderNames = {
            "plexi_fragment_default_primitive",
            "plexi_fragment_default_text"
    };
    plexiConfig.shaderCount = plexiConfig.vertexShaderNames.size();

	if (plexiConfig.userPreferredGFXBackend == PLEXI_NULL_BACKEND) {
		std::cerr << "No default plexi renderer specified. Please specify a plexi config or change the default renderer" << std::endl;
	} else if(plexiConfig.userPreferredGFXBackend == PLEXI_VULKAN) {
        //Only for vulkan - Do check to see if these need to be populated in the initPlexi function - If they aren't runtime error as this is information that Vulkan needs to know
        std::vector<const char*> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};//Init to blank bc we are going to assume that if the user wants to render that they will say I NEED SWAPCHAIN SUPPORT
        std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};

        plexiConfig.plexiGFXRequiredInformation.vulkan_DEVICE_EXTENSIONS = deviceExtensions.data();
        plexiConfig.plexiGFXRequiredInformation.vulkan_EXT_SIZE = deviceExtensions.size();

        //we are leaving the other items inited to the default values

        plexiConfig.plexiGFXOptionalInformation.vulkan_VALIDATION_LAYERS = validationLayers.data();
        plexiConfig.plexiGFXOptionalInformation.vulkan_VALID_LAYER_SIZE = validationLayers.size();

        GFXBackendMap[plexiConfig.userPreferredGFXBackend]->setRequiredInformation(plexiConfig.plexiGFXRequiredInformation);
        GFXBackendMap[plexiConfig.userPreferredGFXBackend]->setOptionInformation(plexiConfig.plexiGFXOptionalInformation);


        if(!GFXBackendMap[plexiConfig.userPreferredGFXBackend]->isSupported()){
            std::cerr << "Plexi Default renderer is unsupported. Please specify a plexi config or change the default renderer" << std::endl;
            return;
        }

        plexiConfig.activeBackendName = plexiConfig.userPreferredGFXBackend;
    }


    for(size_t i = 0; i < plexiConfig.shaderCount; i++){
        Shader vertexShaderTemp = {};
        Shader fragShaderTemp = {};

    if(Shaders::checkForPrecompiledShaders(plexiConfig.vertexShaderNames[i], vertexShaderTemp) &&
       Shaders::checkForPrecompiledShaders(plexiConfig.fragmentShaderNames[i], fragShaderTemp)) {
        vertexShaderTemp.shaderType = 0;
        fragShaderTemp.shaderType = 0;

        loadedVertexShaders.push_back(vertexShaderTemp);
        loadedFragmentShaders.push_back(fragShaderTemp);
    } else {
//            plexiConfig.vertexShaderNames.erase(plexiConfig.vertexShaderNames.begin()+i);
//            plexiConfig.fragmentShaderNames.erase(plexiConfig.fragmentShaderNames.begin()+i);

        std::cerr << "A default precompiled shader was not found. Ensure all default Plexi shaders are compiled and in default location" << std::endl;
    }

}

    plexiConfig.vertexShaderNames.shrink_to_fit();
    plexiConfig.vertexShaderNames.shrink_to_fit();

    if(loadedFragmentShaders.empty() || loadedVertexShaders.empty()){
        std::cerr << "No shaders were loaded. Plexi is currently unable to render." << std::endl;
    }


    activeConfig = plexiConfig;

    //Assuming that if we got here there were no errors in checking for support

    //Remove all other pointer to backend backends then delete the unused references

    for(auto &[GFXBackendName, GFXBackend] : GFXBackendMap){
        if(GFXBackendName != activeConfig.activeBackendName){
            delete GFXBackend;
            GFXBackend = nullptr;

        }
    }

    activeConfig.setPlexiInit(GFXBackendMap[activeConfig.activeBackendName]->initBackend());
    std::cout << "Plexi initialization complete with default parameters. Current Plexi status: " << (activeConfig.getPlexiInit() ?  "OK" : "FAILURE" ) << std::endl;

    if(activeConfig.getPlexiInit()){

        for(size_t i = 0; i < loadedVertexShaders.size(); i++){
            GFXBackendMap[activeConfig.activeBackendName]->bindShaders(loadedVertexShaders[i], loadedFragmentShaders[i]);
        }

    }

}

void Plexi::initPlexi(const Plexi::PlexiConfig &config) {
    std::cout << "UNSUPPORTED" << std::endl;
    exit(0);
}


GLFWwindow* Plexi::getWindowRef(){
    return GFXBackendMap[activeConfig.activeBackendName]->getWindowRef();
}

void Plexi::cleanupPlexi() {
    GFXBackendMap[activeConfig.activeBackendName]->cleanup();

    delete GFXBackendMap[activeConfig.activeBackendName];

    activeConfig.activeBackendName = PLEXI_NULL_BACKEND;

    activeConfig.setPlexiInit(false);

    //maybe deref active config?
}

