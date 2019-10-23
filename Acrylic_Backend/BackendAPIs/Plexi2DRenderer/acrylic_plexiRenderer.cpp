#include "acrylic_plexiRenderer.hpp"

void Plexi::initPlexi() {
    //CONNECT LOGGER - For now we'll be using std::out

    PlexiConfig plexiConfig = {};
    plexiConfig.userPreferedGFXBackend = PLEXI_DEFAULT_GFX_BACKEND;
    plexiConfig.hotSwapEnabled = false;
    if(plexiConfig.userPreferedGFXBackend == PLEXI_VULKAN) {
        plexiConfig.vulkan_deviceExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

        if(!GFXBackendMap[plexiConfig.userPreferedGFXBackend]->isSupported()){
            std::cerr << "Plexi Default renderer is unsupported. Please specify a plexi config or change the default renderer" << std::endl;
            return;
        }

        plexiConfig.activeBackend = plexiConfig.userPreferedGFXBackend;
    }
    if(plexiConfig.userPreferedGFXBackend == PLEXI_NULL_BACKEND){
        std::cerr<<"No default plexi renderer specified. Please specify a plexi config or change the default renderer" << std::endl;
    }

}

void Plexi::initPlexi(const Plexi::PlexiConfig *config) {

}