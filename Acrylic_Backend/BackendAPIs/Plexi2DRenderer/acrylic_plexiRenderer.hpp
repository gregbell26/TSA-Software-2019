#ifndef PLEXI_RENDERER_HPP
#define PLEXI_RENDERER_HPP

#include <vector>
#include <iostream>

#include "PlexiBackend/acrylic_plexiBackend.hpp"
#include "plexi_usrStructs.hpp" //All structs to work with plexi are defined here


namespace Plexi {
    const PLEXI_GFX_BACKENDS PLEXI_DEFAULT_GFX_BACKEND = PLEXI_VULKAN;
    //Where the config will be stored
    PlexiConfig* activeConfig;

    //will init Plexi to default settings
    void initPlexi();

    //will init Plexi to user provided settings
    void initPlexi(const PlexiConfig*);






    int getCurrentFPS();

    bool addRenderTask();
}


#endif//PLEXI_RENDERER_HPP