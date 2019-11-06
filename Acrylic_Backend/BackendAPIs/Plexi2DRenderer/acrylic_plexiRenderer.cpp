#include "PlexiBackend/acrylic_plexiBackend.hpp"
#include "plexi_usrStructs.hpp" //All structs to work with plexi are defined here
#include "acrylic_plexiRenderer.hpp"

void Plexi::initPlexi() {
    //TODO: CONNECT LOGGER - For now we'll be using std::out

    PlexiConfig plexiConfig = {};
    plexiConfig.userPreferredGFXBackend = PLEXI_DEFAULT_GFX_BACKEND;
    plexiConfig.hotSwapEnabled = false;
    plexiConfig.applicationName = "powered by Acrylic2D";

    if(plexiConfig.userPreferredGFXBackend == PLEXI_VULKAN) {
        plexiConfig.vulkan_deviceExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
        plexiConfig.vulkan_opt_validationLayers.push_back("VK_LAYER_KHRONOS_validation");//Default API validation Layers

        GFXBackendMap[plexiConfig.userPreferredGFXBackend]->setRequiredInformation(plexiConfig.vulkan_deviceExtensions.data(), plexiConfig.vulkan_deviceExtensions.size(), plexiConfig.applicationName);
        GFXBackendMap[plexiConfig.userPreferredGFXBackend]->setOptionInformation(plexiConfig.vulkan_opt_validationLayers.data(), plexiConfig.vulkan_opt_validationLayers.size(),
                                                                                 plexiConfig.vulkan_opt_deviceExtensions.data(), plexiConfig.vulkan_opt_deviceExtensions.size());


        if(!GFXBackendMap[plexiConfig.userPreferredGFXBackend]->isSupported()){
            std::cerr << "Plexi Default renderer is unsupported. Please specify a plexi config or change the default renderer" << std::endl;
            return;
        }

        plexiConfig.activeBackendName = plexiConfig.userPreferredGFXBackend;
    }
    if(plexiConfig.userPreferredGFXBackend == PLEXI_NULL_BACKEND){
        std::cerr<< "No default plexi renderer specified. Please specify a plexi config or change the default renderer" << std::endl;
    }

    activeConfig = &plexiConfig;

    //Assuming that if we got here there were no errors in checking for support

    //Remove all other pointer to backend backends then delete the unused references

    for(auto &[GFXBackendName, GFXBackend] : GFXBackendMap){
        if(GFXBackendName != activeConfig->activeBackendName){
            delete GFXBackend;
            GFXBackend = nullptr;

            GFXBackendMap.erase(GFXBackendName);
        }
    }

    activeConfig->setPlexiInit(GFXBackendMap[activeConfig->activeBackendName]->initBackend());
    std::cout << "Plexi initialization complete with default parameters. Current Plexi status: " << (activeConfig->getPlexiInit() ?  "OK" : "FAILURE" ) << std::endl;

    if(activeConfig->getPlexiInit()){
        //Add thread for this task
        GFXBackendMap[activeConfig->activeBackendName]->runBackend();
        //display message w/ thread PID
    }

}

void Plexi::initPlexi(const Plexi::PlexiConfig &config) {
    std::cout << "UNSUPPORTED" << std::endl;
    exit(0);
}

void Plexi::cleanupPlexi() {
    //stop thead
    std::cout << GFXBackendMap[activeConfig->activeBackendName] << std::endl;`
    GFXBackendMap[activeConfig->activeBackendName]->cleanup();

}


int main(){
    Plexi::initPlexi();
    Plexi::cleanupPlexi();
}