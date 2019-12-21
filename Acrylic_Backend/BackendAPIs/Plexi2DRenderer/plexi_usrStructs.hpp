#ifndef PLEXI_USR_STRUCT_HPP
#define PLEXI_USR_STRUCT_HPP


namespace Plexi {
    struct PlexiColor {
        float red;
        float green;
        float blue;
        float alpha;

        PlexiColor(float r, float g, float b, float a) :
            red(r), green(g), blue(b), alpha(a)
        {}

        PlexiColor(float r, float g, float b) :
                red(r), green(g), blue(b), alpha(1.0f)
        {}
    };


    struct PlexiConfig {
        PLEXI_GFX_BACKENDS userPreferredGFXBackend = PLEXI_NULL_BACKEND;

        PLEXI_GFX_BACKENDS activeBackendName = PLEXI_NULL_BACKEND;

        PlexiGFX_RequiredInformation plexiGFXRequiredInformation = {};
        PlexiGFX_OptionalInformation plexiGFXOptionalInformation = {};

        int shaderCount = 0;
        std::vector<Plexi::Shaders::ShaderCreateInfo> shaderCreateInfos = {};
        Plexi::Shaders::ShaderLanguage defaultShaderLanguage = Plexi::Shaders::UNKNOWN;
        std::vector<Plexi::Buffer::BufferCreateInfo> bufferCreateInfos = {};

        PlexiColor clearColor = {0, 0,0};

        //So that the user can't directly access these vars.
        void setPlexiInit(bool isPlexiInit){
            plexiInit = isPlexiInit;
        }

        bool getPlexiInit(){
            return plexiInit;
        }

        ~PlexiConfig(){
            //Clean up!
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