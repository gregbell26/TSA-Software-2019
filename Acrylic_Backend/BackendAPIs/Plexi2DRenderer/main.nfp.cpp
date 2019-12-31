#include "acrylic_plexiRenderer_core.hpp"

#include <GLFW/glfw3.h>

int main(){ 
    initLogger("Plexi2D", log_severity_information, log_mode_all)
    Plexi::initPlexi();
    Plexi::TextureCreateInfo textureCreateInfo = {};
    textureCreateInfo.height = 1;
    textureCreateInfo.width = 1;
    textureCreateInfo.channelCount = 4;
    textureCreateInfo.dataSize = sizeof(uint32_t);
    uint32_t data = 0xFFFFFFFF;
    textureCreateInfo.textureData.dataType.generic = &data;
    textureCreateInfo.textureData.usingGenericType = true;


    uint32_t plainWhiteTexture = Plexi::Texture::create2DTexture(textureCreateInfo, Plexi::getActiveBackend());

    StandardRenderTask obj1 = {
            "plexi_default_primitive",
            {0.25f, 1.0f,0.0f, 1.0f},
            {0.0f, 0.0f, 0.0f},
            {3.0f, 3.0f},
            1,
            &plainWhiteTexture
    };

    StandardRenderTask obj2 = {
            "plexi_default_primitive",
            {1.0f, 0.0f,0.25f, 1.0f},
            {-1.0f, -1.0f, 1.0f},
            {2.5f, 2.5f},
            1,
            &plainWhiteTexture
    };

    StandardRenderTask obj3 = {
            "plexi_default_primitive",
            {0.25f, 0.0f,1.0f, 1.0f},
            {1.0f, 1.0f, -0.1f},
            {3.5f, 3.5f},
            1,
            &plainWhiteTexture
    };

    while(!glfwWindowShouldClose(Plexi::getWindowRef())){
        glfwPollEvents();
        Plexi::submitScene({obj1, obj2, obj3});
        Plexi::onUpdate();
    }


//    std::cin.get();
    Plexi::cleanupPlexi();

    endLogger()



    return 0;
}