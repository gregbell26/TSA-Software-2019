namespace Plexi {
    struct PlexiConfig {
        PLEXI_GFX_BACKENDS userPreferedGFXBackend = PLEXI_NULL_BACKEND;

        PLEXI_GFX_BACKENDS activeBackend = PLEXI_NULL_BACKEND;

        //The ability to hot swap APIs
        bool hotSwapEnabled = false;
        //If that is true then these will be acknowledged - MUST BE INITED IF USING HOT SWAP
        size_t enabledBackendsCount; //the count of the enabled backends

        //Only for vulkan - Do check to see if these need to be populated in the initPlexi function - If they aren't runtime error as this is information that Vulkan needs to know
        std::vector<const char*> vulkan_deviceExtensions = {};//Init to blank bc we are going to assume that if the user wants to render that they will say I NEED SWAPCHAIN SUPPORT


        //So that the user can't directly access these vars.
        void setPlexiInit(bool isPlexiInit){
            plexiInit = true;
        }

        bool getPlexiInit(){
            return plexiInit;
        }

    protected:
        bool plexiInit = false;
    };

    struct RenderTask {
        char* taskType;
        char* batch;
    };
}