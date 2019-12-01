#ifndef PLEXI_RENDERER_HPP
#define PLEXI_RENDERER_HPP

#include <vulkan/vulkan.h>

#include <iostream>
#include <thread>
#include <cstdlib>
#include <ctime>


namespace Plexi {

#ifndef PLEXI_LIBRARY_ACTIVE

    const PLEXI_GFX_BACKENDS PLEXI_DEFAULT_GFX_BACKEND = PLEXI_OPENGL;
    //Where the config will be stored
    static PlexiConfig activeConfig;
//    std::thread plexiLoopThread;
    static std::vector<Plexi::Shaders::ShaderCreateInfo> loadedShaders;
    static std::vector<Plexi::Buffer::BufferCreateInfo> bufferData;

    static std::vector<RenderTask> renderQueue;

#endif //PLEXI_LIBRARY_ACTIVE

    //will init Plexi to default settings
    void initPlexi();

    //will init Plexi to user provided settings
    void initPlexi(PlexiConfig&);

//    void runPlexi();



    void submitScene();

    void onUpdate();

    void cleanupPlexi();

    //Adds a render task to the active backend. Returns false if it fails
    bool addRenderTask(const RenderTask&);



}


#endif//PLEXI_RENDERER_HPP