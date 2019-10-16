#ifndef PLEXI_BACKEND_HPP
#define PLEXI_BACKEND_HPP

#include <map>
#include <any>
#include "PlexiBackend_Vulkan/vulkanMain.hpp"

namespace Plexi {
    enum PLEXI_GFX_BACKENDS {
        PLEXI_NULL_BACKEND = 0, PLEXI_VULKAN//Add more backends at a later date
    };
    //Instance Vars

    //I was going to do this with
    static std::map<Plexi::PLEXI_GFX_BACKENDS, PlexiGFXBackend*> GFXBackendMap = {{Plexi::PLEXI_NULL_BACKEND, nullptr}, {Plexi::PLEXI_VULKAN, new Vulkan()}};

}

#endif//PLEXI_BACKEND_HPP