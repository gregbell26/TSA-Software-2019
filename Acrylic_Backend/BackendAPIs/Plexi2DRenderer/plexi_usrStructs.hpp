#ifndef PLEXI_USR_STRUCT_HPP
#define PLEXI_USR_STRUCT_HPP

namespace Plexi {
    struct PlexiConfig {
        PLEXI_GFX_BACKENDS userPreferredGFXBackend = PLEXI_NULL_BACKEND;

        PLEXI_GFX_BACKENDS activeBackendName = PLEXI_NULL_BACKEND;

        PlexiGFX_RequiredInformation plexiGFXRequiredInformation = {};
        PlexiGFX_OptionalInformation plexiGFXOptionalInformation = {};

        int shaderCount = 0;
        std::vector<std::string> vertexShaderNames = {};
        std::vector<std::string> fragmentShaderNames = {};

        //So that the user can't directly access these vars.
        void setPlexiInit(bool isPlexiInit){
            plexiInit = isPlexiInit;
        }

        bool getPlexiInit(){
            return plexiInit;
        }

    protected:
        bool plexiInit = false;
    };

    struct BufferLayouts {

    };

    struct RenderTask {
        const char* taskType;
        const char* batch;

        //TODO: Add shader stuff for location
        //TODO: Different Render Tasks
    };
}

#endif //PLEXI_USR_STRUCT_HPP