#ifndef PLEXI_BACKEND_HPP
#define PLEXI_BACKEND_HPP

#include <map>
#include "PlexiBackend_OpenGL/OpenGLMain.hpp"
//#include "PlexiBackend_Vulkan/vulkanMain.hpp"

namespace Plexi {

    enum PLEXI_GFX_BACKENDS {
        PLEXI_NULL_BACKEND = 0, PLEXI_CPU, PLEXI_VULKAN, PLEXI_OPENGL//, PLEXI_DIRECTX, PLEXI_METAL//Add more backends at a later date
    };





    //Instance Vars
#ifndef PLEXI_LIBRARY_ACTIVE
    static std::map<Plexi::PLEXI_GFX_BACKENDS, PlexiGraphicsAPI*> GFXBackendMap = {
            {PLEXI_NULL_BACKEND, nullptr},
            {PLEXI_CPU, nullptr},
            {PLEXI_VULKAN, nullptr},
            {PLEXI_OPENGL, new OpenGL()}
//            {PLEXI_DIRECTX, nullptr},
//            {PLEXI_METAL, nullptr}
    };

#endif //PLEXI_LIBRARY_ACTIVE

    GLFWwindow *getWindowRef();
}

#endif//PLEXI_BACKEND_HPP