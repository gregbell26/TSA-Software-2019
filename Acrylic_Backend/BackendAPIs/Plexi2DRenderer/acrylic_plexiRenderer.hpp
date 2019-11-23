#ifndef PLEXI_RENDERER_HPP
#define PLEXI_RENDERER_HPP


#include <iostream>
#include <thread>

namespace Plexi {
#ifndef PLEXI_USE_LIB

    const PLEXI_GFX_BACKENDS PLEXI_DEFAULT_GFX_BACKEND = PLEXI_VULKAN;
    //Where the config will be stored
    PlexiConfig* activeConfig;
    std::thread plexiLoopThread;

#endif //PLEXI_USE_LIB
    //will init Plexi to default settings
    void initPlexi();

    //will init Plexi to user provided settings
    void initPlexi(const PlexiConfig&);


    void cleanupPlexi();

    //Adds a render task to the active backend. Returns false if it fails
    bool addRenderTask(const RenderTask&);



}


#endif//PLEXI_RENDERER_HPP