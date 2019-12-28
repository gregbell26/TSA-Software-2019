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
        PLEXI_GFX_BACKENDS preferredGraphicsBackend = PLEXI_NULL_BACKEND;

#ifndef PLEXI_LIBRARY_ACTIVE
        PLEXI_GFX_BACKENDS activeBackendName = PLEXI_NULL_BACKEND;
#endif //PLEXI_LIBRARY_ACTIVE
        PlexiGFX_RequiredInformation plexiGFXRequiredInformation = {};
        PlexiGFX_OptionalInformation plexiGFXOptionalInformation = {};

        int shaderCount = 0;
        std::vector<Plexi::Shaders::ShaderCreateInfo> shaderCreateInfos = {};
        Plexi::Shaders::ShaderLanguage defaultShaderLanguage = Plexi::Shaders::UNKNOWN;
        std::vector<Plexi::Buffer::BufferCreateInfo> bufferCreateInfos = {};

        PlexiColor clearColor = {0, 0,0};

#ifndef PLEXI_LIBRARY_ACTIVE
        //So that the user can't directly access these vars.
        void setPlexiInit(bool isPlexiInit){
            plexiInit = isPlexiInit;
        }

#endif //PLEXI_LIBRARY_ACTIVE
        bool getPlexiInit(){
            return plexiInit;
        }

        ~PlexiConfig(){
            //Clean up!
        }

    protected:
        bool plexiInit = false;
    };

    struct TextureCreateInfo {
        void* textureData = nullptr;
        uint32_t dataSize = 0;
        int height = 0;
        int width = 0;
        int channelCount = 4;//4 = RGBA 3 = RGB
    };


    struct RenderTask {
//        Texture* texture;
        glm::vec4 position;


        //TODO: Add shader stuff for location
        //TODO: Different Render Tasks
    };

}

#endif //PLEXI_USR_STRUCT_HPP